#include<complex>
#include<cstdio>
#include<iostream>
#include<vector>

using namespace std;

typedef complex<double> cd;

typedef pair<cd, cd> segment;

typedef vector<double> vd;
typedef vector<cd> vcd;
typedef vector<vcd> vvcd;
typedef vcd polygon;
typedef struct {
  double r;
  cd center;
  double argMin;
  double argMax;
} arc;


// -----------------------------------------------------------------------------
// EPSILON
// -----------------------------------------------------------------------------
#define EPS 1e-6

// -----------------------------------------------------------------------------
// Macros
// -----------------------------------------------------------------------------

#define dump(x)  cerr << #x << " = " << (x) << endl;
#define debug(x) cerr << #x << " = " << (x) << " (L" << __LINE__ << ")" << " " << __FILE__ << endl;
#define EACH(i,c) for(typeof((c).begin()) i=(c).begin(); i!=(c).end(); ++i)
#define FOR(i,a,b) for(int i=(a);i<(int)(b);++i)
#define REP(i,n)  FOR(i,0,n)

// -----------------------------------------------------------------------------
// Input related methods.
// -----------------------------------------------------------------------------

cd readCd() {
  double x, y;
  cin >> x >> y;
  return cd(x, y);
}

polygon readPolygon(int n) {
  vector<cd> output;
  for (int i = 0; i < n; i++) {
    output.push_back(readCd());
  }
  return output;
}

// -----------------------------------------------------------------------------
// Debug output related methods.
// -----------------------------------------------------------------------------
void printSegment(const segment &s) {
  cout << "Segment: " << s.first << " - " << s.second << endl;
}

void printArc(const arc &a) {
  cout << "Arc: " << a.center << ", " << a.r << ", " <<
       a.center + polar(a.r, a.argMin) << "(" << a.argMin << "), " <<
       a.center + polar(a.r, a.argMax) << "(" << a.argMax << ")" << endl; 
}

void printVcd(const vcd &v) {
  cout << "--------------------" << endl;
  EACH(it, v) {
    cout<<*it<<endl;
  }
}

// -----------------------------------------------------------------------------
// Geom related methods.
// -----------------------------------------------------------------------------

arc makeArc(const double &r, const cd &center,
    const double &argMin, const double &argMax) {
  arc c;
  c.r = r;
  c.center = center;
  c.argMin = argMin;
  c.argMax = argMax;
  return c;
}

cd getPoint(const polygon &poly, int index) {
  return poly[index % poly.size()];
}

segment getSegment(const polygon &poly, int index) {
  return make_pair(getPoint(poly, index), getPoint(poly, index+1));
}

cd getNormalUnitVector(cd v) {
  return (v / abs(v)) * cd(0, 1);
}

bool equals(const cd &cd1, const cd &cd2) {
  return abs(cd1 - cd2) < EPS;
}

// -----------------------------------------------------------------------------
// "on" methods.
// -----------------------------------------------------------------------------

bool onSegment(const segment &s, const cd &p) {
  cd temp = (p - s.first) * conj(s.second - s.first);
  return abs(imag(temp)) < EPS &&
      0.0 <= real(temp) && real(temp) <= norm(s.second - s.first);
}

double normalizeArgument(
    double argument, const double &argMin, const double &argMax) {
  while (argument < argMin) {
    argument += 2.0*M_PI;
  }
  while (argument > argMax) {
    argument -= 2.0*M_PI;
  }
  return argument;
}

bool onArc(const arc &a, const cd &p) {
  if (abs(abs(p - a.center) - a.r) < EPS) {
    double argument = normalizeArgument(arg(p - a.center), a.argMin, a.argMax);
    return a.argMin <= argument && argument <= a.argMax;
  }
  return false;
}

segment shiftSegment(const segment &s, double len) {
  cd v = getNormalUnitVector(s.second - s.first);
  return make_pair(s.first + len*v, s.second + len*v);
}

#define CCW_NEUTRAL 0
#define CCW_LEFT 2
#define CCW_RIGHT 3

int ccw(const cd &p1, const cd &p2, const cd &p3) {
  cd temp = (p3 - p1) * conj(p2 - p1);
  if (imag(temp) > EPS) {
    return CCW_LEFT;
  } else if (imag(temp) < -EPS) {
    return CCW_RIGHT;
  } else {
    return CCW_NEUTRAL;
  }
}

bool turnRight(const cd &p1, const cd &p2, const cd &p3) {
  return ccw(p1, p2, p3) == CCW_RIGHT;
}

double distancePointSegment(const cd &p, const segment &s) {
  cd temp = (p - s.first) * conj(s.second - s.first);
  if (0.0 <= real(temp) && real(temp) <= norm(s.second - s.first)) {
    return abs(imag(temp)) / abs(s.second - s.first);
  }
  return min(abs(p - s.first), abs(p - s.second));
}

bool includePoint(const polygon &poly, const cd &p) {
  double argument = 0.0;
  for (int i = 0; i < (int)poly.size(); i++) {
    segment s = getSegment(poly, i);
    argument += arg((s.second - p) / (s.first - p));
  }
  // if p is inside of poly, argument is M_PI.
  return fabs(argument) > M_PI/2.0;
}

// -----------------------------------------------------------------------------
// Common Points related methods.
// -----------------------------------------------------------------------------

//p1+a1*v1 = p2+a2*v2
//a1*v1=p2-p1+a2*v2
//a1*v1/v2=(p2-p1)/v2+a2
//a1*imag(v1/v2)=imag((p2-p1)/v2)
//a1=imag((p2-p1)/v2)/imag(v1/v2)
vcd commonPointsTwoLines(const segment &l1, const segment &l2) {
  vcd output;
  cd p1 = l1.first;
  cd v1 = l1.second - l1.first;;
  cd p2 = l2.first;
  cd v2 = l2.second - l2.first;
  if (abs(imag(v1/v2)) < EPS) {
    return output;
  }
  double a1 = imag((p2-p1)/v2) / imag(v1/v2);
  output.push_back(p1 + a1*v1);
  return output;
}

vcd commonPointsTwoSegments(const segment &s1, const segment &s2) {
  vcd temp = commonPointsTwoLines(s1, s2);
  vcd output;
  EACH (it, temp) {
    if (onSegment(s1, *it) && onSegment(s2, *it)) {
      output.push_back(*it);
    }
  }
  return output;
}

// a2*x^2 + a1*X + a0 = 0
vd solveSecondDegreeEquation(double a2, double a1, double a0) {
  vd output;

  double d = a1*a1 - 4.0*a2*a0;
  if (d >= 0.0) {
    output.push_back((-a1+sqrt(d))/2.0/a2);
    output.push_back((-a1-sqrt(d))/2.0/a2);
  } else if(d > -EPS) {
    output.push_back(-a1/2.0/a2);
  }
  return output;
}

// |p+a*v-c| = r
// |a*v+(p-c)| = r
// p-c = t
// |a*v+t| = r
// |a*v+t|^2 = |r|^2
// (a*v+t)conj(a*v+t) = |r|^2
// (a*v)conj(a*v) + (a*v)conj(t) + t*conj(a*v) + t*conj(t) = |r|^2
// a and r is real number.
// v*conj(v)*a^2 + (v*conj(t) + t*conj(v))*a + t*conj(t) - r^2 = 0
// norm(v)*a^2 + 2.0*real(v*conj(t))*a + (norm(t) - r*r) = 0
vcd commonPointsLineCircle(const segment &l, const arc &crl) {
  cd p = l.first;
  cd v = l.second - l.first;
  cd c = crl.center;
  cd t = p - c;
  double r = crl.r;
  
  vd as = solveSecondDegreeEquation(
      norm(v), 2.0*real(v*conj(t)), norm(t) - r*r);
  vcd output;
  EACH (it, as) {
    cd candidate = p + *it*v;
    output.push_back(candidate);
  }
  return output;
}

vcd commonPointsSegmentCircle(const segment &s, const arc &crl) {
  vcd temp = commonPointsLineCircle(s, crl); 
  vcd output;
  EACH (it, temp) {
    if (onSegment(s, *it)) {
      output.push_back(*it);
    }
  }
  return output;
}

vcd commonPointsLineArc(const segment &l, const arc &a) {
  vcd temp = commonPointsLineCircle(l, a);
  vcd output;
  EACH (it, temp) {
    if (onArc(a, *it)) {
      output.push_back(*it);
    }
  }
  return output;
}

vcd commonPointsSegmentArc(const segment &s, const arc &a) {
  vcd temp = commonPointsLineCircle(s, a);
  vcd output;
  EACH (it, temp) {
    if (onSegment(s, *it) && onArc(a, *it)) {
      output.push_back(*it);
    }
  }
  return output;
}

vcd commonPointsTwoCircles(const arc &c1, const arc &c2) {
  vcd output;
  double r1 = c1.r;
  double r2 = c2.r;
  cd v = c2.center - c1.center;
  double acosv =
      (r1*r1 + norm(c1.center - c2.center) - r2*r2) /
      (2.0*r1*abs(c1.center - c2.center));
  if (abs(acosv) <= 1.0) {
    double argument = acos(acosv);
    double base = arg(v);
    output.push_back(c1.center + polar(r1, base + argument));
    output.push_back(c1.center + polar(r1, base - argument));
  }
  return output;
}

vcd commonPointsTwoArcs(const arc &a1, const arc &a2) {
  vcd temp = commonPointsTwoCircles(a1, a2);
  vcd output;
  EACH (it, temp) {
    if (onArc(a1, *it) && onArc(a2, *it)) {
      output.push_back(*it);
    }
  }
  return output;
}

double areaPolygonNoAbs(const polygon &p) {
  double area = 0.0;
  for (int i = 0; i < (int)p.size(); i++) {
    area += imag(getPoint(p, i+1) * conj(getPoint(p, i))) / 2.0;
  }
  return area;
}

double areaPolygon(const polygon &p) {
  return fabs(areaPolygonNoAbs(p));
}
