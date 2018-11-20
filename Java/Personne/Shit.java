import java.util.*;

public class Shit {
  public static String readLn(int maxLg) {
    byte lin[] = new byte[maxLg];
    int lg = 0, car = -1;
    String line = "";
    try {
      while (lg < maxLg) {
        car = System.in.read();
        if ((car < 0) || (car == '\n')) {
          break;
        }
        lin[lg++] += car;
      }
    } catch (java.io.IOException e) {
      return (null);
    }
    if  ((car < 0) && (lg == 0)) {
      return (null); // eof
    }
    return (new String(lin, 0, lg));
  }
  public static void main(String[] args) {
    
    
    try {
      System.out.println(readLn(1));
    } catch (Exception e) {
      System.err.print(e);
    }
    
  }
}
