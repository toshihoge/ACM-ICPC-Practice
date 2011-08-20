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

#define MAX_PRIME 1000000

void makePrimeTable(bool* prime, int size) {
  fill(prime, prime+size, true);
  prime[0] = false;
  prime[1] = false;
  for(int i = 2; i*i < size; i++) {
    if (prime[i]) {
      for (int j = i; j*i < size; j++) {
        prime[j*i] = false;
      }
    }
  }
}

int solve(int a, int d, int n, const bool* prime) {
  for (int x = a; true; x += d) {
    if (prime[x]) {
      n--;
      if (n == 0) {
        return x;
      }
    }
  }
}

int main(void) {
  bool prime[MAX_PRIME];
  makePrimeTable(prime, MAX_PRIME);

  WT {
    int a, d, n;
    cin >> a >> d >> n;
    if (!a) {
      break;
    }
    cout << solve(a, d, n, prime) << endl;
  }
}
