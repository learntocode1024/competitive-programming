#include <algorithm>
#include <cctype>
#include <climits>
#include <iostream>
using namespace std;
typedef long long ll;

struct seg {
  ll c = 0;
  int l = 0;
  int r = 0;
} a[1 << 22];
int rts[100005], tot_roots = 1;

int freed[1 << 22], tot_freed = -1, tot_all;
inline int New() {
  if (tot_freed >= 0)
    return freed[tot_freed--];
  return ++tot_all;
}

inline void Delete(int &id) {
  a[id].c = 0;
  a[id].l = 0;
  a[id].r = 0;
  freed[++tot_freed] = id;
  id = 0;
}

inline void pushup(int p) { a[p].c = a[a[p].l].c + a[a[p].r].c; }

void strip(int &p, int &q, int l, int r, int s, int t) {
  if (p == 0)
    return;
  if (l == s && r == t) {
    q = p;
    p = 0;
    return;
  }
  int mid = l + (r - l) / 2;
  if (q == 0)
    q = New();
  if (s < mid)
    strip(a[p].l, a[q].l, l, mid, s, min(t, mid));
  if (t > mid)
    strip(a[p].r, a[q].r, mid, r, max(s, mid), t);
  pushup(p);
  pushup(q);
}

void merge(int &q, int &p) {
  if (q == 0)
    return;
  if (p == 0) {
    p = q;
    return;
  }
  a[p].c += a[q].c;
  merge(a[q].l, a[p].l);
  merge(a[q].r, a[p].r);
  Delete(q);
}

void insert(int &p, int l, int r, int pos, ll k) {
  if (p == 0)
    p = New();
  if (r - l == 1) {
    a[p].c += k;
    return;
  }
  int mid = l + (r - l) / 2;
  if (pos < mid)
    insert(a[p].l, l, mid, pos, k);
  else
    insert(a[p].r, mid, r, pos, k);
  pushup(p);
}

// explict validation of k required
int kth(int p, int l, int r, ll k) {
  if (r - l == 1)
    return l;
  int mid = l + (r - l) / 2;
  if (k <= a[a[p].l].c)
    return kth(a[p].l, l, mid, k);
  else
    return kth(a[p].r, mid, r, k - a[a[p].l].c);
}

ll count(int p, int l, int r, int s, int t) {
  if (l == s && r == t) {
    return a[p].c;
  }
  int mid = l + (r - l) / 2;
  ll ret = 0;
  if (s < mid)
    ret += count(a[p].l, l, mid, s, min(t, mid));
  if (t > mid)
    ret += count(a[p].r, mid, r, max(s, mid), t);
  return ret;
}

int n, m;

int fa[100005], id[100005];

int get(int x) {
  if (x == fa[x])
    return x;
  fa[x] = get(fa[x]);
  return fa[x];
}

inline void concat(int x, int y) {
  if (get(x) == get(y))
    return;
  merge(rts[get(y)], rts[get(x)]);
  fa[get(y)] = get(x);
}

int main() {
  cin >> n >> m;
  for (int i = 0; i < n; ++i) {
    int tmp;
    cin >> tmp;
    fa[i + 1] = i + 1;
    id[tmp - 1] = i + 1;
    insert(rts[i + 1], 0, n, tmp - 1, 1);
  }
  for (int i = 0; i < m; ++i) {
    int x, y;
    cin >> x >> y;
    concat(x, y);
  }
  cin >> m;
  string op;
  int x, y;
  while (m--) {
    cin >> op >> x >> y;
    if(op == "B")
      concat(x, y);
    else {
      if (y > a[rts[get(x)]].c)
        cout << -1 << endl;
      else
        cout << id[kth(rts[get(x)], 0, n, y)] << endl;
    }
  }
  return 0;
}
