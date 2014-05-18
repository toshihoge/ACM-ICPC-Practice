import java.util.*;
import java.util.regex.*;

public class C_StackOverflow {
  private static Pattern BOTTOM_PATTERN = Pattern.compile("(\\[[0-9]+\\])+");
  private static Pattern FINAL_PATTERN = Pattern.compile("^\\[([0-9]+)\\]$");
  
  private static int getMinimumWin(String input, boolean bottom) {
    String[] strs = input.split("\\]\\[");
    ArrayList<Integer> nums = new ArrayList<Integer>();
    for (String s : strs) {
      s = s.replaceAll("[\\[\\]]", "");
      if (bottom) {
        nums.add(Integer.parseInt(s) / 2 + 1);
      } else {
        nums.add(Integer.parseInt(s));
      }
    }
    Collections.sort(nums);
    int sum = 0;
    for (int i = 0; i < nums.size()/2 + 1; i++) {
      sum += nums.get(i);
    }
    return sum;
  }
  
  private static String voteBottom(String input, boolean bottom) {
    String[] others = BOTTOM_PATTERN.split(input, 0);
    ArrayList<Integer> minWins = new ArrayList<Integer>();
    Matcher matcher = BOTTOM_PATTERN.matcher(input);
    while (matcher.find()) {
      minWins.add(getMinimumWin(matcher.group(), bottom));
    }
    if (others.length != minWins.size() + 1) {
      throw new RuntimeException();
    }
    String output = others[0];
    for (int i = 0; i < minWins.size(); i++) {
      output += minWins.get(i);
      output += others[i+1];
    }
    return output;
  }
  
  private static int solve(String input) {
    boolean bottom = true;
    while(true) {
      Matcher matcher = FINAL_PATTERN.matcher(input);
      if (matcher.find()) {
        return Integer.parseInt(matcher.group(1));
      }
      input = voteBottom(input, bottom);
      bottom = false;
    }
  }
  
  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    int n = s.nextInt();
    for (int i = 0; i < n; i++) {
      System.out.println(solve(s.next()));
    }
  }
}
