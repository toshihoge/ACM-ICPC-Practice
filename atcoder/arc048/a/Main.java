import java.util.*;
import java.math.*;
 
public class Main {
  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    int a = s.nextInt();
    int b = s.nextInt();
    if (a < 0 && b > 0) {
      System.out.println(b - a - 1);
    } else {
      System.out.println(b - a);
    }
  }
}
