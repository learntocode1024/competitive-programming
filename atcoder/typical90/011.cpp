// Original Author: misaka18931
// Date: $DATE
// tag:
//

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <tuple>
#include <vector>
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;

#define pb(x) push_back(x)
#define pf(x) push_front(x)
#define MX 5005

LL dp[2][MX];
int c[MX], d[MX], s[MX];

void solve() {
  int n;
  cin >> n;
  vector<tuple<int, int, int>> tmp;
  for (int i = 0; i < n; ++i) {
    cin >> d[i] >> c[i] >> s[i];
    tmp.push_back(make_tuple(d[i], c[i], s[i]));
  }
  sort(begin(tmp), end(tmp));
  for (int i = 0; i < n; i++) {
    d[i] = get<0>(tmp[i]);
    c[i] = get<1>(tmp[i]);
    s[i] = get<2>(tmp[i]);
  }
  for (int i = 0; i < n; ++i) {
    LL* const (&a) = dp[i & 1];
    LL* const (&b) = dp[~i & 1];
    for (int t = 0; t <= 5000; ++t) {
      a[t] = max(a[t], b[t]);
      if (t + c[i] <= d[i])
        a[t + c[i]] = max(a[t + c[i]], s[i] + b[t]);
    }
  }
  LL ans = 0;
  for (int i = 0; i <= 5000; ++i) {
    ans = max(ans, dp[(n - 1) & 1][i]);
  }
  cout << ans << endl;
}

int main() {
  int T = 1;
  while (T--)
    solve();
  return 0;
}

/****************************** Railgun *********************************
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⠀⠠⢀⠠⢀⠠⠀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡀⠠⠐⠠⠈⠄⠨⠐⡀⠂⠄⠂⡁⠄⢁⠡⠐⢀⠀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡀⠄⡂⠄⠡⠈⠄⠡⠈⠄⠡⠐⡈⠄⠡⢀⠨⢀⠐⡈⢀⠂⠄⠄⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡀⡀⠠⡀⡄⡔⣄⢦⢕⣔⢕⠔⡅⢅⠅⢅⠅⢅⠅⠅⢅⠂⠅⢌⠀⡂⠀⡂⢐⠀⡂⢐⠀⡂⠐⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡀⡄⣢⢪⣲⣲⣪⣞⣮⣾⣾⣷⣿⣿⣾⣷⡯⣪⢢⠱⡐⢅⠢⠡⡑⡐⢅⢑⢐⠡⡀⠅⡐⠄⡂⠢⠐⡀⢂⠁⠄⡐⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⢤⢱⣼⣾⣿⢿⣿⣿⣿⣿⣿⣿⣻⣻⡻⡽⣻⡻⡿⣯⣧⣯⡪⣪⢸⠨⡢⠨⡂⡢⠡⡊⠔⡐⢀⢊⠔⠡⠡⠐⡀⠂⠅⢊⠠⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⢀⠠
⠀⠀⠀⠀⠀⠀⠀⢄⢕⣽⣿⣿⣿⣾⣿⡿⡯⡳⡳⡱⡣⡣⡒⢕⢑⠕⢕⢝⠪⢎⢯⡻⡷⣷⣝⣮⡳⡱⣑⠱⡐⡡⢂⢆⢂⠅⠅⠅⢅⢂⠁⠌⡀⢂⠡⠠⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡀⡐⡌⣆⡖⡵
⠀⠀⠀⠀⠀⠄⡕⣵⣽⡟⡟⡞⡝⢞⠫⡚⡜⡑⠡⡃⡪⢐⢌⠂⠕⢌⠢⡡⡑⢕⠱⡱⡹⡽⣿⣷⣿⣯⢮⢪⠂⡜⡐⠌⡆⡥⡁⡃⢅⠢⠨⢀⠂⡐⢀⠂⡁⡀⠀⠀⠀⠀⠀⢀⢀⢂⢆⢧⣻⡪⢮⢛
⠀⠀⠀⢄⢱⣱⡽⡟⡕⠕⠁⠂⠈⠀⠂⡐⠐⢀⢕⠨⠢⡑⡔⢅⢋⠢⡑⡐⢄⠥⡑⢌⠎⠮⡿⡿⡿⡿⣿⣕⠕⡜⡎⢎⢸⢸⢌⠢⠡⡨⠨⢀⠂⡐⡀⢂⠐⡀⠅⢄⠠⡐⡨⡐⠴⠫⡙⢌⠢⠊⠐⠀
⠀⠠⢨⣪⣾⡯⡣⢑⠀⠁⠀⠀⠀⠀⠀⡊⠀⡐⡆⡣⡃⢕⢑⠄⢕⢑⠄⡊⡢⢑⢌⠢⡑⢱⢱⣫⢻⡊⡇⡎⡅⡏⣞⢎⢞⡵⡕⡕⢅⠢⡁⢂⠐⡀⡂⠢⡈⡢⡱⡱⣵⣳⡝⡍⠌⠂⠐⠀⠀⠀⠀⠀
⢀⢪⣲⢟⠕⠕⠈⠀⠀⠀⠀⠀⠀⠀⠐⠀⠀⡐⢅⠢⡊⡢⠂⢅⠣⢪⢀⢆⢊⢪⢐⠅⡕⢜⢜⡜⣕⢝⠨⡢⡁⢧⡓⡗⡹⣽⣮⣺⢸⡐⢌⢆⢂⢪⢨⣪⡪⡮⣺⢝⣾⢳⢑⠅⢂⠀⠀⠀⠀⠀⠀⠀
⢜⣶⡟⡜⠨⠈⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢌⠢⢱⠨⠨⡈⢢⢑⢕⢐⢅⢎⠆⡅⢣⠁⡵⣕⢽⡸⡕⡇⡆⡪⡪⡪⡺⢜⠽⡽⣷⣯⡮⣪⣪⢺⢨⡣⡇⣗⡽⡗⡏⡎⡢⠡⠈⠄⠂⠄⠀⠀⠀⠀⠀
⡟⡏⡊⠐⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡂⡃⢕⠨⡊⠌⡐⢌⢂⢕⣘⣑⠇⢪⡳⡸⡜⡮⣪⡺⣪⢳⠐⠜⡨⡀⠄⠢⢢⢧⣻⣿⣟⢾⣺⣪⢪⡎⡞⡕⢜⠘⢌⠢⡂⢅⠡⠈⠄⠡⢈⢀⠀⠀⠀
⠕⠡⠐⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡢⠊⠀⢕⠨⡂⠌⡂⢕⢑⠴⢑⣁⠑⡐⠘⠌⢮⡫⡮⣺⢪⢮⢲⡹⣝⣀⢆⢀⢪⢇⣿⣿⣿⣿⣳⢗⢕⢑⢑⠌⡐⠨⢀⠑⢄⢑⠄⡡⠨⢐⠠⠀⡂⠀⠀
⠈⠄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡀⠊⠀⠀⠀⢕⠨⡂⠅⠂⡕⡔⡁⣼⣺⠐⠘⠃⢳⢕⣎⢯⢮⡳⣝⢵⡹⣜⡺⠥⣕⢸⢽⢾⣿⣷⣿⣽⢱⢑⢐⢐⢐⠨⠐⡐⢈⠐⡠⠡⢂⠂⡁⡂⠡⠐⠠⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢂⠨⡂⢑⠠⢸⣊⢞⢮⡻⣞⢇⣊⢼⡳⡵⣝⢮⣺⡪⡳⣝⣜⢮⡫⣎⢯⢯⣿⣿⣿⢿⣺⢸⠐⠄⢂⢐⠠⢁⠂⢂⠂⠄⠡⠂⠅⠄⠂⠅⡈⠀⠀
⠀⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡂⢅⠊⢄⢑⢈⢗⡲⡘⡷⡽⣝⢭⣲⡳⣝⣞⢮⡳⡵⣝⣝⢮⡺⣪⡺⣪⡫⣗⣿⣻⣿⣿⢯⠪⠌⠌⠄⡂⠌⡐⠨⢀⢂⠡⠁⠌⠨⠠⠁⠡⢀⠡⠀
⠀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⠪⢐⠡⢊⠔⣐⢅⡢⡙⡗⡮⣻⢮⣻⣪⢾⣕⢷⢝⡮⣯⡺⣪⡳⣝⢮⡺⣪⢞⢵⡳⣻⣿⢿⢕⠕⢅⠑⠄⡂⠡⠠⢁⠕⡀⡂⠡⠨⠀⠅⢂⠀⠐⠀⠂
⢀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠢⡁⠢⢑⣖⣽⣺⢽⣫⡽⣾⢾⣾⢯⣞⢞⣷⢽⡽⡽⡽⡺⡮⣓⢭⢮⡳⣝⢮⡫⡪⣝⣽⡿⣝⢜⠌⠄⠅⠅⠄⠡⢁⠂⠄⠐⠄⠅⠌⡐⠈⠠⠀⠀⠀⠀
⠠⢀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠌⢀⣝⣗⡗⡗⣽⣻⢷⣻⡯⡿⣽⣻⡽⣿⢾⣟⡿⣻⡽⣝⢾⣕⢯⡳⣝⢮⠣⡣⣃⢮⣺⡯⡪⡢⠡⠡⢑⠨⢈⠈⡐⠨⢈⠀⠈⠂⠅⡐⠀⠀⠁⠀⠀⠀
⠨⢀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢈⠀⡼⣞⢞⣮⢿⣯⢿⢽⣳⢯⣟⣗⢷⣻⣽⣻⣽⡾⡕⣝⢽⢵⡳⡽⣺⠱⡱⡱⣕⢽⡺⣼⢣⠣⡊⠌⠌⡐⠨⢐⠀⠠⢁⢂⠀⠀⠈⢂⠂⡁⠀⠀⠀⠀⠀
⣕⢐⠠⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⡽⣕⣟⣾⢿⡽⣽⣻⣺⢽⣺⣺⢽⣞⣾⣳⡿⣽⣻⣊⣪⢳⢙⢝⢔⢝⣜⢞⡎⡧⣟⢷⢕⢑⠌⠌⢐⠨⠀⢂⠂⠀⠐⠠⠀⠀⠀⠀⢂⠀⠀⠀⠀⠀⠀
⡳⣕⣕⢀⠂⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣺⢸⡳⣕⣗⣿⢯⣟⣗⣗⡯⣟⡾⡽⣽⣺⣞⣷⢿⡽⣞⡆⣿⢷⡷⣵⢵⣓⡵⢫⡺⣽⡺⡯⡯⡦⠡⠁⠀⠂⠀⠐⠀⠀⠀⠨⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀:⠀
⠸⢮⡻⣜⢄⠅⠀⠀⠀⠀⠀⠀⢀⡼⣵⣳⡺⡜⡮⣺⢿⣻⣗⡿⣺⢱⡵⣯⢽⡳⣻⢾⣽⢿⡽⣯⢺⣟⣿⣻⣽⢿⢭⣞⡷⡽⣾⢽⡽⣝⡾⡐⡄⢄⠄⡀⠈⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠈⠪⡪⡳⡵⣑⠅⡂⠀⠀⠀⠀⡷⡽⣺⢮⢧⡣⣽⢽⣻⣻⣽⣟⣿⡸⣿⢽⡯⣟⣾⣟⡯⡿⣽⡳⡽⣿⣽⣻⡾⣿⣪⡷⣟⣿⣚⣿⢽⣳⣻⢨⡸⡐⢕⢌⠪⠪⡣⡢⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠁⡘⢜⢎⢎⢇⣆⠅⡂⡀⢠⢯⢞⣗⢯⢗⡽⡽⡽⡜⣟⣾⢽⣻⣷⡽⣿⣽⣿⢯⡗⡵⣻⡳⡯⣧⣳⢻⣽⣻⢣⣳⢟⣯⣿⣽⣺⣽⡓⣛⢜⡜⡎⡖⡔⡑⢅⢫⢮⡸⡄⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⡑⡘⠽⡘⡔⢕⢆⡢⡯⣯⣳⢽⢭⣳⢯⣟⣕⢕⣟⣾⣻⢼⣟⣿⣯⡷⣻⡹⣜⢝⠬⠯⣻⡺⡮⣗⢶⢜⢿⣺⣟⣯⣷⡞⣾⣺⡅⡇⡧⡳⡹⣘⢌⢊⢢⢱⣓⢵⢝⢆⡀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠠⢁⠣⢇⢇⢇⣾⢿⣳⡯⡿⡽⣮⢻⣺⣺⣜⡾⣾⣽⣏⣿⣳⡯⣯⢳⡹⡸⡪⢍⡯⡎⢝⡙⡞⣗⡣⣗⣻⣟⣯⡷⣇⡿⡮⡇⢇⢗⢕⢝⢔⢕⢌⠢⡱⣘⢱⢹⢱⢱⢰⢰⢠⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠠⠁⡇⡯⣿⢾⣿⢯⣿⣻⢿⡽⣷⡽⣷⢿⣜⡿⣞⡷⡝⡾⡽⣽⡪⡪⣚⡬⣗⡯⣇⢧⢯⢾⣵⢿⡽⣾⣙⢷⣟⣗⡯⣟⣽⡨⢘⢜⢕⢵⢱⢱⢑⢜⢎⢯⢎⡗⣕⢧⢳⢱⢍⢆⠀⠀⠀
⠀⠀⠀⠀⠀⠀⢅⠪⣝⢾⢿⣻⣟⣷⡿⣯⣿⢷⡷⣝⢯⡷⣏⡫⣯⢷⢹⡽⣺⢽⢪⣞⣽⣳⣻⣳⣟⡿⣽⣾⣻⡽⣗⠧⡇⢿⣺⢾⣹⡺⡆⡇⡇⡗⡕⡕⡕⡕⣜⢜⡬⢥⢍⡎⡮⣊⡊⣎⢪⠪⡂⠆
⠀⠀⠀⠀⠀⠌⢴⢑⢃⢃⢻⢽⣻⣾⢿⣿⣻⣿⣻⣽⣯⣏⣗⣵⢮⢿⢽⢽⡽⣯⢗⣷⢷⣯⢿⡹⣪⢫⢗⡯⣷⣻⢿⣫⣎⢣⣑⢟⡮⣫⢟⢜⢜⡜⡜⡜⡜⡜⡔⡕⣝⢕⢧⢳⢹⢸⡸⡸⡸⡱⡱⡱
⠀⠀⠀⠠⢈⢊⠣⢁⠂⠀⠀⠳⡭⣺⢿⠽⣻⡾⣯⡿⣞⠵⣻⢽⡫⣝⣻⣻⢹⡯⣏⣯⢿⣞⢏⡞⡜⡌⣗⢽⡺⣺⣻⣗⡷⡵⣈⠦⡙⢭⢯⢘⢜⢜⢜⢜⢜⢜⢜⢌⢪⢣⢳⢕⡝⣜⢜⢜⢎⢎⢎⢎
⠀⠀⡀⠪⡐⡫⢈⠀⠀⠀⠀⠀⠈⠑⠫⢯⡲⣖⣖⢮⡺⣝⣞⢽⡺⣝⢶⡹⡵⡭⡪⣺⢽⢫⢇⣇⢣⢚⣎⢧⡫⣳⢽⣞⣯⣟⢮⡣⡍⡪⡃⢰⡸⡸⡸⡸⡸⡸⡘⡜⡄⡇⡇⡇⡧⡣⡳⡱⡱⡱⡑⡕
⢀⢂⡊⡋⡂⠂⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠘⠪⠗⠽⣕⢷⢝⡮⣗⢽⡺⣢⢯⢇⠯⡫⣓⢯⢲⢱⡱⣕⢵⢹⡪⣳⣻⣳⢯⢷⣫⢞⡆⡍⠎⢎⢎⢎⢎⢎⠎⢊⡈⠜⡰⢱⢑⢕⢕⢕⢕⢕⢕⢕⢕
⣰⠸⠨⠐⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠑⠙⡮⣳⢝⡮⣳⠽⡑⡕⡕⣝⢷⢵⢝⡜⣎⢇⢯⢺⣪⢯⢏⡯⣞⢷⣝⢮⡊⡜⢜⢜⢜⢌⢎⠰⢍⠆⡂⢕⠕⡅⢇⢇⢇⢇⢇⢕⢜
⡣⡑⢁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠡⡙⣊⢪⢸⠨⡪⡪⡻⣞⡵⣝⢜⢎⢮⢣⡳⣽⢳⡹⣜⢵⠽⣗⢕⢜⢌⢆⢇⢕⢕⢱⢈⢀⢂⢇⢣⢱⠡⡣⡣⡣⢣⢱⢘

************************************************************************/
