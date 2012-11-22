#include<iostream>
#include<vector>

using namespace std;

typedef vector<vector<int> > vvi;

// Global
int n, m;

vvi mul(const vvi &matrix1, const vvi &matrix2) {
  vvi output(n, vector<int>(n, 0));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      for (int k = 0; k < n; k++) {
        output[i][j] += matrix1[i][k] * matrix2[k][j];
        output[i][j] %= m;
      }
    }
  }
  return output;
}

vvi pow(const vvi &matrix, int t) {
  if (t == 0) {
    vvi output(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
      output[i][i] = 1;
    }
    return output;
  } else if (t % 2 == 1) {
    vvi temp = pow(matrix, t/2);
    return mul(mul(temp, temp), matrix);
  } else {
    vvi temp = pow(matrix, t/2);
    return mul(temp, temp);
  }
}

int main(void) {
  while (true) {
    int a, b, c, t;
    cin >> n >> m >> a >> b >> c >> t;
    if (n == 0) {
      break;
    }
    int s[n];
    for (int i = 0; i < n; i++) {
      cin >> s[i];
    }
    vvi matrix(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
      if (i-1 >= 0) {
        matrix[i][i-1] = a;
      }
      matrix[i][i] = b;
      if (i+1 < n) {
        matrix[i][i+1] = c;
      }
    }
    vvi powered = pow(matrix, t);
    for (int i = 0; i < n; i++) {
      if (i > 0) {
        cout << " ";
      }
      int sum = 0;
      for (int j = 0; j < n; j++) {
        sum += powered[i][j] * s[j];
        sum %= m;
      }
      cout << sum;
    }
    cout << endl;
  }
}
