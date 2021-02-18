#include "decimal.h"
#include <cstdio>
#include <map>
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
// typedef long long Decimal;
typedef __int128 lll;

Decimal Q_pow(Decimal a, Decimal index, const Decimal& mod) {
  Decimal ans = 1;
  while (index != 0) {
    if (index % 2 == 1) ans = ans * a % mod;
    a = a * a % mod;
    index /= 2;
  }
  return ans;
}

Decimal gcd(Decimal a, Decimal b) {
  if (!a || !b) return 0;
  while ((a %= b) && (b %= a));
  return a + b;
}

Decimal abs(const Decimal& x) {
  if (x < 0) return -x;
  return x;
}

const int iter_count = 8;
int miller_rabin(const Decimal &p) {
  if (p == 2 || p == 3) return 1;
  if (p == 1 || p % 2 == 0) return 0;
  Decimal x = p - 1;
  int cnt = 0;
  while (x % 2 == 0) {
    x /= 2;
    ++cnt;
  }
  for (int iter_var = 0; iter_var < iter_count; ++iter_var) {
    Decimal a = rand() % (p - 3) + 2;
    Decimal val = Q_pow(a, x, p);
    if (val == 1 || val == p - 1) continue;
    int i = 1;
    while (i < cnt) {
      val = val * val % p;
      if (val == p - 1) break;
      ++i;
    }
    if (i == cnt) return 0;
  }
  return 1;
}

const int delay = 127;
const int timeout = 50000;
static Decimal func_c;

Decimal func_init() {
  func_c = rand() % 180 + 20;
  return func_c;
}
Decimal func(const Decimal &x, const Decimal &mod) {
  return (x * x + func_c) % mod;
}

Decimal pollard_rho(const Decimal &x) {
  Decimal t = func_init(), s;
  // cout << t << endl;
  Decimal val, d;
  for (long long len = 1; len < timeout; len <<= 1, s = t, val = 1) {
    for (long long i = 0; i < len; ++i) {
      s = func(s, x);
      val = val * abs(s - t) % x;
      if (i % delay == 0) {
        d = gcd(val, x);
        if (d > 1) return d;
        val = 1;
      }
    }
    d = gcd(val, x);
    if (d > 1) return d;
  }
  return x;
}

std::map<Decimal, int> factor;
void fac(Decimal x) {
  if (x == 1) return;
  if (miller_rabin(x)) {
    ++factor[x];
    return;
  }
  Decimal p = x;
  while (p >= x) p = pollard_rho(x);
  x /= p;
  if (miller_rabin(p)) {
    ++factor[p];
  } else fac(p);
  if (miller_rabin(x)) {
    ++factor[x];
  } else fac(x);
}

void output() {
  for (auto i = factor.begin(); i != factor.end(); ++i) {
    cout << i->first << ' ' << i->second << '\n';
  }
  cout << endl;
  factor.clear();
}

void init() {
  srand(time(0));
}

int main() {
  init();
  int task, T;
  cin >> task >> T;
  while (T--) {
    Decimal t;
    cin >> t;
    cout << pollard_rho(t) << endl;
    output();
  }
  return 0;
}
