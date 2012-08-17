import java.util.*;
public class FoxPaintingBalls {
  private long needsR(long n) {
    n--;
    return (n+2)*(n+1)/2 - 2*needsGB(n+1);
  }
  private long needsGB(long n) {
    n--;
    long div3 = n/3;
    long div3p = div3*(div3+1)/2;
    switch ((int)(n - 3*div3)) {
    case 0:
      return 3*div3p;
    case 1:
      return 3*div3p + div3 + 1;
    case 2:
      return 3*div3p + 2*div3 + 2;
    }
    return 0;
  }

  private boolean ac(long r, long g, long b, long v, long base, long diff) {
    double vd = (double)v;
    double based = (double)base;
    double rd = (double)r;
    double gd = (double)r;
    double bd = (double)r;
    if (rd*2.0 < based*vd || gd*2.0 < based*vd || bd*2.0 < based*vd) {
      return false;
    }
    r -= v*base;
    g -= v*base;
    b -= v*base;
    if (r < 0 || g < 0 || b < 0) {
      return false;
    }
    if (diff == 0) {
      return true;
    }
    return r/diff + g/diff + b/diff >= v;
  }

  public long theMax(long r, long g, long b, int nint) {
    long n = (long)nint;
    long base = needsGB(n);
    long diff = needsR(n) - needsGB(n);
    
    long max = 1L<<62;
    long min = 0;

    while (max - min > 1) {
      //System.out.printf("%d %d\n", max, min);
      long mid = (max + min) / 2;
      if (ac(r, g, b, mid, base, diff)) {
        min = mid;
      } else {
        max = mid;
      }
    }
    if (ac(r, g, b, max, base, diff)) {
      return max;
    } else {
      return min;
    }
  }

// BEGIN CUT HERE
    public static void main(String[] args) {
        try {
            eq(0,(new FoxPaintingBalls()).theMax(2L, 2L, 2L, 3),1L);
            eq(1,(new FoxPaintingBalls()).theMax(1L, 2L, 3L, 3),0L);
            eq(2,(new FoxPaintingBalls()).theMax(8L, 6L, 6L, 4),2L);
            eq(3,(new FoxPaintingBalls()).theMax(7L, 6L, 7L, 4),2L);
            eq(4,(new FoxPaintingBalls()).theMax(100L, 100L, 100L, 4),30L);
            eq(5,(new FoxPaintingBalls()).theMax(19330428391852493L, 48815737582834113L, 11451481019198930L, 3456),5750952686L);
            eq(6,(new FoxPaintingBalls()).theMax(1L, 1L, 1L, 1),3L);
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
