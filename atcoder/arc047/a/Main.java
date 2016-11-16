import java.util.*;
import java.math.*;
 
public class Main {
  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    int tabs = 1;
    int crash = 0;
    int n = s.nextInt();
    int l = s.nextInt();
    String input = s.next();
    for (char c : input.toCharArray()) {
      if (c == '+') {
        tabs++;
        if (tabs > l) {
          crash++;
          tabs = 1;
        }
      } else {
        tabs--;
      }
    }
    System.out.println(crash);
  }
}
