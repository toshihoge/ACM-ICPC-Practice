import java.util.*;
import java.math.*;

public class Main {
  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    int n = s.nextInt();
    int k = s.nextInt();
    if (k == 1) {
      System.out.println(n);
      return;
    }
    int prev = Integer.parseInt(s.next());
    int increaseLength = 0;
    int count = 0;
    for (int i = 1; i < n; i++) {
      int current = Integer.parseInt(s.next());
      if (current > prev) {
        increaseLength++;
        if (increaseLength >= k-1) {
          count++;
        }
      } else {
        increaseLength = 0;
      }
      prev = current;
    }
    System.out.println(count);
  }
}
