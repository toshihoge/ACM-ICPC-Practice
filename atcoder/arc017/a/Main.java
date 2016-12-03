import java.util.*;
import java.math.*;
public class Main {
  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    int n = s.nextInt();
    for (int i = 2; i*i <= n; i++) {
      if (n % i == 0) {
        System.out.println("NO");
        return;
      }
    }
    System.out.println("YES");
  }
}
