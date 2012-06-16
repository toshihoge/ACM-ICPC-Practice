// This code was written after the contest.

import java.util.*;
public class FavouriteDigits {
  final static int WIDTH = 16;
  int[] target, test;
  int d1, d2;

  private void add(ArrayList<Integer> ds, int n) {
    if (!ds.contains(n)) {
      ds.add(n);
    }
  }

  private int decrementValue(int d, int dx, int cx, boolean leading0) {
    if (d == dx && cx > 0) {
      if (dx != 0 || !leading0) {
        return 1;
      }
    }
    return 0;
  }

  private boolean dfs(int index, int c1, int c2, boolean equal, boolean leading0) {
    if (index == WIDTH) {
      return c1 == 0 && c2 == 0;
    }
    if (WIDTH - index < c1 + c2) {
      return false;
    }
    ArrayList<Integer> ds = new ArrayList<Integer>();
    add(ds, 0);
    add(ds, d1);
    add(ds, d2);
    add(ds, target[index]);
    if (target[index]+1 < 10) {
      add(ds, target[index]+1);
    }
    Collections.sort(ds);
    for (int d: ds) {
      if (equal && d < target[index]) {
        continue;
      }
      int nextC1 = c1 - decrementValue(d, d1, c1, leading0);
      int nextC2 = c2 - decrementValue(d, d2, c2, leading0);
      boolean nextEqual = equal && d == target[index];
      boolean nextLeading0 = leading0 && d == 0;
      test[index] = d;
      if (dfs(index+1, nextC1, nextC2, nextEqual, nextLeading0)) {
        return true;
      }
    }
    return false;
  }

  public long findNext(long N, int d1, int c1, int d2, int c2) {
    target = new int[WIDTH];
    test = new int[WIDTH];
    this.d1 = d1;
    this.d2 = d2;
    Arrays.fill(target, 0);
    Arrays.fill(test, 0);
    long nn = N;
    for (int i = WIDTH-1; nn > 0; i--, nn/=10) {
      target[i] = (int)(nn % 10);
    }
    dfs(0, c1, c2, true, true);
    long output = 0;
    for (int i = 0; i < WIDTH; i++) {
      output *= 10;
      output += test[i];
    }
    return output;
  }

// BEGIN CUT HERE
    public static void main(String[] args) {
        try {
            eq(0,(new FavouriteDigits()).findNext(47L, 1, 0, 2, 0),47L);
            eq(1,(new FavouriteDigits()).findNext(47L, 5, 0, 9, 1),49L);
            eq(2,(new FavouriteDigits()).findNext(47L, 5, 0, 3, 1),53L);
            eq(3,(new FavouriteDigits()).findNext(47L, 2, 1, 0, 2),200L);
            eq(4,(new FavouriteDigits()).findNext(123456789012345L, 1, 2, 2, 4),123456789012422L);
            eq(5,(new FavouriteDigits()).findNext(92L, 1, 1, 0, 0),100L);
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
