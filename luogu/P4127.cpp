#include <iostream>
#include <cstring>

#include "utils"

i64 dp[19][163][163];

long long ans, a, b;

inline i64 calc(i64 n, i64 mod) {
  i64 ret = 0;
  int cnt = 0;
  int sum = 0;
  for (__int128 i = 1; i <= n; i *= 10) ++cnt, sum += n / i % 10;
  ret += sum == mod && n % mod == 0;
  i64 msk = 1;
  if (cnt > 19) exit(0);
  for (int i = 0; i < cnt; ++i, msk *= 10) {
    int cur = n / msk % 10;
    for (int j = 0; j < cur; ++j) {
      i64 r = (n / msk - cur + j) * msk % mod;
      int s = sum - cur + j;
      if (s > mod) continue;
      ret += dp[i][mod - s][(mod - r) % mod];
    }
    sum -= cur;
  }
  return ret;
}

void work() {
  for (int mod = 1; mod < 163; ++mod) {
    memset(dp, 0, sizeof(dp));
    dp[0][0][0] = 1;
    for (int i = 1; i <= 18; ++i) {
      for (int s = 0; s <= (i - 1) * 9; ++s) {
        for (int r = 0; r < mod; ++r) {
          for (int c = 0; c + s <= mod && c < 10; ++c) {
            dp[i][s + c][(r * 10 + c) % mod] += dp[i - 1][s][r];
          }
        }
      }
    }
    ans += calc(b, mod) - calc(a - 1, mod);
  }
}

int main() {
  // IO::init_in();
  cin >> a >> b;
  work();
  cout << ans << '\n';
}
