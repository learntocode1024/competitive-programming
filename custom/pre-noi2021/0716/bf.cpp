#include <cstdio>
#include <iostream>
using namespace std;

const int n = 5;

int a[n];

int gauss(int f) {
  for (int t = 0; t < n; ++t) {
    a[t] = (f >> n * t) & ((1 << n) - 1);
  }
  for (int i = 0; i < n; ++i) {
    int f = -1;
    for (int j = 0; j < n && f < 0; ++j)
      if ((a[j] & -a[j]) == 1 << i) f = j;
    for (int j = 0; j < n; ++j) {
      if (a[j] & (1 << i) && j != f) a[j] ^= a[f];
    }
  }
  int ret = 0;
  for (int i = 0; i < n; ++i) {
    ret += a[i] != 0;
  }
  return ret;
}

int cnt[n];
int main() {  
  for (int i = 0; i < 1 << n * n; ++i) {
      cnt[gauss(i)] += 1;
  }
  for (int i = 0; i < n + 1; ++i) {
    cout << cnt[i] << endl;
  }
}
