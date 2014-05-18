import java.util.*;

public class C {
  private static ParseResult parse(int index, char[] input) {
    ArrayList<Integer> nums = new ArrayList<Integer>();
    outside: while (index < input.length) {
      switch (input[index]) {
        case '[':
          ParseResult parseResult = parse(index+1, input);
          nums.add(parseResult.number);
          index = parseResult.position + 1;
          break;
        case ']':
          break outside;
        default:  // [0-9]
          int output = 0;
          while (input[index] != ']') {
            output *= 10;
            output += input[index] - '0';
            index++;
          }
          return new ParseResult(index, output/2 + 1);
      }
    }
    Collections.sort(nums);
    int sum = 0;
    for (int i = 0; i < nums.size() / 2 + 1; i++) {
      sum += nums.get(i);
    }
    return new ParseResult(index, sum);
  }
  
  private static int solve(String input) {
    ParseResult p = parse(0, input.toCharArray());
    return p.number;
  }
  
  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    int n = s.nextInt();
    for (int i = 0; i < n; i++) {
      System.out.println(solve(s.next()));
    }
  }
}

class ParseResult {
  int position;
  int number;
  
  ParseResult(int position, int number) {
    this.position = position;
    this.number = number;
  }
}
