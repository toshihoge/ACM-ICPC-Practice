import java.util.*;
import java.math.*;
 
public class Main {
  private static boolean match(int k, int a) {
    int diff = k - a;
    if (Math.abs(diff) < 10) {
      return true;
    }
    if (Math.abs(diff) < 100 && diff % 10 == 0) {
      return true;
    }
    if (diff % 100 == 0) {
      return true;
    }
    return false;
  }
 
  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    int a = s.nextInt();
    int b = s.nextInt();
    int max = -1000;
    for (int k = 100; k <= 999; k++) {
      if (match(k, a)) {
        max = Math.max(max, k - b);
      }
      if (match(k, b)) {
        max = Math.max(max, a - k);
      }
    }
    System.out.println(max);
  }
}
