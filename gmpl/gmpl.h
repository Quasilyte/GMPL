#pragma once

#include <gmp.h>

//! @brief Compiled expression
struct GmplExpr {
  int arity;
};

//! @brief Expression execution result
struct GmplResult {
  mpz_ptr* values;
  int count;
};

//! @brief Library instance
struct GmplApi {
  struct GmplExpr(*compile)(const char* signature, const char* code);
  struct GmplResult(*run)(struct GmplExpr*, const char* fmt, ...);
};

//! @brief Options to customize library instance
struct GmplConfig {};

//! @brief Get library instance
struct GmplApi gmpl_init(struct GmplConfig);
