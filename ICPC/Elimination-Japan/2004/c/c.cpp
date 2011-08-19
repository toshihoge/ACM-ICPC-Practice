#include<cmath>
#include<iostream>
#include<vector>

using namespace std;

typedef vector<int> vi;

#define DL cerr<<"Debug: "<<__LINE__<<endl
#define DUMP(x) cerr<<#x<<" = "<<(x)<<" (@"<<__LINE__<<")"<<endl
#define FOR(i,a,b) for(int i=(a);i<(int)(b);i++)
#define REP(i,n) FOR(i,0,n)

// 800 * 12000 = 9.6*10^6 < 10^7
#define EPS (1e-8)

int dfs(double sum, int mul, int count, int last, int a, int n, double t) {
  if (fabs(t - sum) < EPS) {
    return 1;
  }
  if (sum > t + EPS || count >= n) {
    return 0;
  }
  int output = 0;
  for (int i = last; i*mul <= a; i++) {
    output += dfs(sum + 1.0/(double)i, mul*i, count+1, i, a, n, t);
  }
  return output;
}

int solve(int p, int q, int a, int n) {
  return dfs(0.0, 1, 0, 1, a, n, (double)p/q);
}

int main(void) {
  while (true) {
    int p, q, a, n;
    cin >> p >> q >> a >> n;
    if (p == 0 && q == 0 && a == 0 && n == 0) {
      break;
    }
    cout << solve(p, q, a, n) << endl;
  }
}
