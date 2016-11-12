import java.util.*;

public class Main {
  private static int dfs(int index, int previousIndex, ArrayList<ArrayList<Integer>> matrix, int[] jewels) {
    ArrayList<Integer> edges = matrix.get(index);
    int sum = 0;
    for (int next : edges) {
      if (next == previousIndex) {
        continue;
      }
      sum += dfs(next, index, matrix, jewels);
    }
    int backCost = previousIndex > 0 ? 2 : 0;
    if (sum > 0) {
      return sum+backCost;
    }
    if (jewels[index] > 0) {
      return backCost;
    }
    return 0;
  }

  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    int n = s.nextInt();
    int x = s.nextInt();
    int[] jewels = new int[n+1];
    for (int i = 1; i <= n; i++) {
      jewels[i] = s.nextInt();
    }
    ArrayList<ArrayList<Integer>> matrix = new ArrayList<ArrayList<Integer>>();
    for (int i = 0; i <= n; i++) {
      matrix.add(new ArrayList<Integer>());
    }
    for (int i = 0; i < n-1; i++) {
      int a = s.nextInt();
      int b = s.nextInt();
      matrix.get(a).add(b);
      matrix.get(b).add(a);
    }
    System.out.println(dfs(x, -1, matrix, jewels));
  }
}
