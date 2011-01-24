#include<iostream>
#include<cmath>

using namespace std;

double len3d(double x, double y, double z) {
  return sqrt(x*x + y*y + z*z);
}

bool visible(double sx, double sy, double sz, double tx, double ty, double tz, double angle) {
  return (sx*tx + sy*ty + sz*tz) / len3d(sx, sy, sz) / len3d(tx, ty, tz) > cos(angle);
}

bool visibleArray(double sx, double sy, double sz, int m, const double* tx, const double* ty, const double* tz, const double* angle) {
  for (int i = 0; i < m; i++) {
    if (visible(sx, sy, sz, tx[i], ty[i], tz[i], angle[i])) return true;
  }
  return false;
}

int solve(int n, const double* sx, const double* sy, const double* sz, int m, const double* tx, const double* ty, const double* tz, const double* angle) {
  int output = 0;
  for (int i = 0; i < n; i++) {
    if (visibleArray(sx[i], sy[i], sz[i], m, tx, ty, tz, angle)) output++;
  }
  return output;
}

int main(void) {
  while (true) {
    int n;
    cin >> n;
    if (n == 0) {
      break;
    }
    double sx[n], sy[n], sz[n];
    for (int i = 0; i < n; i++) {
      cin >> sx[i] >> sy[i] >> sz[i];
    }
    int m;
    cin >> m;
    double tx[m], ty[m], tz[m], angle[m];
    for (int i = 0; i < m; i++) {
      cin >> tx[i] >> ty[i] >> tz[i] >> angle[i];
    }
    cout << solve(n, sx, sy, sz, m, tx, ty, tz, angle) << endl;
  }
}
