import java.util.*;
 
public class Main {
  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    int n = s.nextInt();
    int a = n / 10;
    int b = n % 10;
    if (15 * b > 100) {
      b = 0;
      a++;
    }
    System.out.println(100*a + 15*b);
  }
}
