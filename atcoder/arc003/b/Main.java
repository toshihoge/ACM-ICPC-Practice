import java.util.*;
 
public class Main {
  private static String reverse(String word) {
    String reverseWord = "";
    for (char c : word.toCharArray()) {
      reverseWord = c + reverseWord;
    }
    return reverseWord;
  }

  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    int n = s.nextInt();
    String[] reverseWords = new String[n];
    for (int i = 0; i < n; i++) {
      reverseWords[i] = reverse(s.next());
    }
    Arrays.sort(reverseWords);
    for (String reverseWord : reverseWords) {
      System.out.println(reverse(reverseWord));
    }
  }
}
