// Original Author: misaka18931
// Date: 04-23-21
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

string raw, s1, s2;

void solve() {
  int n, q;
  cin >> n >> raw >> q;
  s1 = raw.substr(0, n);
  s2 = raw.substr(n, 2 * n);
  string * ptr[2];
  ptr[0] = &s1;
  ptr[1] = &s2;
  int a, b, t;
  while (q--) {
    cin >> t >> a >> b;
    if (t == 2) swap(ptr[0], ptr[1]);
    else {
      --a, --b;
      char tmp = (*ptr[a / n])[a % n];
      (*ptr[a / n])[a % n] = (*ptr[b / n])[b % n];
      (*ptr[b / n])[b % n] = tmp;
    }
  }
  cout << *ptr[0] << *ptr[1] << endl;
}

int main() {
  int T = 1;
  // cin >> T;
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