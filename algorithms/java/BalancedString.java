
// Write a function that returns true if the brackets in a given string are balanced.
// The function must handle parens (), square brackets [], and curly braces {}.

import java.io.*;
import java.util.*;
import java.util.regex.Pattern;
import java.util.Deque;
import java.util.ArrayDeque;

class BalancedString {
  public static void main (String[] args) {
    System.out.println("(a[0]+b[2c[6]]) {24 + 53}  passed:" + parensMatch("(a[0]+b[2c[6]]) {24 + 53}"));
    System.out.println("f(e(d))                    passed:" + parensMatch("f(e(d))"));
    System.out.println("[()]{}([])                 passed:" + parensMatch("[()]{}([])"));
    System.out.println("((b)                       passed:" + !parensMatch("((b)"));
    System.out.println("(c]                        passed:" + !parensMatch("(c]"));
    System.out.println("{(a[])                     passed:" + !parensMatch("{(a[])"));
    System.out.println("([)]                       passed:" + !parensMatch("([)]"));
    System.out.println(")(                         passed:" + !parensMatch(")("));
    System.out.println(" (empty)                   passed:" + parensMatch(""));
  }

  public static boolean parensMatch2(String sentence){
    int parentsCounter = 0, bracketsCounter = 0, bracesCounter = 0;
    boolean corruptionFound = false;
    for (int i = 0; i < sentence.length(); i++) {
      switch (String.valueOf(sentence.charAt(i))) {
        case "(":
          parentsCounter++;
          break;
        case ")":
          parentsCounter--;
          break;
        case "[":
          bracketsCounter++;
          break;
        case "]":
          bracketsCounter--;
          break;
        case "{":
          bracesCounter++;
          break;
        case "}":
          bracesCounter--;
          break;
      }
      if (parentsCounter < 0 || bracketsCounter  < 0 || bracesCounter < 0)
        return false;
    }
    return !corruptionFound && parentsCounter == 0 && bracketsCounter  == 0 && bracesCounter == 0;
  }

  public static boolean parensMatch(String sentence){
    Deque<Character> stack = new ArrayDeque<>();
    for (int i = 0; i < sentence.length(); i++) {
      char character = sentence.charAt(i);
      switch (character) {
        case '(':
          stack.addFirst(character);
          break;
        case ')':
          if (stack.isEmpty() || stack.removeFirst() != '(') {
            return false;
          }
          break;
        case '[':
          stack.addFirst(character);
          break;
        case ']':
          if (stack.isEmpty() || stack.removeFirst() != '[') {
            return false;
          }
          break;
        case '{':
          stack.addFirst(character);
          break;
        case '}':
          if (stack.isEmpty() || stack.removeFirst() != '{') {
            return false;
          }
          break;
      }
    }
    return stack.isEmpty();
  }
}