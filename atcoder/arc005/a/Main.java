import java.util.*;

public class Main {
  private static boolean isTakahashikun(String word) {
    word = word.replaceAll("\\.", "");
    return word.equals("TAKAHASHIKUN") ||
        word.equals("Takahashikun") ||
        word.equals("takahashikun");
  }

  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    int n = s.nextInt();
    int count = 0;
    for (int i = 0; i < n; i++) {
      if (isTakahashikun(s.next())) {
        count++;
      }
    }
    System.out.println(count);
  }
}
