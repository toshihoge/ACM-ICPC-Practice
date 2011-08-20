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

#define EPS 1e-6

class Robot {
public:
  string name;
  cd initial;
  vd ts;
  vector<cd> vs;

  Robot(){}

  Robot(string name, cd initial) :
      name(name), initial(initial) {}
  void insertTandV(double t, cd v) {
    ts.push_back(t);
    vs.push_back(v);
  }

  cd getPosition(double t) const {
    cd output = initial;
    double prevT = 0.0;
    REP(i,ts.size()) {
      if (t < ts[i]) {
        return output + vs[i]*(t - prevT);
      } else {
        output += vs[i]*(ts[i] - prevT);
        prevT = ts[i];
      }
    }
    return output;
  }
};

vd solve2ndEq(double a2, double a1, double a0) {
  vd output;
  if (fabs(a2) < EPS) {
    return output;
  }
  double d = a1*a1 - 4.0*a2*a0;
  if (d < 0.0) {
    return output;
  }
  output.push_back((-a1+sqrt(d)) / (2.0*a2));
  output.push_back((-a1-sqrt(d)) / (2.0*a2));
  return output;
}

//p11 -> p12
//p21 -> p22
// p1 = p11
// v1 = p12 - p11
// p2 = p21
// v2 = p22 - p21
//|(p1 + tv1) - (p2 + tv2)| = r
//|(p1 - p2) + t(v1-v2)| = r
// p = p1 - p2 = p11 - p21
// v = v1 - v2 = p12 - p11 - p22 + p21
//|p+tv| = r
//(p+tv)conj(p+tv) = r*r
//p*conj(p) + t*(p*conj(v) + v*conj(p)) + t*t*v*conj(v) = r*r

vd calculateMeetTimes(const Robot &r1, const Robot &r2, double r) {
  vd times;
  times.push_back(0);
  EACH(t, r1.ts) {
    times.push_back(*t);
  }
  EACH(t, r2.ts) {
    times.push_back(*t);
  }
  SORT(times);
  vd output;
  FOR(i,1,times.size()) {
    double b = times[i-1];
    double e = times[i];
    cd p11 = r1.getPosition(b);
    cd p12 = r1.getPosition(e);
    cd p21 = r2.getPosition(b);
    cd p22 = r2.getPosition(e);
    cd p = p11 - p21;
    cd v = p12 - p11 - p22 + p21;
    double a2 = norm(v);
    double a1 = 2.0*real(p*conj(v));
    double a0 = norm(p) - r*r;
    vd xs = solve2ndEq(a2, a1, a0);
    REP(j,xs.size()) {
      if (0.0 <= xs[j] && xs[j] <= 1.0) {
        output.push_back(b + (e-b)*xs[j]);
      }
    }
  }
  return output;
}

void updateInformationDfs(int index, int n, bool* hasInformation,
    const cd* positions, bool* visited, double r) {
  if (visited[index]) {
    return;
  }
  visited[index] = true;
  hasInformation[index] = true;
  REP(i,n) {
    if (abs(positions[index] - positions[i]) < r) {
      updateInformationDfs(i, n, hasInformation, positions, visited, r);
    }
  }
}

void updateInformation(int n, bool* hasInformation, const cd* positions,
    double r) {
  bool visited[n];
  fill(visited, visited+n, false);
  REP(i,n) {
    if (hasInformation[i] && !visited[i]) {
      updateInformationDfs(i, n, hasInformation, positions, visited, r);
    }
  }
}

vector<string> solve(int n, int t, int r, const Robot* robots) {
  vd times;
  times.push_back(0.0);
  times.push_back(t);
  REP(i,n) {
    FOR(j,i+1,n) {
      vd meetTimes = calculateMeetTimes(robots[i], robots[j], r);
      EACH(t, meetTimes) {
        times.push_back(*t);
      }
    }
  }
  SORT(times);
  bool hasInformation[n];
  fill(hasInformation, hasInformation+n, false);
  hasInformation[0] = true;
  FOR(i,1,times.size()) {
    if (fabs(times[i] - times[i-1]) > EPS) {
      double mid = (times[i] + times[i-1])/2.0;
      cd positions[n];
      REP(j,n) {
        positions[j] = robots[j].getPosition(mid);
      }
      updateInformation(n, hasInformation, positions, r);
    }
  }
  vector<string> output;
  REP(i,n) {
    if (hasInformation[i]) {
      output.push_back(robots[i].name);
    }
  }
  SORT(output);
  return output;
}

int main(void) {
  WT {
    int n, tmax, r;
    cin >> n >> tmax >> r;
    if (!n) {
      break;
    }
    Robot robots[n];
    REP(i,n) {
      string name;
      cin >> name;
      int t0, x0, y0;
      cin >> t0 >> x0 >> y0;
      robots[i] = Robot(name, cd(x0, y0));
      WT {
        int t, vx, vy;
        cin >> t >> vx >> vy;
        robots[i].insertTandV(t, cd(vx, vy));
        if (t >= tmax) {
          break;
        }
      }
    }
    vector<string> result = solve(n, tmax, r, robots);
    EACH(s,result) {
      cout << *s << endl;
    }
  }
}
