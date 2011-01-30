#include<algorithm>
#include<iostream>
#include<cmath>
#include<map>

using namespace std;

typedef pair<int, int> PI;

int areaTwice(PI *log, int startIndex, int endIndex) {
  int areaSum = 0;
  for (int i = startIndex+1; i <= endIndex; i++) {
    int x1 = log[i-1].first;
    int y1 = log[i-1].second;
    int x2 = log[i].first;
    int y2 = log[i].second;
    areaSum += x1*y2-x2*y1;
  }
  return areaSum;
}

void makeAreaTableDfs(int index, PI* log, map<PI, int> &result, int startIndex, int endIndex, const int* length) {
  if (index == endIndex) {
    int area = areaTwice(log, startIndex, endIndex);
    if (result.find(log[index]) == result.end() || result[log[index]] < area) {
      result[log[index]] = area;
    }
    return;
  }
  
  for (int x = -length[index]; x <= length[index]; x++) {
    double dy = sqrt(length[index]*length[index] - x*x);
    int y = (int)dy;
    if (y*y + x*x != length[index]*length[index]) {
      continue;
    }
    log[index+1] = make_pair(log[index].first + x, log[index].second + y);
    makeAreaTableDfs(index+1, log, result, startIndex, endIndex, length);
    log[index+1] = make_pair(log[index].first + x, log[index].second - y);
    makeAreaTableDfs(index+1, log, result, startIndex, endIndex, length);
  }
}

map<PI, int> makeAreaTable(int startIndex, int endIndex, const int* length) {
  map<PI, int> result;
  PI log[endIndex+1];
  log[startIndex] = make_pair(0, 0);
  makeAreaTableDfs(startIndex, log, result, startIndex, endIndex, length);
  return result;
}

int solveFixedOrder(int n, const int* length) {
  int maxArea = -1;
  map<PI, int> table1 = makeAreaTable(0, n/2, length);
  map<PI, int> table2 = makeAreaTable(n/2, n, length);
  
  for (map<PI, int>::iterator it1 = table1.begin(); it1 != table1.end(); it1++) {
    PI inverse = make_pair(-it1->first.first, -it1->first.second);
    map<PI, int>::iterator it2 = table2.find(inverse);
    if (it2 != table2.end()) {
      maxArea = max(maxArea, it1->second + it2->second);
    }
  }
  return maxArea;
}

int solve(int n, int* length) {
  sort(length, length+n);
  int maxArea = 0;
  do {
    maxArea = max(maxArea, solveFixedOrder(n, length));
  } while (next_permutation(length+1, length+n));
  return maxArea > 0 ? maxArea/2 : -1;
}

int main(void){
  while(true) {
    int n;
    cin >> n;
    if (n == 0) {
      break;
    }
    int length[n];
    for (int i = 0; i < n; i++) {
      cin >> length[i];
    }
    cout << solve(n, length) << endl;
  }
}
