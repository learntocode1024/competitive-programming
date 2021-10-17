#include <bits/stdc++.h>
using namespace std;
typedef long long i64;
typedef unsigned long long u64;
typedef unsigned u32;
#define FOR(i, j, k) for (int i = j; i < k; ++i)
const int p = 9901, pp = p - 1;

int inv[p];

inline int q_pow(int a, int x) {
  int ret = 1;
  while (x) {
    if (x & 1) ret = ret * a % p;
    a = a * a % p;
    x >>= 1;
  }
  return ret;
}

i64 A, B;
int pi[p], al[p], tot;
inline void fac() {
  for (i64 i = 2; i * i <= A; ++i) {
    if (A % i == 0) {
      pi[tot] = i % p;
      while (A % i == 0) {
        ++al[tot];
        A /= i;
      }
      ++tot;
    }
  }
  if (A != 1) {
    pi[tot] = A % p;
    al[tot] = 1;
    ++tot;
  }
  //FOR(i, 0, tot) {
  //  cerr << pi[i] << ' ';
  //}
  //cerr << '\n';
}

inline void calc() {
  int ans = 1;
  FOR(i, 0, tot) {
    if (pi[i] == 0) continue;
    int cur = (p - 1 + q_pow(pi[i], (al[i] * B + 1) % pp)) * inv[pi[i] - 1] % p;
    ans = ans * cur % p;
  }
  cout << ans << '\n';
}

int main() {
  freopen("spring.in", "r", stdin);
  freopen("spring.out", "w", stdout);
  inv[1] = 1;
  FOR(i, 2, p) {
    inv[i] = (p - inv[p % i]) * (p / i) % p;
  }
  cin >> A >> B;
  fac();
  calc();
  return 0;
}
