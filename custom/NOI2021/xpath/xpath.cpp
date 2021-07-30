#include <algorithm>
#include <cstdio>
#include <climits>
#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;
typedef long long i64;
typedef unsigned i32;
typedef unsigned long long u64;
template<typename T>
void chkmax(T &a, const T &b) {
  a = max(a, b);
}
template<typename T>
void chkmin(T &a, const T &b) {
  a = min(a, b);
}
#define FILEIO(x) freopen(x".in", "r", stdin); freopen(x".out", "w", stdout);
#define MX

template <uint32_t mod>
struct LazyMontgomeryModInt {
  using mint = LazyMontgomeryModInt;
  using i32 = int32_t;
  using u32 = uint32_t;
  using u64 = uint64_t;

  static constexpr u32 get_r() {
    u32 ret = mod;
    for (i32 i = 0; i < 4; ++i) ret *= 2 - mod * ret;
    return ret;
  }

  static constexpr u32 r = get_r();
  static constexpr u32 n2 = -u64(mod) % mod;
  static_assert(r * mod == 1, "invalid, r * mod != 1");
  static_assert(mod < (1 << 30), "invalid, mod >= 2 ^ 30");
  static_assert((mod & 1) == 1, "invalid, mod % 2 == 0");

  u32 a;

  constexpr LazyMontgomeryModInt() : a(0) {}
  constexpr LazyMontgomeryModInt(const int64_t &b)
      : a(reduce(u64(b % mod + mod) * n2)){};

  static constexpr u32 reduce(const u64 &b) {
    return (b + u64(u32(b) * u32(-r)) * mod) >> 32;
  }

  constexpr mint &operator+=(const mint &b) {
    if (i32(a += b.a - 2 * mod) < 0) a += 2 * mod;
    return *this;
  }

  constexpr mint &operator-=(const mint &b) {
    if (i32(a -= b.a) < 0) a += 2 * mod;
    return *this;
  }

  constexpr mint &operator*=(const mint &b) {
    a = reduce(u64(a) * b.a);
    return *this;
  }

  constexpr mint &operator/=(const mint &b) {
    *this *= b.inverse();
    return *this;
  }

  constexpr mint operator+(const mint &b) const { return mint(*this) += b; }
  constexpr mint operator-(const mint &b) const { return mint(*this) -= b; }
  constexpr mint operator*(const mint &b) const { return mint(*this) *= b; }
  constexpr mint operator/(const mint &b) const { return mint(*this) /= b; }
  constexpr bool operator==(const mint &b) const {
    return (a >= mod ? a - mod : a) == (b.a >= mod ? b.a - mod : b.a);
  }
  constexpr bool operator!=(const mint &b) const {
    return (a >= mod ? a - mod : a) != (b.a >= mod ? b.a - mod : b.a);
  }
  constexpr mint operator-() const { return mint() - mint(*this); }

  constexpr mint pow(u64 n) const {
    mint ret(1), mul(*this);
    while (n > 0) {
      if (n & 1) ret *= mul;
      mul *= mul;
      n >>= 1;
    }
    return ret;
  }
  
  constexpr mint inverse() const { return pow(mod - 2); }

  friend ostream &operator<<(ostream &os, const mint &b) {
    return os << b.get();
  }

  friend istream &operator>>(istream &is, mint &b) {
    int64_t t;
    is >> t;
    b = LazyMontgomeryModInt<mod>(t);
    return (is);
  }
  
  constexpr u32 get() const {
    u32 ret = reduce(a);
    return ret >= mod ? ret - mod : ret;
  }

  static constexpr u32 get_mod() { return mod; }
};

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;
template<typename T>
class matrix {
  vector<vector<T>> _data;
  int _col, _row;
  void print() {
    for (int i = 0; i < _row; ++i) {
      for (int j = 0; j < _col; ++j) {
        cerr << _data[i][j] << ' ';
      }
      cerr << endl;
    }
    cerr << endl;
  }
public:
  matrix() : _row(), _col(), _data() {};
  matrix(int row, int col) : _row(row), _col(col), _data(row, vector<T>(col)) {};
  matrix(int rank) : _row(rank), _col(rank), _data(rank, vector<T>(rank)) {};
  static matrix E(int rank) {
    matrix ret(rank);
    for (int i = 0; i < rank; ++i) {
      ret[i][i] = 1;
    }
    return ret;
  }
  vector<T> &operator[](int k) {
    return _data[k];
  }
  const vector<T> &operator[](int k) const {
    return _data[k];
  }
  friend matrix operator* (const matrix& x, const matrix& y) {
    matrix ret(x._row, y._col);
    for (int i = 0; i < x._row; ++i) {
      for (int j = 0; j < y._col; ++j) {
        for (int k = 0; k < x._col; ++k) {
          ret[i][j] += x[i][k] * y[k][j];
        }
      }
    }
    return ret;
  }
  friend matrix operator+ (const matrix& x, const matrix& y) {
    matrix ret(x._row, y._col);
    for (int i = 0; i < x._row; ++i) {
      for (int j = 0; j < y._col; ++j) {
        ret[i][j] = x[i][j] + y[i][j];
      }
    }
    return ret;
  }
  friend T det(matrix x) {
    if (x._row != x._col) return 0;
    T sig = 1, ret = 1;
    int cur = 0;
    for (int i = 0; i < x._col; ++i) {
      int j;
      for (j = cur; j < x._row; ++j) {
        if (x._data[j][i] != 0) break;
      }
      if (j == x._row) continue;
      swap(x._data[j], x._data[cur]);
      if (j != cur) sig = -sig;
      for (++j; j < x._row; ++j) {
        if (x._data[j][i] != 0) {
          T fac = x._data[j][i] / x._data[cur][i];
          for (int k = i; k < x._col; ++k) {
            x._data[j][k] -= fac * x._data[cur][k];
          }
        }
      }
      ++cur;
    }
    for (int i = 0; i < x._col; ++i) {
      ret *= x[i][i];
    }
    return ret * sig;
  }
  friend matrix inv(matrix x) {
    matrix y = matrix::E(x._row);
    if (x._row != x._col) return matrix();
    T sig = 1, ret = 1;
    int cur = 0;
    for (int i = 0; i < x._col; ++i) {
      int j;
      for (j = cur; j < x._row; ++j) {
        if (x._data[j][i] != 0) break;
      }
      if (j == x._row) continue;
      swap(x._data[j], x._data[cur]);
      swap(y._data[j], y._data[cur]);
      if (j != cur) sig = -sig;
      for (j = 0; j < x._row; ++j) {
        if (j == cur) continue;
        if (x._data[j][i] != 0) {
          T fac = x._data[j][i] / x._data[cur][i];
          for (int k = i; k < x._col; ++k) {
            x._data[j][k] -= fac * x._data[cur][k];
            y._data[j][k] -= fac * y._data[cur][k];
          }
        }
      }
      ++cur;
    }
    if (cur != x._row) return matrix();
    for (int i = 0; i < x._row; ++i) {
      for (int j = 0; j < x._col; ++j) {
        y[i][j] /= x[i][i];
      }
        x[i][i] /= x[i][i];
    }
    return y;
  }
};

typedef LazyMontgomeryModInt<998244353> mod32;

typedef matrix<mod32> mat;
int n[200], m[200];
int main() {
  cin.tie(0);
  ios::sync_with_stdio(0);
  int T;
  cin >> T;
  int k;
  while (T--) {
    vector<mat> V;
    cin >> k;
    for (int i = 0; i < k; ++i) cin >> n[i];
    for (int i = 0; i < k - 1; ++i) cin >> m[i];
    for (int i = 0; i < k - 1; ++i) V.emplace_back(n[i], n[i + 1]);
    for (int i = 0; i < k - 1; ++i) {
      for (int j = 0; j < m[i]; ++j) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        V[i][u][v] = 1;
      }
    }
    mat ans = V[0];
    for (int i = 1; i < k - 1; ++i) ans = ans * V[i];
    cout << det(ans) << endl;
  }
  return 0;
}

