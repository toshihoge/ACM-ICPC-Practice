#include<cmath>
#include<iostream>
#include<vector>

using namespace std;

#define INF 1e+6
#define EPS 1e-6
#define MAX_ABS_X 100
#define OUTSIDE_ABS_BOUND 101

#define DEBUG cout<<"LINE:"<<__LINE__<<endl

typedef struct p3 {
  double x, y, z;
  p3 (double _x, double _y, double _z) {
    x = _x;
    y = _y;
    z = _z;
  }
} P3;

#define OUTP3 P3(INF, INF, INF)

typedef vector<P3> P3S;
typedef P3S::iterator P3S_IT;
typedef P3S::const_iterator P3S_CIT;
typedef vector<P3S> P3SS;
typedef P3SS::iterator P3SS_IT;
typedef P3SS::const_iterator P3SS_CIT;

typedef pair<double, double> P2;
typedef vector<P2> P2S;
typedef P2S::const_iterator P2S_IT;

bool isOutPoint3D(const P3 &p) {
  return p.x == INF;
}

P2 getMinAndMaxX(const P2S &p2s) {
  double maxx = -2*MAX_ABS_X;
  double minx = 2*MAX_ABS_X;
  for (P2S_IT it = p2s.begin(); it != p2s.end(); it++) {
    maxx = max(maxx, it->first);
    minx = min(minx, it->first);
  }
  return make_pair(maxx, minx);
}

double getCrossingHeight(const P2S &p2s, int index, double x) {
  P2 p21 = p2s[index];
  P2 p22 = p2s[(index+1)%p2s.size()];
  double x1 = p21.first;
  double x2 = p22.first;
  //ignore when horizontal line.
  if (x1 == x2 || x < min(x1, x2) || max(x1, x2) < x) {
    return INF;
  }
  double h1 = p21.second;
  double h2 = p22.second;
  return (h2 - h1) * (x - x1) / (x2 - x1) + h1;
}

double cutAndMidAtX(const P2S &p2s, double x) {
  double minH = INF;
  double maxH = -INF;
  for (int i = 0; i < p2s.size(); i++) {
    double h = getCrossingHeight(p2s, i, x);
    if (h == INF) continue;
    minH = min(minH, h);
    maxH = max(maxH, h);
  }
  return 0.5*(maxH + minH);
}

P3 findInnerPoint(const P2S &xys, const P2S &xzs) {
  pair<double, double> xRange1 = getMinAndMaxX(xys);
  pair<double, double> xRange2 = getMinAndMaxX(xzs);
  double xRangeCommonMax = min(xRange1.first, xRange2.first);
  double xRangeCommonMin = max(xRange1.second, xRange2.second);
  if (xRangeCommonMax <= xRangeCommonMin) {
    return OUTP3;
  }
  double midX = 0.5*(xRangeCommonMax + xRangeCommonMin);
  return P3(midX, cutAndMidAtX(xys, midX), cutAndMidAtX(xzs, midX));
}

int makePrevFaceIndex(int index, int size) {
  return (index-1+size) % size;
}

bool samePoint(const P3 &p1, const P3 &p2) {
  return fabs(p1.x - p2.x) < EPS && fabs(p1.y - p2.y) < EPS && fabs(p1.z - p2.z) < EPS;
}

void addPoint(P3S &points, const P3 &p) {
  for (P3S_CIT it = points.begin(); it != points.end(); it++) {
    if (samePoint(*it, p)) return;
  }
  points.push_back(p);
}

P3 outerProduct(const P3 &p1, const P3 &p2) {
  return P3(p1.y*p2.z-p2.y*p1.z, p1.z*p2.x-p2.z*p1.x, p1.x*p2.y-p2.x*p1.y);
}

double innerProduct(const P3 &p1, const P3 &p2) {
  return p1.x*p2.x + p1.y*p2.y + p1.z*p2.z;
}

double outerProductAndInnerProduct(const P3 &p1, const P3 &p2, const P3 &p3) {
  return innerProduct(outerProduct(p1, p2), p3);
}

P3 sub(const P3 &p1,const P3 &p2) {
  return P3(p1.x - p2.x, p1.y - p2.y, p1.z - p2.z);
}

P3S moveInnerPointToO(const P3 &innerPoint, const P3S &points) {
  P3S output;
  for (P3S_CIT it = points.begin(); it != points.end(); it++) {
    output.push_back(sub(*it, innerPoint));
  }
  return output;
}

P3 findAndEraseNextPoint3DForCalArea(const P3 &base, P3S &points) {
  P3S_IT currentOutputIt = points.begin();
  for (P3S_IT it = (points.begin()++); it != points.end(); it++) {
    double temp = outerProductAndInnerProduct(base, *currentOutputIt, *it);
    if (temp < 0) {
      currentOutputIt = it;
    }
  }
  P3 output = *currentOutputIt;
  points.erase(currentOutputIt);
  return output;
}

bool isOnYZPlain(const P3S &points) {
  double maxX = -INF;
  double minX = INF;
  for (P3S_CIT it = points.begin(); it != points.end(); it++) {
    maxX = max(maxX, it->x);
    minX = min(minX, it->x);
  }
  return maxX - minX < EPS;
}

double calculateArea(const P3 &innerPoint, const P3S &pointsOnFace) {
  if (pointsOnFace.size() < 3) {
    return 0.0;
  }
  P3S points = moveInnerPointToO(innerPoint, pointsOnFace);
  
  P3S_IT it = points.begin();
  P3 base = *it;
  points.erase(it);
  
  double area = 0.0;
  P3 current = findAndEraseNextPoint3DForCalArea(base, points);
  while(points.size() > 0) {
    P3 next = findAndEraseNextPoint3DForCalArea(base, points);
    area += outerProductAndInnerProduct(base, current, next) / 6.0;
    current = next;
  }
  
  return area;
}

double sumCalculateAreaSimple(const P3 &innerPoint, const P3SS &pointsOnFaces) {
  double area = 0.0;
  for (P3SS_CIT it = pointsOnFaces.begin(); it != pointsOnFaces.end(); it++) {
    area += calculateArea(innerPoint, *it);
  }
  return area;
}

bool isAlreadyCalculatedX(const vector<double> &xs, double x) {
  for (vector<double>::const_iterator it = xs.begin(); it != xs.end(); it++) {
    if (fabs(*it - x) < EPS) {
      return true;
    }
  }
  return false;
}

double sumCalculateAreaForYZPlain(const P3 &innerPoint, const P3SS &pointsOnFaces) {
  vector<double> alreadyCalculatedXs;
  double area = 0.0;
  for (P3SS_CIT it = pointsOnFaces.begin(); it != pointsOnFaces.end(); it++) {
    if (!isAlreadyCalculatedX(alreadyCalculatedXs, (*it)[0].x)) {
      area += calculateArea(innerPoint, *it);
      alreadyCalculatedXs.push_back((*it)[0].x);
    }
  }
  return area;
}

pair<P3SS, P3SS> splitOnYZPlainAndNot(const P3SS &pointsSets) {
  P3SS onYZPlain;
  P3SS notOnYZPlain;
  for (P3SS_CIT it = pointsSets.begin(); it != pointsSets.end(); it++) {
    if (isOnYZPlain(*it)) {
      onYZPlain.push_back(*it);
    } else {
      notOnYZPlain.push_back(*it);
    }
  }
  return make_pair(onYZPlain, notOnYZPlain);
}

double solve(const P2S &xys, const P2S &xzs) {
  P3 innerPoint = findInnerPoint(xys, xzs);
  if (isOutPoint3D(innerPoint)) {
    return 0.0;
  }
  
  P3SS pointsOnXysFaces;
  P3SS pointsOnXzsFaces;
  for (int i = 0; i < xys.size(); i++) {
    pointsOnXysFaces.push_back(P3S());
  }
  for (int j = 0; j < xzs.size(); j++) {
    pointsOnXzsFaces.push_back(P3S());
  }
  
  for (int i = 0; i < xys.size(); i++) {
    double x = xys[i].first;
    double y = xys[i].second;
    for (int j = 0; j < xzs.size(); j++) {
      double z = getCrossingHeight(xzs, j, x);
      if (z == INF) continue;
      P3 p = P3(x, y, z);
      addPoint(pointsOnXysFaces[i], p);
      addPoint(pointsOnXysFaces[makePrevFaceIndex(i, xys.size())], p);
      addPoint(pointsOnXzsFaces[j], p);
    }
  }
  for (int j = 0; j < xzs.size(); j++) {
    double x = xzs[j].first;
    double z = xzs[j].second;
    for (int i = 0; i < xys.size(); i++) {
      double y = getCrossingHeight(xys, i, x);
      if (y == INF) continue;
      P3 p = P3(x, y, z);
      addPoint(pointsOnXzsFaces[j], p);
      addPoint(pointsOnXzsFaces[makePrevFaceIndex(j, xzs.size())], p);
      addPoint(pointsOnXysFaces[i], p);
    }
  }
  
  P3SS pointsSets;
  for (P3SS_CIT it = pointsOnXysFaces.begin(); it != pointsOnXysFaces.end(); it++) {
    pointsSets.push_back(*it);
  }
  for (P3SS_CIT it = pointsOnXzsFaces.begin(); it != pointsOnXzsFaces.end(); it++) {
    pointsSets.push_back(*it);
  }
  
  pair<P3SS, P3SS> p = splitOnYZPlainAndNot(pointsSets);
  return sumCalculateAreaForYZPlain(innerPoint, p.first) + sumCalculateAreaSimple(innerPoint, p.second);
}

int main(void) {
  while (true) {
    int m, n;
    cin >> m >> n;
    if (m == 0 && n == 0) {
      break;
    }
    
    P2S xys;
    P2S xzs;
    for (int i = 0; i < m; i++) {
      int x, y;
      cin >> x >> y;
      xys.push_back(make_pair(x, y));
    }
    for (int j = 0; j < n; j++) {
      int x, z;
      cin >> x >> z;
      xzs.push_back(make_pair(x, z));
    }
    printf("%.10f\n", solve(xys, xzs));
  }
}
