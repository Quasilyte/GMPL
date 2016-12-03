#pragma once

//! @brief Define struct and create its typedef
#define DEF_STRUCT(X) typedef struct X X; struct X

//! @brief Library fatal error; "should never happen"
#define BUG(MSG) assert(0 && "BUG" MSG)

//! @brief User error; should be fixed at user side
#define ERROR(MSG) assert(0 && "ERROR" MSG)

#define thread_local _Thread_local

#define bool _Bool
#define true ((_Bool)1)
#define false ((_Bool)0)

#ifndef NULL
  #define NULL ((void*)0)
#endif

/*!
 * @brief Simple string data type; has no notion of encoding
 * @warning In general case its not NULL-terminated
 */
DEF_STRUCT(Str) {
  const char* data;
  int len;
};

//! @brief Check if two strings are character-wise equal
bool str_eq(Str, Str);
