#include<iostream>
#include<vector>

using namespace std;

typedef vector<vector<int> > Matrix;

#define MAX_D 400

#define UNDEF 0

int findMaxValue(int prevMax, int* counter) {
  for (int i = prevMax; i > 0; i--) {
    if (counter[i] > 0) {
      return i;
    }
  }
  return 0;
}

bool setISide(int iIndex, int w, int value, Matrix &slots, int* counter) {
  bool result = true;
  
  counter[value]--;
  slots[iIndex][0] = value;
  if (counter[value] < 0) {
    result = false;
  }
  for (int i = w-1, j = 1; i > iIndex; i--, j++) {
    if (slots[i][0] == UNDEF) {
      return result;
    }
    int nextValue = slots[iIndex][0] - slots[i][0];
    counter[nextValue]--;
    slots[iIndex][j] = nextValue;
    if (counter[nextValue] < 0) {
      result = false;
    }
  }
  return result;
}

void revertISide(int iIndex, int w, Matrix &slots, int* counter) {
  counter[slots[iIndex][0]]++;
  slots[iIndex][0] = UNDEF;
  for (int i = w-1, j = 1; i > iIndex; i--, j++) {
    counter[slots[iIndex][j]]++;
    slots[iIndex][j] = UNDEF;
  }
}

bool setJSide(int jIndex, int w, int value, Matrix &slots, int* counter) {
  bool result = true;
  
  counter[value]--;
  slots[0][jIndex] = value;
  if (counter[value] < 0) {
    result = false;
  }
  for (int j = w-1, i = 1; j > jIndex; j--, i++) {
    if (slots[0][j] == UNDEF) {
      return result;
    }
    int nextValue = slots[0][jIndex] - slots[0][j];
    counter[nextValue]--;
    slots[i][jIndex] = nextValue;
    if (counter[nextValue] < 0) {
      result = false;
    }
  }
  return result;
}

void revertJSide(int jIndex, int w, Matrix &slots, int* counter) {
  counter[slots[0][jIndex]]++;
  slots[0][jIndex] = UNDEF;
  for (int j = w-1, i = 1; j > jIndex; j--, i++) {
    counter[slots[i][jIndex]]++;
    slots[i][jIndex] = UNDEF;
  }
}


void dfs(int i, int j, int iMax, int iMin, int jMax, int jMin, int w, int total, Matrix &slots, int prevMax, int* counter);

void doISide(int i, int j, int iMax, int iMin, int jMax, int jMin, int w, int total, Matrix &slots, int currentMax, int* counter) {
  if (iMin < currentMax && currentMax < iMax) {
    int jSideValue = total - currentMax;
    if (jMin < jSideValue && jSideValue < jMax && counter[jSideValue] > 0) {
      if (setISide(i, w, currentMax, slots, counter)) {
        if (setJSide(w-i, w, jSideValue, slots, counter)) {
          dfs(i+1, j, currentMax, iMin, jMax, jSideValue, w, total, slots, currentMax, counter);
        }
        revertJSide(w-i, w, slots, counter);
      }
      revertISide(i, w, slots, counter);
    }
  }
}

void doJSide(int i, int j, int iMax, int iMin, int jMax, int jMin, int w, int total, Matrix &slots, int currentMax, int* counter) {
  if (jMin < currentMax && currentMax < jMax) {
    int iSideValue = total - currentMax;
    if (iMin < iSideValue && iSideValue < iMax && counter[iSideValue] > 0) {
      if (setJSide(j, w, currentMax, slots, counter)) {
        if (setISide(w-j, w, iSideValue, slots, counter)) {
          dfs(i, j+1, iMax, iSideValue, currentMax, jMin, w, total, slots, currentMax, counter);
        }
        revertISide(w-j, w, slots, counter);
      }
      revertJSide(j, w, slots, counter);
    }
  }
}

void dfsSingle(int i, int j, int iMax, int iMin, int jMax, int jMin, int w, int total, Matrix &slots, int currentMax, int* counter) {
  doJSide(i, j, iMax, iMin, jMax, jMin, w, total, slots, currentMax, counter);
  doISide(i, j, iMax, iMin, jMax, jMin, w, total, slots, currentMax, counter);
}

void dfsDouble(int i, int j, int iMax, int iMin, int jMax, int jMin, int w, int total, Matrix &slots, int currentMax, int* counter) {
  doISide(i, j, iMax, iMin, jMax, jMin, w, total, slots, currentMax, counter);
}

void dfs(int i, int j, int iMax, int iMin, int jMax, int jMin, int w, int total, Matrix &slots, int prevMax, int* counter) {
  int currentMax = findMaxValue(prevMax, counter);
  
  if (currentMax == 0) {
    cout << slots[w-1][0];
    for (int k = 1; k < w; k++) {
      cout << " " << slots[w-1-k][k];
    }
    cout << endl;
    return;
  }
  
  if (counter[currentMax] == 2) {
    dfsDouble(i, j, iMax, iMin, jMax, jMin, w, total, slots, currentMax, counter);
  } else if(counter[currentMax] == 1) {
    dfsSingle(i, j, iMax, iMin, jMax, jMin, w, total, slots, currentMax, counter);
  }
}

void solve(int w, int total, int* counter) {
  Matrix slots(w);
  for (int i = 0; i < w; i++) {
    for (int j = 0; j < w-i; j++) {
      slots[i].push_back(UNDEF);
    }
  }
  slots[0][0] = total;
  
  dfs(1, 1, total, 0, total, 0, w, total, slots, total, counter);
}

int main(void) {
  while (true) {
    int n;
    cin >> n;
    if (n == 0) {
      break;
    }
    int total;
    cin >> total;
    
    int counter[MAX_D];
    fill(counter, counter+400, 0);
    for (int i = 1; i < n*(n-1)/2; i++) {
      int v;
      cin >> v;
      counter[v]++;
    }
    solve(n-1, total, counter);
    cout << "-----" << endl;
  }
}
