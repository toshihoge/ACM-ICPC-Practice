import java.util.*;
import java.math.*;
 
public class Main {
  private static long calculate(
      ArrayList<Integer> positions,
      ArrayList<Boolean> directions,
      int rightBegin,
      int rightEnd,
      int leftBegin,
      int leftEnd) {
    long rightCount = rightEnd - rightBegin + 1;
    long leftCount = leftEnd - leftBegin + 1;
    
    int rightMax;
    int leftMin;
    if (rightCount > leftCount) {
      rightMax = positions.get(leftBegin) - 1;
      leftMin = positions.get(leftBegin);
    } else {
      rightMax = positions.get(rightEnd);
      leftMin = positions.get(rightEnd) + 1;
    }
 
    long sum = 0;
    for (int i = rightBegin; i <= rightEnd; i++) {
      sum += rightMax - positions.get(i);
    }
    sum -= rightCount * (rightCount - 1) / 2;
 
    for (int i = leftBegin; i <= leftEnd; i++) {
      sum += positions.get(i) - leftMin;
    }
    sum -= leftCount * (leftCount - 1) / 2;
    return sum;
  }
 
  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    int n = s.nextInt();
    int l = s.nextInt();
    ArrayList<Integer> positions = new ArrayList<Integer>();
    ArrayList<Boolean> directions = new ArrayList<Boolean>();
 
    positions.add(-1);
    directions.add(false);  // right
    positions.add(0);
    directions.add(true);  // left
    for (int i = 0; i < n; i++) {
      positions.add(s.nextInt());
      directions.add(s.next().charAt(0) == 'L');
    }
    positions.add(l+1);
    directions.add(false);  // right
    positions.add(l+2);
    directions.add(true);   // left
 
    long sum = 0;
    int rightBegin = 0;
    while (rightBegin < directions.size()) {
      int rightEnd =  rightBegin;
      while (directions.get(rightEnd+1) == false) {
        rightEnd++;
      }
      int leftBegin = rightEnd+1;
      int leftEnd = leftBegin;
      while (leftEnd+1 < directions.size() &&
          directions.get(leftEnd+1) == true) {
        leftEnd++;
      }
      sum += calculate(
          positions,
          directions,
          rightBegin,
          rightEnd,
          leftBegin,
          leftEnd);
      rightBegin = leftEnd + 1;
    }
    System.out.println(sum);
  }
}
