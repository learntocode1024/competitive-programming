#include <algorithm>
#include <cstdio>
using namespace std;

long long x, a, b, p;
long long perm[100005];
int n;
long long RAND() {
    x = ((__int128)x * a + b) % p;
    return x;
}
void Main() {
    for (int i = 1; i <= n; i++) {//RANDom shuffle [1, 2,..., n]
        perm[i] = i;
        swap(perm[i], perm[RAND() % i + 1]);
    }
}

long long A[100005];

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
   scanf("%lld", A + i);
  }
  scanf("%lld%lld%lld", &a, &b, &p);
  for (int x = 0; x < p; ++x) {
    ::x = x;
    Main();
    int f = 1;
    for (int i = 1; i <= n; ++i) {
      if (A[i] != perm[i]) f = 0;
      break;
    }
    if (f == 1) {
      printf("%d", x);
      exit(0);
    }
  }
}
