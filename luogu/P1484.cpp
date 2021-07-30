/**********************************************************************
 * This file is the c++ solution to a particular CP problem written by
 * misaka18931 and was hosted on GitHub Repository below:
 * URL: https://github.com/misaka18931/competitive-programming
 *
 * Original Author: misaka18931
 * Date: Jul 15, 2021
 * Algorithm: priority_queue, mutual-link-list
 * Difficulty: normal
 *
 *********************************************************************/

#include <algorithm>
#include <cctype>
#include <climits>
#include <cstdio>
#include <iostream>
#include <queue>
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;

namespace IO {
template<unsigned T>
struct buffer {
  char in[T], out[T];
  char *o, *p, *o1, *p1;
  buffer() {
    o = o1 = in;
    p = out;
    p1 = out + T;
  }
  ~buffer() {
    fwrite(out, 1, p - out, stdout);
  }
  inline char get() {
    return (o == o1) && o1 = (o = in) + fread(in, 1, T, stdin), o == o1 ? EOF : *o++;
  }
  inline char put(char c) {
    if (p == p1) p1 = (p = out) + fwrite(out, 1, T, stdout);
    *p++ = c;
  }
};
buffer<1 << 20> io;

}

#define pb(x) push_back(x)
#define pf(x) push_front(x)
#define MX 500005

int n, k;
LL a[MX], b[MX], c[MX];
bool d[MX];

priority_queue<pair<LL, int>> pq;

void solve() {
  cin >> n >> k;
  // init
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
    b[i] = i - 1;
    c[i] = i + 1;
    pq.push(make_pair(a[i], i));
  }
  a[0] = a[n + 1] = -1e17;
  int tot = n + 1;
  LL ans = 0, mx = 0;
  while (k--) {
    while (d[pq.top().second]) pq.pop();
    auto t = pq.top();
    pq.pop();
    ans += t.first;
    mx = max(ans, mx);
    d[t.second] = 1;
    int p = b[t.second], q = c[t.second];
    d[p] = d[q] = 1;
    a[++tot] = a[p] + a[q] - t.first;
    b[tot] = b[p];
    c[tot] = c[q];
    c[b[p]] = tot;
    b[c[q]] = tot;
    pq.push(make_pair(a[tot], tot));
  }
  cout << mx << endl;
}

int main() {
  int T = 1;
  while (T--)
    solve();
  return 0;
}

