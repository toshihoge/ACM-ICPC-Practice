import java.util.*;
import java.math.*;
 
public class Main {
  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    String line = s.next();
    char[] array = line.toCharArray();
    for (int i = 0; i < array.length / 2; i++) {
      if (array[i] != '*' &&
          array[array.length - 1 - i] != '*' &&
          array[i] != array[array.length - 1 - i]) {
        System.out.println("NO");
        return;
      }
    }
    System.out.println("YES");
  }
}
