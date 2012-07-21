import java.util.*;
public class RotatingBot {
  private final static int W = 128;
  private final static int WH = 64;

  private final static int[] DI = new int[]{0, -1, 0, 1};
  private final static int[] DJ = new int[]{1, 0, -1, 0};

  private final static int EMPTY = 0;
  private final static int VISIT = 1;
  private final static int WALL = 2;


  public int minArea(int[] moves) {
    int[][] map = new int[W][W];
    for (int[] m: map) {
      Arrays.fill(m, EMPTY);
    }
    int i = WH;
    int j = WH;
    int drct = 0;
    map[i][j] = VISIT;

    for (int a = 0; a < moves.length; a++) {
      int m = moves[a];
      for (int x = 0; x < m; x++) {
        i += DI[drct];
        j += DJ[drct];
        if (map[i][j] != EMPTY) {
          return -1;
        }
        map[i][j] = VISIT;
      }
      int nexti = i + DI[drct];
      int nextj = j + DJ[drct];
      if (map[nexti][nextj] == EMPTY && a < moves.length-1) {
        map[nexti][nextj] = WALL;
      }
      drct++;
      drct %= 4;
    }
/*
    for (int ia = 0; ia < W; ia++) {
      for (int ja = 0; ja < W; ja++) {
        System.out.print(map[ia][ja]);
      }
      System.out.println();
    }
    */

    int maxVisitI = 0;
    int maxVisitJ = 0;
    int minVisitI = W;
    int minVisitJ = W;
    for (int ia = 0; ia < W; ia++) {
      for (int ja = 0; ja < W; ja++) {
        if (map[ia][ja] == VISIT) {
          maxVisitI = Math.max(maxVisitI, ia);
          minVisitI = Math.min(minVisitI, ia);
          maxVisitJ = Math.max(maxVisitJ, ja);
          minVisitJ = Math.min(minVisitJ, ja);
        }
      }
    }

    for (int ia = minVisitI; ia <= maxVisitI; ia++) {
      for (int ja = minVisitJ; ja <= maxVisitJ; ja++) {
        if (map[ia][ja] == WALL) {
          return -1;
        }
      }
    }
    return (maxVisitI - minVisitI + 1) * (maxVisitJ - minVisitJ + 1);
  }

// BEGIN CUT HERE
    public static void main(String[] args) {
        try {
            eq(0,(new RotatingBot()).minArea(new int[] {15}),16);
            eq(1,(new RotatingBot()).minArea(new int[] {3,10}),44);
            eq(2,(new RotatingBot()).minArea(new int[] {1,1,1,1}),-1);
            eq(3,(new RotatingBot()).minArea(new int[] {9,5,11,10,11,4,10}),132);
            eq(4,(new RotatingBot()).minArea(new int[] {12,1,27,14,27,12,26,11,25,10,24,9,23,8,22,7,21,6,20,5,19,4,18,3,17,2,16,1,15}),420);
            eq(5,(new RotatingBot()).minArea(new int[] {8,6,6,1}),-1);
            eq(6,(new RotatingBot()).minArea(new int[] {8,6,6}),63);
            eq(7,(new RotatingBot()).minArea(new int[] {5,4,5,3,3}),30);
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
