#include <complex>
#include <vector>
#include <iostream>
#include <cmath>
#define PI 3.14159265358979323846264338328l
#define ROUND_2_INT(f) ((int)(f >= 0.0 ? (f + 0.5) : (f - 0.5)))
using namespace std;
#define TEST

typedef complex<double> comp;
vector<unsigned> inv;
void inverse(comp* const y, unsigned len) {
  inv.push_back(0);
  for (unsigned i = 1; i < len; ++i) {
    inv.push_back(inv[i / 2] / 2 + (i & 1) * len / 2);
  }
  for (unsigned i = 0; i < len; ++i) {
    if (i < inv[i]) swap(y[i], y[inv[i]]);
  }
  inv.clear();
}

void fft_base(comp* const y, unsigned len, int op) {
  inverse(y, len);
  for (unsigned step = 2; step <= len; step <<= 1) {
    comp wn(cos(2 * PI / step), sin(op * 2 * PI / step));
    for (unsigned beg = 0; beg < len; beg = beg + step) {
      comp w(1, 0);
      for (unsigned i = beg; i < beg + step / 2; ++i) {
        comp p = y[i];
        comp t = w * y[i + step / 2];
        y[i] = p + t;
        y[i + step / 2] = p - t;
        w = w * wn;
      }
    }
  }
}

void fft(comp *const y, unsigned len) { return fft_base(y, len, 1); }

void idft(comp *const y, unsigned len) {
  fft_base(y, len, -1);
  for (int i = 0; i < len; ++i) {
    y[i] /= len;
  }
}

#ifdef TEST
comp a[1048576], b[1048576];
string sa, sb;
inline void to_comp(comp *const y, string& s) {
  for (int i = s.size() - 1; i >= 0; --i) {
    y[s.size() - i - 1] = s[i] - '0';
  }
}
int main() {
  cin >> sa >> sb;
  to_comp(a, sa);
  to_comp(b, sb);
  fft(a, 1048576);
  fft(b, 1048576);
  for (int i = 0; i < 1048576; ++i) {
    a[i] *= b[i];
  }
  idft(a, 1048576);
  int reg = 0;
  string ans;
  for (int i = 0; i < 1048576; ++i) {
    if (i > sa.size() + sb.size() && reg + ROUND_2_INT(a[i].real()) == 0) break;
    ans.push_back((reg + ROUND_2_INT(a[i].real())) % 10 + '0');
    reg = (reg + ROUND_2_INT(a[i].real())) / 10;
  }
  int i = ans.size() - 1;
  while (ans[i] == '0') --i;
  if (reg > 0)  cout << reg;
  for (; i >= 0; --i) cout << ans[i];
  cout << endl;
  return 0;
}
#endif