#include<algorithm>
#include "geom.hpp"

#define NUM_BOX 4

#define INF 1e+8

vector<arc> makeArcVector(const polygon &box, const vd &distances, int len) {
  vector<arc> arcs;
  REP(i, box.size()) {
    if (distances[i] < len) {
      arcs.push_back(makeArc(len - distances[i], box[i],
          (i-3)*M_PI/2.0, i*M_PI/2.0));
    }
  }
  return arcs;
}

vector<segment> makeSplitter(const polygon &box, cd p1, cd p2) {
  vector<segment> splitters;
  splitters.push_back(make_pair(cd(0, 0), p1));
  splitters.push_back(make_pair(cd(0, 0), p2));
  REP(i, box.size()) {
    splitters.push_back(getSegment(box, i));
  }
  return splitters;
}

vector<arc> splitArcs(const vector<arc> &arcs,
    const vector<segment> &splitterSegments) {
  vector<arc> output;
  REP(i, arcs.size()) {
    vd arguments;
    arguments.push_back(arcs[i].argMin);
    arguments.push_back(arcs[i].argMax);
    REP(j, arcs.size()) {
      if (j == i) {
        continue;
      }
      vcd points = commonPointsTwoArcs(arcs[j], arcs[i]);
      REP(k, points.size()) {
        arguments.push_back(normalizeArgument(
            arg(points[k] - arcs[i].center), arcs[i].argMin, arcs[i].argMax));
      }
    }
    REP(j, splitterSegments.size()) {
      vcd points = commonPointsLineArc(splitterSegments[j], arcs[i]);
      REP(k, points.size()) {
        arguments.push_back(normalizeArgument(
            arg(points[k] - arcs[i].center), arcs[i].argMin, arcs[i].argMax));
      }
    }
    sort(arguments.begin(), arguments.end());
    double prev = arguments[0];
    for (int j = 1; j < arguments.size(); j++) {
      if (arguments[j] - prev < EPS) {
        continue;
      }
      output.push_back(makeArc(arcs[i].r, arcs[i].center, prev, arguments[j]));
      prev = arguments[j];
    }
  }
  return output;
}

bool crossWithBox(const segment &s, const polygon &box) {
  REP(i, box.size()) {
    vcd temp = commonPointsTwoSegments(s, getSegment(box, i));
    if (temp.size() > 0 && abs(temp[0] - s.first) > EPS &&
        abs(temp[0] - s.second) > EPS) {
      return true;
    }
  }
  return false;
}

double nearestDistance(cd p, const polygon &box, const vcd &points,
    const vd &distances) {
  double output = INF;
  REP(i, points.size()) {
    segment s = make_pair(p, points[i]);
    if (!crossWithBox(make_pair(p, points[i]), box)) {
      output = min(output, distances[i] + abs(p - points[i]));
    }
  }
  return output;
}

bool isOutmostArc(const arc& a, const polygon &box, const vcd &points,
    const vd &distances, double len) {
  return fabs(nearestDistance(a.center + polar(a.r, (a.argMin + a.argMax)*0.5),
      box, points, distances) - len) < EPS;
}

double calculateLengthBehindBuilding(
    int len, const polygon &box, vd distances, vector<segment> splitters) {
  vector<arc> splittedArcs = splitArcs(
      makeArcVector(box, distances, len), splitters);
  double sum = 0.0;
  vcd points = box;
  points.push_back(cd(0, 0));
  vd distancesWithOrigin = distances;
  distancesWithOrigin.push_back(0.0);
  REP(i, splittedArcs.size()) {
    arc a = splittedArcs[i];
    if (isOutmostArc(a, box, points, distancesWithOrigin, len)) {
      sum += a.r*(a.argMax - a.argMin);
    }
  }
  return sum;
}

double calculateCrossAngleOrDefault(
    int len, const cd &p, const cd &target) {
  vcd points = commonPointsSegmentCircle(make_pair(p, target),
      makeArc(len, cd(0, 0), -M_PI, M_PI));
  if (points.size() > 0) {
    return arg(points[0]);
  } else {
    return arg(target);
  }
}

double calculateVisibleAngleLocatedFirstQuadrant(
    int len, cd leftBottom, cd rightBottom, cd leftTop) {
  return calculateCrossAngleOrDefault(len, leftBottom, leftTop) -
      calculateCrossAngleOrDefault(len, leftBottom, rightBottom);
}
    
double calculateVisibleAngleLocatedFirstOrSecondQuadrant(
    int len, int xmin, cd leftPositive, cd leftNegative) {
  cd leftBase = cd(xmin, 0);
  return calculateCrossAngleOrDefault(len, leftBase, leftPositive) -
      calculateCrossAngleOrDefault(len, leftBase, leftNegative);
}

double solveWhenLocatedFirstQuadrant(
    int len, int xmin, int ymin, int xmax, int ymax) {
  cd nearest = cd(xmin, ymin);
  if (len <= abs(nearest)) {
    return 2.0 * M_PI * len;
  }
  polygon box;
  box.push_back(cd(xmin, ymin));
  box.push_back(cd(xmax, ymin));
  box.push_back(cd(xmax, ymax));
  box.push_back(cd(xmin, ymax));

  vd distances;
  distances.push_back(INF);
  distances.push_back(abs(box[1]));
  if (abs(box[1]) + ymax - ymin < abs(box[3]) + xmax - xmin) {
    distances.push_back(abs(box[1]) + ymax - ymin);
  } else {
    distances.push_back(abs(box[3]) + xmax - xmin);
  }
  distances.push_back(abs(box[3]));
  return len*(2.0*M_PI - calculateVisibleAngleLocatedFirstQuadrant(
      len, box[0], box[1], box[3])) +
      calculateLengthBehindBuilding(len, box, distances, makeSplitter(box, box[1], box[3]));
}

double solveWhenLocatedFirstOrSecondQuadrant(
    int len, int xmin, int xmax, int ypositive, int ynegative) {
  if (len <= xmin) {
    return 2.0 * M_PI * len;
  }
  polygon box;
  box.push_back(cd(xmin, ynegative));
  box.push_back(cd(xmax, ynegative));
  box.push_back(cd(xmax, ypositive));
  box.push_back(cd(xmin, ypositive));
  vd distances;
  distances.push_back(abs(box[0]));
  distances.push_back(abs(box[0]) + xmax - xmin);
  distances.push_back(abs(box[3]) + xmax - xmin);
  distances.push_back(abs(box[3]));
  return len*(2.0*M_PI - calculateVisibleAngleLocatedFirstOrSecondQuadrant(
      len, xmin, box[3], box[0])) +
      calculateLengthBehindBuilding(len, box, distances, makeSplitter(box, box[0], box[3]));
}

double solve(int len, int xmin, int ymin, int xmax, int ymax) {
  if (xmin >= 0 && ymin >= 0) {
    return solveWhenLocatedFirstQuadrant(
        len, xmin, ymin, xmax, ymax);
  } else if (xmax <= 0 && ymin >= 0) {
    return solveWhenLocatedFirstQuadrant(
        len, abs(xmax), ymin, abs(xmin), ymax);
  } else if (xmax <= 0 && ymax <= 0) {
    return solveWhenLocatedFirstQuadrant(
        len, abs(xmax), abs(ymax), abs(xmin), abs(ymin));
  } else if (xmin >= 0 && ymax <= 0) {
    return solveWhenLocatedFirstQuadrant(
        len, xmin, abs(ymax), xmax, abs(ymin));
  } else if (xmin > 0) {
    return solveWhenLocatedFirstOrSecondQuadrant(
        len, xmin, xmax, ymax, ymin);
  } else if (xmax < 0) {
    return solveWhenLocatedFirstOrSecondQuadrant(
        len, abs(xmax), abs(xmin), ymax, ymin);
  } else if (ymin > 0) {
    return solveWhenLocatedFirstOrSecondQuadrant(
        len, ymin, ymax, xmax, xmin);
  } else if (ymax < 0) {
    return solveWhenLocatedFirstOrSecondQuadrant(
        len, abs(ymax), abs(ymin), xmax, xmin);
  } else {
    debug("UnSupported problem instance");
    cerr << len << " " << xmin << " " << ymin << " "
        << xmax << " " << ymax << endl;
    return -1;
  }
}

int main(void) {
  while (true) {
    int len, x1, y1, x2, y2;
    cin >> len >> x1 >> y1 >> x2 >> y2;
    if (len == 0) {
      break;
    }
    printf("%.6f\n", solve(len, x1, y1, x2, y2));
  }
}
