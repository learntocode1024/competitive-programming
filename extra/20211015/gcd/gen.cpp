#include <bits/stdc++.h>
using namespace std;
typedef long long i64;
typedef unsigned long long u64;
typedef unsigned u32;
#define FOR(i, j, k) for (int i = j; i < k; ++i)
const int N = 200000;
bool vis[N];
int a[N];

int main() {
  i64 seed = chrono::steady_clock::now().time_since_epoch().count();
  mt19937 gen(seed);
  uniform_int_distribution<int> e{1, 500000};
  uniform_int_distribution<int> f{1, N};
  cout << N << ' ' << N << '\n';
  FOR(i, 0, N) a[i] = e(gen);
  FOR(i, 0, N) cout << a[i] << ' ';
  cout << '\n';
  FOR(i, 0, N) {
    int t = f(gen);
    cout << t << '\n';
    --t;
    vis[t] ^= 1;
    continue;
    int ans = 0;
    FOR(i, 0, N) {
      if (vis[i]) {
        FOR(j, i + 1, N) {
          if (vis[j]) {
            if (__gcd(a[i], a[j]) == 1) ++ans;
          }
        }
      }
    }
    cerr << ans << '\n';
  }
  return 0;
}
