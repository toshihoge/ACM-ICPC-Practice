#include<iostream>
#include<set>
#include<vector>
#include<string>

using namespace std;

typedef unsigned int brd;

#define E 0
#define W 1
#define B 2
#define R 3

#define EMP 0U

// TOP/BOTTOM: WHITE
// RIGHT/LEFT: BLUE
// UP/DOWN: RED

#define WBR 1U

// TOP/BOTTOM: WHITE
// RIGHT/LEFT: RED
// UP/DOWN: BLUE

#define WRB 5U

// TOP/BOTTOM: BLUE
// RIGHT/LEFT: WHITE
// UP/DOWN: RED

#define BWR 2U

// TOP/BOTTOM: BLUE
// RIGHT/LEFT: RED
// UP/DOWN: WHITE

#define BRW 6U

// TOP/BOTTOM: RED
// RIGHT/LEFT: WHITE
// UP/DOWN: BLUE

#define RWB 3U

// TOP/BOTTOM: RED
// RIGHT/LEFT: BLUE
// UP/DOWN: WHITE

#define RBW 7U

//011,0110,1101,1011,0110,1101,1011
#define TOP_MASK 0x36DB6DB

#define REMOVE_INDEX_MASK 0x7FFFFFF

#define RL 0
#define UD 1

int rotateTable[2][8] = 
{
  //EMP, WBR, BWR, RWB, EMP, WRB, BRW, RBW
  { EMP, BWR, WBR, WRB, EMP, RWB, RBW, BRW }, //rotate right/left
  { EMP, RBW, RWB, BWR, EMP, BRW, WRB, WBR }, //rotate up/down
};

#define mp(x,y) make_pair(x,y)

int rotateLength[9] = {
  2,  // (0, 0) 0
  3,  // (0, 1) 1
  2,  // (0, 2) 2
  3,  // (1, 0) 3
  4,  // (1, 1) 4
  3,  // (1, 2) 5
  2,  // (2, 0) 6
  3,  // (2, 1) 7
  2,  // (2, 2) 8
};

pair<int, int> rotateTypeTable[9][4] = {
  {           mp(1, RL),            mp(3, UD), mp(0,  0), mp(0,  0)}, // (0, 0) 0
  {mp(0, RL), mp(2, RL),            mp(4, UD), mp(0,  0)           }, // (0, 1) 1
  {mp(1, RL),                       mp(5, UD), mp(0,  0), mp(0,  0)}, // (0, 2) 2
  {           mp(4, RL), mp(0, UD), mp(6, UD), mp(0,  0)           }, // (1, 0) 3
  {mp(3, RL), mp(5, RL), mp(1, UD), mp(7, UD)                      }, // (1, 1) 4
  {mp(4, RL),            mp(2, UD), mp(8, UD), mp(0,  0)           }, // (1, 2) 5
  {           mp(7, RL), mp(3, UD),            mp(0,  0), mp(0,  0)}, // (2, 0) 6
  {mp(6, RL), mp(8, RL), mp(4, UD),            mp(0,  0)           }, // (2, 1) 7
  {mp(7, RL),            mp(5, UD),            mp(0,  0), mp(0,  0)}, // (2, 1) 8
};

//0-26 box arrangment
//27-30 empty index

#define INITIAL_ALL ((WBR<<24) | (WBR<<21) | (WBR<<18) | (WBR<<15) | (WBR<<12) | (WBR<<9) | (WBR<<6) | (WBR<<3) | WBR)

brd makeInitialBoard(int ei, int ej) {
  brd index = 3*(ei - 1) + (ej - 1);
  return (index << 27) | (INITIAL_ALL - (WBR<<(3*index)));
}

brd makeGoal(const string *tops) {
  brd output = 0U;
  for (int i = 8; i >= 0; i--) {
    output <<= 3;
    switch (tops[i][0]) {
    case 'W':
      output += W;
      break;
    case 'R':
      output += R;
      break;
    case 'B':
      output += B;
      break;
    }
  }
  return output;
}

brd rotate(brd origin, int emptySrcIndex, int emptyDstIndex, int rotateType) {
  brd rotatedBoxValue = (origin >> (3*emptyDstIndex)) & 0x7;
  brd nextRotatedBoxValue = rotateTable[rotateType][rotatedBoxValue];
  brd temp = ((origin & REMOVE_INDEX_MASK) - (rotatedBoxValue << (3*emptyDstIndex))) | (nextRotatedBoxValue << (3*emptySrcIndex)) | (emptyDstIndex << 27);
  return temp;
}

int solve(brd src, brd dst) {
  if ((src & TOP_MASK) == dst) {
    return 0;
  }
  
  int step = 1;
  set<brd> visited;
  vector<brd> v1, v2;
  vector<brd> *before;
  vector<brd> *after;
  before = &v1;
  after = &v2;
  
  visited.insert(src);
  before->push_back(src);
  while(!before->empty()) {
    for (int i = 0; i < before->size(); i++) {
      int emptySrcIndex = (*before)[i] >> 27;
      for (int j = 0; j < rotateLength[emptySrcIndex]; j++) {
        int emptyDstIndex = rotateTypeTable[emptySrcIndex][j].first;
        int rotateType = rotateTypeTable[emptySrcIndex][j].second;
        brd next = rotate((*before)[i], emptySrcIndex, emptyDstIndex, rotateType);
        if (step < 30 && visited.find(next) == visited.end()) {
          visited.insert(next);
          after->push_back(next);
        }
        if ((next & TOP_MASK) == dst) {
          return step;
        }
      }
    }
    swap(before, after);
    after->clear();
    step++;
  }
  return -1;
}

int main(void) {
  while (true) {
    int ei, ej;
    cin >> ej >> ei;
    if (ei == 0) {
      break;
    }
    string tops[9];
    for (int i = 0; i < 9; i++) {
      cin >> tops[i];
    }
    cout << solve(makeInitialBoard(ei, ej), makeGoal(tops)) << endl;
  }
}
