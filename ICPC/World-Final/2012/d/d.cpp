#include<iostream>
#include<vector>
#include<map>
#include<set>
#include<queue>

using namespace std;

// 2^63
#define LIMIT 9223372036854775808.0
#define DEBUG cout<<"Debug:"<<__LINE__<<endl

typedef long long int ll;
typedef vector<ll> vll;
typedef vector<vll> vvll;
typedef map<ll, ll> mll2ll;

typedef struct state {
  int totalPrimes;
  int numberPrimes;
  int index;
  ll n;

  state(int totalPrimes_, int numberPrimes_, int index_, ll n_) :
      totalPrimes(totalPrimes_),
      numberPrimes(numberPrimes_),
      index(index_),
      n(n_) {}
} state;

typedef pair<ll, state> node; 
typedef priority_queue<node, vector<node>, greater<node> > pq;

int PRIMES[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53}; 

ll multiply(ll a, ll b) {
  return (double)a*(double)b < LIMIT ? a*b : -1;
}

bool operator<(const state& s1, const state& s2) {
  if (s1.totalPrimes != s2.totalPrimes) return s1.totalPrimes < s2.totalPrimes;
  if (s1.numberPrimes != s2.numberPrimes) return s1.numberPrimes < s2.numberPrimes;
  if (s1.n != s2.n) return s1.n < s2.n;
  return s1.index < s2.index;
}

vvll generateCombinationTable() {
  vvll table(64, vll(64, 1));
  for (int i = 1; i <= 63; i++) {
    for (int j = 1; j < i; j++) {
      table[i][j] = table[i-1][j-1] + table[i-1][j];
    }
  }
  return table;
}

ll power(ll a, int b) {
  ll output = 1;
  for (int i = 0; i < b; i++) {
    output = multiply(output, a);
    if (output < 0) {
      return -1;
    }
  }
  return output;
}

vll solveAll(const vll& inputAll) {
  vvll combinationTable = generateCombinationTable();
  mll2ll results;
  for (int i = 0; i < inputAll.size(); i++) {
    results[inputAll[i]] = -1;
  }
  pq q;
  set<state> visited;
  q.push(make_pair(1, state(0, 64, 0, 1)));
  int rest = results.size();
  while (!q.empty()) {
    node n = q.top();
    q.pop();
    ll k = n.first;
    state s = n.second;
    if (visited.count(s)) {
      continue;
    }
    visited.insert(s);
    if (results.count(s.n) && results[s.n] < 0 && k > 1) {
      results[s.n] = k;
      rest--;
      if (rest <= 0) {
        break;
      }
    }
    for (int i = 1; i <= s.numberPrimes; i++) {
      ll p = power(PRIMES[s.index], i);
      if (p < 0) {
        break;
      }
      ll nextK = multiply(k, p);
      if (nextK < 0) {
        break;
      }
      int nextTotalPrimes = s.totalPrimes + i;
      int nextNumberPrimes = i;
      int nextIndex = s.index+1;
      ll nextN = multiply(s.n, combinationTable[nextTotalPrimes][nextNumberPrimes]);
      if (nextN < 0) {
        break;
      }
      state nextState(nextTotalPrimes, nextNumberPrimes, nextIndex, nextN);
      if (visited.count(nextState)) {
        continue;
      }
      q.push(make_pair(nextK, nextState));
    }
  }
  vll answerAll;
  for (int i = 0; i < inputAll.size(); i++) {
    answerAll.push_back(results[inputAll[i]]);
  }
  return answerAll;
}

int main(void) {
  vll inputAll;
  ll n;
  while (cin >> n) {
    inputAll.push_back(n);
  }
  vll answerAll = solveAll(inputAll);
  for (int i = 0; i < inputAll.size(); i++) {
    cout << inputAll[i] << " " << answerAll[i] << endl;
  }
}
