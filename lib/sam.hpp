#pragma once

struct sam {
  int len[MX << 1], nxt[26][MX << 1], f[MX << 1];
  int lst, tot;
  void extend(char ch) {
    int cur = ++tot;
    len[cur] = len[lst] + 1;
    sz[cur] = 1;
    int p = lst;
    for (; p != -1 && !nxt[ch][p]; p = f[p]) {
      nxt[ch][p] = cur;
    }
    if (p == -1) {
      f[cur] = 0;
    } else {
      int q = nxt[ch][p];
      if (len[q] == len[p] + 1) {
        f[cur] = q;
      } else {
        int mir = ++tot;
        for (int i = 0; i < 26; ++i) nxt[i][mir] = nxt[i][q];
        len[mir] = len[p] + 1;
        f[mir] = f[q];
        f[q] = f[cur] = mir;
        for (; p != -1 && nxt[ch][p] == q; p = f[p]) {
          nxt[ch][p] = mir;
        }
      }
    }
    lst = cur;
  }
  void init(char *s) {
    f[0] = -1;
    while (*s) extend(*s++ - 'a');
  }
};