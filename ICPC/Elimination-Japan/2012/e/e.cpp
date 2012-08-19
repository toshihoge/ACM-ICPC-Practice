#include<algorithm>
#include<complex>
#include<cstdio>
#include<iostream>
#include<vector>

using namespace std;

typedef complex<double> cd;

#define MAX_N 100
#define INF 1e40
#define EPS 1e-6

int n;
cd c[MAX_N];
double r[MAX_N];

pair<cd,cd> crossCircles(cd c1, double r1, cd c2, double r2) {
  double c12 = abs(c2 - c1);
  double cos_value = (r1*r1 + c12*c12 - r2*r2) / (2.0 * r1 * c12);
  double acos_value = acos(cos_value);
  double arg_value = arg(c2 - c1);
  return make_pair(
      c1 + polar(r1, arg_value + acos_value),
      c1 + polar(r1, arg_value - acos_value));
}

pair<double, double> crossLineCircle(cd p1, cd p2, cd c, double r) {
  p2 -= p1;
  c -= p1;
  c /= p2;
  r /= abs(p2);
  double y = abs(imag(c));
  double x = real(c);
  if (y >= r) {
    return make_pair(INF, INF);
  }
  double dx = sqrt(r*r - y*y);
  double xmin = x-dx;
  double xmax = x+dx;
  if (xmax < 0.0 || 1.0 < xmin) {
    return make_pair(INF, INF);
  }
  return make_pair(xmin, xmax);
}

bool covered(cd p1, cd p2) {
  vector<pair<double, double> > pdds;
  for (int i = 0; i < n; i++) {
    pair<double, double> pdd = crossLineCircle(p1, p2, c[i], r[i]+EPS);
    if (pdd.first != INF) {
      pdds.push_back(pdd);
    }
  }
  if (pdds.size() == 0) {
    return false;
  }
  sort(pdds.begin(), pdds.end());
  if (pdds[0].first > 0.0) {
    return false;
  }
  double xmax = pdds[0].second;
  for (int i = 0; i < n; i++) {
    if (xmax < pdds[i].first) {
      return false;
    }
    xmax = max(xmax, pdds[i].second);
    if (xmax >= 1.0) {
      return true;
    }
  }
  return false;
}

void solve() {
  vector<cd> ps;
  ps.push_back(c[0]);
  ps.push_back(c[n-1]);
  for (int i = 1; i < n; i++) {
    pair<cd, cd> p = crossCircles(c[i-1], r[i-1], c[i], r[i]);
    ps.push_back(p.first);
    ps.push_back(p.second);
  }

  int m = ps.size();
  double matrix[m][m];
  for (int i = 0; i < m; i++) {
    for (int j = i+1; j < m; j++) {
      matrix[i][i] = 0.0;
      if (covered(ps[i], ps[j])) {
        matrix[i][j] = matrix[j][i] = abs(ps[i] - ps[j]);
      } else {
        matrix[i][j] = matrix[j][i] = INF;
      }
    }
  }
  for (int k = 0; k < m; k++) {
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < m; j++) {
        matrix[i][j] = min(matrix[i][j], matrix[i][k] + matrix[k][j]);
      }
    }
  }
  printf("%.4f\n", matrix[0][1]);
}

int main(void) {
  while (true) {
    cin >> n;
    if (n == 0) {
      break;
    }
    for (int i = 0; i < n; i++) {
      double x, y;
      cin >> x >> y >> r[i];
      c[i] = cd(x, y);
    }
    solve();
  }
}
