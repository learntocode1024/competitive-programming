// Original Author: misaka18931
// Date: 03-23-21
// tag:
// 

#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long LL;
#define pb(x) push_back(x)
#define pf(x) push_front(x)
#define MX

vector<int> v[2];

int main() {
  cin.tie(NULL);
  std::ios::sync_with_stdio(false);
  int n, m, c;
  cin >> n >> m >> c;
  int siz[2], off[2];
  siz[0] = n / 2;
  siz[1] = n - siz[0];
  off[0] = 1, off[1] = 1 + siz[0];
  for (int i = 0; i < 2; ++i) {
    while (v[i].size() < siz[i]) {
      int a;
      cin >> a;
      auto it = upper_bound(v[i].begin(), v[i].end(), a);
      cout << it - v[i].begin() + off[i] << endl;
      fflush(stdout);
      if (it == v[i].end()) v[i].pb(a);
      else *it = a;
    }
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