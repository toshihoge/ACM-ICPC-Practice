import java.util.*;


import java.util.*;

/**
 * Usage:
 *  MaximumBipartiteMatchingSolver solver =
 *      new MaximumBipartiteMatchingSolver();
 *
 *  solver.addEdege(srcIndex, dstIndex);  // Each edge
 *
 *  int maximumNumber = solver.solve();
 *
 * Verified:
 *  AOJ1185 
 */
class MaximumBipartiteMatchingSolver {
  private int maxSrc;
  private int maxDst;
  private HashSet<Integer> edges;

  public MaximumBipartiteMatchingSolver() {
    maxSrc = 1;
    maxDst = 1;
    edges = new HashSet<Integer>();
  }

  private int makeEdge(int src, int dst) {
    return (src << 16) | dst;
  }

  public void addEdge(int src, int dst) {
    maxSrc = Math.max(maxSrc, src+1);
    maxDst = Math.max(maxDst, dst+1);
    edges.add(makeEdge(src, dst));
  }

  private boolean containEdge(int src, int dst) {
    return edges.contains(makeEdge(src, dst));
  }

  private boolean dfs(int srcIndex, int[] prev, boolean[] visit) {
    if (srcIndex < 0) {
      return true;
    }
    for (int i = 0; i < maxDst; i++) {
      if (visit[i] || !containEdge(srcIndex, i)) {
        continue;
      }
      visit[i] = true;
      if (dfs(prev[i], prev, visit)) {
        prev[i] = srcIndex;
        return true;
      }
    }
    return false;
  }

  public int solve() {
    int count = 0;
    int[] prev = new int[maxDst];
    boolean[] visit = new boolean[maxDst];
    Arrays.fill(prev, -1);
    for (int i = 0; i < maxSrc; i++) {
      Arrays.fill(visit, false);
      if (dfs(i, prev, visit)) {
        count++;
      }
    }
    return count;
  }
}

public class Incubator {
  public int maxMagicalGirls(String[] love) {
    int n = love.length;
    boolean[][] matrix = new boolean[n][n];
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (love[i].charAt(j) == 'Y') {
          matrix[i][j] = true;
        } else {
          matrix[i][j] = false;
        }
      }
    }
    for (int k = 0; k < n; k++) {
      for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
          matrix[i][j] |= matrix[i][k] && matrix[k][j];
        }
      }
    }
    MaximumBipartiteMatchingSolver solver =
        new MaximumBipartiteMatchingSolver();
  
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (matrix[i][j]) {
          solver.addEdge(i, j);
        }
      }
    }
  
    return n - solver.solve();
  }

// BEGIN CUT HERE
    public static void main(String[] args) {
        try {
            eq(0,(new Incubator()).maxMagicalGirls(new String[] {"NY","NN"}),1);
            eq(1,(new Incubator()).maxMagicalGirls(new String[] {"NYN", "NNY", "NNN"}),1);
            eq(2,(new Incubator()).maxMagicalGirls(new String[] {"NNYNN","NNYNN","NNNYY","NNNNN","NNNNN"}),2);
            eq(3,(new Incubator()).maxMagicalGirls(new String[] {"NNNNN","NYNNN","NYNYN","YNYNN","NNNNN"}),2);
            eq(4,(new Incubator()).maxMagicalGirls(new String[] {"NNNNN","NNNNN","NNNNN","NNNNN","NNNNN"}),5);
            eq(5,(new Incubator()).maxMagicalGirls(new String[] {"NNYNNNNN","NNNYNNNN","NNNNYNNN","NNYNNNNN","NNNNNYYN","NNNYNNNY","NNNNNNNN","NNNNNNNN"}),2);
            eq(6,(new Incubator()).maxMagicalGirls(new String[] {"Y"}),0);
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
