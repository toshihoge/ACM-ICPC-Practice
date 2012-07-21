import java.util.*;
public class CheckerExpansion {
  public static boolean exist(long y, long x, long width) {
    if (width == 0) {
      return false;
    }
    if (y == 0 && x == 0) {
      return true;
    }
    long w4 = width/4;
    long w2 = width/2;
    if (x < w2 && y < w4) {
      return exist(y, x, w2);
    }
    if (w4 <= x && w4 <= y) {
      return exist(y - w4, x - w4, w2);
    }
    if (w2 <= x) {
      return exist(y, x - w2, w2);
    }
    return false;
  }

  public static char getChar(long t, long y, long x) {
    if (y < 0) return '.';
    if (x < 0) return '.';
    if (y > x) return '.';
    if ((y + x) % 2 == 1) return '.';
    if ((y+x) > (t-1)*2) return '.';
    if (exist(y, x, 1L << 60)) {
      if ((y+x) % 4 == 0) {
        return 'A';
      } else {
        return 'B';
      }
    }
    return '.';
  }
  public static String[] resultAfter(long t, long x0, long y0, int w, int h) {
    String[] res = new String[h];
    for (int i = 0; i < h; i++) {
      res[i] = "";
      for (int j = 0; j < w; j++) {
        res[i] += getChar(t, y0 + h - i - 1, x0 + j);
      }
    }
    return res;
  }

// BEGIN CUT HERE
    public static void main(String[] args) {
        try {
            eq(0,(new CheckerExpansion()).resultAfter(1L, 0L, 0L, 4, 4),new String[] {"....", "....", "....", "A..." });
            eq(1,(new CheckerExpansion()).resultAfter(5L, 4L, 1L, 3, 4),new String[] {"A..", "...", "B..", ".B." });
            eq(2,(new CheckerExpansion()).resultAfter(1024L, 1525L, 512L, 20, 2),new String[] {"B...B...B...........", ".B.A.B.A.B.........." });
            eq(3,(new CheckerExpansion()).resultAfter(53L, 85L, 6L, 5, 14),new String[] {".....", ".....", "B....", ".B.A.", ".....", ".....", ".....", ".....", ".....", ".....", "B....", ".B...", "..B..", ".A.B." });
        } catch( Exception exx) {
            System.err.println(exx);
            exx.printStackTrace(System.err);
        }
        exist(2L, 4L, 1L<<60);
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
