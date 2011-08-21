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

pair<pii, pii> sortByArea(int w1, int d1, int w2, int d2) {
  if (w1*d1 < w2*d2) {
    return make_pair(make_pair(w1, d1), make_pair(w2, d2));
  } else {
    return make_pair(make_pair(w2, d2), make_pair(w1, d1));
  }
}

pair<pii, pii> cut(pii origin, int s) {
  int cutPoint = s % (origin.first + origin.second);
  if (cutPoint < origin.first) {
    return sortByArea(cutPoint, origin.second,
        origin.first - cutPoint, origin.second);
  } else {
    cutPoint -= origin.first;
    return sortByArea(origin.first, cutPoint,
        origin.first, origin.second - cutPoint);
  }
}

vi solve(int n, int w, int d, const int* p, const int* s) {
  vector<pii> cakes;
  cakes.push_back(make_pair(w, d));
  REP(i,n) {
    pii cake = cakes[p[i]-1];
    cakes.erase(cakes.begin() + p[i]-1);
    pair<pii, pii> nextCakes = cut(cake, s[i]);
    cakes.push_back(nextCakes.first);
    cakes.push_back(nextCakes.second);
  }
  vi output;
  EACH(c,cakes) {
    output.push_back(c->first * c->second);
  }
  SORT(output);
  return output;
}

int main(void) {
  WT {
    int n, w, d;
    cin >> n >> w >> d;
    if (!w) {
      break;
    }
    int p[n], s[n];
    REP(i,n) {
      cin >> p[i] >> s[i];
    }
    vi areas = solve(n, w, d, p, s);
    cout << areas[0];
    FOR(i,1,areas.size()) {
      cout << " " << areas[i];
    }
    cout << endl;
  }
}
