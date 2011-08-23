import java.util.*;

public class Main {
  private final static String[] VARS = new String[]{"P", "Q", "R"};
  private final static String[] VALUES = new String[]{"0", "1", "2"};
  private final static String[][] PATTERNS = new String[][]{
    {"-0", "2"},
    {"-1", "1"},
    {"-2", "0"},
    {"\\(0\\*0\\)", "0"},
    {"\\(0\\*1\\)", "0"},
    {"\\(0\\*2\\)", "0"},
    {"\\(1\\*0\\)", "0"},
    {"\\(1\\*1\\)", "1"},
    {"\\(1\\*2\\)", "1"},
    {"\\(2\\*0\\)", "0"},
    {"\\(2\\*1\\)", "1"},
    {"\\(2\\*2\\)", "2"},
    {"\\(0\\+0\\)", "0"},
    {"\\(0\\+1\\)", "1"},
    {"\\(0\\+2\\)", "2"},
    {"\\(1\\+0\\)", "1"},
    {"\\(1\\+1\\)", "1"},
    {"\\(1\\+2\\)", "2"},
    {"\\(2\\+0\\)", "2"},
    {"\\(2\\+1\\)", "2"},
    {"\\(2\\+2\\)", "2"},
  };

  private static boolean eval(String line, int[] i) {
    for (int j = 0; j < 3; j++) {
      line = line.replaceAll(VARS[j], VALUES[i[j]]);
    }
    while (line.length() > 1) {
      for (String[] pair : PATTERNS) {
        line = line.replaceAll(pair[0], pair[1]);
      }
    }
    return "2".equals(line);
  }

  private static int solve(String line) {
    int count = 0;
    for (int p = 0; p < 3; p++) {
      for (int q = 0; q < 3; q++) {
        for (int r = 0; r < 3; r++) {
          if (eval(line, new int[]{p, q, r})) {
            count++;
          }
        }
      }
    }
    return count;
  }

  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    while(true) {
      String line = s.next();
      if (".".equals(line)) {
        break;
      }
      System.out.println(solve(line));
    }
  }
}
