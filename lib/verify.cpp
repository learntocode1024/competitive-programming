#include "utils"
#include "io"
#include "modint"
using IO::rd;
using IO::rdstr;
using IO::rdll;
#include "poly/poly"

int n;
bool flag = 0;

namespace IO {
pair<int, mint> rdm() {
  mint u = 0;
  int alt = 0;
  while (*o && *o <= 32) ++o;  // skip whitespaces...
  if (*o == '-' || *o == '+')
    ++o;  // skip sign
  while (*o >= '0' && *o <= '9') {
    u = u * 10 + (*o - '0');
    alt = (alt * 10 + (*o++ - '0')) % 998244352ll;
    flag = flag || u.get() > n;  // u * 10 = u * 8 + u * 2 :)
  }
  return mkp(alt, u);
}
}

typedef poly<mint> FPS;
int main() {
  IO::init_in();
  n = rd();
  mint k;
  int _pow_k;
  auto K = IO::rdm();
  _pow_k = K.fi;
  k = K.se;
  FPS a(n);
  for (int i = 0, t; i < n; ++i) {
    a[i] = rd();
  }
  int cnt = 0;
  while (cnt < a.size() && a[cnt] == 0) ++cnt;
  if (cnt && flag || (k * cnt).get() >= n) {
    for (int i = 0; i < n; ++i) cout << "0 ";
    cout << endl;
    return 0;
  }
  for (int i = 0; i < (k * cnt).get(); ++i) cout << "0 ";
  n -= (k * cnt).get();
  for (int i = 0; i < n; ++i) {
    a[i] = a[i + cnt];
  }
  a.resize(n);
  mint _pow_const(1);
  if (a[0] != 1) {
    mint x0 = a[0].inverse();
    _pow_const = a[0].pow(_pow_k);
    for (auto& i : a) {
      i *= x0;
    }
  }
  a.ln();
  a *= k;
  a.exp();
  a *= _pow_const;
  print(a);
  return 0;
}
