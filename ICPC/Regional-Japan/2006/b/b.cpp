#include<iostream>
#include<complex>
#include<vector>

using namespace std;

typedef complex<double> cd;

#define EPS 1e-6
#define INF 1e+10
#define NON_POINT cd(INF, INF)

bool onLeft(cd cutsrc, cd cutdst, cd target) {
  return imag((target - cutsrc) / (cutdst - cutsrc)) >= 0;
}

void addPoint(vector<cd> &points, cd p) {
  if (points.size() == 0 || abs(points.back() - p) > EPS) {
    points.push_back(p);
  }
}

cd cross(cd seg1, cd seg2, cd line1, cd line2) {
  cd p1 = seg1;
  cd v1 = seg2 - seg1;
  cd p2 = line1;
  cd v2 = line2 - line1;
  if (abs(imag(v1/v2)) < EPS) {
    return NON_POINT;
  }
  double a1 = imag((p2-p1)/v2) / imag(v1/v2);
  if (-EPS<a1 && a1<1.0+EPS) {
    return p1+a1*v1;
  }
  return NON_POINT;
}

vector<cd> cut(cd cutsrc, cd cutdst, const vector<cd> &points) {
  vector<cd> output;
  for (int i = 0; i < points.size(); i++) {
    cd cp = cross(points[i], points[(i+1)%points.size()], cutsrc, cutdst);
    if (onLeft(cutsrc, cutdst, points[i])) {
      addPoint(output, points[i]);
    }
    if (cp != NON_POINT) {
      addPoint(output, cp);
    }
  }
  return output;
}

int solve(const vector<cd> &points) {
  vector<cd> rest = points;
  for (int i = 0; i < points.size(); i++) {
    rest = cut(points[i], points[(i+1)%points.size()], rest);
    if (rest.size() < 3) {
      return 0;
    }
  }
  return 1;
}

int main(void) {
  while(true) {
    int n;
    cin >> n;
    if (n == 0) {
      break;
    }
    vector<cd> points;
    for (int i = 0; i < n; i++) {
      int x, y;
      cin >> x >> y;
      points.push_back(cd(x, y));
    }
    cout << solve(points) << endl;
  }
}
