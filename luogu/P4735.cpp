#include <algorithm>
#include <iostream>

#include "utils"
#include "io"
const int N = 600005, bitln = 25;
int n, m;

struct trie {
  int ch[N * bitln][2], cnt[N * bitln], rts[N << 1];
  int tot;
  int _n;
  int x;
  int cpy(int p) {
    int ret = ++tot;
    cnt[ret] = cnt[p];
    ch[ret][0] = ch[p][0];
    ch[ret][1] = ch[p][1];
    return ret;
  }
  void insert(int _x) {
    x ^= _x;
    int p = (!_n) ? cpy(0) : cpy(rts[_n - 1]);
    rts[_n] = p;
    ++cnt[p];
    for (int i = bitln - 2; i >= 0; --i) {
      ch[p][(x >> i) & 1] = cpy(ch[p][(x >> i) & 1]);
      p = ch[p][(x >> i) & 1];
      ++cnt[p];
    }
    ++_n;
  }
  int xormax(int _x, int l, int r) {
    int cur = x ^ _x;
    int p = rts[r];
    int q = (!l) ? 0 : rts[l - 1];
    int ret = 0;
    for (int i = bitln - 2; i >= 0; --i) {
      int iv = ((cur >> i) & 1) ^ 1;
      if (ch[p][iv] && (!ch[q][iv] || cnt[ch[p][iv]] > cnt[ch[q][iv]])) {
        p = ch[p][iv];
        q = ch[q][iv];
        ret |= 1 << i;
      } else {
        p = ch[p][iv ^ 1];
        q = ch[q][iv ^ 1];
      }
    }
    return ret;
  }
} T;

char s[100];

int main() {
  IO::init_in();
  n = rd(), m = rd();
  T.insert(0);
  FOR(i, 0, n) T.insert(rd());
  FOR(i, 0, m) {
    rdstr(s);
    if (s[0] == 'A') {
      T.insert(rd());
    } else {
    int l = rd() - 1, r = rd() - 1, x = rd();
    cout << T.xormax(x, l, r) << '\n';
    }
  }
}