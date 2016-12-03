#pragma once

#include <gmpl/project.h>

//! @brief Basic read-only cursor
DEF_STRUCT(Cursor) {
  const char* pos;
  const char* end;
};

//! @brief All possible token types
typedef enum {
  TOK_INVALID,

  TOK_LPAREN,
  TOK_RPAREN,

  TOK_OP_BEGIN,
  TOK_ADD,
  TOK_SUB,
  TOK_MUL,
  TOK_DIV,
  TOK_EXP,
  TOK_OP_END,

  TOK_MINUS,

  TOK_VAL_BEGIN,
  TOK_IDENT,
  TOK_INT,
  TOK_FLOAT,
  TOK_MP_INT,
  TOK_MP_FLOAT,
  TOK_VAL_END,
} TokenTag;

/*!
 * @brief Tokenized value
 *
 * Token can contain captured data.
 * Only tokens with [tag > TOK_VAL_BEGIN && tag < TOK_VAL_END]
 * have len and data members initialized
 */
DEF_STRUCT(Token) {
  TokenTag tag; //!< Token type
  int len; //!< Token data length
  const char* data; //!< Token data
};

//! @brief Check if cursor contains data to be read/tokenized
bool can_read(Cursor*);

/*!
 * @brief Try to skip given character
 * @return No input is consumed if false is returned (failure)
 */
bool consume(Cursor*, char target);

//! @brief Skip until given character is found
void seek(Cursor*, char target);

/*!
 * @brief Tokenize all data from @p c into @p toks
 * @param limit sets tokenization upper limit
 * @warning toks[-1] should always contain TOK_INVALID
 * @return Number of tokens produced
 */
int tokenize(Cursor* c, Token* toks, int limit);
