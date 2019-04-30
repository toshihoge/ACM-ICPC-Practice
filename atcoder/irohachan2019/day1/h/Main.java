import java.util.*;

public class Main {
  private static int f(long n) {
    int fv = 0;
    while (n > 0) {
      fv += n % 10;
      n /= 10;
    }
    return fv;
  }
  
  private static long createFMin(int fv, int d) {
    String s = "";
    while (fv > 0) {
      long min10 = Math.min(fv - d, 9 - d);
      fv -= min10;
      s = "" + min10 + s;
      d = 0;
    }
    return Long.parseLong(s);
  }
  
  private static List<Integer> split9(int fv) {
    List<Integer> list = new ArrayList<Integer>();
    while (fv > 0) {
      list.add(Math.min(fv, 9));
      fv -= Math.min(fv, 9);
    }
    return list;
  }
  
  private static long build(List<Integer> list) {
    long output = 0;
    for (int i = list.size() - 1; i >= 0; i--) {
      output *= 10;
      output += list.get(i);
    }
    return output;
  }
  
  private static void confirm(List<Integer> list) {
    if (list.get(list.size() - 1) == 9) {
      list.remove(list.size() - 1);
      list.add(8);
      list.add(1);
      return;
    }
    if (list.size() > 1) {
      int d1 = list.remove(list.size() - 1);
      int d2 = list.remove(list.size() - 1);
      list.add(d2 - 1);
      list.add(d1 + 1);
      return;
    } else {
      int d = list.remove(list.size() - 1);
      list.add(d - 1);
      list.add(1);
      return;
    }
  }
  
  private static long solver(long n) {
    int fv = f(n);
    List<Integer> s9 = split9(fv);
    if (build(s9) != n) {
      return build(s9);
    }
    confirm(s9);
    return build(s9);
    /*
    int fv = f(n);
    long x;
    x = createFMin(fv, 0);
    if (x != n) {
      return x;
    }
    x = createFMin(fv, 1);
    return x;
    */
  }
  
  private static long naiveSolver(long n) {
    long fv = f(n);
    for (int i = 1; i < 100000; i++) {
      if (i == n) {
        continue;
      }
      if (f(i) == fv) {
        return i;
      }
    }
    return -1;
  }
  
  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    
    /*
    for (int i = 1; i < 10000; i++) {
      if (solver(i) != naiveSolver(i)) {
        System.out.println(solver(i));
        System.out.println(naiveSolver(i));
        System.out.println(i);
        break;
      }
    }
    */
    
    long n = s.nextLong();
    System.out.println(solver(n));
  }
}
