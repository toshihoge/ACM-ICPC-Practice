#include <algorithm>
#include <cstring>
#include "geom.hpp"

//#define SHOW_DEBUG_INFO

typedef vector<double> vd;

typedef struct {
  bool isSegment;
  segment s;
  arc a;
} element;

typedef vector<element> velement;
typedef vector<velement> vvelement;

void printElement(const element &e) {
  if (e.isSegment) {
    printSegment(e.s);
  } else {
    printArc(e.a);
  }
}

void printVElement(const velement &v) {
  cout << "----------------------------------------" << endl;
  EACH (it, v) {
    printElement(*it);
  }
}


element makeElementFromSegment(const segment &s) {
  element output;
  output.isSegment = true;
  output.s = s;
  return output;
}

element makeElementFromArc(const arc &a) {
  element output;
  output.isSegment = false;
  output.a = a;
  return output;
}

void addCircularElementIfExistable(velement &dst, const double &r,
                                   const cd &p1, const cd &p2, const cd &p3) {
  if (turnRight(p1, p2, p3)) {
    double argMin = arg((p3-p2) * cd(0, 1));
    dst.push_back(makeElementFromArc(
        makeArc(r, p2, argMin, argMin + arg((p2 - p1) * conj(p3 - p2)))));
  }
}


velement generateElementCandidates(const polygon &room, const double &r) {
  velement output;
  REP(i, room.size()) {
    output.push_back(makeElementFromSegment(
        shiftSegment(getSegment(room, i), r)));
    addCircularElementIfExistable(
        output, r, getPoint(room, i), getPoint(room, i+1), getPoint(room, i+2));
  }
  return output;
}

bool isValidRoombaPosition(const polygon &room, double r, cd p) {
  if (!includePoint(room, p)) {
    return false;
  }
  for (int i = 0; i < (int)room.size(); i++) {
    segment s = getSegment(room, i);
    double distance = distancePointSegment(p, s);
    if (distance < r - EPS) {
      return false;
    }
  }
  return true;
}

vcd commonPointsSegmentAndElement(const segment &s, const element &e) {
  if (e.isSegment) {
    return commonPointsTwoSegments(s, e.s);
  } else {
    return commonPointsSegmentArc(s, e.a);
  }
}

vcd commonPointsArcAndElement(const arc &a, const element &e) {
  if (e.isSegment) {
    return commonPointsSegmentArc(e.s, a);
  } else {
    return commonPointsTwoArcs(a, e.a);
  }
}

void addIfNew(vd &v, const double &d) {
  EACH (it, v) {
    if (abs(d - *it) < EPS) {
      return;
    }
  }
  v.push_back(d);
}

void splitSegmentElement(
    velement &output, const segment &s, const velement &src,
    const polygon &room, const double &r) {
  cd p = s.first;
  cd v = s.second - s.first;
  vd factors;
  factors.push_back(0.0);
  factors.push_back(1.0);
  EACH (it1, src) {
    vcd commonPoints = commonPointsSegmentAndElement(s, *it1);
    EACH (it2, commonPoints) {
      addIfNew(factors, abs(*it2 - s.first) / abs(s.second - s.first));
    }
  }
  sort(factors.begin(), factors.end());
  FOR (i, 1, factors.size()) {
    if (isValidRoombaPosition(room, r, p + v*(factors[i-1] + factors[i])*0.5)) {
      output.push_back(makeElementFromSegment(
          make_pair(p+v*factors[i-1], p+v*factors[i])));
    }
  }
}

void splitArcElement(
    velement &output, const arc &a, const velement &src,
    const polygon &room, const double &r) {
  vd args;
  args.push_back(a.argMin);
  args.push_back(a.argMax);
  EACH (it1, src) {
    vcd commonPoints = commonPointsArcAndElement(a, *it1);
    EACH (it2, commonPoints) {
      addIfNew(args,
          normalizeArgument(arg(*it2 - a.center), a.argMin, a.argMax));
    }
  }
  sort(args.begin(), args.end());
  FOR (i, 1, args.size()) {
    if (isValidRoombaPosition(
        room, r, a.center + polar(a.r, (args[i-1] + args[i])*0.5))) {
      output.push_back(makeElementFromArc(
          makeArc(r, a.center, args[i-1], args[i])));
    }
  }
}

velement splitElementEachOther(
    const velement &src, const polygon &room, const double &r) {
  velement output;
  EACH (it, src) {
    if (it->isSegment) {
      splitSegmentElement(output, it->s, src, room, r);
    } else {
      splitArcElement(output, it->a, src, room, r);
    }
  }
  return output;
}

cd getHeadFromElement(const element &e) {
  if (e.isSegment) {
    return e.s.second;
  } else {
    return e.a.center + polar(e.a.r, e.a.argMin);
  }
}

cd getTailFromElement(const element &e) {
  if (e.isSegment) {
    return e.s.first;
  } else {
    return e.a.center + polar(e.a.r, e.a.argMax);
  }
}

bool constructLoopDfs(
    const velement &elements, bool* visited, velement &history) {
  if (equals(
      getTailFromElement(history[0]),
      getHeadFromElement(history[history.size() - 1]))) {
    return true;
  }
  REP (i, elements.size()) {
    if (visited[i]) {
      continue;
    }
    if (equals(
        getHeadFromElement(history[history.size() - 1]),
        getTailFromElement(elements[i]))) {
      visited[i] = true;
      history.push_back(elements[i]);
      if (constructLoopDfs(elements, visited, history)) {
        return true;
      }
      history.pop_back();
      visited[i] = false;
    }
  }
  return false;
}

vvelement constructLoops(const velement &elements) {
  vvelement output;
  bool visited[elements.size()];
  fill(visited, visited + elements.size(), false);
  REP (i, elements.size()) {
    if (visited[i]) {
      continue;
    }
    visited[i] = true;
    velement history;
    history.push_back(elements[i]);
    if (constructLoopDfs(elements, visited, history)) {
      output.push_back(history);
    }
  }
  return output;
}

void addEdge(polygon &poly, cd src, cd dst) {
  if (poly.size() == 0) {
    poly.push_back(src);
    poly.push_back(dst);
  } else {
    if (!equals(poly[poly.size() - 1], src)) {
      cerr << "Point Jumped!!!" << endl;
    }
    if (poly.size() >= 2 && equals(poly[poly.size() - 2], dst)) {
      poly.pop_back();
      return;
    }
    poly.push_back(dst);
  }
}

vcd bumpUp(const velement &loop, double r) {
  vcd output;
  REP(i, loop.size()) {
    if (loop[i].isSegment) {
      segment shifted = shiftSegment(loop[i].s, -r);
      addEdge(output, loop[i].s.first, shifted.first);
      addEdge(output, shifted.first, shifted.second);
      addEdge(output, shifted.second, loop[i].s.second);
    } else {
      addEdge(
          output,
          loop[i].a.center + polar(loop[i].a.r, loop[i].a.argMax),
          loop[i].a.center);
      addEdge(
          output,
          loop[i].a.center,
          loop[i].a.center + polar(loop[i].a.r, loop[i].a.argMin));
    }
  }
  if (output.size() >= 1) {
    if (equals(output[0], output[output.size() - 1])) {
      output.pop_back();
    }
  }
  if (output.size() >= 3) {
    if (equals(output[0], output[output.size() - 2])) {
      output.pop_back();
      output.pop_back();
    } else if(equals(output[1], output[output.size() - 1])) {
      //pop front twice.
      output.erase(output.begin());
      output.erase(output.begin());
    }
  }
  return output;
}

vvcd bumpUpEach(const vvelement &loops, double r) {
  vvcd output;
  EACH (it, loops) {
    output.push_back(bumpUp(*it, r));
  }
  return output;
}

bool onOneOfSegment(const polygon &room, const cd &p) {
  REP(i, room.size()) {
    if (onSegment(getSegment(room, i), p)) {
      return true;
    }
  }
  return false;
}

double cleanableArea(
    const polygon &bumpUped, const polygon &room, const double &r) {
  double argumentSum = 0.0;
  REP(i, bumpUped.size()) {
    cd p0 = getPoint(bumpUped, i);
    cd p1 = getPoint(bumpUped, i+1);
    cd p2 = getPoint(bumpUped, i+2);
    if (!onOneOfSegment(room, p1)) {
      argumentSum += arg((p2 - p1) / (p0 - p1));
    }
  }
  return argumentSum*r*r/2.0 + areaPolygon(bumpUped);
}

bool showDebugInfo = false;

double solve(const polygon &room, const cd &src, const double &r) {
  velement elementCandidates = generateElementCandidates(room, r);
  if (showDebugInfo) {
    debug("generateElementCandidates done.");
    printVElement(elementCandidates);
  }
  velement splittedElements = splitElementEachOther(elementCandidates, room, r);
  if (showDebugInfo) {
    debug("splitElementEachOther done.");
    printVElement(splittedElements);
  }
  vvelement loops = constructLoops(splittedElements);
  if (showDebugInfo) {
    debug("constructLoops done.");
    debug(loops.size());
    EACH (it, loops) {
      printVElement(*it);
    }
  }
  vvcd bumpUps = bumpUpEach(loops, r);
  if (showDebugInfo) {
    debug("bumpUpEach done.");
    EACH (it, bumpUps) {
      printVcd(*it);
    }
  }
  EACH (it, bumpUps) {
    if (includePoint(*it, src)) {
      return cleanableArea(*it, room, r);
    }
  }
  return -1.0;
}

int main(int argc, char* argv[]) {
  if (argc >= 2) {
    if (strcmp(argv[1], "-v") == 0) {
      showDebugInfo = true;
    }
  }
  while (true) {
    int n;
    if (!(cin >> n) || n == 0) {
      break;
    }

    cd src = readCd();
    double r;
    cin >> r;
    polygon room = readPolygon(n);
    if (showDebugInfo) {
      cout << "-------------" << endl;
      cout << "START SOLVING" << endl;
      cout << "-------------" << endl;
    }
    double result = solve(room, src, r);
    if (showDebugInfo) {
      cout << "--------------" << endl;
      cout << "FINISH SOLVING" << endl;
      cout << "--------------" << endl;
    }
    printf("%.10f\n", result);
  }
}
