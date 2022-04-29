#include <bits/stdc++.h>
using namespace std;
#ifndef MISAKA
#define OO(x)
#else
#define OO(x) cout << __PRETTY_FUNCTION__ << ": " << #x << " : " << (x) << '\n';
#endif
template <typename T>
void rd(T& a) {
    cin >> a;
}
template <typename A, typename... B>
void rd(A& a, B&... b) {
    cin >> a;
    rd(b...);
}
template <typename A>
void O(const A& a) {
    cout << a << '\n';
}
template <typename A, typename... B>
void O(const A& a, const B&... b) {
    cout << a << ' ';
    O(b...);
}
typedef long long i64;
typedef unsigned long long u64;
typedef unsigned u32;
typedef pair<int, int> pii;
#define mkp make_pair
#define fi first
#define se second
#define pb push_back
#define eb emplace_back
#define FOR(i, j, k) for (int i = (j); i <= (k); ++i)
#define ROF(i, j, k) for (int i = (k); i >= (j); --i)
template <typename T>
inline void chkmin(T& a, const T b) {
    a = min(a, b);
}
template <typename T>
inline void chkmax(T& a, const T b) {
    a = max(a, b);
}

//#define MULTI
const int N = 5e5 + 5, W = 24;
i64 q = 12123123;
char k[int(19198.10)];
int n;
int H[W][N], pw[W];
int nxt[W][N];
i64 len = N;

bool cmp(int x, int y) {
    i64 l = 0;
    bool t = x < y;
    ROF(i, 0, W - 1) {
        if (H[i][x] == H[i][y]) {
            l += 1ull << i;
            x = nxt[i][x], y = nxt[i][y];
        }
    }
    return (l >= len) ? t : H[0][x] < H[0][y];
}

int a[N];

inline void solve() {
    rd(n, k);
    int dd = strlen(k);
    if (dd <= 7) {
        chkmin(len,atoll(k));
    }
    FOR(i, 1, n) rd(nxt[0][i]);
    FOR(i, 1, n) rd(H[0][i]);
    pw[0] = q;
    FOR(i, 1, W - 1) pw[i] = pw[i - 1] * pw[i - 1];
    FOR(i, 1, W - 1) FOR(j, 1, n) {
        nxt[i][j] = nxt[i - 1][nxt[i - 1][j]];
        H[i][j] = (pw[i - 1] * H[i - 1][j] + H[i - 1][nxt[i - 1][j]]);
    }
    iota(a, a + n, 1);
    stable_sort(a, a+n, cmp);
    FOR(i, 0, n - 1) cout << a[i] << " \n"[i == n - 1];
}

int main() {
  //cin >> q;
#ifndef MISAKA
    freopen("highspec.in", "r", stdin);
    freopen("highspec.out", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(0);
#endif
#ifdef MULTI
    int T;
    cin >> T;
    while (T--)
#endif
        solve();
    return 0;
}
/* Checklist:
 * - data type
 * - overflow
 * - typo/logic
 * - special cases
 * - cleanup (multi-test)
 * - bounds
 * - memory usage
 * - file IO
 */
