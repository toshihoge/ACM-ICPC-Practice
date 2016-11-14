import java.util.*;

public class Main {
  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    int n = s.nextInt();
    int m = s.nextInt();
    int a = s.nextInt();
    int b = s.nextInt();
    for (int i = 1; i <= m; i++) {
      if (n <= a) {
        n += b;
      }
      n -= s.nextInt();
      if (n < 0) {
        System.out.println(i);
        return;
      }
    }
    System.out.println("complete");
  }
}
