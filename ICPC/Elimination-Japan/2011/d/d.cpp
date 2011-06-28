#include<iostream>
#include<complex>
#include<vector>

using namespace std;

typedef complex<double> cd;
typedef pair<int, int> pii;
typedef vector<pii> vpii;

#define EPS 1e-6
#define N 24 //6*4
#define MAX_COLOR 4

#define mark() cerr << "L" << __LINE__ << " " << __FILE__ << endl
#define debug(x) cerr << #x << " = " << (x) << " (L" << __LINE__ << ")" << " " << __FILE__ << endl

//------------------
// Global variable
//------------------

int n;
cd centers[N];
int r[N];
int colors[N];
int pairs[N];
bool assigned[N];

bool removableDish(int index, const bool* removedDish) {
  for (int i = 0; i < index; i++) {
    if (!removedDish[i] &&
        abs(centers[index] - centers[i]) < r[index] + r[i] - EPS) {
      return false;
    }
  }
  return true;
}

int findRemovablePair(const vpii &pairs, const bool* removedDish,
    const bool* removedPair) {
  for (int i = 0; i < pairs.size(); i++) {
    if (!removedPair[i] && removableDish(pairs[i].first, removedDish) &&
        removableDish(pairs[i].second, removedDish)) {
      return i;
    }
  }
  return -1;
}

int removeDishes(const vpii &pairs) {
  bool removedDish[n];
  bool removedPair[pairs.size()];
  fill(removedDish, removedDish+n, false);
  fill(removedPair, removedPair+pairs.size(), false);
  int count = 0;
  while (true) {
    int pairIndex = findRemovablePair(pairs, removedDish, removedPair);
    if (pairIndex < 0) {
      return count;
    }
    removedPair[pairIndex] = true;
    removedDish[pairs[pairIndex].first] = true;
    removedDish[pairs[pairIndex].second] = true;
    count += 2;
  }
}

int findFirstNonAssignedIndex() {
  for (int i = 0; i < n; i++) {
    if (!assigned[i]) {
      return i;
    }
  }
  return -1;
}

int generatePairsDfs(vpii &pairs) {
  int index = findFirstNonAssignedIndex();
  if (index >= 0) {
    int result = 0;
    for (int i = index+1; i < n; i++) {
      if (!assigned[i] && colors[index] == colors[i]) {
        assigned[i] = true;
        assigned[index] = true;
        pairs.push_back(make_pair(index, i));
        result = max(result, generatePairsDfs(pairs));
        assigned[i] = false;
        assigned[index] = false;
        pairs.pop_back();
      }
    }
    return result;
  } else {
    return removeDishes(pairs);
  }
}

int countColor(int color) {
  int count = 0;
  for (int i = 0; i < n; i++) {
    if (colors[i] == color) {
      count++;
    }
  }
  return count;
}

int selectUnpairableDish(int color) {
  if (color > MAX_COLOR) {
    vpii pairs;
    return generatePairsDfs(pairs);
  } else {
    int count = countColor(color);
    if (count % 2 == 0) {
      return selectUnpairableDish(color+1);
    } else {
      int result = 0;
      for (int i = 0; i < n; i++) {
        if (colors[i] == color) {
          assigned[i] = true;
          result = max(result, selectUnpairableDish(color+1));
          assigned[i] = false;
        }
      }
      return result;
    }
  }
}

int solve() {
  vpii pairs;
  fill(assigned, assigned+n, false);
  return selectUnpairableDish(1);
}

int main(void) {
  while (true) {
    cin >> n;
    if (n == 0) {
      break;
    }
    for (int i = 0; i < n; i++) {
      int x, y;
      cin >> x >> y >> r[i] >> colors[i];
      centers[i] = cd(x, y);
    }
    cout << solve() << endl;
  }
}

