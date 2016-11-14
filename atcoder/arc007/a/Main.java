import java.util.*;

public class Main {
  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    String brokenKey = s.next();
    String text = s.next();
    System.out.println(text.replaceAll(brokenKey, ""));
  }
}
