#include "utils"
#include "io"
#include "modint"
#include "poly"

const int N = 200005;
int a[N];

vector<mint> reduce(int l, int r, vector<mint> dn) {
  int _w = r - l;
  int _h = a[r];
  if (l > 0) _h -= a[l - 1];
  if (_w == 1)
    return vector<mint>(_h, dn[0]);
  int mid = l + (r - l) / 2;
  vector<mint> ldn;
  for (int i = 0; i < mid - l; ++i)
    ldn.push_back(dn[i]);
  auto lt = reduce(l, mid, ldn);
  for () {
    
  }
}

void solve() {
  int n = rd();
  for (int i = 0; i < n; ++i) a[i] = rd();
  auto ans = reduce(0, n, vector<mint>(n, mint(1)));
  mint out(0);
  for (auto i : ans)
    out += ans;
  cout << out << '\n';
}

int main() {
  IO::init_in();
  int T = rd();
  solve();
  return 0;
}