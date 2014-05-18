#include<iostream>
#include<complex>
#include<cstdio>

using namespace std;

typedef complex<double> cd;

bool coverPoint(int n, const cd* ps, const double* rs, const cd& p, int skip1, int skip2) {
  for (int i = 0; i < n; i++) {
    if (i == skip1 || i == skip2) {
      continue;
    }
    if (abs(p - ps[i]) > rs[i]) {
      return false;
    }
  }
  return true;
}

pair<cd, cd> circlesCrossPoints(cd c1, double r1, cd c2, double r2) {
  double arg1 = arg(c2 - c1);
  double a = abs(c2 - c1);
  double b = r1;
  double c = r2;
  double cosv = (a*a + b*b - c*c) / (2.0 * a * b);
  double arg2 = acos(cosv);
  return make_pair(c1 + polar(r1, arg1 + arg2), c1 + polar(r1, arg1 - arg2));
}

bool flyable(int n, const cd* ps, const double* ls, double h) {
  double rs[n];
  for (int i = 0; i < n; i++) {
    rs[i] = sqrt(ls[i]*ls[i] - h*h);
  }
  
  for (int i = 0; i < n; i++) {
    if (coverPoint(n, ps, rs, ps[i], -1, -1)) {
      return true;
    }
  }
  
  for (int i = 0; i < n; i++) {
    for (int j = i+1; j < n; j++) {
      double pdiff = abs(ps[i] - ps[j]);
      if (abs(rs[i] - rs[j]) < pdiff && pdiff < rs[i] + rs[j]) {
        pair<cd, cd> p = circlesCrossPoints(ps[i], rs[i], ps[j], rs[j]);
        if (coverPoint(n, ps, rs, p.first, i, j) || coverPoint(n, ps, rs, p.second, i, j)) {
          return true;
        }
      }
    }
  }
  
  return false;
}

double solve(int n, const cd* ps, const double* ls) {
  double hmax = 1000;
  for (int i = 0; i < n; i++) {
    hmax = min(hmax, ls[i]);
  }
  double hmin = 0.0;
  
  for (int i = 0; i < 64; i++) {
    double hmid = (hmax + hmin) / 2.0;
    if (flyable(n, ps, ls, hmid)) {
      hmin = hmid;
    } else {
      hmax = hmid;
    }
  }
  return hmin;
}

int main(void) {
  while(true) {
    int n;
    cin >> n;
    if (n == 0) {
      break;
    }
    cd ps[n];
    double ls[n];
    for (int i = 0; i < n; i++) {
      double dx, dy;
      cin >> dx >> dy >> ls[i];
      ps[i] = cd(dx, dy);
    }
    printf("%.6f\n", solve(n, ps, ls));
  }
}
