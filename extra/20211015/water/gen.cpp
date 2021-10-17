#include <bits/stdc++.h>
using namespace std;
typedef long long i64;
typedef unsigned long long u64;
typedef unsigned u32;
#define FOR(i, j, k) for (int i = j; i < k; ++i)
const int N = 305;
bool vis[N];
int a[N][N];
int n = 300, m = 300;

int main() {
  i64 seed = chrono::steady_clock::now().time_since_epoch().count();
  mt19937 gen(seed);
  uniform_int_distribution<int> fn{1, n};
  uniform_int_distribution<int> fm{1, m};
  uniform_int_distribution<int> fv{-1000000000, 1000000000};
  cout << n << ' ' << m << '\n';
  FOR(i, 1, n + 1) {
    FOR(j, 1, m + 1) cout << (a[i][j] = fv(gen)) << ' ';
    cout << '\n';
  }
  return 0;
}
