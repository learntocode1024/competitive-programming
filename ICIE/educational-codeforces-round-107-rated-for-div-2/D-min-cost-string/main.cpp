// Original Author: misaka18931
// Date: 04-12-21
// tag:
// 

#include <cstdio>
#include <string>
#include <iostream>
#include <algorithm>
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


void solve() {
  int n, k;
  cin >> n >> k;
  string s0;
  for (int i = 0; i < k; ++i) {
    s0 += 'a' + i;
    for (int j = i + 1; j < k; ++j) {
      s0 += 'a' + i;
      s0 += 'a' + j;
    }
  }
  int q = n / s0.size();
  int r = n % s0.size();
  while (q--)
    cout << s0;
  cout << s0.substr(0, r) << endl;
}

int main() {
  cin.tie(NULL);
  std::ios::sync_with_stdio(false);
  int T = 1;
  // cin >> T;
  while (T--) {
    solve();
  }
  return 0;
}

/************************************ Man Of Culture **************************************
⣿⣷⡄⠙⠿⠏⢸⣷⣶⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣾⣽⢿⣿⣿⣿⣿⣿⣿⣿⣿⣷⡆⠄⠄⢴⣾⣿⣿⣿⣿⣿⣿⣿⣿⣦⣍⠷⣎⠸⢄⠸⣿⣇⢐⠸⡿⠏⡐⢐⢄⠹⣿⣮⡹⢿⣿⣿⣿⣯⡹⣷
⣿⣿⣿⠄⠄⠄⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣮⡹⢿⣿⣿⣿⣿⣿⠏⠁⠄⣼⣷⣶⣍⡻⢿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣎⡳⣎⡡⢌⠻⡆⡃⠃⠘⠄⢀⡐⣗⠸⢿⣷⣎⢻⣿⣿⣿⣇⡸
⣿⢟⡁⣀⣠⣴⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣎⡈⠻⠿⠏⠁⢠⠆⢠⣿⣿⣿⣿⣿⣶⣝⡻⣿⣿⣯⣻⣿⣿⡿⠿⠷⠈⠓⠦⠁⠄⠄⠄⠄⠄⢾⢧⡀⡀⠸⣿⣿⣧⡙⢿⣿⣿⣇
⣶⡆⠠⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⡄⠄⣤⣌⠋⠄⣴⣿⣿⣿⣿⣿⣿⣿⣿⣎⠻⣿⣿⣯⣿⣦⡔⢰⠁⠈⠄⠄⠄⠄⠄⠄⠚⠲⠰⠐⡆⠇⣿⣿⣿⣷⡌⢻⣿⣿
⣿⢣⣾⣿⣿⣿⣿⣿⣇⢻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣆⢹⣿⣧⣴⣶⣤⣬⣬⣭⣛⡛⠛⠛⠟⠓⠈⢻⣿⣷⣽⢷⡌⠚⣢⠱⠌⠋⡈⠄⠄⠄⠈⠄⠄⡀⢘⠫⣿⣿⣿⣿⣆⢹⣿
⣣⣿⣿⣿⣿⣿⣿⣿⣿⣏⢻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣇⢻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧⡻⣿⣻⣷⣝⢧⡜⠰⣀⡐⠁⡄⠄⠄⢀⠄⠄⠈⠄⠐⠄⠉⠙⠛⠛⠃⠙
⣿⣿⣿⣿⣿⣿⣿⣿⣿⣽⣧⠻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⣿⣿⣿⣿⡟⢿⡿⢿⣿⣇⢻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣧⡜⣿⢿⣿⣼⢻⣷⣌⣠⡤⠁⢀⠄⠆⠠⡘⢃⣦⣤⡄⠄⣤⣤⣭⣬⡌
⣿⣿⡏⣿⣿⣿⣿⣿⣿⣿⣼⣷⡜⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⣿⣿⣧⢕⢢⣤⣬⣌⢉⣥⣤⣶⣶⣶⣷⣶⣶⣦⣬⣭⣿⣿⣿⣷⡜⢿⣿⣿⣗⣹⣿⣯⣿⡇⠰⡀⢸⡇⢀⠆⢈⡛⠁⠄⢿⣿⣿⣿⣷
⣿⣿⣿⣽⣿⣿⣿⣿⣿⣿⣿⡜⣿⣮⡻⣿⣿⣿⣿⣿⣟⢿⣿⣿⣿⣿⣟⢿⣿⣿⣿⣿⣿⣿⡏⢿⣿⣿⣿⣿⣿⣿⣿⣿⡿⣿⣿⣿⣿⣿⣿⡜⣿⡟⢿⡏⠺⣿⣿⣷⡈⠢⣤⣙⠄⠉⠄⠄⠐⠄⣼⣿⠿⣿⣿
⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣎⢻⣷⣎⡻⣿⣿⣿⣿⣯⣿⣿⣿⣿⣯⣿⣿⣿⣿⡯⣿⣿⣿⡜⣿⣟⣿⣿⣿⣿⣿⣿⣿⣿⣾⣿⣿⢿⣿⣷⡼⢷⠈⢿⣏⣿⢿⢎⠻⡆⠴⠬⠤⢤⣠⣔⣄⢈⠹⣿⣷⣾⡙
⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⡽⢿⣷⣎⡻⣿⣿⣿⣧⢻⣿⣿⣿⢾⡷⡿⣿⣷⡼⢿⣿⣷⡸⢻⣿⡿⢿⣋⣽⠷⠾⠟⠛⠋⠙⠛⠉⢩⣥⣹⡇⡨⣿⡷⢟⣿⣇⠈⠆⠶⠶⠶⠍⢺⣞⣇⢑⢌⠹⢿⣧
⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣮⡹⢿⣿⣮⡙⢿⣿⣯⢻⣿⣿⣿⣿⣿⣿⣷⣷⡘⢿⢾⡇⢚⣫⡿⠋⠉⠁⠄⠄⢀⣀⣀⣠⣤⣤⣤⣬⣇⠃⢡⢸⣿⣎⢛⣿⣀⡀⢰⣷⡱⣾⡾⠏⠻⣾⣷⣄⡤⢉
⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⢇⣿⣮⡹⢏⠹⣦⣙⡻⢏⢹⣿⣻⣟⣿⣿⣿⣻⣇⠘⣿⡽⡎⣿⡾⠁⢀⣰⣶⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⡀⢸⡞⣿⣿⡼⠎⢸⡇⠸⣿⣷⣿⡸⣏⡁⣹⣿⣿⣷⣎
⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠇⣸⣿⣿⣿⣷⣕⡀⠈⡓⠮⢉⡹⢽⣿⣿⣿⣿⣽⣿⡆⢻⡇⢁⢩⣵⣶⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣻⣿⣇⣾⠇⢸⣷⡷⠁⣠⠌⠄⣩⣵⣾⣷⢿⡿⠿⢯⣿⢿⣿
⣿⡾⣿⣿⣿⣟⣿⣿⣿⣿⣿⣿⡟⠁⢰⣿⣿⣿⣿⣿⢿⡷⣦⣌⠹⠶⠆⢠⣉⣉⠙⠣⣿⣿⡇⠸⡇⢀⠘⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣯⣿⣿⣷⡇⢸⡿⣡⣾⣷⡇⠄⢰⣶⣿⣿⣸⣿⣇⣸⣿⣿⣿
⣿⣷⣹⣿⣿⣿⣿⣿⣿⣿⣿⡟⢡⣴⣿⣿⣿⣿⣿⣿⣿⣟⣾⣿⣣⡀⢖⡌⢲⡷⣻⣟⣿⣿⡇⠄⡃⣹⡄⣿⣿⣿⣻⣞⣿⡿⣿⣿⢿⣽⣿⣿⡿⣻⣾⢿⣇⢨⣔⣿⣫⣿⡷⣦⣬⣙⡟⣿⡏⠙⠛⢻⡎⢯⢹
⣿⣿⡧⢻⣿⣷⣿⣿⡿⣿⣟⢣⣿⣿⣿⣿⣷⣿⣿⣯⣽⣿⣻⣯⣟⡆⠞⢣⢨⢛⣿⣿⣿⣿⣇⠄⠄⣿⡧⣻⣟⣿⣿⣾⣿⣿⣿⣿⣿⣿⣿⢿⣽⣿⣿⣿⣷⢯⣯⣿⣿⣿⣧⢣⣬⡜⢣⢣⣿⣄⣠⣿⢡⠱⠈
⣿⣿⣿⣇⢻⣿⣻⣻⣟⢿⢧⣾⣻⣿⣿⠿⡯⡜⣿⣿⣿⡯⣾⣾⣿⢵⢸⡜⡞⡗⢽⣽⣯⣿⡇⢘⢸⣟⣿⣿⣾⣻⣿⣿⣿⢿⣽⣿⣿⣿⣿⣿⣻⣿⢿⣿⣽⣿⣿⣿⣿⣿⣿⡜⣿⣿⠇⡸⣻⣿⣿⣿⣸⠈⡀
⢹⣿⣿⣿⣇⢹⣿⣿⣿⣂⠘⣟⣿⡿⣿⣻⣟⣷⡜⢻⡛⠛⠋⠡⠼⣾⡆⣧⠁⢻⣼⣾⡗⠟⢡⣿⣯⣿⣻⣿⣽⣿⣿⣿⣿⣿⣿⣿⣿⣽⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡏⠟⠃⢸⣧⠸⣿⣿⣿⡇⢥⡷
⡇⢻⣿⣿⣿⣧⣙⢿⣯⣿⣧⡜⢹⣯⣿⣿⣿⡿⢹⣆⠘⢿⣡⣶⣶⣿⡧⢸⡇⢸⣧⣕⡼⡻⠻⣷⣟⣽⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⣿⣿⣿⣿⣿⣷⠄⠄⠄⢹⡀⢹⣿⣿⡇⣸⣧
⣿⡞⣿⣿⣿⣿⣷⡄⡳⣽⡿⣯⣦⠸⡻⢽⣏⣼⡿⢻⣅⢢⡝⢿⣿⣿⣝⣬⡟⣼⣿⣟⣿⣿⣧⣬⣹⣿⣿⣿⣿⣿⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⢻⡿⣿⣿⣿⣿⠄⠄⢠⡾⣇⢸⣿⡿⢳⣿⣿
⢚⢿⣜⢿⣿⢻⣿⣿⣯⡺⡻⣷⣿⣷⣜⠄⠑⠿⣽⣿⢾⣷⡜⢿⣯⠺⢢⣄⣽⣯⣟⣾⣿⣿⣿⣾⣿⣿⡿⠿⠟⠋⠉⠉⠙⠛⠛⣛⣛⡻⣿⣿⣿⣿⣿⣿⣿⣿⡿⣿⢸⣿⣿⡇⠄⢰⢾⡿⠜⢿⣿⢣⣿⣿⣿
⣧⢚⣿⣾⣿⣇⠻⣿⣟⡹⢤⣭⣻⣟⣿⡅⢆⡰⢮⣙⢿⣯⣿⣮⡙⢷⣿⣾⢿⣟⣿⣿⣿⣿⣿⣷⡟⠉⠄⠄⠄⠄⢀⣠⢴⡤⡯⣿⣿⣽⣮⡹⢿⣿⣿⣿⣿⣿⣿⣶⣾⣿⡿⠁⠄⠸⣏⢳⣄⣠⣿⣿⣿⣿⣿
⣿⣿⢯⣍⢹⣿⣏⠹⢿⣷⣮⣙⢿⣬⡫⣇⣸⣿⣬⣝⠷⣪⢙⡻⠅⣮⣺⣿⣟⣿⣿⣿⣿⣿⣿⣿⠃⠄⠄⠄⠄⢰⢶⡗⣿⣿⣿⣾⣶⣷⣿⣿⣮⣹⣿⣿⣿⣿⣿⣿⣿⣿⠃⠄⠄⠄⠈⢹⣟⠻⣿⣿⣿⣿⣿
⣗⣿⣼⣇⣢⣾⣟⢧⡈⠻⢾⡷⣷⣎⣙⠺⢝⣿⣿⣿⢷⣮⡙⢳⣖⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠄⠄⠄⢀⣰⡿⣽⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⣿⣿⣿⣿⣿⣿⣿⠇⠄⠄⢀⣴⠶⢮⣿⣼⣿⣿⣿⡿⢟
⣿⣿⣻⣿⣏⣹⣿⣷⡕⠆⠈⠙⠿⢿⡿⣷⣌⡉⠺⠳⠿⠏⣱⣾⣾⣷⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡆⠄⠄⢼⣭⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⢳⣿⣿⣿⣿⣿⣿⠇⠄⠄⠄⢸⣿⡄⠈⠁⢸⡿⠟⠉⣰⣏
⣿⣿⣿⣿⣿⣿⢿⣿⣿⣧⡀⠸⢿⢎⣩⣙⣛⡷⠦⠉⣶⣺⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⡀⠄⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠿⣱⣿⣿⣿⣿⣿⣿⠏⠄⣰⡀⠄⢸⣿⡿⢦⣠⠞⠁⢀⣀⣼⣿
⢺⡿⣿⡇⠉⢹⣯⡳⣿⣿⢧⠰⣦⣘⣻⣿⣿⣷⡎⠲⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣄⢺⡶⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣾⣿⣿⣿⣿⣿⣿⠏⠄⢠⣿⡇⠄⠸⠋⠁⢀⣠⣴⣶⣿⣿⣿⣿
⣧⣹⣿⣿⣿⣿⣿⣿⣿⡿⣿⣣⡘⢧⣿⣿⣯⡤⢤⠜⢢⡸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣝⠫⣿⣿⡿⢛⣫⣿⣿⣿⣿⣿⣿⣿⣿⣿⡟⠃⠄⣸⣦⣽⡻⡄⢸⣿⢸⡟⣿⣿⣿⣿⣿⣿⣿
⣿⣧⣹⣿⣿⣿⣿⣿⣿⣟⣿⣿⣿⣦⣝⠛⢿⣿⣿⣧⠳⠄⢈⠻⣿⣿⣿⣿⣿⣯⣧⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠋⠄⠄⢠⣿⣿⣿⣿⣧⡌⢻⢸⣷⢸⣿⣿⣿⣿⣿⣿
⣿⣿⣧⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠷⢮⡝⠛⠻⣶⣾⣷⣌⠛⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣵⣾⣿⣿⣿⣿⣿⣿⣿⡟⠁⠄⠄⠄⢸⣿⣿⣿⣿⣿⣿⣧⡉⢿⡿⣿⣿⣿⣿⡿⠟
⣿⣿⣿⣇⢻⡯⠙⢿⣿⣿⣿⣻⣿⣿⡟⣿⡇⠘⢻⣧⣄⠄⠄⠄⠈⠄⠄⠈⠛⠻⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠟⠛⠃⠄⠄⠠⠄⠄⢸⣿⣿⣿⣿⣿⣿⣿⣷⣾⣷⣩⡌⢩⣥⣴⣿
⣿⣿⣿⣿⣘⣗⢸⣯⡻⣷⣿⣷⡽⣿⣿⣜⣿⣤⣿⣿⣷⣷⣧⣄⡀⠠⡀⠄⠄⠄⠄⠄⢸⠍⠛⠛⠛⠛⠛⠛⠛⠛⠛⠛⢩⣭⣥⣤⣤⣄⣄⣀⣀⣠⣤⣤⣾⣾⢸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣼⣿⣿⣿
⣿⣿⡟⠛⠻⢧⣼⣿⣿⣮⡟⢿⣷⣌⠻⣿⣿⣏⣹⣿⣿⣿⣟⣿⣿⣿⣾⣾⡒⢤⣄⡀⠄⠄⠄⠄⠄⠄⠄⢠⣤⣤⡀⠄⠄⢙⠃⢰⣶⣶⣶⣬⣭⣽⣛⠻⢿⣿⡿⣿⣿⣿⣿⣿⣿⣿⡿⠛⠛⠛⣿⣿⣿⣿⣿
⣿⣿⣿⣦⣄⠄⠙⣿⠿⢿⣿⣷⣮⣙⢷⣾⡿⢿⡿⣿⣟⣿⣽⣿⣿⣟⣿⡿⠿⣦⣐⡫⢍⣑⣲⡬⠉⠛⠻⢿⣯⡙⡟⢡⣦⡌⢷⢸⣿⣿⣿⣿⣿⣿⣿⣿⣷⣶⣅⣹⣿⡿⠟⠉⠁⠄⣀⣀⡀⠄⢸⣿⣿⣿⣿
⣿⡿⢿⣿⢻⡇⠲⣿⣆⠈⢻⣿⣿⣿⣷⣾⣧⣀⣰⢯⣍⣙⡻⠿⠿⠿⢿⡄⠄⢻⡿⡿⠶⣮⣍⣛⣻⣿⣿⠿⣋⣵⡼⣶⣯⣙⡞⢺⣿⣿⣿⣿⣿⣿⣿⡿⠿⠿⠛⠛⠉⠁⢀⡴⠶⠿⠿⠿⠿⠄⠘⢿⣿⣿⣿
⢸⣷⡌⠹⢿⣿⠄⣿⣿⣷⣾⣿⣿⣿⣿⣿⣿⣿⣿⣶⣭⣹⣿⣿⣷⣶⣾⣧⠄⠘⣷⠶⠞⢉⢹⡿⢿⣫⣵⣾⣿⣿⣿⣮⡻⣿⣷⣆⢻⣿⣿⣿⠟⠋⠁⠄⢀⣀⠄⠄⢀⣀⣤⣴⣶⣶⣶⣶⣶⣶⣶⣶⣦⣍⣙
******************************************************************************************/