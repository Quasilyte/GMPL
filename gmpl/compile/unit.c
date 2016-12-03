#include <gmpl/compile/unit.h>

#include <assert.h>

DEF_STRUCT(InstrVec) {
  int len;
  int cap;
  Instr* data;
};

DEF_STRUCT(VarVec) {
  int len;
  int cap;
  Str* names;
};

DEF_STRUCT(Unit) {
  VarVec vars;
  InstrVec instrs;
};

#define INSTRS_CAP 32
#define NAMES_CAP 24

static thread_local Str names[NAMES_CAP];
static thread_local Instr instrs[INSTRS_CAP];
static thread_local Unit unit = {
  {0, NAMES_CAP, NULL},
  {0, INSTRS_CAP, NULL},
};

Unit* unit_empty(void) {
  unit.instrs.data = instrs;
  unit.vars.names = names;

  unit.vars.len = 0;
  unit.instrs.len = 0;

//  var_list.names[0] = (Str){"a", 1};
//  var_list.names[1] = (Str){"b", 1};

  return &unit;
}

void unit_push_instr(Unit* u, Instr instr) {
  assert(u->instrs.cap != u->instrs.len);
  u->instrs.data[u->instrs.len] = instr;
  u->instrs.len += 1;
}

InstrRange unit_get_instrs(Unit* u) {
  return (InstrRange){u->instrs.data, u->instrs.data + u->instrs.len};
}

int unit_get_var(Unit* u, Str name) {
  for (int i = 0; i < u->vars.len; ++i) {
    if (str_eq(name, u->vars.names[i])) {
      return i;
    }
  }

  ERROR("variable not found");
}
