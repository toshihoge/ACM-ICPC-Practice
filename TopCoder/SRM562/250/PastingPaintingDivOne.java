import java.util.*;
public class PastingPaintingDivOne {
  private char[][] pasteSmall(char[][] cb, int t) {
    char[][] canvas = new char[120][120];
    for (char[] c: canvas) {
      Arrays.fill(c, '.');
    }
    for (int a = 0; a < t; a++) {
      for (int i = 0; i < cb.length; i++) {
        for (int j = 0; j < cb[i].length; j++) {
          if (cb[i][j] != '.') {
            canvas[i+a][j+a] = cb[i][j];
          }
        }
      }
    }
    return canvas;
  }

  private int charIndex(char c) {
    switch(c) {
    case 'R':
      return 0;
    case 'G':
      return 1;
    case 'B':
      return 2;
    default:
      return -1;
    }
  }

  private long[] count(char[][] canvas) {
    long[] output = new long[3];
    for (int i = 0; i < canvas.length; i++) {
      for (int j = 0; j < canvas.length; j++) {
        int index = charIndex(canvas[i][j]);
        if (index >= 0) {
          output[index]++;
        }
      }
    }
    return output;
  }
  public long[] countColors(String[] clipboard, int t) {
    int n = clipboard.length;
    int m = clipboard[0].length();
    char[][] cb = new char[n][m];
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        cb[i][j] = clipboard[i].charAt(j);
      }
    }
    long[] res;
    if (t > 60) {
      char[][] canvas = pasteSmall(cb, 60);
      long[] output = new long[3];
      for (int i = 59; i < canvas.length; i++) {
        int index = charIndex(canvas[i][59]);
        if (index < 0) continue;
        output[index] += (t - 60);
      }
      for (int j = 60; j < canvas.length; j++) {
        int index = charIndex(canvas[59][j]);
        if (index < 0) continue;
        output[index] += (t - 60);
      }
      long[] answer = count(canvas);
      for (int i = 0; i < 3; i++) {
        answer[i] += output[i];
      }
      return answer;
    } else {
      char[][] canvas = pasteSmall(cb, t);
      long[] answer = count(canvas);
      return answer;
    }
  }

// BEGIN CUT HERE
    public static void main(String[] args) {
        try {
            eq(0,(new PastingPaintingDivOne()).countColors(new String[] {
               "..G",
               "R..",
               "BG."
               }, 3),new long[] {3L, 4L, 3L });
            eq(1,(new PastingPaintingDivOne()).countColors(new String[] {
               "R...",
               "....",
               "....",
               "...R"
               }, 2),new long[] {4L, 0L, 0L });
            eq(2,(new PastingPaintingDivOne()).countColors(new String[] {"RGB"}, 100000),new long[] {100000L, 100000L, 100000L });
            eq(3,(new PastingPaintingDivOne()).countColors(new String[] {"."}, 1000000000),new long[] {0L, 0L, 0L });
            eq(4,(new PastingPaintingDivOne()).countColors(new String[] {
               "RB.",
               ".G."
               }
               , 100),new long[] {100L, 1L, 100L });
            eq(5,(new PastingPaintingDivOne()).countColors(new String[] {
               "..........G..........",
               ".........G.G.........",
               "........G...G........",
               ".......G.....G.......",
               "......G..B.B..G......",
               ".....G...B.B...G.....",
               "....G...........G....",
               "...G...R.....R...G...",
               "..G.....RRRRRR....G..",
               ".G..........RR.....G.",
               "GGGGGGGGGGGGGGGGGGGGG"
               }, 1000000000),new long[] {2000000018L, 17000000048L, 2000000005L });
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
