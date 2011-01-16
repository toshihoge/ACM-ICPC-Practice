#include<iostream>
#include<complex>

using namespace std;

typedef complex<double> cd;
typedef pair<cd, cd> Segment;

#define EPS 1e-6
#define INF 1e+6
#define NO_POINT cd(INF, INF)
#define OUT_INDEX -1

#define DEBUG cout<<"DEBUG: "<<__LINE__<<endl

cd mirrorCd(Segment &axis, cd src) {
  cd v = axis.second - axis.first;
  return conj((src - axis.first)/v)*v+axis.first;
}

Segment mirrorSegment(Segment &axis, Segment &src) {
  return make_pair(mirrorCd(axis, src.first), mirrorCd(axis, src.second));
}

//p0+a0*v0 = p1+a1*v1
//a0*v0 = p1-p0+a1*v1
//a0*v0 = p1-p0+a1*v1
//a0*v0/v1 = (p1-p0)/v1+a1
//a0*imag(v0/v1) = imag((p1-p0)/v1)
//a0 = imag((p1-p0)/v1) / imag(v0/v1)

cd cross(cd p0, cd v0, cd p1, cd v1) {
  if (abs(imag(v0/v1)) < EPS) {
    return NO_POINT;
  }
  double a0 = imag((p1-p0)/v1) / imag(v0/v1);
  double a1 = imag((p0-p1)/v0) / imag(v1/v0);
  
  if (0.0 < a0 && a0 < 1.0 && 0.0 < a1 && a1 < 1.0) {
    return p0+a0*v0;
  }
  return NO_POINT;
}

pair<int, cd> getNearestHit(int exceptIndex, int n, const Segment* segments, cd src, cd dst) {
  int outputIndex = OUT_INDEX;
  cd outputCd = NO_POINT;
  
  for (int i = 0; i < n; i++) {
    if (i == exceptIndex) continue;
    cd p = cross(segments[i].first, segments[i].second-segments[i].first, src, dst-src);
    if (p == NO_POINT) continue;
    if (abs(p-src) < abs(outputCd-src)) {
      outputCd = p;
      outputIndex = i;
    }
  }
  return make_pair(outputIndex, outputCd);
}

double verify(int* log, int size, int n, const Segment* segments, cd src, cd dst) {
  Segment segmentsMirrored[size+1][n];
  cd dstMirrored[size+1];
  
  for (int i = 0; i < n; i++) {
    segmentsMirrored[0][i] = segments[i];
  }
  dstMirrored[0] = dst;
  
  for (int i = 0; i < size; i++) {
    Segment axis = segmentsMirrored[i][log[i]];
    segmentsMirrored[i+1][log[i]] = axis;
    for (int j = 0; j < n; j++) {
      if (j == log[i]) {
        segmentsMirrored[i+1][j] = segmentsMirrored[i][j];
      } else {
        segmentsMirrored[i+1][j] = mirrorSegment(axis, segmentsMirrored[i][j]);
      }
    }
    
    dstMirrored[i+1] = mirrorCd(axis, dstMirrored[i]);
  }
  
  cd finalMirroredDst = dstMirrored[size];
  int exceptIndex = -1;
  cd currentSrc = src;
  for (int i = 0; i < size; i++) {
    pair<int, cd> p = getNearestHit(exceptIndex, n, segmentsMirrored[i], currentSrc, finalMirroredDst);
    if (p.first != log[i]) {
      return INF;
    }
    exceptIndex = p.first;
    currentSrc = p.second;
  }
  pair<int, cd> p = getNearestHit(exceptIndex, n, segmentsMirrored[size], currentSrc, finalMirroredDst);
  if (p.first != OUT_INDEX) {
    return INF;
  }
  return abs(finalMirroredDst - src);
}

double dfs(int index, int* log, int n, const Segment* segments, cd src, cd dst) {
  double answer = verify(log, index, n, segments, src, dst);
  
  if (index < 5) {
    for (int i = 0; i < n; i++) {
      if (index == 0 || log[index-1] != i) {
        log[index] = i;
        answer = min(answer, dfs(index+1, log, n, segments, src, dst));
      }
    }
  }
  return answer;
}

int main(void) {
  while (true) {
    int n;
    cin >> n;
    if (n == 0) {
      break;
    }
    Segment segments[n];
    for (int i = 0; i < n; i++) {
      double px, py, qx, qy;
      cin >> px >> py >> qx >> qy;
      segments[i] = make_pair(cd(px, py), cd(qx, qy));
    }
    double tx, ty, lx, ly;
    cin >> tx >> ty >> lx >> ly;
    int log[5];
    printf("%.4f\n", dfs(0, log, n, segments, cd(tx, ty), cd(lx, ly)));
  }
}
