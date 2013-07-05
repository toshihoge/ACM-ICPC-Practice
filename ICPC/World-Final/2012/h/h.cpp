#include<algorithm>
#include<iostream>
#include<vector>

using namespace std;

typedef vector<int> vi;
typedef pair<int, int> pii;
typedef vector<pii> vpii;

#define INF (1<<28)
#define MAX_N 512

int costTable[MAX_N][MAX_N];

vi calculateMergeCosts(int begin, int width, const int* dolls) {
  vpii sizeIndexList;
  for (int i = begin; i < begin+width; i++) {
    sizeIndexList.push_back(make_pair(dolls[i], i - begin));
  }
  sort(sizeIndexList.begin(), sizeIndexList.end());
  int minIndex = INF;
  int maxIndex = 0;
  int minSideBonus[width];
  int maxSideBonus[width];
  fill(minSideBonus, minSideBonus+width, 0);
  fill(maxSideBonus, maxSideBonus+width, 0);
  for (int i = 0; i < width; i++) {
    int index = sizeIndexList[i].second;
    minIndex = min(minIndex, index);
    maxIndex = max(maxIndex, index);
    minSideBonus[minIndex] = i+1;
    maxSideBonus[maxIndex] = i+1;
  }
  for (int i = 1; i < width; i++) {
    maxSideBonus[i] = max(maxSideBonus[i], maxSideBonus[i-1]);
  }
  for (int i = width-1; i > 0; i--) {
    minSideBonus[i-1] = max(minSideBonus[i-1], minSideBonus[i]);
  }
  vi cost;
  cost.push_back(0);
  for (int i = 1; i < width; i++) {
    cost.push_back(width - maxSideBonus[i-1] - minSideBonus[i]);
  }
  cost.push_back(0);
  return cost;
}

int calculateCombineCost(int begin, int width, const int* dolls) {
  vi mergeCosts = calculateMergeCosts(begin, width, dolls);
  int cost = INF;
  for (int frontWidth = 1; frontWidth <= width-1; frontWidth++) {
    int tempCost = costTable[begin][frontWidth] +
        costTable[begin+frontWidth][width - frontWidth] + 
        mergeCosts[frontWidth];
    cost = min(cost, tempCost);
  }
  return cost;
}

void calculateAllCombineCosts(int n, const int* dolls) {
  for (int begin = 0; begin < n; begin++) {
    costTable[begin][1] = 0;
  }
  bool noDuplicateMatrix[n+1][n+1];
  for (int i = 0; i <= n; i++) {
    for (int j = 0; j <= n; j++) {
      noDuplicateMatrix[i][j] = false;
    }
  }
  for (int begin = 0; begin < n; begin++) {
    bool exist[n+1];
    fill(exist, exist+n+1, false);
    for (int i = 0; begin + i < n; i++) {
      int d = dolls[begin + i];
      if (exist[d]) {
        break;
      }
      exist[d] = true;
      noDuplicateMatrix[begin][i+1] = true;
    }
  }
  for (int width = 2; width <= n; width++) {
    for (int begin = 0; begin + width <= n; begin++) {
      if (noDuplicateMatrix[begin][width]) {
        costTable[begin][width] = calculateCombineCost(begin, width, dolls);
      } else {
        costTable[begin][width] = INF;
      }
    }
  }
}

// Assumption: There is no duplicated size dolls between [begin, begin+width).
bool isConsecutiveRange(int begin, int width, const int* dolls) {
  for (int i = begin; i < begin+width; i++) {
    if (dolls[i] > width) {
      return false;
    }
  }
  return true;
}

int dp(int n, const int* dolls) {
  int dpTable[n+1];
  dpTable[0] = 0;
  for (int i = 1; i <= n; i++) {
    dpTable[i] = INF;
    for (int j = 0; j < i; j++) {
      if (costTable[j][i-j] < INF && isConsecutiveRange(j, i-j, dolls)) {
        int tempCost = dpTable[j] + costTable[j][i-j];
        dpTable[i] = min(dpTable[i], tempCost);
      }
    }
  }
  return dpTable[n];
}

int solve(int n, const int* dolls) {
  calculateAllCombineCosts(n, dolls);
  return dp(n, dolls);
}

int main(void) {
  int n;
  cin >> n;
  int dolls[n];
  for (int i = 0; i < n; i++) {
    cin >> dolls[i];
  }
  int answer = solve(n, dolls);
  if (answer < INF) {
    cout << answer << endl;
  } else {
    cout << "impossible" << endl;
  }
}
