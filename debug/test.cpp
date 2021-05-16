#include <algorithm>
#include <iostream>
#include <vector>
#define lowbit(X) ((X) & (-X))
using namespace std;
typedef vector<long long> arr;
int n, k;

arr dp, mx, c, x;
bool valid[1000005];

void addall(long long val) {
  int p = 1;
  while (p <= k) {
    mx[p] += val;
    p += lowbit(p);
  }
}

void add(int col, long long val) {
  while (col <= k) {
    mx[col] += val;
    col += lowbit(col);
  }
}

long long getmx(int col) {
  long long ans = 0;
  while (col) {
    ans += mx[col];
    col -= lowbit(col);
  }
  return ans;
}

void modmx(int col, long long val) {
  long long tmp = getmx(col);
  if (valid[col] && tmp >= val)
    return;
  valid[col] = true;
  tmp = val - tmp;
  add(col, tmp);
  add(col + 1, -tmp);
}

int main() {
  cin >> n >> k;
  c = x = dp = arr(n);
  mx = arr(k + 5);
  for (int i = 0; i < n; ++i)
    cin >> c[i];
  for (int i = 0; i < n; ++i)
    cin >> x[i];
  modmx(c[0], x[0]);
  for (int i = 1; i < n; ++i) {
    dp[i] = max(dp[i - 1], valid[c[i]] * (getmx(c[i]) + x[i]));
    modmx(c[i], dp[i - 1]);
    addall(x[i]); // maintain best choices.
  }
  cout << dp[n - 1] << endl;
  return 0;
}
