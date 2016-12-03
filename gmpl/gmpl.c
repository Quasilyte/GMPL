#include <gmpl/gmpl_with_typedefs.h>

#include <gmpl/compile/compile.h>

static GmplResult run(GmplExpr* e, const char* fmt, ...) {
  GmplResult result;

  return result;
}

GmplApi gmpl_init(GmplConfig cfg) {
  (void)cfg; // Config is always empty, but this may change in future

  GmplApi api = {compile, run};

  return api;
}
