import java.util.*;

public class D {
  
  private static final double EPS = 1e-8;
  
  private static int gcd(int a, int b) {
    if (a == 0) return b;
    if (b == 0) return a;
    if (a % b == 0) return b;
    return gcd(b, a % b);
  }
  
  private static ArrayList<ArrayList<Time> > createTimeTable() {
    ArrayList<ArrayList<Time> > timeTable = new ArrayList<ArrayList<Time> >();
    
    for (int h = 0; h <= 100; h++) {
      if (h < 2) {
        // dummy
        timeTable.add(new ArrayList<Time>());
        continue;
      }
      
      ArrayList<Time> list = new ArrayList<Time>();
      // Search an additinal one minite in next day for test cases no more today's candidate time.
      for (int minitesBase = 0; minitesBase < 60 * h + 1; minitesBase++) {
        long secondMin = 60 * minitesBase;
        long secondMax = 60 * (minitesBase + 1);
        long numSecondHandGoRound = minitesBase;
        long numMiniteHandGoRound = minitesBase / 60;
        long numHourHandGoRound = minitesBase / (60 * h);
        /*
        k = -1, 0, 1
        (t%60)/60 = {(t%3600)/3600 + (t%(3600h))/(3600h)}/2 + 1/2k
        (t - 60*numSecondHandGoRound)/60 = {(t - 3600*numMiniteHandGoRound)/3600 + (t - 3600*h*numHourHandGoRound)/(3600*h)}/2 + 1/2k
        2*(t - 60*numSecondHandGoRound)/60 = (t - 3600*numMiniteHandGoRound)/3600 + (t - 3600*h*numHourHandGoRound)/(3600*h) + k
        2*60*h(t - 60*numSecondHandGoRound) = h(t - 3600*numMiniteHandGoRound) + (t - 3600*h*numHourHandGoRound) + 3600hk
        120ht - 7200h*numSecondHandGoRound = h*t - 3600h*numMiniteHandGoRound + t - 3600h*numHourHandGoRound + 3600hk
        (119h - 1)t = 7200h*numSecondHandGoRound - 3600h*numMiniteHandGoRound - 3600h*numHourHandGoRound + 3600hk
        t = (7200h*numSecondHandGoRound - 3600h*numMiniteHandGoRound - 3600h*numHourHandGoRound + 3600hk) / (119h - 1)
        */
        for (int k = -1; k <= 1; k++) {
          long n = 7200*h*numSecondHandGoRound - 3600*h*numMiniteHandGoRound - 3600*h*numHourHandGoRound + 3600*h*k;
          long d = 119*h - 1;
          if (n < 0) {
            continue;
          }
          long s = n / d;
          if (s < secondMin || secondMax <= s) {
            continue;
          }
          double second = (double)n / (double)d;
          double secondHandPos = (second - 60.0*numSecondHandGoRound) / 60.0;
          double miniteHandPos = (second - 3600.0*numMiniteHandGoRound) / 3600.0;
          double hourHandPos = (second - 3600.0*h*numHourHandGoRound) / (3600.0*h);
          
          if (Math.abs(miniteHandPos - secondHandPos) < EPS ||
              Math.abs(hourHandPos - miniteHandPos) < EPS ||
              Math.abs(secondHandPos - hourHandPos) < EPS) {
            continue;
          }
          int hour = (int)(s / 3600);
          int min = (int)((s / 60) % 60);
          int outputN = (int)(n - (3600 * hour + 60 * min) * d);
          int outputD = (int)d;
          int g = gcd(outputN, outputD);
          outputN /= g;
          outputD /= g;
          Time time = new Time(hour, min, outputN, outputD);
          list.add(time);
        }
      }
      timeTable.add(list);
    }
    return timeTable;
  }
  
  public static void main(String[] args) {
    ArrayList<ArrayList<Time> > timeTable = createTimeTable();
    
    Scanner sc = new Scanner(System.in);
    while(true) {
      int baseH = sc.nextInt();
      if (baseH == 0) {
        break;
      }
      int h = sc.nextInt();
      int m = sc.nextInt();
      int s = sc.nextInt();
      Time key = new Time(h, m, s, 1);
      ArrayList<Time> table = timeTable.get(baseH);
      int index = Collections.binarySearch(table, key);
      if (index >= 0) {
        table.get(index).print(baseH);
      } else {
        table.get(-(index+1)).print(baseH);
      }
    }
  }
}

class Time implements Comparable<Time> {
  int h, m, n, d;
  Time (int h, int m, int n, int d) {
    this.h = h;
    this.m = m;
    this.n = n;
    this.d = d;
  }
  public int compareTo(Time t) {
    if (this.h != t.h) {
      return this.h - t.h;
    }
    if (this.m != t.m) {
      return this.m - t.m;
    }
    //this.n / this.d - t.n / t.d
    //= (this.n * t.d - t.n * this.d) / (this.d * t.d)
    // Max d: 119*100 - 1
    // Max n: Max d * 60
    // Max d*n: at most 8 * 10^8
    return this.n * t.d - t.n * this.d;
  }
  
  public void print(int baseH) {
    System.out.printf("%d %d %d %d\n", h % baseH, m, n, d);
  }
}
