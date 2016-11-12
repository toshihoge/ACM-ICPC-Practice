import java.util.*;

public class Main {
  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    String name = s.next();
    for (int i = 0; i < name.length() / 2; i++) {
      if (name.charAt(i) != name.charAt(name.length() - 1 - i)) {
        System.out.println("NO");
        return;
      }
    }
    System.out.println("YES");
  }
}
