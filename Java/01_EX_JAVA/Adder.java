import java.util.*;

class Adder {
  public static void main(String[] args) {    

    if (args.length < 1) {
      System.out.println("No arguments");
      System.exit(0);
    } else {
      boolean isFirstRun = true;
      int total = 0;
      
      for (String s : args) {
        try {
          total += Integer.parseInt(s);
        } catch (Exception e) {
          // User friendly 'we f***ed up' message:
          System.out.println("Error: please provide numeric arguments");
          // Get line of exception
          StackTraceElement lineOfException = new Exception().getStackTrace()[0];
          // Debug info
          System.err.println("Exception on line " + lineOfException.getLineNumber()
            + " in file: " + lineOfException.getFileName()
            + "\n\nException message: \n" + e);
          // Gracefully quit (aka crash)
          System.exit(1);
        }
        
        if (isFirstRun) {
          isFirstRun = false;
          System.out.print(s);
        } else {
          System.out.print(" + " + s);
        }
      } // for (String s : args)
      System.out.println(" = " + total);
    } // if (args.length < 1)
  } // void main(String[] args)
} // class Adder
