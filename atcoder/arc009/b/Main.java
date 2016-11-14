import java.util.*;

class Number implements Comparable<Number> {
  String original;
  String key;

  public Number (String original, String key) {
    this.original = original;
    this.key = key;
  }

  public int compareTo(Number number) {
    return this.key.compareTo(number.key);
  }
}

public class Main {
  private static final String[] KEY_CHAR = new String[]{
    "a", "b", "c", "d", "e", "f", "g", "h", "i", "j"
  };
  private static final int LENGTH = 10;

  private static String getKey(String original, String[] bs) {
    String key = original;
    for (int i = 0; i < 10; i++) {
      key = key.replaceAll(bs[i], KEY_CHAR[i]);
    }
    while (key.length() < LENGTH) {
      key = "a" + key;
    }
    return key;
  }

  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    String[] bs = new String[10];
    for (int i = 0; i < 10; i++) {
      bs[i] = s.next();
    }
    int n = s.nextInt();
    Number[] as = new Number[n];
    for (int i = 0; i < n; i++) {
      String original = s.next();
      as[i] = new Number(original, getKey(original, bs));
    }
    Arrays.sort(as);
    for (Number a : as) {
      System.out.println(a.original);
    }
  }
}
