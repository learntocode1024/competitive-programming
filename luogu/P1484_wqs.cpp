/**********************************************************************
 * This file is the c++ solution to a particular CP problem written by
 * misaka18931 and was hosted on GitHub Repository below:
 * URL: https://github.com/misaka18931/competitive-programming
 *
 * Original Author: misaka18931
 * Date:
 * Algorithm:
 * Difficulty:
 *
 *********************************************************************/

#include <algorithm>
#include <cctype>
#include <climits>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;

#define pb(x) push_back(x)
#define pf(x) push_front(x)
#define MX 500005

int n, k;
LL a[MX], dp[MX];
int cnt[MX];

struct Node{
    LL x,y;
    bool operator<(const Node &a)const{
        if(x!=a.x)return x<a.x;
        else return y>a.y;
    }
    bool operator>(const Node &a)const{
        return a<*this;
    }
    Node operator+(const Node &a)const{
        return (Node){x+a.x,y+a.y};
    }
}f[MX],g[MX];

// int check(int mid){
//     f[1]=(Node){a[1]+mid,1};
//     g[1]=max(g[0],f[1]);
//     for(int i=2;i<=n;++i){
//         f[i]=g[i-2]+(Node){a[i]+mid,1};
//         g[i]=max(g[i-1],f[i]);
//     }
//     // printf("%d %d\n",mid,g[n].y);
//     return g[n].y;
// }

bool check(LL c) {
  if (a[0] >= c) dp[0] = a[0] - c, cnt[0] = 1;
  for (int i = 1; i < n; ++i) {
    if (i > 1 && (a[i] - c + dp[i - 2] > dp[i - 1] || a[i] - c + dp[i - 2] == dp[i - 1] && cnt[i - 2] + 1 > cnt[i - 1])) {
      a[i] = a[i] - c + dp[i - 2];
      cnt[i] = cnt[i - 2] + 1;
    } else {
      a[i] = a[i - 1];
      cnt[i] = cnt[i - 1];
    }
  }
  return cnt[n - 1];
}

void solve() {
  cin >> n >> k;
  for (int i = 0; i < n; ++i) {
    cin >> a[i];
  }
  LL l = 0, r = 1e7;
  LL ans = 0;
  while (r - l) {
    int mid = l + (r - l) / 2;
    if (check(mid) >= k) l = mid + 1;
    else r = mid;
  }
  cout << dp[n - 1] + k * l << endl;
}

int main() {
  int T = 1;
  while (T--)
    solve();
  return 0;
}

