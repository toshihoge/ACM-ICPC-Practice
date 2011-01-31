#include<iostream>
#include<string>
#include<queue>
#include<set>
#include<vector>

using namespace std;

#define ALPHABET_SIZE 26
#define MAX_LENGTH 21
#define UNREACHABLE "-"

vector<vector<string> > ruleTable;
bool visitedTable[ALPHABET_SIZE][MAX_LENGTH];
string cacheTable[ALPHABET_SIZE][MAX_LENGTH];

int countLowerLetters(const string &str) {
  int count = 0;
  for (int i = 0; i < str.length(); i++) {
    if ('a' <= str[i] && str[i] <= 'z') {
      count++;
    }
  }
  return count;
}

string solvesub(int index, int length);

vector<string> replaceFirstUpperLetter(const string &str, int length) {
  for (int i = 0; i < str.length(); i++) {
    if ('A' <= str[i] && str[i] <= 'Z') {
      int index = str[i] - 'A';
      int numberLowerLetters = countLowerLetters(str);
      vector<string> output;
      for (int j = 0; j <= length-numberLowerLetters; j++) {
        string sub = solvesub(index, j);
        if (sub != UNREACHABLE) {
          output.push_back(str.substr(0, i) + sub + str.substr(i+1));
        }
      }
      return output;
    }
  }
  return vector<string>();
}

string solvesub(int index, int length) {
  if (visitedTable[index][length]) {
    return cacheTable[index][length];
  }
  visitedTable[index][length] = true;
  cacheTable[index][length] = UNREACHABLE;
  
  set<string> visited;
  priority_queue<string, vector<string>, greater<string> > queue;
  for (int i = 0; i < ruleTable[index].size(); i++) {
    if (countLowerLetters(ruleTable[index][i]) <= length && visited.find(ruleTable[index][i]) == visited.end()) {
      queue.push(ruleTable[index][i]);
      visited.insert(ruleTable[index][i]);
    }
  }
  while (!queue.empty()) {
    string str = queue.top();
    queue.pop();
    if (countLowerLetters(str) == length && str.length() == length) {
      cacheTable[index][length] = str;
      return str;
    }
    vector<string> replacedStrings = replaceFirstUpperLetter(str, length);
    for (int i = 0; i < replacedStrings.size(); i++) {
      if (visited.find(replacedStrings[i]) == visited.end()) {
        visited.insert(replacedStrings[i]);
        queue.push(replacedStrings[i]);
      }
    }
  }
  return UNREACHABLE;
}

string solve(int n, int length, const string* rules) {
  ruleTable = vector<vector<string> >(ALPHABET_SIZE);
  for (int i = 0; i < n; i++) {
    ruleTable[rules[i][0]-'A'].push_back(rules[i].substr(2));
  }
  
  for (int i = 0; i < ALPHABET_SIZE; i++) {
    for (int j = 0; j <= length; j++) {
      visitedTable[i][j] = false;
    }
  }
  return solvesub('S' - 'A', length);
}

int main(void) {
  while(true) {
    int n, length;
    cin >> n >> length;
    if (n == 0) {
      break;
    }
    string rules[n];
    for (int i = 0; i < n; i++) {
      cin >> rules[i];
    }
    cout << solve(n, length, rules) << endl;
  }
}
