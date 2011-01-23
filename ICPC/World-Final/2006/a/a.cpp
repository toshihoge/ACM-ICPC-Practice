#include<cstdio>
#include<iostream>
#include<vector>
#include<string>

using namespace std;

bool hasA(string v) {
  return v.find("A") != string::npos;
}

bool hasB(string v) {
  return v.find("B") != string::npos;
}

bool mayHaveO(string v) {
  return v.find("AB") == string::npos;
}

bool isAB(string v) {
  return v.find("AB") != string::npos;
}

bool isA(string v) {
  return !isAB(v) && hasA(v);
}

bool isB(string v) {
  return !isAB(v) && hasB(v);
}

bool isO(string v) {
  return v.find("O") != string::npos;
}

bool isP(string v) {
  return v.find("+") != string::npos;
}

bool isN(string v) {
  return v.find("-") != string::npos;
}

bool acceptableABO(string p1, string p2, string c) {
  if (isA(c)) {
    return hasA(p1) || hasA(p2);
  }
  if (isB(c)) {
    return hasB(p1) || hasB(p2);
  }
  if (isAB(c)) {
    return (hasA(p1) && hasB(p2)) || (hasB(p1) && hasA(p2));
  }
  if (isO(c)) {
    return mayHaveO(p1) && mayHaveO(p2);
  }
  return false;
}

bool acceptableRH(string p1, string p2, string c) {
  if (isN(p1) && isN(p2) && isP(c)) {
    return false;
  }
  return true;
}

bool acceptable(string p1, string p2, string c) {
  return acceptableABO(p1, p2, c) && acceptableRH(p1, p2, c);
}

string concatenates(vector<string> v) {
  if (v.size() == 0) {
    return "IMPOSSIBLE";
  }
  if (v.size() == 1) {
    return v[0];
  }
  string output = "{" + v[0];
  for (int i = 1; i < v.size(); i++) {
    output += ", " + v[i];
  }
  output += "}";
  return output;
}

int main(void) {
  for (int casenumber = 1; true; casenumber++) {
    string input[3];
    cin >> input[0] >> input[1] >> input[2];
    if (input[0] == "E") {
      break;
    }
    cout << "Case " << casenumber << ": ";
    vector<string> v;
    string types[] = {"A+", "A-", "B+", "B-", "AB+", "AB-", "O+", "O-"};
    
    if (input[0] == "?") {
      for (int i = 0; i < 8; i++) {
        if (acceptable(types[i], input[1], input[2])) {
          v.push_back(types[i]);
        }
      }
      cout << concatenates(v) << " " << input[1] << " " << input[2] << endl;
    } else if(input[1] == "?") {
      for (int i = 0; i < 8; i++) {
        if (acceptable(input[0], types[i], input[2])) {
          v.push_back(types[i]);
        }
      }
      cout << input[0] << " " << concatenates(v) << " " << input[2] << endl;
    } else {
      for (int i = 0; i < 8; i++) {
        if (acceptable(input[0], input[1], types[i])) {
          v.push_back(types[i]);
        }
      }
      cout << input[0] << " " << input[1] << " " << concatenates(v) << endl;
    }
  }
}

