import java.util.*;
public class Main {
  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    
    long n = s.nextLong();
    long a = s.nextLong();
    int b = s.nextInt();
    long ds[] = new long[b + 2];
    for (int i = 0; i < b; i++) {
      ds[i] = s.nextLong();
    }
    ds[b] = 0;
    ds[b+1] = n + 1;
    Arrays.sort(ds);
    
    long sum = 0;
    for (int i = 1; i < ds.length; i++) {
      sum += ds[i] - ds[i-1] - 1;
      sum -= (ds[i] - ds[i-1] - 1) / a;
    }
    System.out.println(sum);
  }
}
