#include <algorithm>
#include <cstdio>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;
#define FILEIO(X) freopen(x".in", "r", stdin); freopen(x".out", "w", stdout);
template<typename T>
void chkmax(T& a, const T& b) {
  a = max(a, b);
}
template<typename T>
void chkmin(T& a, const T& b) {
  a = min(a, b);
}
#define MX 400005
uint16_t jmp[128];
typedef unsigned long long ull;
const int N = 400000;
uint16_t d[N][16];
uint64_t opt[N][4];

void print(uint16_t *v) {
  for (int i = 0; i < 16; ++i) {
    for (int j = 0; j < 16; ++j) {
      cout << ((v[i] >> j) & 1);
    }
  }
  cout << endl;
}

ull myRand(ull &k1, ull &k2) {
    ull k3 = k1, k4 = k2;
    k1 = k4;
    k3 ^= (k3 << 23);
    k2 = k3 ^ k4 ^ (k3 >> 17) ^ (k4 >> 26);
    return k2 + k4;
}

void gen(int n, ull a1, ull a2) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < 256; j++)
            d[i][j >> 4] |= ((myRand(a1, a2) & (1ull << 32)) ? 1 : 0) << (j & 15);
}
int n, m;
uint16_t last = 0;
ull a1, a2;
char str[100];
uint16_t t[16];
uint64_t tt[4];

vector<int> tab[16][1 << 16];

void solve() {
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < 16; ++j) {
      tab[j][d[i][j]].push_back(i);
    }
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < 4; ++j) {
      opt[i][j] = (uint64_t)d[i][(j << 2)] | ((uint64_t)d[i][(j << 2) + 1] << 16) | ((uint64_t)d[i][(j << 2) + 2] << 32) | ((uint64_t)d[i][(j << 2) + 3] << 48);
    }
  }
  int k;
  for (int i = 0; i < m; ++i) {
    cin >> str >> k;
    memset(t, 0, sizeof(t));
    for (int p = 0; p < 64; ++p) {
      t[p >> 2] |= (jmp[str[p]] ^ last) << ((p & 3) << 2);
    }
    for (int j = 0; j < 4; ++j) {
      tt[j] = (uint64_t)t[(j << 2)] | ((uint64_t)t[(j << 2) + 1] << 16) | ((uint64_t)t[(j << 2) + 2] << 32) | ((uint64_t)t[(j << 2) + 3] << 48);
    }
    int pop = 60;
    for (int id = 0; id < 16; ++id) {
      for (auto cur : tab[id][t[id]]) {
        int ans = 0;
        for (int p = 0; p < 4; ++p) {
          ans += __builtin_popcountll(tt[p] ^ opt[cur][p]);
        }
        chkmin(pop, ans);
      }
    }
    if (pop > k) {
      cout << "0\n", last = 0;
    } else cout << "1\n", last = 15;
  }
}


int main() {
  //freopen("qi.in", "r", stdin);
  //freopen("qi.out", "w", stdout);
  cin.tie(0);
  ios::sync_with_stdio(0);
  jmp['0'] = 0;
  jmp['1'] = 0b1000;
  jmp['2'] = 0b0100;
  jmp['3'] = 0b1100;
  jmp['4'] = 0b0010;
  jmp['5'] = 0b1010;
  jmp['6'] = 0b0110;
  jmp['7'] = 0b1110;
  jmp['8'] = 0b0001;
  jmp['9'] = 0b1001;
  jmp['A'] = 0b0101;
  jmp['B'] = 0b1101;
  jmp['C'] = 0b0011;
  jmp['D'] = 0b1011;
  jmp['E'] = 0b0111;
  jmp['F'] = 0b1111;
  cin >> n >> m >> a1 >> a2;
  gen(n, a1, a2);
  solve();
  return 0;
}
