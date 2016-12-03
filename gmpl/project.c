#include <gmpl/project.h>

#include <string.h>

bool str_eq(Str a, Str b) {
  return a.len == b.len && (strcmp(a.data, b.data) == 0);
}
