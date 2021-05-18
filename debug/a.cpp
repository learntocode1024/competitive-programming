#include <iostream>
#include <vector>
using namespace std;
vector<int> vis, tmp;
int n, m;

int a[105], b[105];

bool check(int k) {
    vis = vector<int>(m + 1, -1);
    tmp = vector<int>(m + 1, -1);
    vis[0] = 0;
    for (int i = 0; i < n; ++i) {
        tmp = vis;
        for (int j = 0; j <= m; ++j) {
            if (vis[j] == -1) continue;
            int x = j, y = vis[j];
            for (int dx = 0; dx < min(m - x, k / a[i]) + 1; ++dx) {
                tmp[x + dx] = max(tmp[x + dx], y + (int) ((k - a[i] * dx) / b[i]));
            }
        }
        vis = tmp;
    }
    return vis[m] >= m;
}

int32_t main() {
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        cin >> a[i] >> b[i];
    }
    int l = 1, r = 1000005;
    while (l < r) {
        int mid = l + (r - l) / 2;
        if (check(mid)) r = mid;
        else l = mid + 1;
    }
    cout << l << endl;
    return 0;
}