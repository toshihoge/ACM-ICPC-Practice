#include<iostream>
#include<set>
#include<vector>

using namespace std;

typedef vector<int> vi;

vi makeVi(int v1, int v2) {
  vi output;
  output.push_back(max(v1, v2));
  output.push_back(min(v1, v2));
  return output;
}

vector<int> solveAll() {
  vector<int> answer(1001);
  
  int count = 0;
  
  vi initial = makeVi(1, 1);
  
  set<vi> visited;
  vector<vi> before;
  before.push_back(initial);
  visited.insert(initial);
  
  int step = 1;
  while (count <= 1000) {
    vector<vi> after;
    for (int i = 0; i < before.size(); i++) {
      int vNexts[4] = {2*before[i][0], 2*before[i][1], before[i][0]+before[i][1], before[i][0]-before[i][1]};
      for (int j = 0; j < 4; j++) {
        if (vNexts[j] <= 1000 && answer[vNexts[j]] == 0) {
          answer[vNexts[j]] = step;
          count++;
        }
        for (int k = 0; k < 2; k++) {
          vi viNext = makeVi(vNexts[j], before[i][k]);
          if (visited.find(viNext) == visited.end()) {
            visited.insert(viNext);
            after.push_back(viNext);
          }
        }
      }
    }
    step++;
    before = after;
    after.clear();
  }
  answer[1] = 0;
  return answer;
}

int main(void) {
  vector<int> answers = solveAll();
  while (true) {
    int n;
    cin >> n;
    if (n == 0) {
      break;
    }
    cout << answers[n] << endl;
  }
}
