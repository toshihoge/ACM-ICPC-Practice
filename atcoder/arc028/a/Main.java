import java.util.*;

public class Main {
  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    int n = s.nextInt();
    int a = s.nextInt();
    int b = s.nextInt();
    while (true) {
      if (n <= a) {
        System.out.println("Ant");
        return;
      }
      n -= a;

      if (n <= b) {
        System.out.println("Bug");
        return;
      }
      n -= b;
    }
  }
}
