#pragma once

#include <vector>
#include <limits>

template<typename T>
class diff_constraints {
  std::vector<std::vector<std::pair<int, T> > > g;
  std::vector<T> d;
  int n;
public:
  diff_constraints(int _n) : g(_n + 1), n(_n), d(_n + 1, std::numeric_limits<T>::max()) {};
  void add_edge(int u, int v, T c) {
    g[v + 1].emplace_back(u + 1, c);
  }
  std::pair<std::vector<T>, bool> solve() {
    for (int i = 1; i <= n; ++i) {
      g[0].emplace_back(i, 0);
    }
    d[0] = 0;
    bool flag = 0;
    for (int i = 0; i <= n; ++i) {
      flag = 0;
      for (int u = 0; u <= n; ++u) {
        for (auto v : g[u]) {
          if (d[v.first] > d[u] + v.second) {
            d[v.first] = d[u] + v.second;
            flag = 1;
          }
        }
      }
    }
    if (flag) return {{}, 0};
    std::vector<T> out;
    for (int i = 1; i <= n; ++i) out.push_back(d[i] == std::numeric_limits<T>::max() ? 0 : d[i]);
    return {out, 1};
  }
};