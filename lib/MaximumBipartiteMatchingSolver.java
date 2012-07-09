import java.util.*;

class MaximumBipartiteMatchingSolver {
  boolean[][] matrix;
  int n;
  private boolean dfs(int index, boolean[] visit) {
    if (index == n-1) {
      return true;
    }
    visit[index] = true;
    for (int i = 0; i < n; i++) {
      if (!matrix[index][i] || visit[i]) {
        continue;
      }
      if (dfs(i, visit)) {
        matrix[index][i] = false;
        matrix[i][index] = true;
        return true;
      }
    }
    return false;
  }

  private int maximumElement(ArrayList<Integer> elements) {
    int maximum = 0;
    for (int e: elements) {
      maximum = Math.max(maximum, e);
    }
    return maximum;
  }

  public int solve(
      ArrayList<Integer> srcs, ArrayList<Integer> dsts) {
    int maxSrc = maximumElement(srcs) + 1;
    int maxDst = maximumElement(dsts) + 1;
    n = maxSrc + maxDst + 2;
    matrix = new boolean[n][n];
    for (int i = 0; i < maxSrc; i++) {
      matrix[n-2][i] = true;
    }
    for (int i = 0; i < maxDst; i++) {
      matrix[i + maxSrc][n-1] = true;
    }
    for (int i = 0; i < srcs.size(); i++) {
      matrix[srcs.get(i)][dsts.get(i) + maxSrc] = true;
    }

    int maching = 0;
    while (dfs(n-2, new boolean[n])) {
      maching++;
    }
    return maching;
  }
}
