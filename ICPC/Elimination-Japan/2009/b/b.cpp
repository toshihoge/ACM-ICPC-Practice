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

void dfs(int i, int j, const vvi &chart, vvi &visited) {
  if (visited[i][j]) {
    return;
  }
  visited[i][j] = 1;
  FOR(a,-1,2) {
    FOR(b,-1,2) {
      int ni = i+a;
      int nj = j+b;
      if (chart[ni][nj] == 1) {
        dfs(ni, nj, chart, visited);
      }
    }
  }
}

int solve(const vvi &chart) {
  vvi visited(chart.size(), vi(chart[0].size(), 0));
  int output = 0;
  REP(i,chart.size()) {
    REP(j,chart[0].size()) {
      if (chart[i][j] == 1 && !visited[i][j]) {
        output++;
        dfs(i, j, chart, visited);
      }
    }
  }
  return output;
}

int main(void) {
  WT {
    int w, h;
    cin >> w >> h;
    if (!w) {
      break;
    }
    vvi chart(h+2, vi(w+2, 0));
    REP(i,h) {
      REP(j,w) {
        cin >> chart[i+1][j+1];
      }
    }
    cout << solve(chart) << endl;
  }
}
