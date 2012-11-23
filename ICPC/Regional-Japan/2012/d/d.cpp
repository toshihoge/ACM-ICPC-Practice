#include<iostream>
#include<vector>
#include<cmath>

using namespace std;

typedef vector<double> vd;
typedef vector<vd> vvd;

#define EPS 1e-6

//Global
int d;

int find_pivot(const vvd &matrix, int index) {
  double max_value = fabs(matrix[index][index]);
  int max_index = index;
  for (int i = index + 1; i < matrix.size(); i++) {
    if (fabs(matrix[i][index]) > max_value) {
      max_value = fabs(matrix[i][index]);
      max_index = i;
    }
  }
  return max_index;
}

void swap_row(vvd &matrix, int i, int j) {
  for (int k = 0; k < matrix[i].size(); k++) {
    double temp = matrix[i][k];
    matrix[i][k] = matrix[j][k];
    matrix[j][k] = temp;
  }
}

bool gaussian_elimination(vvd &matrix, vd &output) {
  for (int i = 0; i < matrix.size(); i++) {
    int pivot = find_pivot(matrix, i);
    if (fabs(matrix[pivot][i]) < EPS) {
      return false;
    }
    swap_row(matrix, pivot, i);
    double factor = matrix[i][i];
    for (int j = 0; j < matrix[i].size(); j++) {
      matrix[i][j] /= factor;
    }
    for (int j = 0; j < matrix.size(); j++) {
      if (j == i) {
        continue;
      }
      factor = matrix[j][i];
      for (int k = 0; k < matrix[j].size(); k++) {
        matrix[j][k] -= factor*matrix[i][k];
      }
    }
  }
  output.clear();
  for (int i = 0; i < matrix.size(); i++) {
    output.push_back(matrix[i][matrix[i].size() - 1]);
  }
  return true;
}

vd get_factors(const vd &vs, int skip1, int skip2) {
  vvd matrix;
  for (int i = 0; i < d + 3; i++) {
    if (i == skip1 || i == skip2) {
      continue;
    }
    vd row;
    for (int j = 0; j < d + 1; j++) {
      row.push_back(pow(i, j));
    }
    row.push_back(vs[i]);
    matrix.push_back(row);
  }

  vd output;
  gaussian_elimination(matrix, output);
  return output;
}

int solve(const vector<double> &vs) {
  double min_diff_value = 1e10;
  int min_index = -1;
  for (int i = 0; i < d + 3; i++) {
    int skip = (i == 0 ? 1 : 0);
    vector<double> fs = get_factors(vs, i, skip);
    double v = 0.0;
    for (int k = 0; k < d + 1; k++) {
      v += fs[k] * pow(skip, k);
    }
    double temp_diff_value = fabs(v - vs[skip]);
    if (min_diff_value > temp_diff_value) {
      min_diff_value = temp_diff_value;
      min_index = i;
    }
  }
  return min_index;
}

int main(void) {
  while(true) {
    cin >> d;
    if (d == 0) {
      break;
    }
    vector<double> vs;
    for (int i = 0; i < d + 3; i++) {
      double v;
      cin >> v;
      vs.push_back(v);
    }
    cout << solve(vs) << endl;
  }
}
