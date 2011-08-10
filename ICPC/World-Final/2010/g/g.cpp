#include<cstdio>
#include<complex>
#include<iostream>
#include<vector>

using namespace std;

typedef complex<double> cd;

#define MAX_N 512
#define EPS 1e-6
#define BSEARCH_NUMBER 64

//Global
double lengths[MAX_N];

int findMaxLengthIndex(int begin, int end) {
  int maxIndex = begin;
  for (int i = begin+1; i < end; i++) {
    if (lengths[i] > lengths[maxIndex]) {
      maxIndex = i;
    }
  }
  return maxIndex;
}

double sumArgument(double r, int begin, int end, int maxIndex,
    bool flipMaxIndex) {
  double output = 0.0;
  for (int i = begin; i < end; i++) {
    double argument = 2.0*asin(0.5*lengths[i]/r);
    if (i == maxIndex && flipMaxIndex) {
      output += 2.0*M_PI - argument;
    } else {
      output += argument;
    }
  }
  return output;
}

bool isRTooLarge(double r, int begin, int end, int maxIndex, bool flipMaxIndex) {
  if (flipMaxIndex) {
    return sumArgument(r, begin, end, maxIndex, flipMaxIndex) > 2.0*M_PI;
  } else {
    return sumArgument(r, begin, end, maxIndex, flipMaxIndex) < 2.0*M_PI;
  }
}

double findR(int begin, int end, int maxIndex, bool flipMaxIndex) {
  double minR = 0.5*lengths[maxIndex];
  double maxR;
  for (maxR = minR; 
      !isRTooLarge(maxR, begin, end, maxIndex, flipMaxIndex); maxR *= 2.0);
  for (int i = 0; i < BSEARCH_NUMBER; i++) {
    double midR = 0.5*(maxR + minR);
    if (isRTooLarge(midR, begin, end, maxIndex, flipMaxIndex)) {
      maxR = midR;
    } else {
      minR = midR;
    }
  }
  return 0.5*(maxR + minR);
}

double calculateArea(double r, int begin, int end, int maxIndex,
    bool flipMaxIndex) {
  double area = 0.0;
  for (int i = begin; i < end; i++) {
    double hlen = 0.5*lengths[i];
    double h = sqrt(r*r - hlen*hlen);
    double a = h*hlen;
    if (i == maxIndex && flipMaxIndex) {
      area -= a;
    } else {
      area += a;
    }
  }
  return area;
}

bool canBePolygon(int begin, int end, int maxIndex) {
  int totalLengthExceptMaxIndex = 0.0;
  for (int i = begin; i < end; i++) {
    if (i == maxIndex) {
      continue;
    }
    totalLengthExceptMaxIndex += lengths[i];
  }
  return totalLengthExceptMaxIndex > lengths[maxIndex] + EPS;
}

double calculateMaxArea(int begin, int end, int maxIndex) {
  if (!canBePolygon(begin, end, maxIndex)) {
    return 0.0;
  }
  bool flipMaxIndex =
      isRTooLarge(0.5*lengths[maxIndex], begin, end, maxIndex, false);
  return calculateArea(findR(begin, end, maxIndex, flipMaxIndex),
      begin, end, maxIndex, flipMaxIndex);
}

double solveWithRange(int begin, int end, vector<vector<double> > &dptable) {
  if (end - begin < 3) {
    return 0.0;
  }
  if (dptable[begin][end] >= 0.0) {
    return dptable[begin][end];
  }
  int maxIndex = findMaxLengthIndex(begin, end);
  double area = calculateMaxArea(begin, end, maxIndex);
  area = max(area, solveWithRange(begin, maxIndex, dptable) +
      solveWithRange(maxIndex+1, end, dptable));
  dptable[begin][end] = area;
  return area;
}

double solve(int n) {
  vector<vector<double> > dptable(n+1, vector<double>(n+1, -1.0));
  return solveWithRange(0, n, dptable);
}

int main(void) {
  for (int casenumber=1; true; casenumber++) {
    int n;
    cin >> n;
    if (n == 0) {
      break;
    }
    for (int i = 0; i < n; i++) {
      cin >> lengths[i];
    }
    printf("Case %d: %.10f\n", casenumber, solve(n));
  }
}
