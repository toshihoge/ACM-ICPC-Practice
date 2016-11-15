import java.util.*;
import java.math.*;
 
public class Main {
  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    int x = s.nextInt();
    int y = s.nextInt();
    int k = s.nextInt();
    if (k < y) {
      System.out.println(x + k);
    } else {
      System.out.println(x + 2 * y - k);
    }
  }
}
