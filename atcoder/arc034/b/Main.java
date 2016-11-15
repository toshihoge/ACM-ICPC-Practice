import java.util.*;
import java.math.*;
 
public class Main {
  private static long getEstimate(int index, int[] digits, int k) {
    long minN = 0;
    long digitSum = 0;
    for (int i = 0; i < index; i++) {
      minN *= 10;
      minN += digits[i];
      digitSum += digits[i];
    }
    for (int i = index; i < digits.length; i++) {
      minN *= 10;
      minN += k;
      digitSum += k;
    }
    return minN + digitSum;
  }
 
  private static long getMin(int index, int[] digits) {
    return getEstimate(index, digits, 0);
  }
 
  private static long getMax(int index, int[] digits) {
    return getEstimate(index, digits, 9);
  }
 
  private static long calculate(int[] digits) {
    long output = 0;
    for (int d : digits) {
      output *= 10;
      output += d;
    }
    return output;
  }
 
  private static void dfs(int index, int[] digits, long n, ArrayList<Long> solutions) {
    if (index >= digits.length) {
      if (getMin(index, digits) == n) {
        solutions.add(calculate(digits));
      }
      return;
    }
 
    if (getMin(index, digits) > n) {
      return;
    }
    if (getMax(index, digits) < n) {
      return;
    }
    for (int i = (index == 0 ? 1 : 0); i <= 9; i++) {
      digits[index] = i;
      dfs(index + 1, digits, n, solutions);
    }
  }
 
  private static ArrayList<Long> solve(long n) {
    ArrayList<Long> solutions = new ArrayList<Long>();
    for (int width = 1; width <= 18; width++) {
      int[] digits = new int[width];
      dfs(0, digits, n, solutions);
    }
    return solutions;
  }
 
  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    long n = s.nextLong();
    ArrayList<Long> solutions = solve(n);
    System.out.println(solutions.size());
    for (long solution : solutions) {
      System.out.println(solution);
    }
  }
}
