#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

namespace IO {
    const int MAXR = 1000000;
    char _READ_[MAXR], _PRINT_[MAXR];
    int _READ_POS_, _PRINT_POS_, _READ_LEN_;
    inline char readc() {
        if (!_READ_POS_) {
            if (feof(stdin)) return -1;
            _READ_LEN_ = fread(_READ_, 1, MAXR, stdin);
        }
        char c = _READ_[_READ_POS_++];
        if (_READ_POS_ == _READ_LEN_) _READ_POS_ = 0;
        return c;
    }
    template<typename T> inline int read(T &x) {
        x = 0; register int flag = 1, c;
        while (((c = readc()) < '0' || c > '9') && c != '-')
            if (c < 0) return -1;
        if (c == '-') flag = -1; else x = c - '0';
        while ((c = readc()) >= '0' && c <= '9') x = x * 10 - '0' + c;
        x *= flag; return 0;
    }
    inline int read(char *s) {
        register int len = 0, c;
        while (isspace(c = readc()) || c <= 0)
            if (c < 0) return -1;
        s[len++] = c;
        while (!isspace(c = readc()) && c) s[len++] = c;
        s[len] = 0;
        return len;
    }
    template<typename T1, typename ...T2> inline int read(T1 &a, T2&... x) {
        return read(a) | read(x...);
    }
}

const int MAXN = 2000005, MOD = 998244353;
LL modpow(LL a, int b) {
	LL res = 1;
	for (; b; b >>= 1) {
		if (b & 1) res = res * a % MOD;
		a = a * a % MOD;
	}
	return res;
}
struct Edge { int v, p, next; } edge[MAXN << 1];
int head[MAXN], dep[MAXN], wson[MAXN], g[MAXN], n, da, db, tot;
int f[MAXN], beg[MAXN], val[MAXN], inv[MAXN], pre1[MAXN], pre2[MAXN];
void add_edge(int u, int v, int p) {
	edge[++tot] = Edge { v, p, head[u] };
	head[u] = tot;
}

void dfs1(int u, int fa) {
	for (int i = head[u]; i; i = edge[i].next) {
		int v = edge[i].v;
		if (v == fa) continue;
		dfs1(v, u);
		if (dep[v] + 1 > dep[u]) {
			wson[u] = v;
			dep[u] = dep[v] + 1;
			val[v] = edge[i].p;
		}
	}
}

struct Num {
	int c0, v, w;
	void init() { c0 = 0, v = w = 1; }
	Num() { c0 = 0, v = w = 1; }
	Num(int p, int q) {
		if (p == 0) c0 = v = w = 1;
		else c0 = 0, v = p, w = q;
	}
	Num(int a, int b, int c) { c0 = a, v = b, w = c; }
	int get() const { return c0 > 0 ? 0 : v; }
	Num& operator*=(const Num &b) {
		c0 += b.c0;
		v = (LL)v * b.v % MOD;
		w = (LL)w * b.w % MOD;
		return *this;
	}
	int operator*(int b) const {
		return c0 > 0 ? 0 : (LL)b * v % MOD;
	}
	Num get_inv() const {
		return Num(-c0, w, v);
	}
} tag[MAXN];

void dfs2(int u, int fa) {
	int ed = min(dep[u], db);
	if (wson[u]) {
		int v = wson[u], p = val[v];
		int q = (1 + MOD - p) % MOD;
		beg[v] = ++tot;
		dfs2(v, u);
		g[u] = g[v];
		if (dep[v] >= db) {
			f[beg[u] + db + 1] = tag[beg[u] + db + 1] * f[beg[u] + db + 1];
			tag[beg[u] + db] *= tag[beg[u] + db + 1];
			g[u] = (g[u] + MOD - f[beg[u] + db + 1]) % MOD;
		}
		g[u] = (LL)g[u] * q % MOD;
		tag[beg[u] + ed] *= Num(q, inv[v]);
		tag[beg[u]] *= Num(inv[v], q);
		f[beg[u]] = (LL)p * g[v] % MOD;
		g[u] = (g[u] + f[beg[u]]) % MOD;
	} else f[beg[u]] = g[u] = 1;
	for (int i = head[u]; i; i = edge[i].next) {
		int v = edge[i].v, p = edge[i].p;
		if (v == fa || v == wson[u]) continue;
		beg[v] = ++tot;
		dfs2(v, u);
		int edv = min(dep[v], db), edv1 = min(dep[v], db - 1), sum = (LL)g[v] * p % MOD;
		for (int j = edv; j > 0; j--) {
			f[beg[v] + j] = tag[beg[v] + j] * f[beg[v] + j];
			tag[beg[v] + j - 1] *= tag[beg[v] + j];
			tag[beg[v] + j].init();
		}
		if (db - edv1 - 1 >= edv1 + 1) {
			for (int j = ed; j > db - edv1 - 1; j--) {
				f[beg[u] + j] = tag[beg[u] + j] * f[beg[u] + j];
				tag[beg[u] + j - 1] *= tag[beg[u] + j];
				tag[beg[u] + j].init();
			}
			for (int j = 0; j <= edv1; j++) {
				f[beg[u] + j + 1] = tag[beg[u] + j].get_inv() * f[beg[u] + j + 1];
				tag[beg[u] + j + 1] *= tag[beg[u] + j];
				tag[beg[u] + j].init();
			}
		} else {
			for (int j = ed; j > 0; j--) {
				f[beg[u] + j] = tag[beg[u] + j] * f[beg[u] + j];
				tag[beg[u] + j - 1] *= tag[beg[u] + j];
				tag[beg[u] + j].init();
			}
		}
		pre1[0] = pre2[0] = 0;
		for (int j = 0; j <= edv1; j++) {
			pre1[j] = (pre1[j] + (LL)(1 + MOD - p) * f[beg[v] + j]) % MOD;
			pre1[j + 1] = pre1[j];
			pre2[j] = (pre2[j] + (LL)(1 + MOD - p) * f[beg[u] + j]) % MOD;
			pre2[j + 1] = pre2[j];
		}
		LL ng = g[u], nga = 0;
		ng += MOD - f[beg[u]];
		f[beg[u]] = (LL)f[beg[u]] * sum % MOD;
		nga += f[beg[u]];
		for (int j = 1; j <= db - edv1 - 1 && j <= edv1 + 1; j++) {
			ng += MOD - f[beg[u] + j];
			f[beg[u] + j] = ((LL)f[beg[u] + j] * (pre1[j - 1] + sum) + (LL)f[beg[v] + j - 1] * pre2[j - 1]) % MOD;
			nga += f[beg[u] + j];
		}
		for (int j = max(db - edv1, edv1 + 2); j <= ed; j++) {
			ng += MOD - f[beg[u] + j];
			f[beg[u] + j] = (LL)f[beg[u] + j] * (sum + (j == db ? 0 : pre1[db - j - 1])) % MOD;
			nga += f[beg[u] + j];
		}
		if (db - edv1 - 1 >= edv1 + 1) {
			//(pre1[edv1]+sum) must be 1
			g[u] = (ng + nga) % MOD;
		} else {
			for (int j = db - edv1; j <= edv1 + 1; j++) {
				f[beg[u] + j] = ((LL)f[beg[u] + j] * ((j == db ? 0 : pre1[min(j - 1, db - j - 1)]) + sum)
					+ (LL)f[beg[v] + j - 1] * pre2[min(j - 1, db - j)]) % MOD;
				nga += f[beg[u] + j];
			}
			g[u] = nga % MOD;
		}
	}
}

int main() {
	IO::read(n, da, db);
	if (db * 2 >= da) {
		puts("1");
		return 0;
	}
	db *= 2;
	const LL dv = modpow(1e7, MOD - 2);
	for (int i = 1; i < n; i++) {
		int u, v, p;
		IO::read(u, v, p);
		p = dv * p % MOD;
		add_edge(u, v, p);
		add_edge(v, u, p);
	}
	dfs1(1, 0);
	pre1[1] = 1;
	for (int i = 2; i <= n; i++) {
		int q = (1 + MOD - val[i]) % MOD;
		pre1[i] = q == 0 ? pre1[i - 1] : (LL)q * pre1[i - 1] % MOD;
	}
	pre1[n] = modpow(pre1[n], MOD - 2);
	for (int i = n; i > 1; i--) {
		int q = (1 + MOD - val[i]) % MOD;
		inv[i] = q == 0 ? 0 : (LL)pre1[i] * pre1[i - 1] % MOD;
		pre1[i - 1] = q == 0 ? pre1[i] : (LL)pre1[i] * q % MOD;
	}
	beg[1] = tot = 1;
	dfs2(1, 0);
	printf("%d\n", g[1]);
	return 0;
}
