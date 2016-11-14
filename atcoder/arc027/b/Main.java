import java.util.*;

public class Main {
  private static long pow10(int k) {
    long output = 1;
    for (int i = 0; i < k; i++) {
      output *= 10;
    }
    return output;
  }

  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    int n = s.nextInt();
    String s1 = s.next();
    String s2 = s.next();
    for (int i = 0; i < n; i++) {
      char c1 = s1.charAt(i);
      char c2 = s2.charAt(i);
      if (c1 != c2) {
        if (Character.isUpperCase(c1) && Character.isUpperCase(c2)) {
          s1 = s1.replaceAll("" + c1, "" + c2);
          s2 = s2.replaceAll("" + c1, "" + c2);
        } else if (Character.isUpperCase(c1) && Character.isDigit(c2)) {
          s1 = s1.replaceAll("" + c1, "" + c2);
          s2 = s2.replaceAll("" + c1, "" + c2);
        } else if (Character.isDigit(c1) && Character.isUpperCase(c2)) {
          s1 = s1.replaceAll("" + c2, "" + c1);
          s2 = s2.replaceAll("" + c2, "" + c1);
        } else {
          throw new RuntimeException("UnExpected");
        }
      }
    }
    HashSet<Character> cset = new HashSet<Character>();
    for (int i = 0; i < n; i++) {
      char c1 = s1.charAt(i);
      if (Character.isUpperCase(c1)) {
        cset.add(c1);
      }
      char c2 = s2.charAt(i);
      if (Character.isUpperCase(c2)) {
        cset.add(c2);
      }
    }

    if (Character.isUpperCase(s1.charAt(0))) {
      System.out.println(9 * pow10(cset.size() - 1));
    } else {
      System.out.println(pow10(cset.size()));
    }
  }
}
