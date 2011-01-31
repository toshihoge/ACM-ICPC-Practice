import java.util.*;

class Solver {
  private final static int LETTERS_SIZE = 26;
  private final static String UNREACHABLE = "-";
  private final static String[] UPPER_LETTERS = {
    "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"
  };

  int length;
  ArrayList<ArrayList<String> > ruleTable;
  boolean[][] visitedTable;
  String[][] resultTable;

  private static int getIndex(char c) {
    return c - 'A';
  }

  private static int countLowerCaseLetters(String str) {
    return str.replaceAll("[A-Z]+", "").length();
  }

  private ArrayList<String> replaceFirstUpperCaseLetter(String str, int sublength) {
    for (int i = 0; i < str.length(); i++) {
      if (Character.isUpperCase(str.charAt(i))) {
        int index = getIndex(str.charAt(i));
        int numberLowerCaseLetters = countLowerCaseLetters(str);
        ArrayList<String> output = new ArrayList<String>();
        for (int j = 0; j <= sublength-numberLowerCaseLetters; j++) {
          String result = solvesub(index, j);
          if (!result.equals(UNREACHABLE)) {
            output.add(str.replaceFirst(UPPER_LETTERS[index], result));
          }
        }
        return output;
      }
    }
    return new ArrayList<String>();
  }

  private String solvesub(int index, int sublength) {
    if (visitedTable[index][sublength]) {
      return resultTable[index][sublength];
    }
    visitedTable[index][sublength] = true;
    resultTable[index][sublength] = UNREACHABLE;;

    HashSet<String> visited = new HashSet<String>();
    PriorityQueue<String> queue = new PriorityQueue<String>();
    for (String rule: ruleTable.get(index)) {
      if (countLowerCaseLetters(rule) <= sublength && !visited.contains(rule)) {
        visited.add(rule);
        queue.add(rule);
      }
    }
    while (!queue.isEmpty()) {
      String str = queue.poll();
      if (countLowerCaseLetters(str) == sublength && str.length() == sublength) {
        resultTable[index][sublength] = str;
        return str;
      }
      ArrayList<String> replacedStrings = replaceFirstUpperCaseLetter(str, sublength);
      for (String replacedString: replacedStrings) {
        if (!visited.contains(replacedString)) {
          visited.add(replacedString);
          queue.add(replacedString);;
        }
      }
    }
    return resultTable[index][sublength];
  }

  public String solve() {
    return solvesub('S' - 'A', length);
  }

  Solver (int length, String[] rules) {
    this.length = length;
    ruleTable = new ArrayList<ArrayList<String> >();  
    for (int i = 0; i < LETTERS_SIZE; i++) {
      ruleTable.add(new ArrayList<String>());
    }
    for (String rule: rules) {
      ruleTable.get(getIndex(rule.charAt(0))).add(rule.substring(2));
    }

    visitedTable = new boolean[LETTERS_SIZE][length+1];
    for (boolean[] v: visitedTable) Arrays.fill(v, false);

    resultTable = new String[LETTERS_SIZE][length+1];
  }
}

public class H {
  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    while (true) {
      int n = s.nextInt();
      int length = s.nextInt();
      if (n == 0) {
        break;
      }
      String[] rules = new String[n];
      for (int i = 0; i < n; i++) {
        rules[i] = s.next();
      }
      Solver solver = new Solver(length, rules);
      System.out.print(solver.solve() + "\n");
    }
  }
}
