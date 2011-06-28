import java.util.*;

public class Main {
  public static String solve(String line) {
    line = line.replaceAll("[^\\(\\)\\[\\]]", "");
    while (!line.equals("")) {
      String previous = line;
      line = line.replaceAll("\\(\\)", "");
      line = line.replaceAll("\\[\\]", "");
      if (previous.equals(line)) {
        return "no";
      }
    }
    return "yes";
  }

  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    while (true) {
      String line = s.nextLine();
      if (line.equals(".")) {
        break;
      }
      System.out.println(solve(line));
    }
  }
}
