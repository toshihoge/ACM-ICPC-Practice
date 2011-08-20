#include<cmath>
#include<complex>
#include<cstdio>
#include<iostream>
#include<map>
#include<queue>
#include<set>
#include<vector>

using namespace std;

typedef pair<int, int> pii;
typedef complex<double> cd;
typedef vector<int> vi;
typedef vector<vi> vvi;

#define DL cerr<<"Debug: "<<__LINE__<<endl
#define DUMP(x) cerr<<#x<<" = "<<(x)<<" (@"<<__LINE__<<")"<<endl
#define HAS(x,y) ((x).find(y)!=(x).end())
#define EACH(i,c) for(typeof((c).begin()) i=(c).begin(); i!=(c).end(); i++)
#define FOR(i,a,b) for(int i=(a);i<(int)(b);i++)
#define REP(i,n) FOR(i,0,n)
#define WT while(true)

int calculateSimpleInterest(int init, int year, double rate, int fee) {
  int interest = 0;
  REP(i,year) {
    interest += (int)((double)init * rate);
    init -= fee;
  }
  return init + interest;
}

int calculateComposedInterest(int init, int year, double rate, int fee) {
  REP(i,year) {
    init += (int)((double)init * rate) - fee;
  }
  return init;
}

int calculate(int init, int year, int type, double rate, int fee) {
  if (type == 0) {
    return calculateSimpleInterest(init, year, rate, fee);
  } else {
    return calculateComposedInterest(init, year, rate, fee);
  }
}

int main(void) {
  int m;
  cin >> m;
  REP(x,m) {
    int init, year, n;
    cin >> init >> year >> n;
    int output = 0;
    REP(i,n) {
      int type, fee;
      double rate;
      cin >> type >> rate >> fee;
      output = max(output, calculate(init, year, type, rate, fee));
    }
    cout << output << endl;
  }
}
