import java.util.*;
 
public class Main {
  private static boolean validate(int[] queens, int index) {
    int i1 = queens[index] / 8;
    int j1 = queens[index] % 8;
    for (int s = 0; s < index; s++) {
      int i2 = queens[s] / 8;
      int j2 = queens[s] % 8;
      if (i1 == i2 || j1 == j2 || Math.abs(i1 - i2) == Math.abs(j1 - j2)) {
        return false;
      }
    }
    return true;
  }

  private static boolean dfs(int[] queens, int index) {
    if (index == 8) {
      return true;
    }
    for (int i = 0; i < 64; i++) {
      queens[index] = i;
      if (validate(queens, index) && dfs(queens, index+1)) {
        return true;
      }
    }
    return false;
  }

  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    int[] queens = new int[8];
    int qIndex = 0;
    for (int i = 0; i < 8; i++) {
      String line = s.next();
      for (int j = 0; j < 8; j++) {
        if (line.charAt(j) == 'Q') {
          queens[qIndex] = 8*i + j;
          qIndex++;
        }
      }
    }
    if (!validate(queens, 1) || !validate(queens, 2) || !dfs(queens, 3)) {
      System.out.println("No Answer");
      return;
    }
    boolean[][] map = new boolean[8][8];
    for (int i = 0; i < 8; i++) {
      map[queens[i] / 8][queens[i] % 8] = true;
    }
    for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 8; j++) {
        System.out.print(map[i][j] ? "Q" : ".");
      }
      System.out.println();
    }
  }
}
