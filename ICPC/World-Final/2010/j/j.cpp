#include<algorithm>
#include<cstdio>
#include<iostream>
#include<queue>
#include<vector>

using namespace std;

#define MAX_CUBES 1000010 // 10^6

class pyramid
{
public:
  int base;
  int cubes;
  bool high;
  pyramid(int base, int cubes, bool high);
  void printLabel() const;
};

pyramid::pyramid(int base, int cubes, bool high) :
    base(base), cubes(cubes), high(high) {
  //do noghing.
}

void pyramid::printLabel() const {
  cout << base;
  if (high) {
    cout << "H";
  } else {
    cout << "L";
  }
}

bool operator< (const pyramid &p1, const pyramid &p2) {
  return p1.cubes < p2.cubes;
}

vector<pyramid> initAllPyramids() {
  vector<pyramid> output;
  for (int base = 2, sum = 5; sum <= MAX_CUBES; base++, sum += base*base) {
    output.push_back(pyramid(base, sum, true));
  }
  for (int base = 3, sum = 10; sum <= MAX_CUBES; base += 2, sum += base*base) {
    output.push_back(pyramid(base, sum, false));
  }
  for (int base = 4, sum = 20; sum <= MAX_CUBES; base += 2, sum += base*base) {
    output.push_back(pyramid(base, sum, false));
  }
  sort(output.begin(), output.end());
  return output;
}

bool dfsDepth(int cubes, int depth, int last, vector<int> &history, const vector<pyramid> &pyramids) {
  if (depth == 0) {
    return cubes == 0;
  }
  for (int i = last-1; i >= 0; i--) {
    if (pyramids[i].cubes <= cubes) {
      history.push_back(i);
      if (dfsDepth(cubes-pyramids[i].cubes, depth-1, i, history, pyramids)) {
        return true;
      }
      history.pop_back();
    }
  }
  return false;
}

int getMaxDepth(int cubes, const vector<pyramid> &pyramids) {
  int sum = 0;
  for (int i = 0; i < pyramids.size(); i++) {
    if (sum > cubes) {
      return i;
    }
    sum += pyramids[i].cubes;
  }
  return pyramids.size();
}

void solve(int cubes, const vector<pyramid> &pyramids) {
  int maxDepth = getMaxDepth(cubes, pyramids);
  vector<int> history;
  for (int i = 1; i <= maxDepth; i++) {
    if (dfsDepth(cubes, i, pyramids.size(), history, pyramids)) {
      for (int j = 0; j < history.size(); j++) {
        cout << " ";
        pyramids[history[j]].printLabel();
      }
      cout << endl;
      return;
    }
  }
  cout << " impossible" << endl;
}

int main(void) {
  vector<pyramid> pyramids = initAllPyramids();
  
  for (int casenumber = 1; true; casenumber++) {
    int cubes;
    cin >> cubes;
    if (cubes == 0) {
      break;
    }
    printf("Case %d:", casenumber);
    solve(cubes, pyramids);
  }
}
