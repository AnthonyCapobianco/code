import java.util.*;

class Oop26October2018 {
  public static void main(String[] args) {
    // xy# not valid cause of the pound char at the end. 
    // new is a reserved keyword 
    // test-env Pas de tiret
    // *result start with *
    // 1stTime starts with 1
 
    // 8 bit -> 255 (de 0 à 255)
    //
    //int a, b, c; a = b = c = 455; 
    
    char singleQuote = '\'';
    char doubleQuote = '\"';
    char backslash = '\\';
    char weirdLetterOUsingUnicodeShit = '\u0153';
    
    // sizeof ISN'T A RESERVED KEYWORD    
    // short hello num???? What the fuck is that even? 

    // 1. println(++var1); -> 8
    // 2. var1++; -> 7  
    // 3. --var1; -> 6
    // 4. var1--; -> 7
    
    // == != only for char, int bool… Only primitives.
    // Cours OOP 1er jour --> == 
    // DON'T USE == AND != FOR FUCKING CLASSES !!! 
    
    String a = "Hi";
    String b = "Hi"; 
    String c = new String("Hi");
    
    // int myAge = 33; 
    // String myName = "Homer"; 
    // sout(myAge + myAge + "Salut"); 
    // 66Salut
    
    // System.out.print("My name is" + myName + "."); FIVE STRINGS 
    // "My name is" is a String 
    // "My name is" + myName is also a String… 
    // Basically use c++ where an std::string is (always) (UB) ONE fucking string cause come on; 
    // Might be UB tho tbh. (i kid) 
    
    /*
     * For some reason you can only define a String at declaration ? Or can you… 
     * Well let's not fuck around with this till I'm sure. 
     */
     
  }
}