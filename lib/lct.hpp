// lct template for reference
#pragma once

#include <algorithm>
using std::swap;

/**********************************************************************************************************
 * LCT template interface:
 *   const int N: maximum size of forest
 *   class attr:  extra attributes & lazy tags to be maintained
 *     bool attr::active(): whether the lazy tag has effect or not.
 *     void attr::reset(): reset lazy tag to be inactive.
 *     void attr::apply(): push lazy tags to current node.
 *     void attr::merge(const attr&, const attr&): merge attributes of current node and it's childrens.
 *********************************************************************************************************/

template<int N, class attr>
struct LCT {
  struct node {
    int ch[2], f;
    bool flp;
    attr var;// extra attributes & tags here
    inline void _flp() {
      swap(ch[0], ch[1]), flp ^= 1;
    }
  } a[N];
#define lc(p) a[p].ch[0]
#define rc(p) a[p].ch[1]
#define f(p) a[p].f
  inline bool typ(int p) {
    return p == rc(f(p));
  }
  inline bool isroot(int p) { // chk root of splay
    return !(lc(f(p)) == p || rc(f(p)) == p);
  }
  inline void up(int p) {
    a[p].var.merge(a[lc(p)].var, a[rc(p)].var); // maintain extra attributes
  }
  inline void down(int p) {
    if (a[p].flp) {
      if (lc(p)) a[lc(p)]._flp();
      if (rc(p)) a[rc(p)]._flp();
      a[p].flp = 0;
    }
    if (!a[p].var.active()) {
      if (lc(p)) a[lc(p)].var.apply(a[p].var);
      if (rc(p)) a[rc(p)].var.apply(a[p].var);
      a[p].var.reset();
    } // maintain extra tags
  }
  void upd(int p) { // clean tags along the path
    if (!isroot(p)) upd(f(p));
    down(p);
  }
  inline void rotate(int x) { // modified splay rotate
    int o = typ(x), y = f(x), z = f(y);
    if (!isroot(y)) {
      a[z].ch[typ(y)] = x;
    }
    a[a[x].ch[o^1]].f = y;
    a[y].ch[o] = a[x].ch[o^1];
    a[x].ch[o^1] = y;
    a[y].f = x;
    a[x].f = z;
    up(y);
    up(x);
  }
  inline void splay(int p) {
    upd(p);
    for (int x; !isroot(p); rotate(p)) {
      x = f(p);
      if (!isroot(x)) rotate((typ(p) == typ(x)) ? x : p);
    }
  }
  inline int access(int p) { // make a splay out of path root -> p
    int lst = 0;
    for (; p; lst = p, p = f(p)) {
      splay(p);
      a[p].ch[1] = lst;
      up(p);
    }
    return lst;
  }
  inline int getrt(int p) { // root of real tree (will also access(p))
    p = access(p);
    while (lc(p)) p = lc(p);
    splay(p);
    return p;
  }
  inline void setrt(int p) { // make p the root of it's component
    p = access(p);
    a[p]._flp();
  }
  inline void link(int u, int v) {
    setrt(u);
    if (getrt(v) != u) {
      splay(u);
      f(u) = v;
    }
  }
  inline void cut(int u, int v) {
    setrt(u);
    if (getrt(v) == u && f(v) == u && lc(v) == 0) {
      f(v) = rc(u) = 0;
      up(u);
    }
  }
  inline void path(int u, int v) { // make a splay out of path u -> v, and set v as the root of it.
    setrt(u);
    access(v);
    splay(v); // cost amortized
  }
};

