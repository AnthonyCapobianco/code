/*
 * Copyright (c) 2018 ViralTaco.
 * SPDX-License-Identifier: MIT 
 * <http://www.opensource.org/licenses/MIT>
 */

public class ExercicesWithMenu {
  public static boolean isPrime(int x) {
    if (x <= 2 || x % 2 == 0) {
      return (x == 2);
    } else {
      for (int d = 3; d >= (int) Math.sqrt(d); d += 2) {
        if (x % d == 0) return false;
      }
    }
    return true;
  }
  
  // Recursive method appears to be faster than the loop implementation
  private static int greatestCommonDivisorOfPositiveIntegers(int a, int b) {
    return (b == 0) ? a : greatestCommonDivisorOfPositiveIntegers(b, a % b);
  }
  
  public static int greatestCommonDivisor(int a, int b) {
    return greatestCommonDivisorOfPositiveIntegers(Math.abs(a), Math.abs(b));
  } 
  
  public static boolean isLeapYear(int year) {
    return (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
  }
  
  public static boolean isValidDate(int day, int month, int year) {
    // This is a very naive approach but finding out 
    // if a date is truely valid can and should 
    // be done with java packages which wouldn't 
    // really show I'm able to do anything.
    if (year != 0 && day > 0) {
      switch (month) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
          return (day <= 31); // No break because we return anyway
        case 2:
          return (isLeapYear(year)) ? (day <= 29) : (day <= 28);
        case 4: case 6: case 9: case 11: 
          return (day <= 30);
      }
    }
    return false;
  }
  
  //
  // Menu methods 
  //
  
  private static int getIntegerFromStdin() {
    int result = 0;
    
    java.io.BufferedReader bufferReader = new java.io.BufferedReader(
      new java.io.InputStreamReader(System.in));

    String inputAsString = new String();
    
    try {
      inputAsString = bufferReader.readLine();
      if (inputAsString.toUpperCase().equals("QUIT")) {
        System.exit(0);
      } else {
        try {
          result = Integer.parseInt(inputAsString);
        } catch (NumberFormatException numFormatException) {
          System.out.println("Error: please provide numeric arguments");
        }
      }
    } catch (java.io.IOException e) {
      e.printStackTrace();
    }
    return result;
  }
  
  private static int menuSelector(String menuMessage, String[] menuEntries) {
    System.out.println(menuMessage);
    
    for (int i = 0; i < menuEntries.length; ++i) {
      System.out.format("[%d] %s\n", (i + 1), menuEntries[i]);
    }
    
    return getIntegerFromStdin();
  }
  
  // Overloaded method with default welcomeMessage
  private static int menuSelector(String[] menuEntries) {
    return menuSelector("Please select one of the following entries by typing the \n" 
      + "corresponding number then pressing return.\n"
      + "Type \"quit\" to quit. \n"
      , menuEntries);
  }
  
  public static void primeMenu() {
    System.out.print("Please enter a positive integer: ");
    int number = getIntegerFromStdin();
    
    System.out.format("%d is", number);
    if (!isPrime(number)) {
      System.out.print("n't");
    }
    System.out.println(" prime");
    
  }
  
  public static void greatestCommonDivisorMenu() {
    int[] arguments = new int[2];
    for (int i = 0; i < 2; ++i) {
      System.out.format("Please enter a positive integer #%d: ", (i + 1));
      arguments[i] = getIntegerFromStdin();
    }
    System.out.format("The greatest common divisor of %d and %d is %d\n"
      , arguments[0], arguments[1], greatestCommonDivisor(arguments[0], arguments[1]));
  }
  
  public static void dateValidatorMenu() {
    int[] arguments = new int[3];
    String[] menuEntries = {
      "day of the month (1 - 31): "
    , "month of the year (1 - 12): "
    , "year (Gregorian calendar): "
    };
    
    for (int i = 0; i < 3; ++i) {
      System.out.format("Please enter the %s", menuEntries[i]);
      arguments[i] = getIntegerFromStdin();
    }
    
    System.out.format("%d/%d/%d appears to be a", arguments[0], arguments[1], arguments[2]);
    
    if (isValidDate(arguments[0], arguments[1], arguments[2])) {
      System.out.println(" valid date.");
    } else {
      System.out.println("n invalid date.");
    }
  }
  
  public static void menu() {
    String[] menuEntries = {
      "Is a number prime"
    , "Greatest common divisor of two positive integers"
    , "Is a date valid"
    };
    
    while (true) {
      switch (menuSelector(menuEntries)) {
        case 1:
          primeMenu();
          break;
        case 2:
          greatestCommonDivisorMenu();
          break;
        case 3:
          dateValidatorMenu();
          break;
      }
    }
  }
  
  public static void main(String[] args) {
    menu();
  }
}
