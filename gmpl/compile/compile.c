#include <gmpl/compile/compile.h>

#include <gmpl/debug/debug.h>

#include <gmpl/compile/lexing.h>
#include <gmpl/compile/parse.h>
#include <gmpl/compile/unit.h>

#include <stdio.h>
#include <string.h>
#include <assert.h>

static void compile_yield(Cursor* c, Unit* u) {
  assert(consume(c, '{'));
  const char* begin = c->pos;
  seek(c, '}');
  const char* end = c->pos;
  assert(consume(c, '}'));

  RpnList rpn = parse_to_rpn(&(Cursor){begin, end});

  for (int i = 0; i < rpn.len; ++i) {
    dump_token(rpn.tokens[i]);
  }

//  Token op_stack_bottom[10];
//  Token output_bottom[20];

//  Token* op_stack = op_stack_bottom;
//  Token* output = output_bottom;



//  while (!consume(c, '}')) {
//    Token tok = read_token(c);

//    if (tok.tag == TOK_IDENT) {
//      *output++ = tok;
//    }
//    else if (tok.tag == TOK_LPAREN) {
//      *op_stack++ = tok;
//    }
//    else if (tok.tag == TOK_RPAREN) {
//      while (op_stack[-1].tag != TOK_LPAREN) {
//        *output++ = *--op_stack;
//      }
//      op_stack -= 1;
//    }
//    else {
//      Token o1 = tok;

//      if (op_stack == op_stack_bottom) {
//        *op_stack++ = o1;
//      }
//      else {
//        Token o2 = *op_stack;
//        while (op_stack != op_stack_bottom &&
//               is_op(o2) &&
//               (is_left_assoc(o1) && prec(o1) <= prec(o2)) &&
//               (is_right_assoc(o1) && prec(o1) < prec(o2))) {
//          *output++ = *--op_stack;
//        }
//        *op_stack++ = o1;
//      }
//    }
//  }

//  while (op_stack != op_stack_bottom) {
//    *output++ = *--op_stack;
//  }

//  for (int i = 0; i < rpn.len; ++i) {
//    dump_token(rpn.tokens[i]);
//  }

//  Token* p = output_bottom;
//  while (p != output) {
//    dump_token(*p);
//    p += 1;
//  }
}

void emit_instructions(Cursor c, Unit* u) {
  while (can_read(&c)) {
    if (c.pos[0] == '{') {
      compile_yield(&c, u);
    }
    else {
      BUG("invalid syntax");
    }
  }
}

GmplExpr compile(const char* signature, const char* code) {
  Unit* u = unit_empty();

  Cursor c = {code, code + strlen(code)};
  emit_instructions(c, u);

  GmplExpr e = {0};
  return e;
}
