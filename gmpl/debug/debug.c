#include <gmpl/debug/debug.h>

#include <stdio.h>

static const char* token_str(Token tok) {
  switch (tok.tag) {
  case TOK_LPAREN: return "<LPAREN>";
  case TOK_RPAREN: return "<RPAREN>";

  case TOK_ADD: return "<ADD>";
  case TOK_SUB: return "<SUB>";
  case TOK_MUL: return "<MUL>";
  case TOK_DIV: return "<DIV>";
  case TOK_EXP: return "<EXP>";
  case TOK_MINUS: return "<MINUS>";

  case TOK_IDENT: return "<IDENT>";
  case TOK_INT: return "<INT>";
  case TOK_FLOAT: return "<FLOAT>";
  case TOK_MP_INT: return "<MP_INT>";
  case TOK_MP_FLOAT: return "<MP_FLOAT>";

  default:
    return "<?>";
  }
}

void dump_token(Token tok) {
  const char* s = token_str(tok);

  if (tok.tag == TOK_IDENT) {
    fprintf(stderr, "%s `%.*s`\n", s, tok.len, tok.data);
  } else {
    fprintf(stderr, "%s\n", s);
  }
}
