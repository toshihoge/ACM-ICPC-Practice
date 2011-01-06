import java.util.*;

class Token {
  public final static char PLUS = '+';
  public final static char MINUS = '-';
  public final static char NEGATE = '^';
  public final static char MULTIPLY = '*';
  public final static char OPENCASEARC = '(';
  public final static char CLOSECASEARC = ')';
  public final static char COMMA = ',';
  public final static char OPENBRACKET = '[';
  public final static char CLOSEBRACKET = ']';
  public final static char TRANSPOSE = '\'';
  public final static char SPACE = ' ';
  public final static char SEMICOLON = ';';
  public final static char NUMBER = 'n';
  public final static char VAR = 'v';
  
  char Token;
  int number;
  
  Token(char t, int n) {
    Token = t;
    number = n;
  }
  
  Token(char t) {
    this(t, 0);
  }
}

class MatrixBody {
  private final static int MOD = 32768;
  
  int h;
  int w;
  long[][] matrix;
  
  public MatrixBody(long v) {
    this.h = 1;
    this.w = 1;
    matrix = new long[1][1];
    matrix[0][0] = v;
  }
  
  public MatrixBody(int h, int w) {
    this.h = h;
    this.w = w;
    matrix = new long[this.h][this.w];
  }
  
  private static long normalize(long n) {
    while (n < 0) {
      n += MOD;
    }
    return n % MOD;
  }
  
  private boolean isScale() {
    return h == 1 && w == 1;
  }
  
  public static MatrixBody add(MatrixBody mb1, MatrixBody mb2) {
    if (mb1.isScale()) {
      return addScale(mb2, mb1.matrix[0][0]);
    } else if (mb2.isScale()) {
      return addScale(mb1, mb2.matrix[0][0]);
    } else {
      return addSameSize(mb1, mb2);
    }
  }
  
  private static MatrixBody addSameSize(MatrixBody mb1, MatrixBody mb2) {
    if (mb1.h == mb2.h && mb1.w == mb2.w) {
      MatrixBody output = new MatrixBody(mb1.h, mb1.w);
      for (int i = 0; i < mb1.h; i++) {
        for (int j = 0; j < mb1.w; j++) {
          output.matrix[i][j] = normalize(mb1.matrix[i][j] + mb2.matrix[i][j]);
        }
      }
      return output;
    } else {
      throw new RuntimeException();
    }
  }
  
  private static MatrixBody addScale(MatrixBody mb, long scale) {
    MatrixBody output = new MatrixBody(mb.h, mb.w);
    for (int i = 0; i < mb.h; i++) {
      for (int j = 0; j < mb.w; j++) {
        output.matrix[i][j] = normalize(mb.matrix[i][j] + scale);
      }
    }
    return output;
  }
  
  public static MatrixBody sub(MatrixBody mb1, MatrixBody mb2) {
    if (mb1.isScale()) {
      return multiplyScale(addScale(mb2, -mb1.matrix[0][0]), -1);
    } else if (mb2.isScale()) {
      return addScale(mb1, -mb2.matrix[0][0]);
    } else {
      return addSameSize(mb1, multiplyScale(mb2, -1));
    }
  }
  
  private static MatrixBody multiplyMatrix(MatrixBody mb1, MatrixBody mb2) {
    if (mb1.w == mb2.h) {
      MatrixBody output = new MatrixBody(mb1.h, mb2.w);
      for (int i = 0; i < mb1.h; i++) {
        for (int j = 0; j < mb2.w; j++) {
          long sum = 0;
          for (int k = 0; k < mb1.w; k++) {
            sum += mb1.matrix[i][k] * mb2.matrix[k][j];
          }
          output.matrix[i][j] = normalize(sum);
        }
      }
      return output;
    } else {
      throw new RuntimeException();
    }
  }
  
  public static MatrixBody mul(MatrixBody mb1, MatrixBody mb2) {
    if (mb1.isScale()) {
      return multiplyScale(mb2, mb1.matrix[0][0]);
    } else if (mb2.isScale()) {
      return multiplyScale(mb1, mb2.matrix[0][0]);
    } else {
      return multiplyMatrix(mb1, mb2);
    }
  }
  
  public static MatrixBody negate(MatrixBody mb) {
    return multiplyScale(mb, -1);
  }
  
  private static MatrixBody multiplyScale(MatrixBody mb, long scale) {
    MatrixBody output = new MatrixBody(mb.h, mb.w);
    for (int i = 0; i < mb.h; i++) {
      for (int j = 0; j < mb.w; j++) {
        output.matrix[i][j] = normalize(mb.matrix[i][j] * scale);
      }
    }
    return output;
  }
  
  public static MatrixBody transpose(MatrixBody mb) {
    MatrixBody output = new MatrixBody(mb.w, mb.h);
    for (int i = 0; i < mb.h; i++) {
      for (int j = 0; j < mb.w; j++) {
        output.matrix[j][i] = mb.matrix[i][j];
      }
    }
    return output;
  }
  
  public static MatrixBody indexedPrimary(MatrixBody mb1, MatrixBody mb2, MatrixBody mb3) {
    if (mb2.h == 1 && mb3.h == 1) {
      MatrixBody output = new MatrixBody(mb2.w, mb3.w);
      for (int i = 0; i < mb2.w; i++) {
        for (int j = 0; j < mb3.w; j++) {
          output.matrix[i][j] = mb1.matrix[(int)mb2.matrix[0][i]-1][(int)mb3.matrix[0][j]-1];
        }
      }
      return output;
    } else {
      throw new RuntimeException();
    }
  }
  
  public static MatrixBody concatenateRowSequence(MatrixBody mb1, MatrixBody mb2) {
    if (mb1.w == mb2.w) {
      MatrixBody output = new MatrixBody(mb1.h+mb2.h, mb1.w);
      for (int i = 0; i < mb1.h; i++) {
        for (int j = 0; j < mb1.w; j++) {
          output.matrix[i][j] = mb1.matrix[i][j];
        }
      }
      for (int i = 0; i < mb2.h; i++) {
        for (int j = 0; j < mb2.w; j++) {
          output.matrix[mb1.h + i][j] = mb2.matrix[i][j];
        }
      }
      return output;
    } else {
      throw new RuntimeException();
    }
  }
  
  public static MatrixBody concatenateRow(MatrixBody mb1, MatrixBody mb2) {
    if (mb1.h == mb2.h) {
      MatrixBody output = new MatrixBody(mb1.h, mb1.w + mb2.w);
      for (int i = 0; i < mb1.h; i++) {
        for (int j = 0; j < mb1.w; j++) {
          output.matrix[i][j] = mb1.matrix[i][j];
        }
        for (int j = 0; j < mb2.w; j++) {
          output.matrix[i][mb1.w + j] = mb2.matrix[i][j];
        }
      }
      return output;
    } else {
      throw new RuntimeException();
    }
  }
  
  public void print() {
    for (int i = 0; i < h; i++) {
      System.out.print(matrix[i][0]);
      for (int j = 1; j < w; j++) {
        System.out.print(" ");
        System.out.print(matrix[i][j]);
      }
      System.out.print("\n");
    }
  }
}

class Matrix {
  int begin;
  MatrixBody mb;
  
  Matrix (int begin, MatrixBody mb) {
    this.begin = begin;
    this.mb = mb;
  }
}

class Parser {
  Matrix[] environment;
  ArrayList<Token> tokens;
  
  Parser (Matrix[] environment) {
    this.environment = environment;
  }
  
  private Matrix parseExpr(int e) {
    Matrix term = parseTerm(e);
    if (term == null) {
      return null;
    }
    
    if (term.begin-1 >= 0) {
      if (tokens.get(term.begin-1).Token == Token.PLUS) {
        Matrix expr = parseExpr(term.begin-2);
        if (expr != null) {
          return new Matrix(expr.begin, MatrixBody.add(expr.mb, term.mb));
        }
      }
      if (tokens.get(term.begin-1).Token == Token.MINUS) {
        Matrix expr = parseExpr(term.begin-2);
        if (expr != null) {
          return new Matrix(expr.begin, MatrixBody.sub(expr.mb, term.mb));
        }
      }
    }
    return term;
  }
  
  private Matrix parseTerm(int e) {
    Matrix factor = parseFactor(e);
    if (factor == null) {
      return null;
    }
    
    if (factor.begin-1 >= 0 && tokens.get(factor.begin-1).Token == Token.MULTIPLY) {
      Matrix term = parseTerm(factor.begin-2);
      if (term != null) {
        return new Matrix(term.begin, MatrixBody.mul(term.mb, factor.mb));
      }
    }
    return factor;
  }
  
  private Matrix parseFactor(int e) {
    Matrix primary = parsePrimary(e);
    if (primary == null) {
      return null;
    }
    if (primary.begin-1 >= 0 && tokens.get(primary.begin-1).Token == Token.NEGATE) {
      return new Matrix(primary.begin-1, MatrixBody.negate(primary.mb));
    } else {
      return primary;
    }
  }
  
  private Matrix parseIndexedPrimary(int e) {
    if (tokens.get(e).Token == Token.CLOSECASEARC) {
      Matrix expr = parseExpr(e-1);
      if (expr != null && expr.begin-1 >= 0 && tokens.get(expr.begin - 1).Token == Token.COMMA) {
        Matrix exprFront = parseExpr(expr.begin - 2);
        if (exprFront != null && exprFront.begin-1 >= 0 && tokens.get(exprFront.begin - 1).Token == Token.OPENCASEARC) {
          Matrix primary = parsePrimary(exprFront.begin - 2);
          if (primary != null) {
            return new Matrix(primary.begin, MatrixBody.indexedPrimary(primary.mb, exprFront.mb, expr.mb));
          }
        }
      }
    }
    return null;
  }
  
  private Matrix parseCaseArcBlock(int e) {
    if (tokens.get(e).Token == Token.CLOSECASEARC) {
      Matrix expr = parseExpr(e-1);
      if (expr != null && expr.begin-1 >= 0 && tokens.get(expr.begin - 1).Token == Token.OPENCASEARC) {
        return new Matrix(expr.begin - 1, expr.mb);
      }
    }
    return null;
  }
      
  private Matrix parseTranspose(int e) {
    if (tokens.get(e).Token == Token.TRANSPOSE) {
      Matrix primary = parsePrimary(e-1);
      if (primary != null) {
        return new Matrix(primary.begin, MatrixBody.transpose(primary.mb));
      }
    }
    return null;
  }
  
  private Matrix parsePrimary(int e) {
    Matrix result = parseNumber(e);
    if (result != null) return result;
    result = parseVar(e);
    if (result != null) return result;
    result = parseMatrix(e);
    if (result != null) return result;
    result = parseCaseArcBlock(e);
    if (result != null) return result;
    result = parseIndexedPrimary(e);
    if (result != null) return result;
    result = parseTranspose(e);
    return result;
  }
  
  private Matrix parseMatrix(int e) {
    if (tokens.get(e).Token == Token.CLOSEBRACKET) {
      Matrix rowSequence = parseRowSequence(e-1);
      if (rowSequence != null && rowSequence.begin-1 >= 0 && tokens.get(rowSequence.begin-1).Token == Token.OPENBRACKET) {
        return new Matrix(rowSequence.begin-1, rowSequence.mb);
      }
    }
    return null;
  }
  
  private Matrix parseRowSequence(int e) {
    Matrix row = parseRow(e);
    if (row == null) {
      return null;
    }
    
    if (row.begin-1 >= 0 && tokens.get(row.begin-1).Token == Token.SEMICOLON) {
      Matrix rowSequence = parseRowSequence(row.begin-2);
      if (rowSequence != null) {
        return new Matrix(rowSequence.begin, MatrixBody.concatenateRowSequence(rowSequence.mb, row.mb));
      }
    }
    return row;
  }
  
  private Matrix parseRow(int e) {
    Matrix expr = parseExpr(e);
    if (expr == null) {
      return null;
    }
    if(expr.begin-1 >= 0 && tokens.get(expr.begin-1).Token == Token.SPACE) {
      Matrix row = parseRow(expr.begin-2);
      if (row != null) {
        return new Matrix(row.begin, MatrixBody.concatenateRow(row.mb, expr.mb));
      }
    }
    return expr;
  }
  
  private Matrix parseNumber(int e) {
    if (tokens.get(e).Token == Token.NUMBER) {
      return new Matrix(e, new MatrixBody(tokens.get(e).number));
    }
    return null;
  }
  
  private Matrix parseVar(int e) {
    if (tokens.get(e).Token == Token.VAR) {
      return new Matrix(e, environment[tokens.get(e).number].mb);
    }
    return null;
  }
  
  private static ArrayList<Token> lex(String line) {
    ArrayList<Token> output = new ArrayList<Token>();
    int index = 0;
    while (index < line.length()) {
      char c = line.charAt(index);
      if (Character.isDigit(c)) {
        int number = 0;
        while (index < line.length() && Character.isDigit(line.charAt(index))) {
          number *= 10;
          number += (line.charAt(index) - '0');
          index++;
        }
        output.add(new Token(Token.NUMBER, number));
      } else if ('A' <= c && c <= 'Z') {
        output.add(new Token(Token.VAR, c - 'A'));
        index++;
      } else {
        switch (c) {
        case '+':
        case '-':
        case '^':
        case '*':
        case '(':
        case ')':
        case ',':
        case '[':
        case ']':
        case '\'':
        case ' ':
        case ';':
          output.add(new Token(c));
          break;
        default:
          throw new RuntimeException("Lex exception!");
        }
        index++;
      }
    }
    return output;
  }
  
  private static String convert3SpacesTo1Space(String line) {
    while (line.contains("---")) {
      line = line.replaceAll("---", "-");
    }
    return line;
  }
  
  public static String convert2Spaces(String line) {
    line = line.replaceAll("^--", "");
    line = line.replaceAll("([0-9A-Z\\)\\]'])--", "$1+");
    line = line.replaceAll("([\\(\\[ ;\\*\\+])--", "$1");
    line = line.replaceAll("^-", "^");
    line = line.replaceAll("([\\(\\[ ;\\*\\+])-", "$1^");
    return line;
  }
  
  private static String preprocess(String line) {
    line = line.replaceAll("\\.", "");
    line = convert3SpacesTo1Space(line);
    line = convert2Spaces(line);
    return line;
  }
  
  public Matrix parse(String line) {
    line = preprocess(line);
    tokens = lex(line);
    Matrix expr = parseExpr(tokens.size() - 1);
    if (expr != null && expr.begin == 0) {
      return expr;
    } else {
      throw new RuntimeException();
    }
  }
}

public class Main {
  private static void solve(String[] lines) {
    Matrix[] results = new Matrix[26];
    Arrays.fill(results, null);
    for (String line : lines) {
      String rightPart = line.substring(2);
      Parser parser = new Parser(results);
      results[line.charAt(0) - 'A'] = parser.parse(rightPart);
      results[line.charAt(0) - 'A'].mb.print();
    }
    System.out.print("-----\n");
  }
  
  public static void main (String[] args) {
    Scanner s = new Scanner(System.in);
    while (true) {
      int n = Integer.parseInt(s.nextLine());
      if (n == 0) {
        break;
      }
      String lines[] = new String[n];
      for (int i = 0; i < n; i++) {
        lines[i] = s.nextLine();
      }
      solve(lines);
    }
  }
}
