//--------------------------------------
// Begin common header
//--------------------------------------
#include<algorithm>
#include<cmath>
#include<complex>
#include<cstdio>
#include<iostream>
#include<map>
#include<queue>
#include<set>
#include<sstream>
#include<vector>

using namespace std;

typedef pair<int, int> pii;
typedef complex<double> cd;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<double> vd;

#define DL cerr<<"Debug: "<<__LINE__<<endl
#define DUMP(x) cerr<<#x<<" = "<<(x)<<" (@"<<__LINE__<<")"<<endl
#define HAS(x,y) ((x).find(y)!=(x).end())
#define EACH(i,c) for(typeof((c).begin()) i=(c).begin(); i!=(c).end(); i++)
#define FOR(i,a,b) for(int i=(a);i<(int)(b);i++)
#define REP(i,n) FOR(i,0,n)
#define SORT(c) sort((c).begin(), (c).end())
#define WT while(true)

//--------------------------------------
// End common header
//--------------------------------------

#define N 128

string solve(const vi &sum, const vvi &has) {
  vi d(2, 0);
  int diff = abs(sum[0] - sum[1]);
  if (diff % 2 == 1) {
    return "-1";
  }
  if (sum[0] > sum[1]) {
    d[0] = diff/2;
    d[1] = 0;
  } else if (sum[0] < sum[1]) {
    d[0] = 0;
    d[1] = diff/2;
  } else {
    d[0] = 0;
    d[1] = 0;
  }

  for(int i = 0; i+max(d[0], d[1]) < N; i++) {
    if (has[0][i+d[0]] == 1 && has[1][i+d[1]] == 1) {
      ostringstream os;
      os << i+d[0] << " " << i+d[1];
      return os.str();
    }
  }
  return "-1";
}

int main(void) {
  WT {
    int n[2];
    cin >> n[0] >> n[1];
    if (!n[0]) {
      break;
    }
    vi sum(2, 0);
    vvi has(2, vi(N, 0));
    REP(i,2) {
      REP(j, n[i]) {
        int v;
        cin >> v;
        sum[i] += v;
        has[i][v] = 1;
      }
    }
    cout << solve(sum, has) << endl;
  }
}
