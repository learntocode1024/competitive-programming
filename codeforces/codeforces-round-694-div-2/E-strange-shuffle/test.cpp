#include <iostream>
using namespace std;
int n = 5;
int k = 10;
int id = 12;
int T = 100;

int a[100], tmp[100];
void out(int t) {
  
  for (int i = 1; i <= n; ++i) {
    cout << a[i] << " ";
  }
  cout << "   T=" << t;
  cout << endl;
}

int main() {
  cin >> n >> k >> T;
  for (int i = 1; i <= n; ++i) {
    a[i] = k;
  }
  int t = 0;
  out(t);
  while (T--) {
    ++t;
    for (int i = 0; i < n + 10; ++i) {
      tmp[i] = 0;
    }
    for (int i = 1; i <= n; ++i) {
      if (i != id)
        tmp[i - 1] += a[i] / 2, tmp[i + 1] +=a[i] - a[i] / 2;
      else tmp[i + 1] += a[i];
    }
    for (int i = 1; i <= n; ++i) {
      a[i] = tmp[i];
    }
    a[1] += tmp[n + 1];
    a[n] += tmp[0];
    out(t);
    // system("sleep 0.5");
  }
  return 0;
}