import java.util.*;

public class Main {
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
  private static int maximumBipartiteMatching(
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

  private static int gcd(int a, int b) {
    return a%b == 0 ? b : gcd(b, a%b);
  }

  private static int solve(int m, int n, int[] b, int[] r) {
    ArrayList<Integer> srcs = new ArrayList<Integer>();
    ArrayList<Integer> dsts = new ArrayList<Integer>();
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        if (gcd(b[i], r[j]) > 1) {
          srcs.add(i);
          dsts.add(j);
        }
      }
    }
    return maximumBipartiteMatching(srcs, dsts);
  }
  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    
    while (true) {
      int m = s.nextInt();
      int n = s.nextInt();
      if (m == 0) {
        break;
      }
      int[] b = new int[m];
      int[] r = new int[n];
      for (int i = 0; i < m; i++) {
        b[i] = s.nextInt();
      }
      for (int i = 0; i < n; i++) {
        r[i] = s.nextInt();
      }
      System.out.println(solve(m, n, b, r));
    }
  }
}
