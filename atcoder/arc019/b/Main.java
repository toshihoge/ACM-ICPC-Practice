import java.util.*;

public class Main {
  public static int getDifferentCharacterCount(String input) {
    int count = 0;
    for (int i = 0; i < input.length() / 2; i++) {
      if (input.charAt(i) != input.charAt(input.length() - 1 - i)) {
        count++;
      }
    }
    return count;
  }

  public static int solve(String input) {
    int differentCharacterCount = getDifferentCharacterCount(input);
    if (differentCharacterCount >= 2) {
      return 25 * input.length();
    } else if (differentCharacterCount == 1) {
      return 25 * input.length() - 2;
    } else if (input.length() % 2 == 0) {
      return 25 * input.length();
    } else {
      return 25 * input.length() - 25;
    }
  }

  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    String input = s.next();
    System.out.println(solve(input));
  }
}
