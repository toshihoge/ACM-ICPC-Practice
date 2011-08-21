#include<cstdlib>
#include<iostream>
#include<set>
#include<vector>

using namespace std;

bool mergable(int length, const string &head, const string &tail) {
  for (int i = 0; i < length; i++) {
    if (head[head.length()-length+i] != tail[i]) return false;
  }
  return true;
}

vector<string> getNextSuffixes(const string &head, const string &tail) {
  vector<string> output;
  for (int i = 0; i < tail.length(); i++) {
    if (mergable(i, head, tail)) output.push_back(tail.substr(i));
  }
  return output;
}

char myCharAt(const string &document, int index) {
  return 0 <= index && index < document.length() ? document[index] : '-';
}

pair<bool, vector<int> > calculateLcsTable(int previousLength, const string &suffix, const vector<int> &previousLcsTable, const string &document, int d) {
  vector<int> table1 = previousLcsTable;
  for (int i = 0; i < suffix.length(); i++) {
    vector<int> table2(2*d+1);
    int minCost = 10;
    for (int j = -d; j <= d; j++) {
      table2[d+j] = table1[d+j] + (suffix[i] != myCharAt(document, previousLength+i+j) ? 1 : 0);
      if (d+j-1 >= 0) table2[d+j] = min(table2[d+j], table2[d+j-1]+1);
      if (d+j+1 < 2*d+1) table2[d+j] = min(table2[d+j], table1[d+j+1]+1);
      minCost = min(table2[d+j], minCost);
    }
    
    if (minCost > d) return make_pair(false, vector<int>());
    table1 = table2;
  }
  return make_pair(true, table1);
}

void dfs(const string &piece, const vector<int> &previousLcsTable, set<string> &visited, set<string> &answer, int d, int n, const string &document, const string* pieces) {
  if (piece.length() > document.length()+2) return;
  visited.insert(piece);
  if (piece.length() >= document.length()-2) {
    if (previousLcsTable[d+document.length()-piece.length()] <= d) answer.insert(piece);
  }
  
  for (int i = 0; i < n; i++) {
    vector<string> nexts = getNextSuffixes(piece, pieces[i]);
    for (vector<string>::iterator it = nexts.begin(); it != nexts.end(); it++) {
      string nextPiece = piece + *it;
      if (visited.find(nextPiece) == visited.end()) {
        pair<bool, vector<int> > p = calculateLcsTable(piece.length(), *it, previousLcsTable, document, d);
        if (p.first) {
          dfs(nextPiece, p.second, visited, answer, d, n, document, pieces);
        }
      }
    }
  }
}

void solve(int d, int n, const string &document, const string* pieces) {
  vector<int> initialLcsTable;
  for (int i = -d; i <= d; i++) initialLcsTable.push_back(abs(i));
  
  set<string> answers;
  set<string> visited;
  dfs("", initialLcsTable, visited, answers, d, n, document, pieces);
  cout << answers.size() << endl;
  if (answers.size() > 5) return;
  for (set<string>::iterator it = answers.begin(); it != answers.end(); it++) cout << *it << endl;
}

int main(void) {
  while (true) {
    int d, n;
    cin >> d >> n;
    if (d == 0) break;
    string document;
    cin >> document;
    string pieces[n];
    for (int i = 0; i < n; i++) cin >> pieces[i];
    solve(d, n, document, pieces);
  }
}
