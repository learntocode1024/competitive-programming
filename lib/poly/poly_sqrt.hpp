#include "../math/cipolla.hpp"
#include "poly.hpp"

template <typename mint = mint, int D = N>
poly<mint, D> sqrt(const poly<mint, D> &a, int deg = -1) {
  assert(a.size());
  int a0 = cipolla(a[0].get(), mint::get_mod());
  assert(a0 != -1);
  chkmin(a0, (int)mint::get_mod() - a0);
  int lim = wrap(deg);
  poly<mint, D> ret(lim), iv(lim);
  ret[0] = a0;
  iv[0] = ret[0].inverse();
  for (int len = 1; len < deg; len <<= 1) {
    int lim = len << 2;
    for (int i = 0; i < len; ++i) {
      A[i] = ret[i];
    }
    for (int i = 0; i < min(2 * len, (int)a.size()); ++i) {
      B[i] = a[i];
    }
    ntt(A, lim);
    ntt(B, lim);
    for (int i = 0; i < lim; ++i) {
      A[i] = A[i] * 2 - A[i] * A[i] * B[i];
    }
    ntt(A, lim, -1);
    for (int i = 0; i < len * 2; ++i) {
      ret[i] = A[i];
    }
    for (int i = 0; i < lim; ++i) {
      A[i] = B[i] = 0;
    }
  }
  ret.shrink(deg);
  return ret;
}