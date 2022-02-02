#include <bits/stdc++.h>
#include "word.h"
using namespace std;
mt19937 rng;
// uniform_int_distribution<int> e;
int n;
const char *s;
char t[6];
int qu[10000];
int tot = 0, mask = 0;
bool v[128], v1[128], v2[128], g[128 ];
int cnt1 = 0;
#define FOR(i, j, k) for (int i = (j); i < (k); ++i)
#define ROF(i, j, k) for (int i = ((k) - 1); i >= j; --i)

const char *guess(int num_testcase, int remaining_guesses, char initial_letter, bool *gold, bool *silver) {
	if (remaining_guesses == 5) {
		tot = 0;
		for (int i = 0; i < n * 5; i += 5) {
			if (s[i] != initial_letter) continue;
			qu[tot++] = i;
		}
		uniform_int_distribution<int> e{0,tot};
		mask = cnt1 = 0;
		FOR(i, 0, 128) v[i] = v1[i] = v2[i] = g[i] = 0;
		int ch = qu[e(rng)];
		for (int i = 0; i < 5; ++i) t[i] = s[i+ch];
		return t;
	}
	tot = 0;
	FOR(i, 0, 5) g[i] |= gold[i]; // settle
	FOR(i, 0, 5) if (!g[i]) {
		if (silver[i]) {
			if (!v1[t[i]]) v1[t[i]] = 1, ++cnt1;
		} else {
			v2[t[i]] = 1;
		}
	}
	for (int i = 0; i < n * 5; i += 5) {
		bool ok = 1;
		for (int j = 0; j < 5; ++j) {
			if (g[j]) {
				if (s[i+j] != t[j]) ok = 0;
			} else {
				if (v2[s[i+j]]) ok = 0;
				if (v1[s[i+j]]) v[s[i+j]] = 1;
			}
		}
		int cnt2 = 0;
		FOR(x, 'a', 'z'+1) {
			if (v[x]) {
				v[x] = 0;
				++cnt2;
			}
		}
		if (cnt2 < cnt1) ok = 0;
		if (ok) {
			qu[tot++] = i;
		}
	}
	uniform_int_distribution<int> e{0,tot};
	int ch = qu[e(rng)];
	FOR(i, 0, 5) t[i] = s[ch+i];
	return t;
}

void init(int num_scramble, const char *scramble) {
	rng = mt19937(chrono::steady_clock::now().time_since_epoch().count());
	s = scramble;
	n = num_scramble;
}
