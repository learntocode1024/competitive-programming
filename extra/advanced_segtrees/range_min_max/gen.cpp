#include <bits/stdc++.h>
using namespace std;
typedef long long i64;
typedef unsigned long long u64;
typedef unsigned int u32;
typedef pair<int, int> pii;
#define pb(x) push_back(x)
#define mkp(x, y) make_pair(x, y)
#define fi first
#define se second
#define FOR(x, y, z) for (int x = y; x < z; ++x)  // always [y, z)
#define ROF(x, y, z) for (int x = z - 1; x >= y; --x)
template <typename T>
void chkmax(T &a, const T &b) {
  a = max(a, b);
}
template <typename T>
void chkmin(T &a, const T &b) {
  a = min(a, b);
}
pii operator+(const pii &a, const pii &b) {
  return mkp(a.fi + b.fi, a.se + b.se);
}
std::random_device dev;
mt19937 gen(dev());

const int n = 6, m = 40;
using uni = uniform_int_distribution<int>;
int a[n];
int _main() {
  memset(a, 0, sizeof a);
  printf("%d\n", n);
  uni f{1,n};
  uni g{-500000000, 10000}, gg{-10000, 500000000};
  uni h{-500000000, 500000000}, hk{-2000, 2000};
  FOR(i, 0, n) {
    a[i] = h(gen);
    printf("%d ", a[i]);
  }
  puts("");
  printf("%d\n", m);
  FOR(i, 0, m) {
      int l = f(gen), r = f(gen);
      i64 ret = 0;
      if (l > r) swap(l, r);
    if (gen()&1) {
      if (gen() % 3 == 0) {
        int w = g(gen);
        FOR(i, l-1, r) chkmin(a[i], w);
        cout << "3 " << l << ' ' << r << ' ' << w << endl;
      } else if (gen()&1) {
        int w = hk(gen);
        FOR(i, l-1, r) a[i] += w;
        cout << "1 " << l << ' ' << r << ' ' << w << endl;
      } else {
        int w = gg(gen);
        FOR(i, l-1, r) chkmax(a[i], w);
        cout << "2 " << l << ' ' << r << ' ' << w << endl;
      }
    } else if (gen()%3==0) {
      ret = INT_MIN;
      FOR(i, l-1, r) chkmax(ret, 1ll*a[i]);
      cerr << ret << endl;
      cout << "5 " << l << ' ' << r << endl;
    } else if (gen()&1) {
      FOR(i, l-1, r) ret += a[i];
      cerr << ret << endl;
      cout << "4 " << l << ' ' << r << endl;
    } else {
      ret = INT_MAX;
      FOR(i, l-1, r) chkmin(ret, 1ll*a[i]);
      cerr << ret << endl;
      cout << "6 " << l << ' ' << r << endl;
    }
  }
}

int main() {
  int T = 1;
  // cout << T << endl;
  while (T--) _main();
}
/*
for i in $(seq 1 1000) ; do ./gen 1> ex.in 2>ex.ans; echo "# $i" ; ./HDU5306 < ex.in | diff ex.ans - || break ; done
*/