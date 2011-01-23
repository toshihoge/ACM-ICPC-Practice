#include<iostream>
#include<complex>
#include<vector>
#include<queue>
#include<cstdio>
#include<cstdlib>

using namespace std;

typedef complex<double> cd;
typedef pair<cd, cd> edge;

#define EPS 1e-6
#define INF 1e+10

#define M_PI 3.14159265358979323846

#define NON_POINT cd(INF, INF)

double round(double x) {
  return floor(x+0.5);
}

//p1+a1*v1=p2+a2*v2
//a1*v1=(p2-p1)+a2*v2
//a1*v1=(p2-p1)+a2*v2
//a1*v1/v2=(p2-p1)/v2+a2
//a1*imag(v1/v2)=imag((p2-p1)/v2)

cd cross(edge e1, edge e2) {
  cd p1 = e1.first;
  cd v1 = e1.second - e1.first;
  cd p2 = e2.first;
  cd v2 = e2.second - e2.first;
  if (abs(imag(v1/v2)) < EPS) {
    return NON_POINT;
  }
  double a1 = imag((p2-p1)/v2) / imag(v1/v2);
  double a2 = imag((p1-p2)/v1) / imag(v2/v1);
  if (-EPS<a1 && a1<1.0+EPS && -EPS<a2 && a2<1.0+EPS) {
    return p1+a1*v1;
  }
  return NON_POINT;
}

bool online(cd p, edge e) {
  cd diff = (p-e.first) / (e.second-e.first);
  return -EPS < real(diff) && real(diff) < 1.0+EPS && abs(imag(diff)) < EPS;
}

bool include(cd p, const vector<edge> &belts) {
  for (int i = 0; i < belts.size(); i++) {
    if (online(p, belts[i])) {
      return false;
    }
  }
  while (true) {
    int crossC = 0;
    edge e = make_pair(p, p+polar(40000.0, 2.0*M_PI*rand() / RAND_MAX));
    for (int i = 0; i < belts.size(); i++) {
      cd crossP = cross(e, belts[i]);
      if (crossP == NON_POINT) continue;
      if (abs(crossP - belts[i].first) < EPS || abs(crossP - belts[i].second) < EPS) {
        crossC = -1;
        break;
      }
      crossC++;
    }
    if (crossC >= 0) {
      return crossC % 2 == 1;
    }
  }
}

bool connect(cd src, cd dst, const vector<edge> &belts) {
  edge e = make_pair(src, dst);
  for (int i = 0; i < belts.size(); i++) {
    cd p = cross(e, belts[i]);
    if (p != NON_POINT && abs(p - src) > EPS && abs(p - dst) > EPS) {
      return false;
    }
  }
  return !include((src+dst)*0.5, belts);
}

vector<double> generateArray(const vector<edge> &belts, cd p, double vp) {
  int n = belts.size();
  vector<vector<double> > matrix(n+1, vector<double>(n+1));
  for (int i = 0; i < n; i++) {
    matrix[i][i] = 0.0;
    for (int j = i+1; j <= n; j++) {
      cd dst = j < n ? belts[j].first : p;
      if (connect(belts[i].first, dst, belts)) {
        matrix[i][j] = abs(belts[i].first - dst) / vp;
        matrix[j][i] = matrix[i][j];
      } else {
        matrix[i][j] = INF;
        matrix[j][i] = INF;
      }
    }
  }
  
  for (int k = 0; k <= n; k++) {
    for (int i = 0; i <= n; i++) {
      for (int j = 0; j <= n; j++) {
        matrix[i][j] = min(matrix[i][j], matrix[i][k] + matrix[k][j]);
      }
    }
  }
  
  return matrix[n];
}

cd getLuggagePosition(const vector<edge> &belts, double v, double sec, double oneRoundTime) {
  sec -= floor(sec/oneRoundTime)*oneRoundTime;
  for (int i = 0; true; i++) {
    if (i >= belts.size()) {
      i -= belts.size();
    }
    cd vec = belts[i].second - belts[i].first;
    if (abs(vec) > v*sec) {
      return belts[i].first + vec*v*sec/abs(vec);
    }
    sec -= abs(vec) / v;
  }
}

bool acceptable(double time, const vector<edge> &belts, cd p, double vl, double vp, const vector<double> &array, double oneRoundTime) {
  cd dst = getLuggagePosition(belts, vl, time, oneRoundTime);
  for (int i = 0; i < belts.size(); i++) {
    if (array[i]+abs(belts[i].first - dst)/vp < time && connect(belts[i].first, dst, belts)) {
      return true;
    }
  }
  if (abs(p - dst)/vp < time && connect(p, dst, belts)) {
    return true;
  }
  return false;
}

double getTotalLength(const vector<edge> &belts) {
  double sum = 0.0;
  for (int i = 0; i < belts.size(); i++) {
    sum += abs(belts[i].second - belts[i].first);
  }
  return sum;
}

int solve(const vector<edge> &belts, cd p, double vl, double vp) {
  vector<double> array = generateArray(belts, p, vp);
  double oneRoundLength = getTotalLength(belts);
  double oneRoundTime = oneRoundLength / vl;
  
  int count = 0;
  double minsec = 0.0;
  double maxsec = 1000000000.0;
  while (round(minsec) != round(maxsec) && count < 53) {
    double mid = (maxsec + minsec) * 0.5;
    if (acceptable(mid, belts, p, vl, vp, array, oneRoundTime)) {
      maxsec = mid;
    } else {
      minsec = mid;
    }
    count++;
  }
  return (int)round((maxsec + minsec) * 0.5);
}

int main(void) {
  for (int casenumber = 1; true; casenumber++) {
    int n;
    cin >> n;
    if (n == 0) {
      break;
    }
    cd p[n];
    vector<edge> belts;
    double x, y, vl, vp;
    for (int i = 0; i < n; i++) {
      cin >> x >> y;
      p[i] = cd(x, y);
    }
    for (int i = 0; i < n; i++) {
      belts.push_back(make_pair(p[i], p[(i+1)%n]));
    }
    cin >> x >> y >> vl >> vp;
    int answer = solve(belts, cd(x, y), vl/60.0, vp/60.0);
    printf("Case %d: Time = %d:%02d\n", casenumber, answer/60, answer%60);
  }
}
