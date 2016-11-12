import java.util.*;

public class Main {
  private static int dfs(int index, int a, int b, int[] t) {
    if (index == t.length) {
      return Math.max(a, b);
    }
    return Math.min(
        dfs(index+1, a+t[index], b, t),
        dfs(index+1, a, b+t[index], t));
  }

  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    int n = s.nextInt();
    int[] t = new int[n];
    for (int i = 0; i < n; i++) {
      t[i] = s.nextInt();
    }
    System.out.println(dfs(0, 0, 0, t));
  }
}
