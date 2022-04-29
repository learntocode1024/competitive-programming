#include <stdlib.h>
#include <string.h>
#include "save.h"
using namespace std;

namespace {
const int N = 4e4+5;
int ch[N][2];
int f[N];
vector<int> g[N];
int s[N];
string ans;
void dfs(int u) {
  if (u == -1) return;
  ans += "0";
  for (u = ch[u][0]; u != -1; u = ch[u][1]) dfs(u);
  ans += "1";
}
}

void read_array(int subtask_id, const std::vector<int> &v) {
  int tl = 0;
  const int n = v.size();
  for (int i = 0; i < n; ++i) ch[i][0] = ch[i][1] = -1;
  for (int i = 0; i < n; ++i) {
    int lst = tl;
    while (tl && v[s[tl]] < v[i]) --tl;
    if (tl) ch[s[tl]][1] = i;
    if (tl < lst) ch[i][0] = s[tl+1];
    s[++tl] = i;
  }
  for (int i = s[1]; i != -1; i = ch[i][1]) dfs(i);
  // cerr << "save.cpp: " << ans << '\n';
  save_to_floppy(ans);
}
