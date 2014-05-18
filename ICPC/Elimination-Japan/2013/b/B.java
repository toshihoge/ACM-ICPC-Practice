import java.util.*;

public class B {
  private static String solve(int m, int t, int p, Submit[] submits) {
    Team[] teams = new Team[t];
    for (int i = 0; i < t; i++) {
      teams[i] = new Team(i+1, p);
    }
    for (Submit submit : submits) {
      for (Team team : teams) {
        team.maybeApplySubmit(submit);
      }
    }
    Arrays.sort(teams);
    String output = "" + teams[0].id;
    for (int i = 1; i < t; i++) {
      if (teams[i-1].compareTeamRank(teams[i]) == 0) {
        output += "=";
      } else {
        output += ",";
      }
      output += teams[i].id;
    }
    return output;
  }
  
  public static void main(String[] args) {
    Scanner s = new Scanner(System.in);
    while (true) {
      int m = s.nextInt();
      int t = s.nextInt();
      int p = s.nextInt();
      int r = s.nextInt();
      if (m == 0) {
        break;
      }
      
      Submit[] submits = new Submit[r];
      for (int i = 0; i < r; i++) {
        submits[i] = new Submit(
            s.nextInt(), s.nextInt(), s.nextInt(), s.nextInt());
      }
      System.out.println(solve(m, t, p, submits));
    }
  }
}

class Submit {
  int m, t, p, j;
  
  Submit (int m, int t, int p, int j) {
    this.m = m;
    this.t = t;
    this.p = p;
    this.j = j;
  }
}

class Team implements Comparable<Team> {
  int id;
  int accept;
  int penalty;
  int[] wrongs;
  
  Team (int id, int p) {
    this.id = id;
    this.accept = 0;
    this.penalty = 0;
    this.wrongs = new int[p+1];
  }
  
  void maybeApplySubmit(Submit submit) {
    if (id != submit.t) {
      return;
    }
    if (submit.j == 0) {
      accept++;
      penalty += submit.m + wrongs[submit.p] * 20;
    } else {
      wrongs[submit.p]++;
    }
  }
  
  public int compareTeamRank(Team team) {
    if (this.accept != team.accept) {
      return team.accept - this.accept;
    }
    if (this.penalty != team.penalty) {
      return this.penalty - team.penalty;
    }
    return 0;
  }
  
  public int compareTo(Team team) {
    int result = this.compareTeamRank(team);
    if (result != 0) {
      return result;
    }
    return team.id - this.id;
  }
}
