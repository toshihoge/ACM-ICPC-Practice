#include<iostream>
#include<stack>

using namespace std;

#define DEBUG cout<<"Debug: "<<__LINE__<<endl

#define ACCEPT 2
#define FAIL 1
#define UNACCEPTABLE 0

int acceptable_memo(int index, bool* visited, int space,
    int w, int n, const int *x, const int* distance) {
  if (visited[index]) {
    return FAIL;
  }
  visited[index] = true;
  if (index == 0) {
    return ACCEPT;
  }
  int chars = x[index-1];
  stack<int> nexts;
  for (int i = index-2; i >= 0; i--) {
    chars += x[i];
    if (chars + (index - i - 1) > w) {
      break;
    }
    if (chars + space*(index - i - 1) >= w) {
      nexts.push(i);
    }
  }
  while (!nexts.empty()) {
    int next = nexts.top();
    nexts.pop();
    int return_value = acceptable_memo(next, visited, space, w, n, x, distance);
    if (return_value != FAIL) {
      return return_value;
    }
  }
  for (int i = index; i >= 0; i--) {
    if (!visited[i]) {
      return FAIL;
    }
    if (distance[index] - distance[i] > w) {
      return UNACCEPTABLE;
    }
  }
  return FAIL;
}

bool acceptable(int space, int w, int n, const int *x, const int *distance) {
  bool visited[n+1];
  fill(visited, visited + n + 1, false);
  stack<int> nexts;
  nexts.push(n);
  nexts.push(n-1);
  int length = x[n-1];
  for (int i = n-2; i >= 0; i--) {
    length += x[i] + 1;
    if (length <= w) {
      nexts.push(i);
    } else {
      break;
    }
  }
  while (!nexts.empty()) {
    int next = nexts.top();
    nexts.pop();
    switch(acceptable_memo(next, visited, space, w, n, x, distance)) {
    case ACCEPT:
      return true;
    case UNACCEPTABLE:
      return false;
    }
  }
  return false;
}

int solve(int w, int n, const int *x) {
  int distance[n+1];
  distance[0] = 0;
  for (int i = 0; i < n; i++) {
    distance[i+1] = distance[i] + x[i];
  }
  
  int min = 0;
  int max = w;
  while (max - min >= 2) {
    int mid = (max + min) / 2;
    if (acceptable(mid, w, n, x, distance)) {
      max = mid;
    } else {
      min = mid;
    }
  }
  return max;
}

int main(void) {
  while (true) {
    int w, n;
    cin >> w >> n;
    if (w == 0) {
      break;
    }
    int x[n];
    for (int i = 0; i < n; i++) {
      cin >> x[i];
    }
    int answer = solve(w, n, x);
    cout << answer << endl;
  }
}
