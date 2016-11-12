import java.util.*;

public class Main {
  private static final int[] DI = new int[]{1, 0, -1, 0};
  private static final int[] DJ = new int[]{0, 1, 0, -1};

  private static int dfs(boolean[][] island, boolean[][] visited, int i, int j) {
    if (!island[i][j] || visited[i][j]) {
      return 0;
    }
    visited[i][j] = true;

    int area = 1;
    for (int k = 0; k < DI.length; k++) {
      area += dfs(island, visited, i+DI[k], j+DJ[k]);
    }
    return area;
  }

  private static boolean singleIsland(boolean[][] island, int i, int j, int totalSize) {
    boolean[][] visited = new boolean[12][12];
    return dfs(island, visited, i, j) == totalSize;
  }

  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    boolean[][] island = new boolean[12][12];
    int totalSize = 0;
    for (int i = 1; i <= 10; i++) {
      String line = s.next();
      for (int j = 1; j <= 10; j++) {
        island[i][j] = line.charAt(j-1) == 'o';
        if (island[i][j]) {
          totalSize++;
        }
      }
    }
    
    for (int i = 1; i <= 10; i++) {
      for (int j = 1; j <= 10; j++) {
        if (island[i][j]) {
          continue;
        }
        island[i][j] = true;
        if (singleIsland(island, i, j, totalSize+1)) {
          System.out.println("YES");
          return;
        }
        island[i][j] = false;
      }
    }
    System.out.println("NO");
  }
}
