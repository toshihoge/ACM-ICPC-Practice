#include<cstdlib>
#include<iostream>
#include<vector>

using namespace std;

typedef vector<int> VEC;
typedef vector<VEC> MTRX;

MTRX generateMatrix(int m, int n, int d, const VEC& input) {
  MTRX output;
  int mn = m * n;
  
  for (int mn1 = 0; mn1 < mn; mn1++) {
    int m1 = mn1 / m;
    int n1 = mn1 % m;
    VEC v;
    for (int mn2 = 0; mn2 < mn; mn2++) {
      int m2 = mn2 / m;
      int n2 = mn2 % m;
      v.push_back(mn1 == mn2 || abs(m1 - m2) + abs(n1 - n2) == d ? 1 : 0);
    }
    v.push_back(input[mn1]);
    output.push_back(v);
  }
  return output;
}

int findNonNegativeIndex(int i0, int j0, const MTRX &matrix) {
  for (int i = i0; i < matrix.size(); i++) {
    if (matrix[i][j0] == 1) {
      return i;
    }
  }
  return -1;
}

void addRow(int targetIndex, int srcIndex, MTRX &matrix) {
  for (int j = 0; j < matrix[srcIndex].size(); j++) {
    matrix[targetIndex][j] = (matrix[targetIndex][j] + matrix[srcIndex][j]) % 2;
  }
}

int gaussianElimination(MTRX &matrix) {
  int i = 0;
  int j = 0;
  while (j < matrix.size()) {
    int nonNegativeIndex = findNonNegativeIndex(i, j, matrix);
    if (nonNegativeIndex >= 0) {
      if (nonNegativeIndex != i) {
        swap(matrix[i], matrix[nonNegativeIndex]);
      }
      for (int k = i+1; k < matrix.size(); k++) {
        if (matrix[k][j] == 1) {
          addRow(k, i, matrix);
        }
      }
      i++;
      j++;
    } else {
      j++;
    }
  }
  return i;
}

int solve(int m, int n, int d, const VEC &input) {
  MTRX matrix = generateMatrix(m, n, d, input);
  int rank = gaussianElimination(matrix);
  for (int i = rank; i < matrix.size(); i++) {
    if (matrix[i][matrix[i].size() - 1] != 0) return 0;
  }
  return 1;
}

int main(void) {
  for (int index = 0; true; index++) {
    int m, n, d;
    cin >> m >> n >> d;
    if (m == 0 && n == 0 && d == 0) {
      break;
    }
    VEC input;
    for (int i = 0; i < n*m; i++) {
      int number;
      cin >> number;
      input.push_back(number);
    }
    cout << solve(m, n, d, input) << endl;
  }
}
