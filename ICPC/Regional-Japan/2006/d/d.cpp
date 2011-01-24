#include<iostream>
#include<vector>

using namespace std;

#define N 1125
#define M 15

int dptable[M][N][200];

bool isPrime(int n, const vector<int> &primes) {
  for (int i = 0; i < primes.size() && primes[i]*primes[i] <= n; i++) {
    if (n % primes[i] == 0) {
      return false;
    }
  }
  return true;
}

vector<int> getPrimes(int limit) {
  vector<int> primes;
  for (int i = 2; i < limit; i++) {
    if (isPrime(i, primes)) {
      primes.push_back(i);
    }
  }
  return primes;
}

int main(void) {
  vector<int> primes = getPrimes(N);
  
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < primes.size(); j++) {
      dptable[1][i][j] = 0;
    }
  }
  for (int i = 0; i < primes.size(); i++) {
    for (int j = i; j < primes.size(); j++) {
      dptable[1][primes[i]][j] = 1;
    }
  }
  for (int i = 2; i < M; i++) {
    for (int j = 0; j < N; j++) {
      for (int k = 0; k < primes.size(); k++) {
        dptable[i][j][k] = 0;
      }
      for (int k = 1; k < primes.size() && primes[k] < j; k++) {
        for (int l = k; l < primes.size(); l++) {
          dptable[i][j][l] += dptable[i-1][j-primes[k]][k-1];
        }
      }
    }
  }
  while (true) {
    int n, k;
    cin >> n >> k;
    if (n == 0) {
      break;
    }
    cout << dptable[k][n][primes.size()-1] << endl;
  }
}
