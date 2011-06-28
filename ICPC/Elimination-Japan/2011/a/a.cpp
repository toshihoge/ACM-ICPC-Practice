#include<iostream>

using namespace std;

#define N 246913 // 123456*2+1

int main(void) {
  bool primes[N];
  for (int i = 0; i < N; i++) {
    primes[i] = true;
  }
  primes[0] = false;
  primes[1] = false;
  for (int j = 2; j*j < N; j++) {
    if (primes[j]) {
      for (int k = j; j*k < N; k++) {
        primes[j*k] = false;
      }
    }
  }

  while (true) {
    int n;
    cin >> n;
    if (n == 0) {
      break;
    }
    int counter = 0;
    for (int i = n+1; i <= 2*n; i++) {
      if (primes[i]) {
        counter++;
      }
    }
    cout << counter << endl;
  }
}
