#include<complex>
#include<cstdio>
#include<iostream>
#include<vector>

using namespace std;

typedef complex<double> cd;

typedef pair<cd, cd> segment;

typedef vector<cd> vcd;
typedef vcd polygon;

#define INF 1e+6

cd readCd() {
  double x, y;
  cin >> x >> y;
  return cd(x, y);
}

polygon readPolygon(int n) {
  vector<cd> output;
  for (int i = 0; i < n; i++) {
    output.push_back(readCd());
  }
  return output;
}

double distanceNoAbs(const cd &p, const segment &s) {
  return imag((p - s.second) /
      (s.second - s.first) * abs(s.second - s.first));
}

double getWidth(const polygon &p, const segment &s) {
  double positiveDistance = 0.0;
  double negativeDistance = 0.0;
  
  for (int i = 0; i < (int)p.size(); i++) {
    double distance = distanceNoAbs(p[i], s);
    positiveDistance = max(positiveDistance, distance);
    negativeDistance = min(negativeDistance, distance);
  }
  return positiveDistance - negativeDistance;
}

double myceil(double d) {
  return ceil(100.0 * d) / 100.0;
}

double solve(const polygon &p) {
  double output = INF;
  for (int i = 0; i < (int)p.size(); i++) {
    for (int j = i+1; j < (int)p.size(); j++) {
      output = min(output, getWidth(p, make_pair(p[i], p[j])));
    }
  }
  return myceil(output);
}

int main(void) {
  for (int casenumber = 1; true; casenumber++) {
    int n;
    cin >> n;
    if (n == 0) {
      break;
    }
    polygon p = readPolygon(n);
    printf("Case %d: %.2f\n", casenumber, solve(p));
  }
}
