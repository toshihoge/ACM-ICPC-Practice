import java.util.*;
import java.math.*;
 
public class Main {
  private static boolean isTree(int parent, int index, boolean[] visited, ArrayList<ArrayList<Integer>> edges) {
    boolean isTree = true;
    visited[index] = true;
    for (int next : edges.get(index)) {
      if (parent == next) {
        continue;
      }
      if (visited[next]) {
        isTree = false;
        continue;
      }
      isTree &= isTree(index, next, visited, edges);
    }
    return isTree;
  }
 
  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    int n = s.nextInt();
    int m = s.nextInt();
    ArrayList<ArrayList<Integer>> edges = new ArrayList<ArrayList<Integer>>();
    for (int i = 0; i < n; i++) {
      edges.add(new ArrayList<Integer>());
    }
    for (int i = 0; i < m; i++) {
      int u = s.nextInt() - 1;
      int v = s.nextInt() - 1;
      edges.get(u).add(v);
      edges.get(v).add(u);
    }
    boolean[] visited = new boolean[n];
    int tree = 0;
    for (int i = 0; i < n; i++) {
      if (visited[i]) {
        continue;
      }
      if (isTree(-1, i, visited, edges)) {
        tree++;
      }
    }
    System.out.println(tree);
  }
}
