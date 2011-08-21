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

int solve(int n, int p) {
  int candidates[n];
  fill(candidates, candidates+n, 0);
  int bowl = p;
  int index = 0;
  WT {
    if (bowl == 0) {
      bowl = candidates[index];
      candidates[index] = 0;
    } else {
      bowl--;
      candidates[index]++;
      if (candidates[index] == p) {
        return index;
      }
    }
    index++;
    index %= n;
  }
}

int main(void) {
  WT {
    int n, p;
    cin >> n >> p;
    if (!n) {
      break;
    }
    cout << solve(n, p) << endl;
  }
}
