#include <gmpl/compile/parse.h>

/*!
 * @brief Implementation of Operator-precedence parser
 *
 * This file implements expressions parsing using
 * Dijkstra shunting-yard algorithm
 */

#include <gmpl/compile/lexing.h>
#include <assert.h>

#define OP_STACK_CAP 16
#define OUTPUT_QUEUE_CAP 32

// TOK_INVALID is needed to make "is_op(top())" safe without stack_size checks
static thread_local Token op_stack[OP_STACK_CAP] =
  {{TOK_INVALID, 0, NULL}};

// TOK_INVALID is needed to make "tokens[-1]" safe inside tokenization
static thread_local Token output_queue[OUTPUT_QUEUE_CAP] =
  {{TOK_INVALID, 0, NULL}};

//! @brief Get precedence of operator contained inside @p tok
static int prec(Token tok) {
  switch (tok.tag) {
  case TOK_ADD:
  case TOK_SUB:
    return 2;

  case TOK_MUL:
  case TOK_DIV:
    return 3;

  case TOK_EXP:
    return 4;

  default:
    BUG("not an op => has no precedence");
  }
}

//! @brief Checks if @p tok represents unary operator
static bool is_unary_op(Token tok) {
  return tok.tag == TOK_MINUS;
}

//! @brief Checks if @p tok represents any kind of operator
static bool is_op(Token tok) {
  return tok.tag > TOK_OP_BEGIN && tok.tag < TOK_OP_END;
}

//! @brief Checks if @p top represents a unit of data
static bool is_val(Token tok) {
  return tok.tag > TOK_VAL_BEGIN && tok.tag < TOK_VAL_END;
}

//! @brief Checks if @p tok is left-associative operator
static bool is_left_assoc(Token tok) {
  switch (tok.tag) {
  case TOK_ADD:
  case TOK_SUB:
  case TOK_MUL:
  case TOK_DIV:
    return true;

  case TOK_EXP:
    return false;

  default:
    BUG("unexpected tag");
  }
}

//! @brief Checks if @p tok is right-associative operator
static bool is_right_assoc(Token tok) {
  return tok.tag == TOK_EXP;
}

RpnList parse_to_rpn(Cursor* c) {
  #define push(X) *stack++ = (X)
  #define pop() *--stack
  #define begin(X) (X + 1)
  #define stack_size() (stack - op_stack - 1)
  #define queue_size() (queue - output_queue - 1)
  #define top() stack[-1]
  #define enqueue(X) *queue++ = (X)

  Token* tokens = begin(output_queue);
  Token* stack = begin(op_stack);
  Token* queue = begin(output_queue);

  int tok_count = tokenize(c, begin(output_queue), OUTPUT_QUEUE_CAP - 1);

  for (int i = 0; i < tok_count; ++i) {
    Token tok = tokens[i];

    if (is_val(tok)) {
      enqueue(tok);
    }
    else if (tok.tag == TOK_LPAREN) {
      push(tok);
    }
    else if (tok.tag == TOK_RPAREN) {
      while (top().tag != TOK_LPAREN) {
        enqueue(pop());
      }
      pop();
    }
    else if (is_unary_op(tok)) {
      BUG("unary ops are not supported yet");
    }
    else {
      assert(is_op(tok));

      Token o1 = tok;

      while (is_op(top())) {
        Token o2 = top();

        if (!(is_left_assoc(o1) && prec(o1) <= prec(o2))) {
          if (!(is_right_assoc(o1) && prec(o1) < prec(o2))) {
            break;
          }
        }

        enqueue(pop());
      }

      push(o1);
    }
  }

  while (stack_size()) {
    enqueue(pop());
  }

  RpnList rpn;
  rpn.len = queue_size();
  rpn.tokens = begin(output_queue);

  return rpn;

  #undef push
  #undef pop
  #undef begin
  #undef stack_size
  #undef queue_size
  #undef top
  #undef enqueue
}
