#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <deque>
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
const LL mod = 1e9 + 7;
#define printb(x) \
  if ((bool)x) printf("YES"); \
  else printf("NO");
#define pb(x) push_back(x)
#define pf(x) push_front(x)
#define MX


int main() {
  long long n, k;
cin >> n >> k;
long long ans = k * (k - 1);
for (int i = 2; i < n; ++i) {
ans *= k * (k - 1) - 1;
}
ans *= (k - 2) * (k - 3);

cout << ans << endl;
}