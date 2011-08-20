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

typedef complex<int> ci;
typedef vector<ci> vci;

#define DL cerr<<"Debug: "<<__LINE__<<endl
#define DUMP(x) cerr<<#x<<" = "<<(x)<<" (@"<<__LINE__<<")"<<endl
#define HAS(x,y) ((x).find(y)!=(x).end())
#define EACH(i,c) for(typeof((c).begin()) i=(c).begin(); i!=(c).end(); i++)
#define FOR(i,a,b) for(int i=(a);i<(int)(b);i++)
#define REP(i,n) FOR(i,0,n)
#define WT while(true)

vci read() {
  int m;
  cin >> m;
  vci output;
  REP(i,m) {
    int x, y;
    cin >> x >> y;
    output.push_back(ci(x, y));
  }
  return output;
}

vci reverse(const vci &input) {
  vci output;
  REP(i,input.size()) {
    output.push_back(input[input.size() - 1 - i]);
  }
  return output;
}

vci normalize(const vci &input) {
  vci output;
  EACH(it, input) {
    output.push_back(*it - input[0]);
  }
  ci rotator;
  if (imag(output[1]) > 0) {
    rotator = ci(0, -1);
  } else if (real(output[1]) < 0) {
    rotator = ci(-1, 0);
  } else if (imag(output[1]) < 0) {
    rotator = ci(0, 1);
  } else {
    rotator = ci(1, 0);
  }
  EACH(it, output) {
    *it *= rotator;
  }
  return output;
}

bool equal(const vci& v1, const vci& v2) {
  if (v1.size() != v2.size()) {
    return false;
  }
  REP(i,v1.size()) {
    if (v1[i] != v2[i]) {
      return false;
    }
  }
  return true;
}

bool equal2(const vci* vs, const vci &v) {
  REP(i,2) {
    if (equal(vs[i], v)) {
      return true;
    }
  }
  return false;
}

int main(void) {
  WT {
    int n;
    cin >> n;
    if (!n) {
      break;
    }
    vci pattern = read();
    vci normalized[2] = {normalize(pattern), normalize(reverse(pattern))};
    REP(i, n) {
      vci test = normalize(read());
      if (equal2(normalized, test)) {
        cout << (i+1) << endl;
      }
    }
    cout << "+++++" << endl;
  }
}
