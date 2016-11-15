import java.util.*;

public class Main {
  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    int n = s.nextInt();
    HashSet<String> words = new HashSet<String>();
    String previous = s.next();
    words.add(previous);
    for (int i = 1; i < n; i++) {
      String word = s.next();
      if (previous.charAt(previous.length() - 1) != word.charAt(0) ||
          words.contains(word)) {
        System.out.println(i % 2 == 1 ? "WIN" : "LOSE");
        return;
      }
      previous = word;
      words.add(word);
    }
    System.out.println("DRAW");
  }
}
