#include<algorithm>
#include<cstdio>
#include<iostream>
#include<string>

using namespace std;

int solve(const string &line) {
  char buffer[27];
  fill(buffer, buffer+27, 'a');
  for (int i = 0; i < line.length(); i++) {
    for (int j = 0; true; j++) {
      if (buffer[j] >= line[i]) {
        buffer[j] = line[i];
        break;
      }
    }
  }
  for (int j = 0; true; j++) {
    if (buffer[j] == 'a') {
      return j;
    }
  }
}

int main(void) {
  for (int casenumber = 1; true; casenumber++) {
    string line;
    cin >> line;
    if (line == "end") {
      break;
    }
    printf("Case %d: %d\n", casenumber, solve(line));
  }
}
