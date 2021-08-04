#include <cstdio>
#include <iostream>
using namespace std;

int main() {
  int T;
  cin >> T;
  while (T--) {
    long long n, k, s;
    cin >> n >> k >> s;
    long long tmp = k * (k + 1) / 2;
    if (s < tmp || s > n * k + k - tmp) cout << "No";
    else cout << "Yes";
    cout << endl;
  }
  return 0;
}
