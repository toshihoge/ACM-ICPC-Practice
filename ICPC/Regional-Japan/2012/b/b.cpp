#include<iostream>
#include<vector>

using namespace std;


typedef struct rcs {
  int r, c, s;
  rcs(int r, int c, int s) : r(r), c(c), s(s) {}
  rcs() : r(0), c(0), s(0) {}
} rcs;
typedef vector<int> vi;
typedef vector<rcs> vrcs;

rcs sum(const rcs &rcs1, const rcs &rcs2) {
  return rcs(rcs1.r + rcs2.r, rcs1.c + rcs2.c, rcs1.s + rcs2.s);
}

int product(const rcs &rcs1, const rcs &rcs2) {
  return rcs1.r*rcs2.r + rcs1.c*rcs2.c + rcs1.s*rcs2.s;
}

rcs parse(const string &line) {
  rcs output;
  for (int i = 0; i < line.size(); i++) {
    switch (line[i]) {
    case '(':
      output.r++;
      break;
    case '{':
      output.c++;
      break;
    case '[':
      output.s++;
      break;
    case ')':
      output.r--;
      break;
    case '}':
      output.c--;
      break;
    case ']':
      output.s--;
      break;
    }
  }
  return output;
}

int count_dots(const string &line) {
  int output = 0;
  for (int i = 0; i < line.size(); i++) {
    if (line[i] != '.') {
      return i;
    }
  }
  // never reaches
  return -1;
}

bool acceptable(const vrcs &rcss, const vi &dots, const rcs &test) {
  for (int i = 0; i < rcss.size(); i++) {
    if (product(rcss[i], test) != dots[i]) {
      return false;
    }
  }
  return true;
}

vector<rcs> get_acceptable_rcs(int p, const string* ps) {
  rcs prev;
  vrcs rcss;
  vi dotss;
  for (int i = 1; i < p; i++) {
    prev = sum(prev, parse(ps[i-1]));
    rcss.push_back(prev);
    dotss.push_back(count_dots(ps[i]));
  }

  vrcs output;
  rcs i;
  for (i.r = 1; i.r <= 20; i.r++) {
    for (i.c = 1; i.c <= 20; i.c++) {
      for (i.s = 1; i.s <= 20; i.s++) {
        if (acceptable(rcss, dotss, i)) {
          output.push_back(i);
        }
      }
    }
  }
  return output;
}

int get_dots_number(const vrcs &masters, const rcs &prev_count) {
  int output = product(masters[0], prev_count);
  for (int i = 1; i < masters.size(); i++) {
    if (output != product(masters[i], prev_count)) {
      return -1;
    }
  }
  return output;
}

vi solve(int p, const string* ps, int q, const string* qs) {
  vrcs masters = get_acceptable_rcs(p, ps);

  vi output;
  rcs prev;
  for (int i = 0; i < q; i++) {
    output.push_back(get_dots_number(masters, prev));
    prev = sum(prev, parse(qs[i]));
  }
  return output;
}

int main(void) {
  while (true) {
    int p, q;
    cin >> p >> q;
    if (p == 0) {
      break;
    }
    string ps[p], qs[q];
    for (int i = 0; i < p; i++) {
      cin >> ps[i];
    }
    for (int i = 0; i < q; i++) {
      cin >> qs[i];
    }
    vi answer = solve(p, ps, q, qs);
    cout << answer[0];
    for (int i = 1; i < answer.size(); i++) {
      cout << " " << answer[i];
    }
    cout << endl;
  }
}
