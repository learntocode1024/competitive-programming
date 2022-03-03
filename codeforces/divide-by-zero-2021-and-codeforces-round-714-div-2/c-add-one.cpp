// Original Author: misaka18931
// Date: 04-10-21
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

LL cnt[10];

LL Q_pow(LL a, LL b) {
  LL ans = 1;
  while (b) {
    if (b & 1) ans = ans * a % mod;
    a = a * a % mod;
    b >>= 1;
  }
  return ans;
}

void solve() {
  for (int i = 0; i < 10; ++i)
    cnt[i] = 0;
  string n;
  int m;
  cin >> n >> m;
  for (auto i : n)
    ++cnt[i - '0'];
  LL q = m / 10;
  LL r = m % 10;
  while (r--) {
    LL tmp = cnt[9] % mod;
    for (int i = 9; i; --i)
      cnt[i] = cnt[i - 1];
    cnt[0] = tmp;
    cnt[1] = (cnt[1] + tmp) % mod;
  }
  LL ans = 0;
  for (int i = 0; i < 10; ++i)
    ans += cnt[i];
  ans = ans * Q_pow(2, q) % mod;
  cout << ans << endl;
}

void solve0() {
  for (int i = 0; i < 10; ++i)
    cnt[i] = 0;
  string n;
  int m;
  cin >> n >> m;
  for (auto i : n)
    ++cnt[i - '0'];
  LL ans = n.size();
  while (m--) {
    ans = (ans + cnt[9]) % mod;
    LL tmp = cnt[9] % mod;
    for (int i = 9; i; --i)
      cnt[i] = cnt[i - 1];
    cnt[0] = tmp;
    cnt[1] = (cnt[1] + tmp) % mod;
  }
  cout << ans << endl;
}

int main() {
  cin.tie(NULL);
  std::ios::sync_with_stdio(false);
  int T = 1;
  cin >> T;
  while (T--) {
    solve0();
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