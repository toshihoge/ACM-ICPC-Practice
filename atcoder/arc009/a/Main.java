import java.util.*;
 
public class Main {
  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    int n = s.nextInt();
    int sum = 0;
    for (int i = 0; i < n; i++) {
      int a = s.nextInt();
      int b = s.nextInt();
      sum += a * b;
    }
    System.out.println(sum * 21 / 20);
  }
}
