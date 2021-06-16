#include <algorithm>
#include <cctype>
#include <climits>
#include <iostream>
using namespace std;
typedef long long ll;

struct seg {
  ll c = 0;
  ll l = -1;
  ll r = -1;
} spc[1 << 24];
int rts[100005];

int freed[1 << 24], tot_freed = -1, tot_all;
inline int get() {
  if (tot_freed >= 0) return freed[tot_freed--];
  return tot_all++;
}

inline void clear(int id) {
  spc[id].c = 0;
  spc[id].l = -1;
  spc[id].r = -1;
  freed[++tot_freed] = id;
}

int n;
void strip(int &p, int &q, int l, int r, int s, int t) {
  if (l == s && r == t) {
    q = p;
    p = -1;
    return;
  }
  
}
void merge(int &p, int &q, int l, int r);
int kth(int p, int l, int r, int k);
int grep(int p, int l, int r, int s, int t);
