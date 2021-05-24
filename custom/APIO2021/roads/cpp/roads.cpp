#include "roads.h"

#include <vector>
#include <algorithm>
using namespace std;
// s1
/*
std::vector<long long> minimum_closure_costs(int N, std::vector<int> U,
                                             std::vector<int> V,
                                             std::vector<int> W) {
  sort(W.begin(), W.end());
  std::vector<long long> ret(N, 0);
  for (int k = N - 2; k >= 0; --k) {
    ret[k] = ret[k + 1] + W[N - 2 - k];
  }
  return ret;
}

*/
// s2
std::vector<long long> minimum_closure_costs(int N, std::vector<int> U,
                                             std::vector<int> V,
                                             std::vector<int> W) {
  std::vector<long long> ret(N, 0);
  long long s, v, t;
  for (int i = 0; i < N - 1; ++i) {
    s += W[i];
    if (i & 1)
      v += W[i];
    else
      t += W[i];
  }
  ret[0] = s;
  ret[1] = min(v, t);
  return ret;
}
/*
// s5
int deg[100005];
std::vector<long long> minimum_closure_costs(int N, std::vector<int> U,
                                             std::vector<int> V,
                                             std::vector<int> W) {
  std::vector<long long> ret(N, 0);
  return ret;
}
/
std::vector<long long> minimum_closure_costs(int N, std::vector<int> U,
                                             std::vector<int> V,
                                             std::vector<int> W) {
  std::vector<long long> ret(N, 0);
  return ret;
}
*/