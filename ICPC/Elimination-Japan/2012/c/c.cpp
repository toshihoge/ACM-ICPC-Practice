#include<cstdlib>
#include<iostream>
#include<vector>

using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;

#define WIDTH 40
#define CENTER 20

#define RIGHT 0
#define FRONT 1
#define LEFT 2
#define BEHIND 3
//           R, F, L, B
int DY[4] = {0, 1, 0, -1};
int DX[4] = {1, 0, -1, 0};

class Dice {
  public:
    int GetTop() {
      return top_;
    }

    int FindFace(int number) {
      if (right_ == number) {
        return RIGHT;
      }
      if (front_ == number) {
        return FRONT;
      }
      if (left_ == number) {
        return LEFT;
      }
      if (behind_ == number) {
        return BEHIND;
      }
      return -1;
    }

    Dice Rotate(int index) {
      switch(index) {
      case RIGHT:
        return RotateRight();
      case FRONT:
        return RotateFront();
      case LEFT:
        return RotateLeft();
      case BEHIND:
        return RotateBehind();
      default:
        exit(1);
      }
    }

    static Dice Get(int top, int front) {
      Dice d(6, 1, 5, 2, 4, 3);
      for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
          if (d.top_ == top && d.front_ == front) {
            return d;
          }
          d = d.RotateZ();
        }
        d = d.RotateRight();
        for (int j = 0; j < 4; j++) {
          if (d.top_ == top && d.front_ == front) {
            return d;
          }
          d = d.RotateZ();
        }
        d = d.RotateFront();
      }
      exit(1);
    }

  private:
    Dice(int top, int bottom, int right, int left, int front, int behind)
        : top_(top), bottom_(bottom), right_(right), left_(left),
        front_(front), behind_(behind) {}
  
    Dice RotateRight() {
      return Dice(left_, right_, top_, bottom_, front_, behind_);
    }

    Dice RotateLeft() {
      return RotateRight().RotateRight().RotateRight();
    }

    Dice RotateFront() {
      return Dice(behind_, front_, right_, left_, top_, bottom_);
    }

    Dice RotateBehind() {
      return RotateFront().RotateFront().RotateFront();
    }

    Dice RotateZ() {
      return Dice(top_, bottom_, front_, behind_, left_, right_);
    }

    int top_;
    int bottom_;
    int right_;
    int left_;
    int front_;
    int behind_;
};

void fall(Dice dice, int y, int x, vvi& height, vvi& top) {
  for (int f = 6; f >= 4; f--) {
    int direction = dice.FindFace(f);
    if (direction == -1) {
      continue;
    }
    int next_y = y + DY[direction];
    int next_x = x + DX[direction];
    if (height[y][x] <= height[next_y][next_x]) {
      continue;
    }
    fall(dice.Rotate(direction), next_y, next_x, height, top);
    return;
  }
  height[y][x]++;
  top[y][x] = dice.GetTop();
}

int count_top(int number, const vvi& top) {
  int count = 0;
  for (int i = 0; i < WIDTH; i++) {
    for (int j = 0; j < WIDTH; j++) {
      if (top[i][j] == number) {
        count++;
      }
    }
  }
  return count;
}

int main(void) {
  while (true) {
    int n;
    cin >> n;
    if (n == 0) {
      break;
    }
    vvi height(WIDTH, vi(WIDTH, 0));
    vvi top(WIDTH, vi(WIDTH, 0));
    for (int i = 0; i < n; i++) {
      int t, f;
      cin >> t >> f;
      Dice dice = Dice::Get(t, f);
      fall(dice, CENTER, CENTER, height, top);
    }
    cout << count_top(1, top);
    for (int i = 2; i <= 6; i++) {
      cout << " " << count_top(i, top);
    }
    cout << endl;
  }
  return 0;
}
