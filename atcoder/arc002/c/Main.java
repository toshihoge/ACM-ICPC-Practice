import java.util.*;
 
public class Main {
  private final static char[] KEYS = new char[]{'A', 'B', 'X', 'Y'};

  private static int getLength(char[] command, char c1, char c2, char c3, char c4) {
    int index = 0;
    int count = 0;
    while (index < command.length) {
      if (index+1 < command.length &&
          command[index] == c1 &&
          command[index+1] == c2) {
        index += 2;
      } else if (index+1 < command.length &&
          command[index] == c3 &&
          command[index+1] == c4) {
        index += 2;
      } else {
        index++;
      }
      count++;
    }
    return count;
  }

  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    int n = s.nextInt();
    String str = s.next();
    char[] command = str.toCharArray();
    int minCount = command.length;
    for (char c1 : KEYS) {
      for (char c2 : KEYS) {
        for (char c3 : KEYS) {
          for (char c4 : KEYS) {
            minCount = Math.min(minCount, getLength(command, c1, c2, c3, c4));
          }
        }
      }
    }
    System.out.println(minCount);
  }
}
