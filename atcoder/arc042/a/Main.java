import java.util.*;
import java.math.*;
 
public class Main {
  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    int n = s.nextInt();
    int m = s.nextInt();
    int[] history = new int[m];
    for (int i = 0; i < m; i++) {
      history[i] = s.nextInt();
    }
    boolean[] shown = new boolean[n+1];
    for (int i = m-1; i >= 0; i--) {
      int h = history[i];
      if (shown[h]) {
        continue;
      }
      shown[h] = true;
      System.out.println(h);
    }
    for (int i = 1; i <= n; i++) {
      if (shown[i]) {
        continue;
      }
      System.out.println(i);
    }
  }
}
