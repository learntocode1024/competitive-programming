// Original Author: misaka18931
// Date: $DATE
// tag:
//

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;

#define pb(x) push_back(x)
#define pf(x) push_front(x)
#define MX
const long long mod = 1000000007;

void solve() {
  int n;
  cin >> n;
  LL ans = 1;
  for (int i = 0; i < n; ++i) {
    int tmp = 0, curr = 0;
    for (int j = 0; j < 6; ++j) {
      cin >> tmp;
      curr += tmp;
    }
    ans = ans * curr % mod;
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
