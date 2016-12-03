#pragma once

#include <gmpl/project.h>

struct Cursor;
struct Token;

DEF_STRUCT(RpnList) {
  const struct Token* tokens;
  int len;
};

RpnList parse_to_rpn(struct Cursor*);
