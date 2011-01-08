#include<cstdlib>
#include<iostream>
#include<map>
#include<vector>

using namespace std;

typedef vector<int> VEC;
typedef vector<VEC> MTRX;

typedef struct mnd {
  int m, n, d;
} Mnd;

typedef multimap<Mnd, pair<VEC, int> > PROBLEMS;

bool operator < (const Mnd &mnd1, const Mnd &mnd2) {
  if (mnd1.m != mnd2.m) return mnd1.m < mnd2.m;
  if (mnd1.n != mnd2.n) return mnd1.n < mnd2.n;
  return mnd1.d < mnd2.d;
}

bool operator != (const Mnd &mnd1, const Mnd &mnd2) {
  return mnd1.m != mnd2.m || mnd1.n != mnd2.n || mnd1.d != mnd2.d;
}

MTRX generateMatrix(Mnd mnd) {
  MTRX output;
  int mn = mnd.m * mnd.n;
  int m = mnd.m;
  
  for (int mn1 = 0; mn1 < mn; mn1++) {
    int m1 = mn1 / m;
    int n1 = mn1 % m;
    VEC v;
    for (int mn2 = 0; mn2 < mn; mn2++) {
      int m2 = mn2 / m;
      int n2 = mn2 % m;
      if (mn1 == mn2 || abs(m1 - m2) + abs(n1 - n2) == mnd.d) {
        v.push_back(1);
      } else {
        v.push_back(0);
      }
    }
    for (int mn3 = 0; mn3 < mn; mn3++) {
      v.push_back(mn1 == mn3 ? 1 : 0);
    }
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

MTRX preSolve(Mnd mnd) {
  MTRX matrix = generateMatrix(mnd);
  int rank = gaussianElimination(matrix);
  MTRX output;
  for (int i = rank; i < matrix.size(); i++) {
    VEC v;
    for (int j = matrix[0].size()/2; j < matrix[0].size(); j++) {
      v.push_back(matrix[i][j]);
    }
    output.push_back(v);
  }
  return output;
}

VEC multiply(const MTRX &matrix, const VEC &row) {
  VEC output;
  for (int i = 0; i < matrix.size(); i++) {
    int sum = 0;
    for (int j = 0; j < matrix[i].size(); j++) {
      sum += matrix[i][j] * row[j];
    }
    output.push_back(sum % 2);
  }
  return output;
}

int acceptable(const vector<vector<int> > matrix, const VEC &input) {
  vector<int> mul = multiply(matrix, input);
  for (int i = 0; i < mul.size(); i++) {
    if (mul[i] != 0) return 0;
  }
  return 1;
}

VEC solves(const PROBLEMS &problems) {
  vector<int> result(problems.size());
  
  Mnd prev;
  prev.m = 0;
  prev.n = 0;
  prev.d = 0;
  
  MTRX matrix;
  for (PROBLEMS::const_iterator it = problems.begin(); it != problems.end(); it++) {
    Mnd mnd = it->first;
    
    if (mnd != prev) {
      matrix = preSolve(mnd);
      prev = mnd;
    }
    result[it->second.second] = acceptable(matrix, it->second.first);
  }
  return result;
}

int main(void) {
  PROBLEMS problems;
  
  for (int index = 0; true; index++) {
    Mnd mnd;
    cin >> mnd.m >> mnd.n >> mnd.d;
    if (mnd.m == 0 && mnd.n == 0 && mnd.d == 0) {
      break;
    }
    vector<int> input;
    for (int i = 0; i < mnd.n*mnd.m; i++) {
      int number;
      cin >> number;
      input.push_back(number);
    }
    problems.insert(PROBLEMS::value_type(mnd, make_pair(input, index)));
  }
  VEC answers = solves(problems);
  for (int i = 0; i < answers.size(); i++) {
    cout << answers[i] << endl;
  }
}
