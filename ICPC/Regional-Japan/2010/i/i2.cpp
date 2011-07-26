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

double calculateArea (const P2S &xys, const P2S &xzs, double x) {
  double y = cut(xys, x);
  double z = cut(xzs, x);
  return y*z;
}

/*
a1*xi*xi + a2*xi + a3 = yi

x0*x0 x0 1 a0   y0
x1*x1 x1 1 a1 = y1
x2*x2 x2 1 a2   y2

a00 a01 a02 a0   y0
a10 a11 a12 a1 = y1
a20 a21 a22 a2   y2
*/

vector<double> findFactors(const double* x, const double* y) {
  double matrix[3][3];
  
  for (int i = 0; i < 3; i++) {
    matrix[i][0] = 1.0;
    matrix[i][1] = x[i];
    matrix[i][2] = x[i]*x[i];
  }
  
  double det = matrix[0][0]*matrix[1][1]*matrix[2][2] + matrix[0][1]*matrix[1][2]*matrix[2][0] + matrix[0][2]*matrix[1][0]*matrix[2][1] -
      matrix[0][0]*matrix[1][2]*matrix[2][1] - matrix[0][1]*matrix[1][0]*matrix[2][2] - matrix[0][2]*matrix[1][1]*matrix[2][0];
      
  double inverse[3][3];
  for (int i = 0; i < 3; i++) {
    int i1 = (i+1) % 3;
    int i2 = (i+2) % 3;
    for (int j = 0; j < 3; j++) {
      int j1 = (j+1) % 3;
      int j2 = (j+2) % 3;
      inverse[j][i] = (matrix[i1][j1]*matrix[i2][j2] - matrix[i2][j1]*matrix[i1][j2]) / det;
    }
  }
  
  vector<double> output;
  for (int i = 0; i < 3; i++) {
    output.push_back(0.0);
    for (int j = 0; j < 3; j++) {
      output[i] += inverse[i][j]*y[j];
    }
  }
  return output;
}

double integralSub(const vector<double> &factors, double x) {
  double xpow = 1.0;
  double sum = 0.0;
  for (int i = 0; i < 3; i++) {
    xpow *= x;
    sum += factors[i]*xpow / (i+1);
  }
  return sum;
}

double integral(const vector<double> &factors, double xmax, double xmin) {
  return integralSub(factors, xmax) - integralSub(factors, xmin);
}

double calculateMass(const P2S &xys, const P2S &xzs, double xmin, double xmax) {
  double x[] = {xmin, 0.5*(xmax + xmin), xmax};
  double y[3];
  for (int i = 0; i < 3; i++) {
    y[i] = calculateArea(xys, xzs, x[i]);
  }
  vector<double> factors = findFactors(x, y);
  return integral(factors, xmax, xmin);
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
  vector<double> xarray;
  for (set<double>::iterator it = xs.begin(); it != xs.end(); it++) {
    xarray.push_back(*it);
  }
  
  double prev = *(xs.begin());
  double mass = 0.0;
  for (int i = 1; i < xarray.size(); i++) {
    mass += calculateMass(xys, xzs, xarray[i-1], xarray[i]);
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
