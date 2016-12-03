## Syntax

```
id = [_a-zA-Z][_a-zA-Z0-9']*
int = [0-9]+
float = int "." int

top_level = statement*

statement = assign
          | expr_block

assign = id "=" rvalue

rvalue = expr_block
       | fn_call

expr_block = "{" expr "}"

operand = id
        | float
        | int
        | "(" expr ")"

expr = operand
     | unary_op operand
     | expr binary_op expr

binary_op = "+"
          | "-"
          | "*"
          | "/"
          | "^"
          ... and others

unary_op = "-"

fn_call = id "(" expr_list ")"

expr_list = expr { "," expr }
```

Notes:

1) Comments are not part of the grammar.
But if you use C preprocessor to wrap the input,
it will handle both kind of comments for you.

```
#define WITH_COMMENTS(X) #X
const char* x = WITH_COMMENTS(/* ok */ { 1 });
```

2) Function calls always classified as `rvalue`, which
is bound only to `assign`. This means that you can
not use them inside expressions, but there is workaround.

```
// Suppose we have abs function
// Will not work: { abs(x) + abs(y) }
x = abs(x)
y = abs(y)
{ x + y }
// But in case of abs there is better option
{ |x| + |y| }
```

### Examples

```
x = 10
x = {x + 1} // x is now 11 (original "x" is shadowed, new "x" is created)
y = sin(x)
{x^y + z!}  // z should be externally bounded
{y + x}     // Second return value
```
