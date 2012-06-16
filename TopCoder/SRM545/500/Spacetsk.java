// This code was written after the contest.

import java.util.*;
public class Spacetsk {
  private final static int MAX = 2010;
  private final static long MOD = 1000000007;
  long[][] makePascalTriangle (int n) {
    long[][] matrix = new long[n+1][n+1];
    for (long[] array: matrix) {
      Arrays.fill(array, 0);
    }
    matrix[0][0] = 1;
    for (int i = 1; i <= n; i++) {
      matrix[i][0] = 1;
      for (int j = 1; j <= i; j++) {
        matrix[i][j] = (matrix[i-1][j] + matrix[i-1][j-1]) % MOD;
      }
    }
    return matrix;

  }

  private int gcd(int a, int b) {
    return b%a == 0 ? a : gcd(b%a, a);
  }
  
  public int countsets(int L, int H, int K) {
    if (K == 1) {
      return (int)((L+1)*(H+1) % MOD);
    }
    long[][] table = makePascalTriangle(MAX);
    long[] cache = new long[L+1];
    cache[0] = 0;
    for (int x = 1; x <= L; x++) {
      cache[x] = cache[x-1];
      for (int y = 1; y <= H; y++) {
        int g = gcd(x, y);
        int num = x / (x / g);
        if (num >= K-1) {
          cache[x] += table[num][K-1];
          cache[x] %= MOD;
        }
      }
    }
    long res = (L+1)*table[H+1][K];
    res %= MOD;
    for (int x = 0; x <= L; x++) {
      res += cache[x];
      res %= MOD;
      res += cache[L-x];
      res %= MOD;
    }
    return (int)res;
  }

// BEGIN CUT HERE
    public static void main(String[] args) {
        try {
            eq(0,(new Spacetsk()).countsets(1, 1, 2),4);
            eq(1,(new Spacetsk()).countsets(1, 1, 1),4);
            eq(2,(new Spacetsk()).countsets(2, 2, 1),9);
            eq(3,(new Spacetsk()).countsets(2, 2, 2),23);
            eq(4,(new Spacetsk()).countsets(5, 5, 3),202);
            eq(5,(new Spacetsk()).countsets(561, 394, 20),786097180);
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
