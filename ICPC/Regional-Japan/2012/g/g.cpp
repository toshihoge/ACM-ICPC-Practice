#include<cmath>
#include<cstdio>
#include<iostream>

using namespace std;

typedef struct {
  double x, y, z;
} P3D;

double product(const P3D &p1, const P3D &p2) {
  return p1.x*p2.x + p1.y*p2.y + p1.z*p2.z;
}

double norm(const P3D &p) {
  return product(p, p);
}

P3D sub(const P3D &p3d1, const P3D &p3d2) {
  P3D output;
  output.x = p3d1.x - p3d2.x;
  output.y = p3d1.y - p3d2.y;
  output.z = p3d1.z - p3d2.z;
  return output;
}

pair<double, double> solve_equation(double a2, double a1, double a0) {
  double d = a1*a1 - a2*a0;
  if (d < 0.0) {
    return make_pair(-1.0, -1.0);
  }
  return make_pair((-a1-sqrt(d)) / a2, (-a1+sqrt(d)) /a2);
}

bool block(const P3D &t, const P3D &s, double sr) {
  pair<double, double> f = solve_equation(norm(t), -1.0*product(t, s), norm(s) - sr*sr);
  return (0.0 < f.first && f.first < 1.0) ||
      (0.0 < f.second && f.second < 1.0);
}

double light(int n, const P3D *s, const double *sr,
    int m, const P3D *t, const double *tb,
    int r, int light_set, double max_value) {
  bool removed[n];
  fill(removed, removed + n, false);
  double value = 0.0;
  for (int i = 0; i < m; i++) {
    if ((light_set & (1 << i)) != 0) {
      value += tb[i] / norm(t[i]);
    }
  }
  if (value < max_value) {
    return 0.0;
  }
  for (int i = 0; i < m; i++) {
    if ((light_set & (1 << i)) != 0) {
      for (int j = 0; j < n; j++) {
        if (removed[j]) {
          continue;
        }
        if (block(t[i], s[j], sr[j])) {
          removed[j] = true;
          r--;
          if (r < 0) {
            return 0.0;
          }
        }
      }
    }
  }
  return value;
}

double solve(int n, const P3D *s, const double *sr,
    int m, const P3D *t, const double *tb, int r) {
  double max_value = 0.0;
  for (int light_set = 0; light_set < (1 << m); light_set++) {
    max_value = max(max_value, light(n, s, sr, m, t, tb, r, light_set, max_value));
  }
  return max_value;
}

int main(void) {
  while(true) {
    int n, m, r;
    cin >> n >> m >> r;
    if (n == 0) {
      break;
    }
    P3D s[n], t[m], e;
    double sr[n], tb[m];
    for (int i = 0; i < n; i++) {
      cin >> s[i].x >> s[i].y >> s[i].z >> sr[i];
    }
    for (int i = 0; i < m; i++) {
      cin >> t[i].x >> t[i].y >> t[i].z >> tb[i];
    }
    cin >> e.x >> e.y >> e.z;
    for (int i = 0; i < n; i++) {
      s[i] = sub(s[i], e);
    }
    for (int i = 0; i < m; i++) {
      t[i] = sub(t[i], e);
    }
    printf("%.5f\n", solve(n, s, sr, m, t, tb, r));
  }
}
