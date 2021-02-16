#include <algorithm>
#include <climits>
#include <iostream>
#include <string>
#define print(x) cout << (((bool)(x)) ? "Possible" : "Impossible") << endl;
using namespace std;

string s, p;
int match[20][20];

int main() {
  cin >> s >> p;
  if (s.size() < p.size() || (s.size() - p.size()) & 1) {
    print(0) return 0;
  }
  if (s == p) {
    print(1) return 0;
  }
  int offset = s.size() - p.size();
  for (int i = 1; i <= s.size(); ++i) {
    for (int j = 1; j <= p.size(); ++j) {
      match[i][j] = -1000;
    }
  }
  for (int i = 1; i <= p.size(); ++i) {
    for (int j = i; j < min(i + offset, (int)s.size() + 1); ++j) {
      match[j][i] = -1000;
      if (s[j - 1] != p[i - 1]) {
        continue;
      }
      int t = 0;
      for (int k = j - 1; k >= i - 1; --k) {
        int curr = match[k][i - 1] + t;
        if (curr >= 0) match[j][i] = max(match[j][i], curr);
        if (s[k - 1] == ')')
          --t;
        else
          ++t;
      }
      printf("(%d, %d) ", j, i);
      cout << match[j][i] << ' ';
    }
    cout << endl;
  }
  bool ans = 0;
  int t = 0;
  for (int i = s.size(); !ans && i >= p.size(); --i) {
    if (s[i - 1] == *p.rbegin() && match[i][p.size()] == t) ans = 1;
    if (s[i - 1] == ')')
      ++t;
    else
      --t;
  }
  print(ans)
  return 0;
}