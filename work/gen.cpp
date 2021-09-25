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

const int n = 500000, m = 500000;
using uni = uniform_int_distribution<int>;
int a[n + 10];

void work() {
  cout << n << ' ' << m << '\n';
  uni f{1,n};
  uni g{-500000000, 10000}, gg{-10000, 500000000};
  uni h{1, 500000}, hk{-2000, 2000};
  FOR(i, 0, n) {
    a[i] = h(gen);
    printf("%d ", a[i]);
  }
  
  puts("");
  FOR(i, 0, m) {
    int l = f(gen), r = f(gen);
    i64 ret = 0;
    if (l > r) swap(l, r);
    cout << l << ' ' << r << '\n';
    // FOR(j, l-1, r) FOR(k, l-1, r) if (a[j] % a[k] == 0) ++ret;
    // cerr << ret << '\n';
  }
}

int main() {
  int T = 1;
  // cout << T << endl;
  work();
}
/*
for i in $(seq 1 1000) ; do ./gen 1> ex.in 2>ex.ans; echo "# $i" ; ./HDU5306 < ex.in | diff ex.ans - || break ; done
*/