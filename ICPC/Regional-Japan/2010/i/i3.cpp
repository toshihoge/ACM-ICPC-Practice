#include<cstdio>
#include<iostream>
#include<vector>
#include<set>

using namespace std;

#define INF 1e+6

typedef pair<double, double> P2;
typedef vector<P2> P2S;
typedef P2S::const_iterator P2S_IT;

double getCrossingHeight(const P2S &p2s, int index, double x) {
  P2 p21 = p2s[index];
  P2 p22 = p2s[(index+1)%p2s.size()];
  double x1 = p21.first;
  double x2 = p22.first;
  //ignore when horizontal line.
  if (x1 == x2 || x < min(x1, x2) || max(x1, x2) < x) {
    return INF;
  }
  double h1 = p21.second;
  double h2 = p22.second;
  return (h2 - h1) * (x - x1) / (x2 - x1) + h1;
}

double cut(const P2S &p2s, double x) {
  double minH = INF;
  double maxH = -INF;
  for (int i = 0; i < p2s.size(); i++) {
    double h = getCrossingHeight(p2s, i, x);
    if (h == INF) continue;
    minH = min(minH, h);
    maxH = max(maxH, h);
  }
  if (maxH == -INF) {
    return 0.0;
  }
  return maxH - minH;
}

// h = first*x + second
P2 solveEquation(double h1, double x1, double h2, double x2) {
  return make_pair((h2-h1) / (x2-x1), (h1*x2 - x1*h2) / (x2-x1));
}

/*
 integral [xmax, xmin] y(x)*z(x) dx
 { y(x) = ya*x + yb, z(x) = za*x + zb }
*/
double calculateMass(const P2S &xys, const P2S &xzs, double xmin, double xmax) {
  P2 py = solveEquation(cut(xys, xmin), xmin, cut(xys, xmax), xmax);
  P2 pz = solveEquation(cut(xzs, xmin), xmin, cut(xzs, xmax), xmax);
  double ya = py.first;
  double yb = py.second;
  double za = pz.first;
  double zb = pz.second;
  
  return ya*za*(xmax*xmax*xmax - xmin*xmin*xmin)/3 + (ya*zb + yb*za)*(xmax*xmax - xmin*xmin)/2 + yb*zb*(xmax - xmin);
}

P2 getMinAndMaxX(const P2S &p2s) {
  double maxx = -INF;
  double minx = INF;
  for (P2S_IT it = p2s.begin(); it != p2s.end(); it++) {
    maxx = max(maxx, it->first);
    minx = min(minx, it->first);
  }
  return make_pair(maxx, minx);
}

double solve(const P2S &xys, const P2S &xzs) {
  set<double> xs;
  
  P2 xRange1 = getMinAndMaxX(xys);
  P2 xRange2 = getMinAndMaxX(xzs);
  double xRangeCommonMax = min(xRange1.first, xRange2.first);
  double xRangeCommonMin = max(xRange1.second, xRange2.second);
  if (xRangeCommonMax <= xRangeCommonMin) {
    return 0.0;
  }
  for (P2S_IT it = xys.begin(); it != xys.end(); it++) {
    double x = it->first;
    if (xRangeCommonMin <= x && x <= xRangeCommonMax) {
      xs.insert(x);
    }
  }
  for (P2S_IT it = xzs.begin(); it != xzs.end(); it++) {
    double x = it->first;
    if (xRangeCommonMin <= x && x <= xRangeCommonMax) {
      xs.insert(x);
    }
  }
  
  double mass = 0.0;
  double prev = INF;
  for (set<double>::iterator it = xs.begin(); it != xs.end(); it++) {
    if (prev != INF) {
      mass += calculateMass(xys, xzs, prev, *it);
    }
    prev = *it;
  }
  return mass;
}

int main(void) {
  while (true) {
    int m, n;
    cin >> m >> n;
    if (m == 0 && n == 0) {
      break;
    }
    
    P2S xys;
    P2S xzs;
    for (int i = 0; i < m; i++) {
      int x, y;
      cin >> x >> y;
      xys.push_back(make_pair(x, y));
    }
    for (int j = 0; j < n; j++) {
      int x, z;
      cin >> x >> z;
      xzs.push_back(make_pair(x, z));
    }
    printf("%.4f\n", solve(xys, xzs));
  }
}
