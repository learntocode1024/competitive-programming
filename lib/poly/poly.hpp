#pragma once

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

#include "modint"
#include "utils"

inline int wrap(int x) { return 1 << (32 - __builtin_clz(x)); }
using mint = MontgomeryModInt<998244353>;

namespace {
const int N = 1 << 21;
u32 bit_inv[N];
mint gp[N], inv[N];
int tot_inv = 2;
inline void expand_inv(int lim) {
  int m = mint::get_mod();
  for (; tot_inv < lim; ++tot_inv) {
    int q = m / tot_inv;
    inv[tot_inv] = -inv[m % tot_inv] * q;
  }
}
constexpr int init() {
  gp[0] = 1;
  inv[1] = 1;
  mint _g = mint(3).pow(998244352 / N);
  for (int i = 1; i < N; ++i) gp[i] = gp[i - 1] * _g;
  return 1;
}
const int root_generation = init();
mint A[N], B[N];
}  // namespace

void ntt(mint *a, int len, int opt = 1) {
  for (int i = 1; i < len; ++i) {
    bit_inv[i] = (bit_inv[i >> 1] >> 1);
    if (i & 1) bit_inv[i] |= (len >> 1);
    if (bit_inv[i] > i) swap(a[i], a[bit_inv[i]]);
  }
  for (int i = 1; i < len; i <<= 1) {
    mint gn = gp[(N / i) >> 1];
    for (int j = 0; j < len; j += i << 1) {
      mint gc(1);
      for (int k = j; k < j + i; ++k) {
        mint x = a[k], y = a[k + i] * gc;
        a[k] = x + y;
        a[k + i] = x - y;
        gc *= gn;
      }
    }
  }
  if (opt == -1) {
    mint t = mint(len).inverse();
    for (int i = 0; i < len; ++i) {
      a[i] *= t;
    }
    reverse(a + 1, a + len);
  }
}

namespace {
mint f[N], g[N];
void _cdq(int l, int r) {
  if (r - l == 1) return;
  int mid = l + (r - l) / 2;
  _cdq(l, mid);
  for (int i = l; i < mid; ++i) {
    A[i - l] = f[i];
  }
  for (int i = 0; i < r - l; ++i) {
    B[i] = g[i];
  }
  int lim = wrap(r + mid - l * 2);
  ntt(A, lim);
  ntt(B, lim);
  for (int i = 0; i < lim; ++i) A[i] *= B[i];
  ntt(A, lim, -1);
  for (int i = mid; i < r; ++i) f[i] += A[i - l];
  for (int i = 0; i < lim; ++i) A[i] = B[i] = 0;
  _cdq(mid, r);
}
void _exp_cdq(int l, int r) {
  if (r - l == 1) {
    if (l) f[l] *= inv[l];
    return;
  }
  int mid = l + (r - l) / 2;
  _exp_cdq(l, mid);
  for (int i = l; i < mid; ++i) {
    A[i - l] = f[i];
  }
  for (int i = 0; i < r - l; ++i) {
    B[i] = g[i];
  }
  int lim = wrap(r + mid - l * 2);
  ntt(A, lim);
  ntt(B, lim);
  for (int i = 0; i < lim; ++i) A[i] *= B[i];
  ntt(A, lim, -1);
  for (int i = mid; i < r; ++i) f[i] += A[i - l];
  for (int i = 0; i < lim; ++i) A[i] = B[i] = 0;
  _exp_cdq(mid, r);
}
}  // namespace

template <typename mint = mint, int D = N>
struct poly : std::vector<mint> {
  using vector<mint>::vector;
  inline void shrink() {
    while (this->size() && this->back() == mint(0)) this->pop_back();
  }
  inline void shrink(int lim) {
    if (this->size() > lim) this->resize(lim);
    shrink();
  }
  inline int shorten() {
    if (!this->size()) return 0;
    int cnt = 0;
    while (cnt < this->size() && (*this)[cnt] == mint(0)) ++cnt;
    for (int i = cnt; i < this->size(); ++i) {
      (*this)[i - cnt] = (*this)[i];
    }
    this->resize(this->size() - cnt);
    this->shrink();
    return cnt;
  }
  friend void print(const poly &a) {
    for (auto i : a) {
      cout << i << ' ';
    }
    cout << endl;
  }
  poly &operator+=(const poly &b) {
    if (this->size() < b.size()) {
      this->resize(b.size(), mint(0));
    }
    for (int i = 0; i < b.size(); ++i) {
      (*this)[i] += b[i];
    }
    this->shrink();
    return *this;
  }
  poly operator+(const poly &b) const { return poly(*this) += b; }
  poly &operator-=(const poly &b) {
    if (this->size() < b.size()) {
      this->resize(b.size(), mint(0));
    }
    for (int i = 0; i < b.size(); ++i) {
      (*this)[i] -= b[i];
    }
    this->shrink();
    return *this;
  }
  poly operator-(const poly &b) const { return poly(*this) -= b; }
  poly &operator*= (const mint &rhs) {
    for (int i = 0; i < this->size(); ++i) (*this)[i] *= rhs;
    return *this;
  }
  poly operator* (const mint &rhs) {
    return poly(*this) *= rhs;
  }
  poly &operator*=(const poly &b) {
    int lim = wrap(this->size() + b.size() - 1);
    int n = this->size(), m = b.size();
    for (int i = 0; i < n; ++i) {
      A[i] = (*this)[i];
    }
    for (int i = 0; i < m; ++i) {
      B[i] = b[i];
    }
    ntt(A, lim);
    ntt(B, lim);
    for (int i = 0; i < lim; ++i) {
      A[i] *= B[i];
    }
    ntt(A, lim, -1);
    this->resize(min(n + m - 1, D));
    for (int i = 0; i < this->size(); ++i) {
      (*this)[i] = A[i];
    }
    for (int i = 0; i < lim; ++i) {
      A[i] = B[i] = 0;
    }
    return *this;
  }
  poly operator*(const poly &b) const { return (poly(*this) *= b); }
  poly &pow(int x, int deg = D) {
    poly ret({1});
    while (x) {
      if (x & 1) ret *= *this;
      ret.shrink(deg);
      *this *= *this;
      shrink(deg);
      x >>= 1;
    }
    *this = ret;
    return *this;
  }
  friend poly pow(const poly &a, int x, int deg = D) {
    return poly(a).pow(x, deg);
  }
  poly &inverse(int deg = D) {
    assert((*this).size() && (*this)[0] != mint(0));
    int lim = wrap(deg);
    poly ret(lim);
    ret[0] = (*this)[0].inverse();
    for (int len = 1; len < deg; len <<= 1) {
      int lim = len << 2;
      for (int i = 0; i < len; ++i) {
        A[i] = ret[i];
      }
      for (int i = 0; i < min(2 * len, (int)(*this).size()); ++i) {
        B[i] = (*this)[i];
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
    *this = ret;
    return *this;
  }
  friend poly inverse(const poly &a, int deg = N) {
    return poly(a).inverse(deg);
  }

  poly &diff() {
    mint f(1), ff(1);
    for (int i = 0; i < this->size() - 1; ++i) {
      (*this)[i] = f * (*this)[i + 1], f += ff;
    }
    this->pop_back();
    return *this;
  }
  friend poly diff(const poly &a) { return poly(a).diff(); }

  poly &integral() {
    int m = mint::get_mod();
    expand_inv(this->size() + 1);
    this->push_back(this->back() * inv[this->size()]);
    for (int i = this->size() - 1; i >= 0; --i) {
      (*this)[i] = (*this)[i - 1] * inv[i];
    }
    (*this)[0] = 0;
    return *this;
  }
  friend poly integral(const poly &a) { return poly(a).integral(); }

  friend poly cdq(const poly &y, int deg = -1) {
    if (deg = -1) deg = y.size();
    for (int i = 0; i < deg; ++i) g[i] = y[i];
    f[0] = 1;
    for (int i = 1; i < deg; ++i) f[i] = 0;
    _cdq(0, deg);
    poly ret(deg);
    for (int i = 0; i < deg; ++i) {
      ret[i] = f[i];
    }
    return ret;
  }

  poly &ln(int deg = -1) {
    if (deg == -1) deg = this->size();
    assert((*this).size() && (*this)[0] == 1);
    *this = poly(*this).diff() * poly(*this).inverse(deg);
    this->shrink(deg - 1);
    this->integral();
    return *this;
  }
  friend poly ln(const poly &a, int deg = -1) { return poly(a).ln(deg); }

  poly &exp(int deg = -1) {
    if (deg == -1) deg = this->size();
    assert(this->size() && (*this)[0] == 0);
    for (int i = 0; i < deg; ++i) g[i] = (*this)[i] * i;
    for (int i = 1; i < deg; ++i) f[i] = 0;
    f[0] = 1;
    expand_inv(deg);
    _exp_cdq(0, deg);
    this->resize(deg);
    for (int i = 0; i < deg; ++i) (*this)[i] = f[i];
    return *this;
  }
  friend poly exp(const poly &a, int deg = -1) { return poly(a).exp(deg); }
};
