#pragma once

#include "io"
#include "modint"

namespace IO {
mint rd() {
  mint u;
  while (*o && *o <= 32) ++o;  // skip whitespaces...
  if (*o == '-' || *o == '+')
    ++o;  // skip sign
  while (*o >= '0' && *o <= '9')
    u = u * 10 + (*o++ - '0');  // u * 10 = u * 8 + u * 2 :)
  return u;
}
}