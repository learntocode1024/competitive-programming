#include <cmath>
#include <iostream>

struct pt {
  double x, y;
  pt() : x(0), y(0){};
  pt(double a, double b) : x(a), y(b){};
  friend std::istream &operator>>(std::istream&, pt&);
  friend double dist(const pt&, const pt&);
  pt operator+(const pt &b) const {
    pt ans = *this;
    ans.x += b.x;
    ans.y += b.y;
    return ans;
  }
  pt operator-(const pt &b) const {
    pt ans = *this;
    ans.x -= b.x;
    ans.y -= b.y;
    return ans;
  }
  pt operator*(const double t) const {
    pt ans = *this;
    ans.x *= t;
    ans.y *= t;
    return ans;
  }
  pt rotate(const double angel) const {
    double theta = atan2(y, x);
    theta += angel;
    double r = sqrt(x * x + y * y);
    return pt(r * cos(theta), r * sin(theta));
  }
};

std::istream &operator>>(std::istream &buf, pt &p) {
  buf >> p.x >> p.y;
  return buf;
}

double dist(const pt &a, const pt &b) {
  double x = a.x - b.x;
  double y = b.y - b.y;
  return sqrt(x * x + y * y);
};