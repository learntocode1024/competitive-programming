#include <cstring>
#include <climits>
#include <iostream>

#include "utils"
int n, m;

const int N = 50005;

int a[N << 2];
void up(int p) {
  a[p] = min(a[p * 2], a[p * 2] + 1);
}
void set(int p, int l, int r, int s, int v) {
  if (r - l == 1) {
    return chkmin(a[p], v);
  }
  int mid = (l + r) / 2;
  if (s < mid) set(p * 2, l, mid, s, v);
  else set(p * 2 + 1, mid, r, s, v);
  up(p);
}
int get(int p, int l, int r, int s, int t) {
  if (r == t && l == s) {
    return a[p];
  }
  int mid = (l + r) / 2;
  int ret = 1e9;
  if (s < mid) chkmin(ret, get(p * 2, l, mid, s, min(mid, t)));
  if (t > mid) chkmin(ret, get(p * 2 + 1, mid, r, max(mid, s), t));
  return ret;
}


int main() {
  cin.tie(0);
  ios::sync_with_stdio(0);
  cin >> n >> m;
  memset(a, 0x3f, sizeof a);
  set(1, 0, n, 0, 0);
  while (m--) {
    int l, r;
    cin >> l >> r;
    --l, --r;
    set(1, 0, n, r, get(1, 0, n, l, r + 1) + 1);
  }
  cout << get(1, 0, n, n - 1, n) << endl;
}