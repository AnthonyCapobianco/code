import java.util.*;
import java.io.*;
import java.math.*;
import java.text.*;


class Solution {
  public static void main(String args[]) throws Exception {
    BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
    
    boolean isSuccesful = false;
    String inputFromReader;
    int number = 0;

    while (!isSuccesful) {
      try {
        inputFromReader = reader.readLine();
        number = Integer.parseInt(inputFromReader);
        // Set succesful to true
        isSuccesful = true;
      } catch (NumberFormatException n) {
        System.out.println("Incorrect input. Please enter an integer.");
      } catch (Exception e) {
        // Get line of exception
        StackTraceElement lineOfException = new Exception().getStackTrace()[0];
        // Debug info
        System.err.println("Exception on line " + lineOfException.getLineNumber()
          + " in file: " + lineOfException.getFileName()
          + "\n\nException message: \n" + e);
        // Gracefully quit (aka crash)
        System.exit(1);
      }
    }

    System.out.println(number);
  }
}