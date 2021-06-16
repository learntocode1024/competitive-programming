#include <algorithm>
#include <cctype>
#include <climits>
#include <iostream>
using namespace std;
typedef int64_t LL;
const int64_t MOD = 998244353ll;

typedef unsigned int uint;
typedef long long unsigned int uint64;
struct IO_Tp {
  const static int _I_Buffer_Size = 11 << 20;
  char _I_Buffer[_I_Buffer_Size], *_I_pos = _I_Buffer;

  const static int _O_Buffer_Size = 11 << 20;
  char _O_Buffer[_O_Buffer_Size], *_O_pos = _O_Buffer;

  uint m[10000], n[0x10000];

  IO_Tp() {
    {
      constexpr uint e0 = '\0\0\0\1', e1 = '\0\0\1\0', e2 = '\0\1\0\0', e3 = '\1\0\0\0';
      int x = 0;
      for (uint i = 0, c0 = '0000'; i != 10; ++i, c0 += e0)
        for (uint j = 0, c1 = c0; j != 10; ++j, c1 += e1)
          for (uint k = 0, c2 = c1; k != 10; ++k, c2 += e2)
            for (uint l = 0, c3 = c2; l != 10; ++l, c3 += e3) m[x++] = c3;
    }
    {
      for (int i = 0; i != 0x10000; ++i) n[i] = -1;
      constexpr uint e0 = '\0\1', e1 = '\1\0';
      int x = 0;
      for (uint i = 0, c0 = '00'; i != 10; ++i, c0 += e0)
        for (uint j = 0, c1 = c0; j != 10; ++j, c1 += e1) n[c1] = x++;
    }

    fread(_I_Buffer, 1, _I_Buffer_Size, stdin);
  }
  ~IO_Tp() {
    fwrite(_O_Buffer, 1, _O_pos - _O_Buffer, stdout);
  }

  IO_Tp &operator>>(int &res) {
    while (!isdigit(*_I_pos)) ++_I_pos;
    res = *_I_pos++ - '0';
    while (~n[*reinterpret_cast<std::uint16_t *&>(_I_pos)])
      res = res * 100 + n[*reinterpret_cast<std::uint16_t *&>(_I_pos)++];
    if (isdigit(*_I_pos)) res = res * 10 + (*_I_pos++ - '0');
    return *this;
  }

  IO_Tp &operator>>(uint &res) {
    while (!isdigit(*_I_pos)) ++_I_pos;
    res = *_I_pos++ - '0';
    while (~n[*reinterpret_cast<std::uint16_t *&>(_I_pos)])
      res = res * 100 + n[*reinterpret_cast<std::uint16_t *&>(_I_pos)++];
    if (isdigit(*_I_pos)) res = res * 10 + (*_I_pos++ - '0');
    return *this;
  }

  IO_Tp &get_digit(int &res) {
    while (!isdigit(*_I_pos)) ++_I_pos;
    res = *_I_pos++ - '0';
    return *this;
  }

  IO_Tp &get_digit(uint &res) {
    while (!isdigit(*_I_pos)) ++_I_pos;
    res = *_I_pos++ - '0';
    return *this;
  }

  IO_Tp &operator<<(uint x) {
    switch (x) {
    default:
      *reinterpret_cast<std::uint32_t *&>(_O_pos)++ = m[x / 1000000], x %= 1000000;
    case 100000 ... 999999:
      *reinterpret_cast<std::uint32_t *&>(_O_pos)++ = m[x / 100], x %= 100;
    case 10 ... 99:
      *reinterpret_cast<std::uint32_t *&>(_O_pos) = m[x * 100], _O_pos += 2;
      break;
    case 100000000 ... 999999999:
      *reinterpret_cast<std::uint32_t *&>(_O_pos)++ = m[x / 100000], x %= 100000;
    case 10000 ... 99999:
      *reinterpret_cast<std::uint32_t *&>(_O_pos)++ = m[x / 10], x %= 10;
    case 0 ... 9:
      *_O_pos++ = '0' | x;
      break;
    case 10000000 ... 99999999:
      *reinterpret_cast<std::uint32_t *&>(_O_pos)++ = m[x / 10000], x %= 10000;
    case 1000 ... 9999:
      *reinterpret_cast<std::uint32_t *&>(_O_pos)++ = m[x];
      break;
    case 1000000 ... 9999999:
      *reinterpret_cast<std::uint32_t *&>(_O_pos)++ = m[x / 1000], x %= 1000;
    case 100 ... 999:
      *reinterpret_cast<std::uint32_t *&>(_O_pos) = m[x * 10], _O_pos += 3;
      break;
    }
    return *this;
  }

  IO_Tp &operator<<(char ch) {
    *_O_pos++ = ch;
    return *this;
  }
} IO;
int64_t Q_pow(LL a, LL x) {
    LL ret(1);

    while (x) {
        if (x & 1)
            ret = ret * a % MOD;

        a = a * a % MOD;
        x >>= 1;
    }

    return ret;
}

namespace DFT {
const int max_len = 1 << 20;
int bit_inv[max_len];
LL gn[max_len];

void prework() {
    gn[1] = Q_pow(3, (MOD - 1) / max_len);

    for (int i = 2; i < max_len; ++i)
        gn[i] = gn[i - 1] * gn[1] % MOD;
}

void DFT(int64_t *a, const int len, const int opt) {
    for (int i = 1; i < len; ++i) {
        bit_inv[i] = bit_inv[i >> 1] >> 1;

        if (i & 1)
            bit_inv[i] |= len >> 1;

        if (bit_inv[i] > i)
            swap(a[i], a[bit_inv[i]]);
    }

    for (int n = 1; n < len; n <<= 1) {
        LL g0 = gn[max_len / n / 2];

        if (opt == -1)
            g0 = gn[max_len - max_len / n / 2];

        for (int i = 0; i < len; i += n * 2) {
            LL g = 1;

            for (int j = i; j < i + n; ++j) {
                LL x = a[j], y = g * a[j + n] % MOD;
                a[j] = (x + y) % MOD;
                a[j + n] = (MOD + x - y) % MOD;
                g = g * g0 % MOD;
            }
        }
    }

    if (opt == -1) {
        LL t = Q_pow(len, MOD - 2);

        for (int i = 0; i < len; ++i) {
            a[i] = a[i] * t % MOD;
        }
    }
}
}

LL a[1 << 20], b[1 << 20];

int main() {
    int n, m;
    IO >> n >> m;
    ++n, ++m;
    int t = max(n, m);

    for (int i = 0; i < n; ++i)
        cin >> a[i];

    for (int i = 0; i < m; ++i)
        cin >> b[i];

    /* DFT::prework(); */
  DFT::DFT(a, 1 << 20, 1);
  DFT::DFT(b, 1 << 20, 1);

    for (int i = 0; i < (1 << 20); ++i) {
        a[i] = a[i] * b[i] % MOD;
    }

  DFT::DFT(a, 1 << 20, -1);

    /* for (int i = 0; i < n + m - 1; ++i) { */
    /*     IO << a[i] << ' '; */
    /* } */

    return 0;
}
