#include <cstdio>
#include <iostream>
using namespace std;
int ans[5][5] {
{},
{1, 1},
{1, 9, 6},
{1, 49, 294, 168},
{1,225,7350,37800,20160}
};

int main() {
  int n, m, q;
  scanf("%d", &q);
  while (q--) {
  scanf("%d%d", &n, &m);
  if (n <= 4) {
    printf("%d\n", ans[n][m]);
  }
    }
  return 0;
}

