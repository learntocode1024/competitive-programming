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
const int n = 100, m = 100;
using uni = uniform_int_distribution<int>;
int a[n];
int _main() {
  memset(a, 0, sizeof a);
  printf("%d %d\n", n, m);
  uni f{1,n};
  uni g{1, 10000};
  uni h{1};
  FOR(i, 0, n) {
    a[i] = h(gen);
    printf("%d ", a[i]);
  }
  puts("");
  FOR(i, 0, m) {
      int l = f(gen), r = f(gen);
      i64 ret = 0;
      if (l > r) swap(l, r);
    if (h(gen)&1) {
      int w = g(gen);
      FOR(i, l-1, r) chkmin(a[i], w);
      cout << "0 " << l << ' ' << r << ' ' << w << endl;
    } else if (h(gen)&1) {
      FOR(i, l-1, r) chkmax(ret, 1ll*a[i]);
      cerr << ret << endl;
      cout << "1 " << l << ' ' << r << endl;
    } else {
      FOR(i, l-1, r) ret += a[i];
      cerr << ret << endl;
      cout << "2 " << l << ' ' << r << endl;

    }
  }
}

int main() {
  int T = 20;
  cout << T << endl;
  while (T--) _main();
}
/*
for i in $(seq 1 1000) ; do ./gen 1> ex.in 2>ex.ans; echo "# $i" ; ./HDU5306 < ex.in | diff ex.ans - || break ; done
*/