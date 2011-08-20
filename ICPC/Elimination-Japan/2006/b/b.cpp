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

string flip(const string &s) {
  string output;
  REP(i,s.size()) {
    output += s[s.size()-1-i];
  }
  return output;
}


int solve(const string &t) {
  set<string> s;
  FOR(i,1,t.size()) {
    string str[2] = {t.substr(0,i), t.substr(i,t.size() - i)};
    REP(flipFirst,2) {
      if (flipFirst == 1) {
        str[0] = flip(str[0]);
      }
      REP(flipSecond,2) {
        if (flipSecond == 1) {
          str[1] = flip(str[1]);
        }
        REP(whichFirst,2) {
          s.insert(str[whichFirst] + str[1-whichFirst]);
        }
      }
    }
  }
  return s.size();
}

int main(void) {
  int n;
  cin >> n;
  REP(i,n) {
    string train;
    cin >> train;
    cout << solve(train) << endl;
  }
}
