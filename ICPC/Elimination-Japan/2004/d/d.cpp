#include<cmath>
#include<complex>
#include<iostream>
#include<vector>

using namespace std;

typedef complex<double> cd;

typedef vector<int> vi;

#define DL cerr<<"Debug: "<<__LINE__<<endl
#define DUMP(x) cerr<<#x<<" = "<<(x)<<" (@"<<__LINE__<<")"<<endl
#define FOR(i,a,b) for(int i=(a);i<(int)(b);i++)
#define REP(i,n) FOR(i,0,n)

int count(int n, int skip1, int skip2, cd c, const cd* p) {
  int output = 0;
  REP(i,n) {
    if (abs(p[i] - c) <= 1.0001) {
      output++;
    }
  }
  return output;
}

int solve(int n, const cd* p) {
  int output = 1;
  REP(i,n) {
    FOR(j,i+1,n) {
      if (abs(p[i] - p[j]) < 2.0) {
        cd mid = (p[i] + p[j])/2.0;
        cd v = p[i] - mid;
        double h = sqrt(1.0 - norm(v));
        v *= cd(0,1) / abs(v);
        output = max(output, count(n, i, j, mid + v*h, p));
        output = max(output, count(n, i, j, mid - v*h, p));
      }
    }
  }
  return output;
}

int main(void) {
  while(true) {
    int n;
    cin >> n;
    if (n == 0) {
      break;
    }
    cd p[n];
    REP(i,n) {
      double x, y;
      cin >> x >> y;
      p[i] = cd(x, y);
    }
    cout << solve(n, p) << endl;
  }
}
