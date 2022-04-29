#include <bits/stdc++.h>
using namespace std;
char s[114514], t[114514];
vector<int> a, b;

void solve() {
    int n;
    a.clear();
    b.clear();
    cin >> n;
    long long s = 0;
    for (int i = 0; i < 30; ++i) {
        cout << (1 << i) << ' ';
        s += 1 << i;
    }
    cerr << s << '\n';
    const int mt = 1 << 29;
    for (int i = 30; i < n; ++i) {
        cout << mt + i << " \n"[i==n-1];
        s += mt+i;
        a.push_back(mt+i);
    }
    fflush(stdout);
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        s += x;
        a.push_back(x);
    }
    s >>= 1;
    for (auto x : a) {
        if (s >= x) {
            s -= x;
            b.push_back(x);
        }
    }
    while (s) {
        int lb = s & -s;
        b.push_back(lb);
        s -= lb;
    }
    for (int i = 0; i < b.size(); ++i) {
      cout << b[i] << " \n"[i==b.size()-1];
    }
    fflush(stdout);
}

int main() {
    int T;
    cin >> T;
    for (int i = 1; i <= T; ++i) {
        // cout << "Case #" << i << ": ";
        solve();
    }
}
