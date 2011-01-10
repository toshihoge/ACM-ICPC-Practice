#include<iostream>
#include<map>

using namespace std;

typedef long long ll;

void generateRandomSequence(ll n, ll s, ll w, ll* a) {
  ll g = s;
  for(int i=0; i<n; i++) {
  a[i] = (g/7) % 10;
    if( g%2 == 0 ) {
      g = (g/2);
    } else {
      g = (g/2) ^ w;
    }
  }
}

ll multiply(ll a, ll b, ll q) {
  return a*b%q;
}

//x^y mod q
ll power(ll x, ll y, ll q) {
  if (y == 0) {
    return 1;
  } else {
    ll x2 = power(x, y/2, q);
    if (y%2 == 0) {
      return multiply(x2, x2, q);
    } else {
      return multiply(multiply(x2, x2, q), x, q);
    }
  }
}

// solve fx+m mod q = k
// fx+m mod q = k
// fx mod q = k-m
// f^(q-1) mod q = 1
// f*f^(q-2) mod q = 1
// f*f^(q-2)*(k-m) mod q = k-m
ll solveX(ll f, ll m, ll k, ll q) {
  return multiply(power(f, q-2, q), (k-m+q)%q, q);
}

void insert(map<ll, ll> &counter, ll v) {
  map<ll, ll>::iterator it = counter.find(v);
  if (it != counter.end()) {
    counter[v] = counter[v] + 1;
  } else {
    counter[v] = 1;
  }
}

ll get(const map<ll, ll> &counter, ll v) {
  map<ll, ll>::const_iterator it = counter.find(v);
  if (it != counter.end()) {
    return it->second;
  } else {
    return 0;
  }
}

ll solve2(ll n, const ll* a) {
  ll countAnswer = 0;
  ll countNumber = 0;
  for (int i = 0; i < n; i++) {
    switch (a[i]) {
    case 0:
      countAnswer += countNumber;
      break;
    case 2:
    case 4:
    case 6:
    case 8:
      countNumber++;
      countAnswer += countNumber;
      break;
    default:
      countNumber++;
      break;
    }
  }
  return countAnswer;
}

ll solve5(ll n, const ll* a) {
  ll countAnswer = 0;
  ll countNumber = 0;
  for (int i = 0; i < n; i++) {
    switch (a[i]) {
    case 0:
      countAnswer += countNumber;
      break;
    case 5:
      countNumber++;
      countAnswer += countNumber;
      break;
    default:
      countNumber++;
      break;
    }
  }
  return countAnswer;
}

ll solveDefault(ll n, ll q, const ll* a) {
  ll countAnswer = 0;
  map<ll, ll> counter;
  
  ll factor = 1;
  ll modulo = 0;
  
  for (int i = 0; i<n; i++) {
    factor = multiply(factor, 10, q);
    modulo = (multiply(modulo, 10, q) + a[i]) % q;
    if (a[i] != 0) {
      insert(counter, solveX(factor, modulo, a[i], q));
    }
    countAnswer += get(counter, solveX(factor, modulo, 0, q));
  }
  return countAnswer;
}

ll solve(ll n, ll q, const ll* a) {
  switch(q) {
  case 2:
    return solve2(n, a);
  case 5:
    return solve5(n, a);
  default:
    return solveDefault(n, q, a);
  }
}

int main(void) {
  ll a[100000];
  while (true) {
    ll n, s, w, q;
    cin >> n >> s >> w >> q;
    if (n == 0) break;
    
    generateRandomSequence(n, s, w, a);
    cout << solve(n, q, a) << endl;
  }
}
