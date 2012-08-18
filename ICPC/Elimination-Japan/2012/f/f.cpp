#include<algorithm>
#include<cstdio>
#include<iostream>

using namespace std;

typedef long long ll;
typedef pair<int, int> pattern;

#define WILDCARD pattern(8, 8)

int N, M, L;

pattern parsePattern(const string& str) {
  if (str == "*") {
    return WILDCARD;
  }
  return pattern(str[0] - 'a', str.length() - 1);
}

ll combination(int a, int b) {
  if (b < 0 || a < b || a < 0) {
    return 0;
  }
  ll output_a = 1;
  ll output_b = 1;
  for (int i = 0; i < b; i++) {
    output_a *= a - i;
    output_b *= i + 1;
  }
  return output_a / output_b;
}

int countSamePatterns(int index, const pattern* test_patterns) {
  int count = 1;
  for (int i = index-1; i >= 0; i--, count++) {
    if (test_patterns[index] != test_patterns[i]) {
      break;
    }
  }
  return count;
}

bool matchTwoPatterns(pattern test_i, pattern query_i, pattern test_j,
    pattern query_j) {
  if (query_i == WILDCARD || query_j == WILDCARD ||
      query_i.first != query_j.first) {
    return true;
  }
  return test_i.first == test_j.first &&
      query_i.second - query_j.second == test_i.second - test_j.second;

}

bool matchPatternsFixedOrder(const pattern* test_patterns,
    const pattern* query_patterns) {
  for (int i = 0; i < L; i++) {
    for (int j = i+1; j < L; j++) {
      if (!matchTwoPatterns(test_patterns[i], query_patterns[i],
                            test_patterns[j], query_patterns[j])) {
        return false;
      }
    }
  }
  return true;
}

bool matchPatternsReorder(const pattern* test_patterns,
    const pattern* query_patterns) {
  pattern copied[L];
  for (int i = 0; i < L; i++) {
    copied[i] = query_patterns[i];
  }
  sort(copied, copied + L);
  do {
    if (matchPatternsFixedOrder(test_patterns, copied)) {
      return true;
    }
  } while (next_permutation(copied, copied + L));
  return false;
}

ll countRankAssignments(const pattern* test_patterns) {
  int different_number = 1;
  int forbidden_number = 0;
  for (int i = 1; i < L; i++) {
    if (test_patterns[i-1] == test_patterns[i]) {
      // skip
    } else if (test_patterns[i-1].first == test_patterns[i].first) {
      forbidden_number++;
    } else {
      different_number++;
      forbidden_number++;
    }
  }
  return combination(M - forbidden_number, different_number);
}

ll countSameRankCardAssignments(const pattern* test_patterns) {
  ll output = 1;
  for (int i = 0; i < L;) {
    int j;
    for (j = i+1; j < L && test_patterns[i] == test_patterns[j]; j++);
    output *= combination(N, j-i);
    i = j;
  }
  return output;
}

ll countMatchHandDfs(int index, pattern* test_patterns,
    const pattern* query_patterns) {
  if (index == 0) {
    test_patterns[0] = pattern(0, 0);
    return countMatchHandDfs(1, test_patterns, query_patterns);
  } else if (index < L) {
    ll output = 0;
    pattern prev = test_patterns[index-1];
    test_patterns[index] = prev;
    if (countSamePatterns(index, test_patterns) <= N) {
      output += countMatchHandDfs(index+1, test_patterns, query_patterns);
    }
    test_patterns[index] = pattern(prev.first, prev.second+1);
    output += countMatchHandDfs(index+1, test_patterns, query_patterns);
    test_patterns[index] = pattern(prev.first+1, 0);
    output += countMatchHandDfs(index+1, test_patterns, query_patterns);
    return output;
  } else {
    return matchPatternsReorder(test_patterns, query_patterns) ?
        countSameRankCardAssignments(test_patterns) *
        countRankAssignments(test_patterns) : 0;
  }
}

double solve(const string* str_patterns) {
  pattern query_patterns[L];
  for (int i = 0; i < L; i++) {
    query_patterns[i] = parsePattern(str_patterns[i]);
  }
  pattern test_patterns[L];
  return (double)countMatchHandDfs(0, test_patterns, query_patterns) /
      combination(N*M, L);
}

int main(void) {
  while (true) {
    cin >> N >> M >> L;
    if (N == 0) {
      break;
    }
    string str_patterns[L];
    for (int i = 0; i < L; i++) {
      cin >> str_patterns[i];
    }
    printf("%.9f\n", solve(str_patterns));
  }
  return 0;
}
