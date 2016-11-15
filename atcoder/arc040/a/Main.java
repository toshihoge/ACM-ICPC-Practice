import java.util.*;
import java.math.*;
 
public class Main {
  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    int n = s.nextInt();
    int r = 0;
    int b = 0;
    for (int i = 0; i < n; i++) {
      for (char c : s.next().toCharArray()) {
        switch(c) {
          case 'R':
            r++;
            break;
          case 'B':
            b++;
            break;
        }
      }
    }
    if (r > b) {
      System.out.println("TAKAHASHI");
    } else if (r < b) {
      System.out.println("AOKI");
    } else {
      System.out.println("DRAW");
    }
  }
}
