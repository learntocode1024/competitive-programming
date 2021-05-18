#include <iostream>
#include <string>
using namespace std;

int main() {
  string s;
  int T;
  cin >> T;
  while (T--) {
    cin >> s;
    if (s.size() % 2 || s[0] == ')' || *s.rbegin() == '(')
      cout << "NO" << endl;
    else
      cout << "YES" << endl;
  }
  return 0;
}
