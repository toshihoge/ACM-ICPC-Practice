import java.util.*;

public class Main {
  private static final int[] DI = new int[]{1, 1, 0, -1};
  private static final int[] DJ = new int[]{0, 1, 1,  1};

  private static int count(char[][] board, char c) {
    int counter = 0;
    for (int i = 1; i <= 19; i++) {
      for (int j = 1; j <= 19; j++) {
        if (board[i][j] == c) {
          counter++;
        }
      }
    }
    return counter;
  }

  private static boolean win(char[][] board, char c) {
    for (int i = 1; i <= 19; i++) {
      for (int j = 1; j <= 19; j++) {
        for (int k = 0; k < 4; k++) {
          int len = 0;
          while (board[i+len*DI[k]][j+len*DJ[k]] == c) {
            len++;
          }
          if (len >= 5) {
            return true;
          }
        }
      }
    }
    return false;
  }

  private static boolean removeAndNotWin(char[][] board, char c) {
    for (int i = 1; i <= 19; i++) {
      for (int j = 1; j <= 19; j++) {
        if (board[i][j] == c) {
          board[i][j] = '.';
          boolean win = win(board, c);
          board[i][j] = c;
          if (!win) {
            return true;
          }
        }
      }
    }
    return false;
  }

  private static boolean validate(char[][] board) {
    int black = count(board, 'o');
    int white = count(board, 'x');
    boolean isLastBlack = black - white == 1;
    boolean isLastWhite = black - white == 0;
    if (isLastBlack == isLastWhite) {
      return false;
    }
    boolean winBlack = win(board, 'o');
    boolean winWhite = win(board, 'x');
    if (winBlack && isLastWhite) {
      return false;
    }
    if (winWhite && isLastBlack) {
      return false;
    }
    if (!winBlack && !winWhite) {
      return true;
    }
    if (winBlack) {
      return removeAndNotWin(board, 'o');
    } else {
      return removeAndNotWin(board, 'x');
    }
  }

  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    char[][] board = new char[21][21];
    for (int i = 1; i <= 19; i++) {
      String line = s.next();
      for (int j = 1; j <= 19; j++) {
        board[i][j] = line.charAt(j-1);
      }
    }
    System.out.println(validate(board) ? "YES" : "NO");
  }
}
