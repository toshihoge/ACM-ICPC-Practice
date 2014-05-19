#include<iostream>
#include<cstdio>
#include<complex>
#include<vector>

using namespace std;

typedef complex<double> cd;

vector<cd> circlesCrossPoints(cd c1, double r1, cd c2, double r2) {
  double arg1 = arg(c2 - c1);
  double a = abs(c2 - c1);
  double b = r1;
  double c = r2;
  double cosv = (a*a + b*b - c*c) / (2.0 * a * b);
  double arg2 = acos(cosv);
  vector<cd> output;
  output.push_back(c1 + polar(r1, arg1 + arg2));
  output.push_back(c1 + polar(r1, arg1 - arg2));
  return output;
}

// |p1 + a(p2 - p1) - c| = r
// |x + t y| = z
// (x + t y) conj (x + t y) = z*z
// (x + t y) conj (x + t y) = z*z
// x conj(x) + t{y conj(x) + x conj(y)} + t*t*y*conj(y) = z*z
vector<cd> circleSegmentCrossPoint(cd center, double r, cd pos1, cd pos2) {
  cd x = pos1 - center;
  cd y = pos2 - pos1;
  double z = r;
  double a = norm(y);
  double b = 2.0*real(y*conj(x));
  double c = norm(x) - z*z;
  double d = b*b - 4.0*a*c;
  vector<cd> output;
  if (d <= 0) {
    return output;
  }
  double ans1 = (-b-sqrt(d)) / (2.0*a);
  if (0.0 < ans1 && ans1 < 1.0) {
    output.push_back(pos1 + ans1 * (pos2 - pos1));
  }
  double ans2 = (-b+sqrt(d)) / (2.0*a);
  if (0.0 < ans2 && ans2 < 1.0) {
    output.push_back(pos1 + ans2 * (pos2 - pos1));
  }
  return output;
}

bool outsidePoint(int n, const cd* ps, const double* rs, const cd& p, int skip1, int skip2) {
  for (int i = 0; i < n; i++) {
    if (i == skip1 || i == skip2) {
      continue;
    }
    if (abs(p - ps[i]) < rs[i]) {
      return false;
    }
  }
  return true;
}

double acceptableDistance(double r, double h) {
  if (h > r) {
    return r;
  }
  double d = r - h;
  return sqrt(r*r - d*d);
}

bool acceptable(double r, int n, double w, const cd* ps, const double* hs) {
  double distanceFromWall = acceptableDistance(r, w);
  if (2.0 * distanceFromWall > 100.0) {
    return false;
  }
  double xmin = distanceFromWall;
  double xmax = 100.0 - distanceFromWall;
  double ymin = distanceFromWall;
  double ymax = 100.0 - distanceFromWall;
  
  cd box[4];
  box[0] = cd(xmin, ymin);
  box[1] = cd(xmax, ymin);
  box[2] = cd(xmax, ymax);
  box[3] = cd(xmin, ymax);
  
  double rs[n];
  for (int i = 0; i < n; i++) {
    rs[i] = acceptableDistance(r, hs[i]);
  }
  
  if (outsidePoint(n, ps, rs, cd(50.0, 50.0), -1, -1)) {
    return true;
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < 4; j++) {
      vector<cd> crosses = circleSegmentCrossPoint(ps[i], rs[i], box[j], box[(j+1)%4]);
      for (int k = 0; k < crosses.size(); k++) {
        cd p = crosses[k];
        if (outsidePoint(n, ps, rs, p, i, -1)) {
          return true;
        }
      }
    }
  }
  for (int i = 0; i < n; i++) {
    for (int j = i+1; j < n; j++) {
      double pdiff = abs(ps[i] - ps[j]);
      if (abs(rs[i] - rs[j]) < pdiff && pdiff < rs[i] + rs[j]) {
        vector<cd> crosses = circlesCrossPoints(ps[i], rs[i], ps[j], rs[j]);
        for (int k = 0; k < 2; k++) {
          cd p = crosses[k];
          if (xmin < real(p) && real(p) < xmax && ymin < imag(p) && imag(p) < ymax && outsidePoint(n, ps, rs, p, i, j)) {
            return true;
          }
        }
      }
    }
  }
  return false;
}

double solve(int n, double w, const cd* ps, const double* hs) {
  double rMax = 1e8;
  double rMin = 0.0;
  
  for (int i = 0; i < 64; i++) {
    double rMid = (rMax + rMin) * 0.5;
    if (acceptable(rMid, n, w, ps, hs)) {
      rMin = rMid;
    } else {
      rMax = rMid;
    }
  }
  return rMin;
}

int main(void) {
  while (true) {
    int n;
    double w;
    cin >> n >> w;
    if (n == 0) {
      break;
    }
    cd ps[n];
    double hs[n];
    for (int i = 0; i < n; i++) {
      double x, y;
      cin >> x >> y >> hs[i];
      ps[i] = cd(x, y);
    }
    printf("%.5f\n", solve(n, w, ps, hs));
  }
}
