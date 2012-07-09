import java.util.*;

class MaximumBipartiteMatchingSolver {
  private static boolean dfs(int index, HashSet<Integer>  visited,
      HashMap<Integer, HashSet<Integer> > matrix) {
    if (index == -2) {
      return true;
    }
    visited.add(index);
    for (int next : matrix.get(index)) {
      if (visited.contains(next)) {
        continue;
      }
      if (dfs(next, visited, matrix)) {
        matrix.get(index).remove(next);
        matrix.get(next).add(index);
        return true;
      }
    }
    return false;
  }

  // All elements must be positive and less than 1<<15
  public static int solve(
      ArrayList<Integer> srcs, ArrayList<Integer> dststemp) {
    ArrayList<Integer> dsts = new ArrayList<Integer>();
    for (int i: dststemp) {
      dsts.add((i+1) << 15);
    }

    HashMap<Integer, HashSet<Integer> > matrix =
        new HashMap<Integer, HashSet<Integer> >();
    matrix.put(-1, new HashSet<Integer>());
    for (int i: srcs) {
      matrix.get(-1).add(i);
      matrix.put(i, new HashSet<Integer>());
    }
    matrix.put(-2, new HashSet<Integer>());
    for (int i: dsts) {
      matrix.put(i, new HashSet<Integer>());
      matrix.get(i).add(-2);
    }
    for (int i = 0; i < srcs.size(); i++) {
      matrix.get(srcs.get(i)).add(dsts.get(i));
    }

    int maching = 0;
    while (dfs(-1, new HashSet<Integer>(), matrix)) {
      maching++;
    }
    return maching;
  }
}
