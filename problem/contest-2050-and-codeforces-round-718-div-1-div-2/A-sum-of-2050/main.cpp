// Original Author: misaka18931
// Date: 04-18-21
// tag:
// 

#include <cstdio>
#include <cstring>
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
  LL n;
  cin >> n;
  if (n % 2050) {
    cout << -1 << endl;
    return;
  }
  n /= 2050;
  int t = 0;
  while (n) {
    t += n % 10;
    n /= 10;
  }
  cout << t << endl;
}

int main() {
  int T = 1;
  cin >> T;
  while (T--)
    solve();
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