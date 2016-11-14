import java.util.*;
 
public class Main {
  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    int n = s.nextInt();
    int max = 0;
    int sum = 0;
    for (int i = 0; i < n; i++) {
      int d = s.nextInt();
      max = Math.max(max, d);
      sum += d;
    }
    System.out.println(sum);
    System.out.println(Math.max(0, 2*max - sum));
  }
}
