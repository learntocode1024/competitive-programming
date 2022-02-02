#include "matrix.h"
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef vector<vector<int> > V;

const int N = 1000, M = 1000000, MOD = 998244353;
const double lambda = 0.5;
V m[N];
int v[M], tot = 1e9, mode=1;

bool mateq(int a, int b) {
	int x = m[a].size(), y = m[b].empty() ? 0 : m[b][0].size();
	if (x != m[b].size() || y != (m[b].empty() ? 0 : m[b][0].size())) return 0;
	if (!x || !y) return 1;
	for (int i = 0; i < x; ++i) for (int j = 0; j < y; ++j) {
		if (m[a][i][j] != m[b][i][j]) return 0;
	}
	return 1;
}

void set_cost(int x) {
	tot = x;
}

int _getrow(int id) {
	return m[id].size();
}

int _getcol(int id) {
	return m[id].empty() ? 0 : m[id][0].size();
}

void _setmatrix(int id, int n, int m1) {
	m[id] = V(n, vector<int>(m1));
}

void _copymatrix(int dst, int x, int y, int id, int r1, int r2, int c1, int c2) {
	V t(r2 - r1 + 1, vector<int>(c2 - c1 + 1));
	for (int i = r1; i <= r2; i++)
	for (int j = c1; j <= c2; j++)
		t[i - r1][j - c1] = m[id][i][j];
	for (int i = 0; i <= r2 - r1; i++)
	for (int j = 0; j <= c2 - c1; j++)
		m[dst][i + x][j + y] = t[i][j];
}

void _addscalar(int a, int s, int c) {
	int R = _getrow(a), C = _getcol(a);
	V t(R, vector<int>(C));
	for (int i = 0; i < R; i++)
	for (int j = 0; j < C; j++)
		t[i][j] = (m[a][i][j] + s) % MOD;
	m[c] = t;
}

void _mulscalar(int a, int s, int c) {
	int R = _getrow(a), C = _getcol(a);
	V t(R, vector<int>(C));
	for (int i = 0; i < R; i++)
	for (int j = 0; j < C; j++)
		t[i][j] = (LL)m[a][i][j] * s % MOD;
	m[c] = t;
}

void _addmatrix(int a, int b, int c) {
	int R = _getrow(a), C = _getcol(a);
	V t(R, vector<int>(C));
	for (int i = 0; i < R; i++)
	for (int j = 0; j < C; j++)
		t[i][j] = (m[a][i][j] + m[b][i][j]) % MOD;
	m[c] = t;
}

void _submatrix(int a, int b, int c) {
	int R = _getrow(a), C = _getcol(a);
	V t(R, vector<int>(C));
	for (int i = 0; i < R; i++)
	for (int j = 0; j < C; j++)
		t[i][j] = (m[a][i][j] + MOD - m[b][i][j]) % MOD;
	m[c] = t;
}

void _mulmatrix(int a, int b, int c) {
	int r = _getrow(a);
	V t(r, vector<int>(r));
	for (int i = 0; i < r; i++)
	for (int j = 0; j < r; j++)
	for (int k = 0; k < r; k++)
		t[i][k] = (t[i][k] + (LL)m[a][i][j] * m[b][j][k]) % MOD;
	m[c] = t;
}

void range(int x, int l, int r) {
	if (x < l || x >= r) {
		printf("index out of bound: %d out of [%d, %d]", x, l, r - 1);
		exit(0);
	}
}

void check(LL cost) {
	if (tot < cost) {
		puts("the cost is too much");
		exit(0);
	}
	tot -= cost;
}

int getrow(int id) {
	range(id, 0, N);
	check(1);
	return _getrow(id);
}

int getcol(int id) {
	range(id, 0, N);
	check(1);
	return _getcol(id);
}

void setmatrixnum(int id, int x, int y, int n, int f) {
	range(id, 0, N);
	range(f, -1, M);
	range(n, 0, MOD);
	range(x, 0, _getrow(id));
	range(y, 0, _getcol(id));
	check(1);
	if (f < 0 || v[f]) m[id][x][y] = n;
}

void setmatrixnum1(int id, int x, int y, int n, int f) {
	range(x, 0, M);
	range(y, 0, M);
	range(n, 0, M);
	setmatrixnum(id, v[x], v[y], v[n], f);
}

void setmatrix(int id, int n, int m, int f) {
	range(id, 0, N);
	range(n, 0, 1e9);
	range(m, 0, 1e9);
	range(f, -1, M);
	if (f >= 0 && !v[f]) {
		check(1);
	} else {
		check(ceil(lambda * n * m));
		_setmatrix(id, n, m);
	}
}

void setmatrix1(int id, int n, int m, int f) {
	range(n, 0, M);
	range(m, 0, M);
	setmatrix(id, v[n], v[m], f);
}

void copymatrix(int dst, int x, int y, int id, int r1, int r2, int c1, int c2, int f) {
	range(dst, 0, N);
	range(id, 0, N);
	range(r1, 0, _getrow(id));
	range(c1, 0, _getcol(id));
	range(r2, r1, _getrow(id));
	range(c2, c1, _getcol(id));
	range(x, 0, _getrow(dst));
	range(y, 0, _getcol(dst));
	range(f, -1, M);
	if (f < 0 || v[f]) {
		check(ceil((r2 - r1 + 1) * (c2 - c1 + 1) * lambda));
		_copymatrix(dst, x, y, id, r1, r2, c1, c2);
	} else check(1);
}

void copymatrix1(int dst, int x, int y, int id, int r1, int r2, int c1, int c2, int f) {
	range(x, 0, M);
	range(y, 0, M);
	range(r1, 0, M);
	range(r2, 0, M);
	range(c1, 0, M);
	range(c2, 0, M);
	copymatrix(dst, v[x], v[y], id, v[r1], v[r2], v[c1], v[c2], f);
}

void addscalar(int a, int s, int c, int f) {
	range(a, 0, N);
	range(c, 0, N);
	range(s, 0, MOD);
	range(f, -1, M);
	if (f < 0 || v[f]) {
		check(ceil(lambda * _getrow(a) * _getcol(a)));
		_addscalar(a, s, c);
	} else check(1);
}

void addscalar1(int a, int s, int c, int f) {
	range(s, 0, M);
	addscalar(a, v[s], c, f);
}

void mulscalar(int a, int s, int c, int f) {
	range(a, 0, N);
	range(c, 0, N);
	range(s, 0, MOD);
	range(f, -1, M);
	if (f < 0 || v[f]) {
		check(ceil(lambda * _getrow(a) * _getcol(a)));
		_mulscalar(a, s, c);
	} else check(1);
}

void mulscalar1(int a, int s, int c, int f) {
	range(s, 0, M);
	mulscalar(a, v[s], c, f);
}

void addmatrix(int a, int b, int c, int f) {
	range(a, 0, N);
	range(b, 0, N);
	range(c, 0, N);
	range(f, -1, M);
	if (_getrow(a) != _getrow(b) || _getcol(a) != _getcol(b)) {
		puts("matrices sizes do not equal in addition");
		exit(0);
	}
	if (f < 0 || v[f]) {
		check(ceil(lambda * _getrow(a) * _getcol(a)));
		_addmatrix(a, b, c);
	} else check(1);
}

void submatrix(int a, int b, int c, int f) {
	range(a, 0, N);
	range(b, 0, N);
	range(c, 0, N);
	range(f, -1, M);
	if (_getrow(a) != _getrow(b) || _getcol(a) != _getcol(b)) {
		puts("matrices sizes do not equal in subtraction");
		exit(0);
	}
	if (f < 0 || v[f]) {
		check(ceil(lambda * _getrow(a) * _getcol(a)));
		_submatrix(a, b, c);
	} else check(1);
}

void mulmatrix(int a, int b, int c, int f) {
	if (mode) {
		puts("You cannot use mulmatrix");
		exit(0);
	}
	range(a, 0, N);
	range(b, 0, N);
	range(c, 0, N);
	range(f, -1, M);
	if (_getrow(a) != _getcol(a) || _getrow(b) != _getcol(b) || _getrow(a) != _getrow(b)) {
		puts("matrices cannot be multiplied");
		exit(0);
	}
	if (f < 0 || v[f]) {
		check(ceil(lambda * pow(_getrow(a), 2.3)));
		_mulmatrix(a, b, c);
	} else check(1);
}

void setnummatrix(int n, int id, int x, int y, int f) {
	range(n, 0, M);
	range(id, 0, N);
	range(x, 0, _getrow(id));
	range(y, 0, _getcol(id));
	range(f, -1, M);
	check(1);
	if (f < 0 || v[f]) v[n] = m[id][x][y];
}

void setnummatrix1(int n, int id, int x, int y, int f) {
	range(x, 0, M);
	range(y, 0, M);
	setnummatrix(n, id, v[x], v[y], f);
}

void setnum(int id, int n, int f) {
	range(id, 0, M);
	range(n, 0, MOD);
	range(f, -1, M);
	check(1);
	if (f < 0 || v[f]) v[id] = n;
}

void setnum1(int id, int n, int f) {
	range(id, 0, M);
	range(n, 0, M);
	range(f, -1, M);
	check(1);
	if (f < 0 || v[f]) v[id] = v[n];
}

void addnum(int a, int b, int c, int f) {
	range(a, 0, M);
	range(b, 0, M);
	range(c, 0, M);
	range(f, -1, M);
	check(1);
	if (f < 0 || v[f]) v[c] = (v[a] + v[b]) % MOD;
}

void subnum(int a, int b, int c, int f) {
	range(a, 0, M);
	range(b, 0, M);
	range(c, 0, M);
	range(f, -1, M);
	check(1);
	if (f < 0 || v[f]) v[c] = (v[a] + MOD - v[b]) % MOD;
}

void mulnum(int a, int b, int c, int f) {
	range(a, 0, M);
	range(b, 0, M);
	range(c, 0, M);
	range(f, -1, M);
	check(1);
	if (f < 0 || v[f]) v[c] = (LL)v[a] * v[b] % MOD;
}

LL modpow(LL a, int b) {
	LL res = 1;
	for (; b; b >>= 1) {
		if (b & 1) res = res * a % MOD;
		a = a * a % MOD;
	}
	return res;
}

void divnum(int a, int b, int c, int f) {
	range(a, 0, M);
	range(b, 0, M);
	range(c, 0, M);
	range(f, -1, M);
	check(1);
	if (f < 0 || v[f]) v[c] = v[a] * modpow(v[b], MOD - 2) % MOD;
}

void lssnum(int a, int b, int c, int f) {
	range(a, 0, M);
	range(b, 0, M);
	range(c, 0, M);
	range(f, -1, M);
	check(1);
	if (f < 0 || v[f]) v[c] = (v[a] < v[b]);
}

void equnum(int a, int b, int c, int f) {
	range(a, 0, M);
	range(b, 0, M);
	range(c, 0, M);
	range(f, -1, M);
	check(1);
	if (f < 0 || v[f]) v[c] = (v[a] == v[b]);
}

void transpose(int a, int b, int f) {
	range(a, 0, N);
	range(b, 0, N);
	range(f, -1, M);
	if (f >= 0 && !v[f]) {
		check(1);
		return;
	}
	int r = _getrow(a), c = _getcol(a);
	check(ceil(lambda * r * c));
	V ret(r, vector<int>(c));
	for (int i = 0; i < r; i++)
	for (int j = 0; j < c; j++)
		ret[j][i] = m[a][i][j];
	m[b] = ret;
}

void LU_decomposition(int a, int L, int U, int f) {
	if (mode != 1) {
		puts("You cannot use LU_decomposition");
		exit(0);
	}
	range(a, 0, N);
	range(L, 0, N);
	range(U, 0, N);
	range(f, -1, M);
	int n = _getrow(a);
	if (n != _getcol(a)) {
		puts("a should be square");
		exit(0);
	}
	if (f >= 0 && !v[f]) {
		check(1);
		return;
	}
	check(ceil(lambda * pow(_getrow(a), 2.3)));
	_setmatrix(L, n, n);
	m[U] = m[a];
	for (int i = 0; i < n; i++) m[L][i][i] = 1;
	for (int i = 0; i < n; i++) {
		LL d = modpow(m[U][i][i], MOD - 2);
		assert(d);
		for (int j = i + 1; j < n; j++) {
			LL p = d * m[U][j][i] % MOD;
			m[L][j][i] = p;
			for (int k = i; k < n; k++)
				m[U][j][k] = (m[U][j][k] + (LL)(MOD - p) * m[U][i][k]) % MOD;
		}
	}
}

void inverse(int a, int b, int f) {
	if (mode != 2) {
		puts("You cannot use inverse");
		exit(0);
	}
	range(a, 0, N);
	range(b, 0, N);
	range(f, -1, M);
	int n = _getrow(a);
	if (n != _getcol(a)) {
		puts("a should be square");
		exit(0);
	}
	if (f >= 0 && !v[f]) {
		check(1);
		return;
	}
	check(ceil(lambda * pow(_getrow(a), 2.3)));
	V x = m[a];
	V t(n, vector<int>(n));
	for (int i = 0; i < n; i++) t[i][i] = 1;
	for (int i = 0; i < n; i++) {
		for (int j = i; j < n; j++) {
			if (x[j][i]) {
				swap(x[i], x[j]);
				swap(t[i], t[j]);
				break;
			}
		}
		LL d = modpow(x[i][i], MOD - 2);
		assert(d);
		for (int j = i + 1; j < n; j++) {
			LL p = d * x[j][i] % MOD;
			for (int k = 0; k < n; k++) {
				x[j][k] = (x[j][k] + (LL)(MOD - p) * x[i][k]) % MOD;
				t[j][k] = (t[j][k] + (LL)(MOD - p) * t[i][k]) % MOD;
			}
		}
	}
	for (int i = n - 1; i >= 0; i--) {
		for (int j = i + 1; j < n; j++) {
			for (int k = 0; k < n; k++)
				t[i][k] = (t[i][k] + (LL)(MOD - x[i][j]) * t[j][k]) % MOD;
			x[i][j] = 0;
		}
		LL d = modpow(x[i][i], MOD - 2);
		assert(d);
		for (int j = 0; j < n; j++)
			t[i][j] = t[i][j] * d % MOD;
		x[i][i] = 1;
	}
	m[b] = t;
}
