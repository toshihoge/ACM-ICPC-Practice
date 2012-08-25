import java.util.*;

/**
 * Usage:
 *  MaximumBipartiteMatchingSolver solver =
 *      new MaximumBipartiteMatchingSolver();
 *
 *  solver.addEdege(srcIndex, dstIndex);  // Each edge
 *
 *  int maximumNumber = solver.solve();
 *
 * Verified:
 *  AOJ1185 
 */
class MaximumBipartiteMatchingSolver {
  private int maxSrc;
  private int maxDst;
  private HashSet<Integer> edges;

  public MaximumBipartiteMatchingSolver() {
    maxSrc = 1;
    maxDst = 1;
    edges = new HashSet<Integer>();
  }

  private int makeEdge(int src, int dst) {
    return (src << 16) | dst;
  }

  public void addEdge(int src, int dst) {
    maxSrc = Math.max(maxSrc, src+1);
    maxDst = Math.max(maxDst, dst+1);
    edges.add(makeEdge(src, dst));
  }

  private boolean containEdge(int src, int dst) {
    return edges.contains(makeEdge(src, dst));
  }

  private boolean dfs(int srcIndex, int[] prev, boolean[] visit) {
    if (srcIndex < 0) {
      return true;
    }
    for (int i = 0; i < maxDst; i++) {
      if (visit[i] || !containEdge(srcIndex, i)) {
        continue;
      }
      visit[i] = true;
      if (dfs(prev[i], prev, visit)) {
        prev[i] = srcIndex;
        return true;
      }
    }
    return false;
  }

  public int solve() {
    int count = 0;
    int[] prev = new int[maxDst];
    boolean[] visit = new boolean[maxDst];
    Arrays.fill(prev, -1);
    for (int i = 0; i < maxSrc; i++) {
      Arrays.fill(visit, false);
      if (dfs(i, prev, visit)) {
        count++;
      }
    }
    return count;
  }
}
