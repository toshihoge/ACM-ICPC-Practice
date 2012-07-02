import java.util.*;
public class KingdomAndDice {
  private int[] getNext(int[] reachable, int number) {
    int[] next = new int[reachable.length];
    for (int i = 0; i < reachable.length; i++) {
      next[i] = reachable[i];
      if (i-number >= 0) {
        next[i] = Math.min(next[i], reachable[i-number]+1);
      }
    }
    return next;
  }

  private int[] getReachable(int[] labels, int target) {
    int[] reachable = new int[target+1];
    Arrays.fill(reachable, 1000);
    reachable[0] = 0;
    for (int i = 1; i < labels.length; i++) {
      for (int j = 0; j < labels[i]; j++) {
        reachable = getNext(reachable, i);
      }
    }
    return reachable;
  }

  public double newFairness(int[] fd, int[] sd, int X) {
    int n = fd.length;
    Arrays.sort(fd);
    Arrays.sort(sd);

    int[] labels = new int[n+1];
    labels[0] = n;
    for (int i = 1; i <= n; i++) {
      int min = sd[i-1];
      int max = i < n ? sd[i] : X+1;
      labels[i] = max - min - 1;
      for (int j = 0; j < n; j++) {
        if (min < fd[j] && fd[j] < max) {
          labels[i]--;
        }
      }
      labels[i] = Math.min(50, labels[i]);
    }

    ArrayList<Integer> targets = new ArrayList<Integer>();
    if (n % 2 == 0) {
      for (int i = 0; i <= n*n/2 + 2; i++) {
        targets.add(n*n/2 - i);
        targets.add(n*n/2 + i);
      }
    } else {
      targets.add(n*n/2);
      for (int i = 0; i <= n*n/2 + 2; i++) {
        targets.add(n*n/2 + i);
        targets.add(n*n/2 - i);
      }
    }

    int wins = 0;
    int blanks = 0;
    for (int i = 0; i < n; i++) {
      if (fd[i] == 0) {
        blanks++;
      }
      for (int j = 0; j < n; j++) {
        if (fd[i] > sd[j]) {
          wins++;
        }
      }
    }
    int[] reachable = getReachable(labels, n*n+1);

    for (int target: targets) {
      if (target - wins >= 0) {
        if (reachable[target-wins] <= blanks) {
          return (double)target / (n*n);
        }
      }
    }
    return 0.0;
  }

// BEGIN CUT HERE
    public static void main(String[] args) {
        try {
            eq(0,(new KingdomAndDice()).newFairness(new int[] {0, 2, 7, 0}, new int[] {6, 3, 8, 10}, 12),0.4375);
            eq(1,(new KingdomAndDice()).newFairness(new int[] {0, 2, 7, 0}, new int[] {6, 3, 8, 10}, 10),0.375);
            eq(2,(new KingdomAndDice()).newFairness(new int[] {0, 0}, new int[] {5, 8}, 47),0.5);
            eq(3,(new KingdomAndDice()).newFairness(new int[] {19, 50, 4}, new int[] {26, 100, 37}, 1000),0.2222222222222222);
            eq(4,(new KingdomAndDice()).newFairness(new int[] {6371, 0, 6256, 1852, 0, 0, 6317, 3004, 5218, 9012}, new int[] {1557, 6318, 1560, 4519, 2012, 6316, 6315, 1559, 8215, 1561}, 10000),0.49);
            eq(6,(new KingdomAndDice()).newFairness(new int[] {0, 0}, new int[] {2, 4}, 5),0.5);
            eq(7,(new KingdomAndDice()).newFairness(new int[] {0, 2}, new int[] {1, 3}, 4),0.25);
            int[] fd = new int[50];
            Arrays.fill(fd, 0);
            int[] sd = new int[50];
            for (int i = 0; i < 50; i++) {
              sd[i] = (i+1)*100;
            }
            eq(5,(new KingdomAndDice()).newFairness(fd, sd, 100000),0.5);
        } catch( Exception exx) {
            System.err.println(exx);
            exx.printStackTrace(System.err);
        }
    }
    private static void eq( int n, int a, int b ) {
        if ( a==b )
            System.err.println("Case "+n+" passed.");
        else
            System.err.println("Case "+n+" failed: expected "+b+", received "+a+".");
    }
    private static void eq( int n, char a, char b ) {
        if ( a==b )
            System.err.println("Case "+n+" passed.");
        else
            System.err.println("Case "+n+" failed: expected '"+b+"', received '"+a+"'.");
    }
    private static void eq( int n, long a, long b ) {
        if ( a==b )
            System.err.println("Case "+n+" passed.");
        else
            System.err.println("Case "+n+" failed: expected \""+b+"L, received "+a+"L.");
    }
    private static void eq( int n, boolean a, boolean b ) {
        if ( a==b )
            System.err.println("Case "+n+" passed.");
        else
            System.err.println("Case "+n+" failed: expected "+b+", received "+a+".");
    }
    private static void eq( int n, String a, String b ) {
        if ( a != null && a.equals(b) )
            System.err.println("Case "+n+" passed.");
        else
            System.err.println("Case "+n+" failed: expected \""+b+"\", received \""+a+"\".");
    }
    private static void eq(int n, double a, double b) {
        if (Math.abs(a - b) < 1e-9)
            System.err.println("Case "+n+" passed.");
        else
            System.err.println("Case "+n+" failed: expected \""+b+"\", received \""+a+"\".");
    }
    private static void eq( int n, int[] a, int[] b ) {
        if ( a.length != b.length ) {
            System.err.println("Case "+n+" failed: returned "+a.length+" elements; expected "+b.length+" elements.");
            return;
        }
        for ( int i= 0; i < a.length; i++)
            if ( a[i] != b[i] ) {
                System.err.println("Case "+n+" failed. Expected and returned array differ in position "+i);
                print( b );
                print( a );
                return;
            }
        System.err.println("Case "+n+" passed.");
    }
    private static void eq( int n, long[] a, long[] b ) {
        if ( a.length != b.length ) {
            System.err.println("Case "+n+" failed: returned "+a.length+" elements; expected "+b.length+" elements.");
            return;
        }
        for ( int i= 0; i < a.length; i++ )
            if ( a[i] != b[i] ) {
                System.err.println("Case "+n+" failed. Expected and returned array differ in position "+i);
                print( b );
                print( a );
                return;
            }
        System.err.println("Case "+n+" passed.");
    }
    private static void eq( int n, String[] a, String[] b ) {
        if ( a.length != b.length) {
            System.err.println("Case "+n+" failed: returned "+a.length+" elements; expected "+b.length+" elements.");
            return;
        }
        for ( int i= 0; i < a.length; i++ )
            if( !a[i].equals( b[i])) {
                System.err.println("Case "+n+" failed. Expected and returned array differ in position "+i);
                print( b );
                print( a );
                return;
            }
        System.err.println("Case "+n+" passed.");
    }
    private static void print( int a ) {
        System.err.print(a+" ");
    }
    private static void print( long a ) {
        System.err.print(a+"L ");
    }
    private static void print( String s ) {
        System.err.print("\""+s+"\" ");
    }
    private static void print( int[] rs ) {
        if ( rs == null) return;
        System.err.print('{');
        for ( int i= 0; i < rs.length; i++ ) {
            System.err.print(rs[i]);
            if ( i != rs.length-1 )
                System.err.print(", ");
        }
        System.err.println('}');
    }
    private static void print( long[] rs) {
        if ( rs == null ) return;
        System.err.print('{');
        for ( int i= 0; i < rs.length; i++ ) {
            System.err.print(rs[i]);
            if ( i != rs.length-1 )
                System.err.print(", ");
        }
        System.err.println('}');
    }
    private static void print( String[] rs ) {
        if ( rs == null ) return;
        System.err.print('{');
        for ( int i= 0; i < rs.length; i++ ) {
            System.err.print( "\""+rs[i]+"\"" );
            if( i != rs.length-1)
                System.err.print(", ");
        }
        System.err.println('}');
    }
    private static void nl() {
        System.err.println();
    }
// END CUT HERE
}
