#include <gmpl/compile/lexing.h>

#include <assert.h>
#include <ctype.h>

#define ASCII_MAX 127

//! @brief \s
bool spaces[ASCII_MAX] = {
  [' ']  = true,
  ['\t'] = true,
  ['\n'] = true,
};

//! @brief \d
bool digits[ASCII_MAX] = {
  ['0' ... '9'] = true
};

static void skip(Cursor* c, bool* alphabet) {
  while (alphabet[c->pos[0]]) {
    c->pos += 1;
  }
}

static Token tokenize_num(Cursor* c) {
  const char* begin = c->pos++;
  TokenTag tag;

  skip(c, digits);
  if (consume(c, '.')) {
    skip(c, digits);
    tag = TOK_FLOAT;
  } else {
    tag = TOK_INT;
  }

  int len = c->pos - begin;
  return (Token){tag, len, begin};
}

static Token tokenize_ident(Cursor* c) {
  const char* begin = c->pos++;

  while (isalnum(c->pos[0])) {
    c->pos += 1;
  }

  int len = c->pos - begin;
  return (Token){TOK_IDENT, len, begin};
}

static Token tokenize_tag(Cursor* c, TokenTag tag) {
  c->pos += 1;
  return (Token){tag};
}

bool can_read(Cursor* c) {
  skip(c, spaces);
  return c->pos < c->end;
}

bool consume(Cursor* c, char target) {
  if (c->pos[0] == target) {
    c->pos += 1;
    return true;
  }
  return false;
}

void seek(Cursor* c, char target) {
  while (c->pos[0] != target) {
    if (c->pos == c->end) {
      BUG("seek failed");
    }
    c->pos += 1;
  }
}

static bool is_unary_prefix(TokenTag tag) {
  switch (tag) {
  case TOK_INVALID:
  case TOK_LPAREN:
  case TOK_ADD:
  case TOK_SUB:
  case TOK_MUL:
  case TOK_DIV:
  case TOK_EXP:
    return true;

  default:
    return false;
  }
}

int tokenize(Cursor* c, Token* toks, int limit) {
  Token* tok = toks;
  Token* last_tok = toks + limit;

  while (can_read(c)) {
    assert(tok != last_tok);

    switch (c->pos[0]) {
    case '0' ... '9':
      *tok++ = tokenize_num(c);
      continue;

    case '_':
    case 'a' ... 'z':
    case 'A' ... 'Z':
      *tok++ = tokenize_ident(c);
      continue;

    case '(': tok->tag = TOK_LPAREN; break;
    case ')': tok->tag = TOK_RPAREN; break;
    case '+': tok->tag = TOK_ADD; break;
    case '*': tok->tag = TOK_MUL; break;
    case '/': tok->tag = TOK_DIV; break;
    case '^': tok->tag = TOK_EXP; break;

    case '-':
      tok->tag = is_unary_prefix(tok[-1].tag) ? TOK_MINUS : TOK_SUB;
      break;

    default:
      BUG("unexpected char");
    }

    c->pos += 1;
    tok += 1;
  }

  return tok - toks;
}
