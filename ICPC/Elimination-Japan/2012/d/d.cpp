#include<iostream>
#include<vector>

using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;

#define INF (1<<28)

int n;

void wf(vvi &matrix) {
  for (int k = 1; k <= n; k++) {
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        matrix[i][j] = min(matrix[i][j], matrix[i][k] + matrix[k][j]);
      }
    }
  }
}

int convert(int d, const int* q, const int* r) {
  int output = min(d, q[0]) * r[0];
  for (int i = 1; q[i - 1] < d; i++) {
    output += (min(d, q[i]) - q[i - 1]) * r[i];
  }
  return output;
}

void convert(vvi &matrix, const int* q, const int* r) {
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      if (matrix[i][j] != INF) {
        matrix[i][j] = convert(matrix[i][j], q, r);
      }
    }
  }
}

void merge(vvi &matrix, const vvi &sub) {
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      matrix[i][j] = min(matrix[i][j], sub[i][j]);
    }
  }
}

int main(void) {
  while (true) {
    int m, c, s, g;
    cin >> n >> m >> c >> s >> g;
    if (n == 0) {
      break;
    }
    vvi matrix(n+1, vi(n+1, INF));
    int x[m], y[m], d[m], t[m];
    for (int i = 0; i < m; i++) {
      cin >> x[i] >> y[i] >> d[i] >> t[i];
    }
    int p[c+1];
    for (int i = 1; i <= c; i++) {
      cin >> p[i];
    }
    for (int i = 1; i <= c; i++) {
      int q[p[i]], r[p[i]];
      for (int j = 0; j < p[i] - 1; j++) {
        cin >> q[j];
      }
      q[p[i] - 1] = INF;
      for (int j = 0; j < p[i]; j++) {
        cin >> r[j];
      }
      vvi submatrix(n+1, vi(n+1, INF));
      for (int j = 0; j < m; j++) {
        if (t[j] == i) {
          submatrix[x[j]][y[j]] = min(submatrix[x[j]][y[j]], d[j]);
          submatrix[y[j]][x[j]] = min(submatrix[y[j]][x[j]], d[j]);
        }
      }
      wf(submatrix);
      convert(submatrix, q, r);
      merge(matrix, submatrix);
    }
    wf(matrix);
    cout << (matrix[s][g] == INF ? -1 : matrix[s][g]) << endl;
  }
}
