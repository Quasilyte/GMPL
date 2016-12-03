#pragma once

#include <gmpl/project.h>

/*!
 * @brief Encapsulation of the compilation state
 * @note Only one instance per thread exists
 */
DEF_STRUCT(Unit);

//! @brief Operation type codes
typedef enum {
  INS_ADD,
  INS_SUB,
  INS_MUL,
  INS_DIV,
  INS_EXP,
  INS_NEG,
} InstrTag;

//! @brief Abstract instruction node (intermediate representation)
DEF_STRUCT(Instr) {
  InstrTag tag;
  int args[3];
};

//! @brief Slice of instructions (mutations are permitted)
DEF_STRUCT(InstrRange) {
  Instr* const begin;
  Instr* const end;
};

//! @brief Prepare and return cleared unit
struct Unit* unit_empty(void);

//! @brief Push another instruction into unit
void unit_push_instr(Unit*, Instr);

//! @brief Get instructions contained inside unit
InstrRange unit_get_instrs(Unit*);

/*!
 * @brief Lookup variable by its name
 * @return Id of the variable; -1 if not found
 */
int unit_get_var(Unit*, Str name);
