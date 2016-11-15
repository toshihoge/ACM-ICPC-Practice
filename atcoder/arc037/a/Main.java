import java.util.*;
import java.math.*;
 
public class Main {
  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    int n = s.nextInt();
    int sum = 0;
    for (int i = 0; i < n; i++) {
      int m = s.nextInt();
      if (m < 80) {
        sum += 80 - m;
      }
    }
    System.out.println(sum);
  }
}
