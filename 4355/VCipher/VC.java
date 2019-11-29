import java.util.*;

public class VC {
   public static void main(String[] args) {
      Scanner in = new Scanner(System.in);
      String cipher = in.nextLine();
      double CipherFrequency[] = new double[26];
      int key = 4;

      RF(CipherFrequency, key, cipher);
      

   
   }
   
   public static void RF(double CipherFrequency[], int key, String cipher) {
      // initialize CipherFrequency array to 0
      initCF(CipherFrequency);
      double subBlockLen = 0;
      // sub block is 0 to 3

      int index = 0;
      while (index < cipher.length()){
         char cipherLetter = cipher.charAt(index);
         System.out.println("\n" + cipherLetter + " index: " + index);
         int pos = cipherLetter - 65;
         
         CipherFrequency[pos] = CipherFrequency[pos] + 1;
         subBlockLen++;
         index = findNextLetter(index, key, cipher);
      }

      System.out.println("subBlockLen: " + subBlockLen);
      // after counting occurence of each alphabetic letter (A-Z)
      // divide by the length of the block
      for (int i = 0; i < 26; i++) {
         CipherFrequency[i] = CipherFrequency[i] / subBlockLen;
      }
   }

   public static void initCF(double CipherFrequency[]) {
      for (int i = 0; i < 26; i++) {
         CipherFrequency[i] = 0;
      }
   }

   public static boolean isLetter(char character){
      if (character >= 65 && character <=90){
         return true;
      } else{
         return false;
      }
   }

   public static  int findNextLetter(int i, int key, String cipher){
      //Index is at the end. need to return
      if( i == cipher.length()-1){
         return cipher.length();
      }
      System.out.println("Enter Method");
      int keyLength = 1;
      
      i++;
      while (keyLength < key && i < cipher.length()){
         // QCHUAMR.
         char character = cipher.charAt(i);
         System.out.println("character: " + character);
         while (!isLetter(character) && i < cipher.length()) {
            i++;
            if(i == cipher.length()){
               break;
            }
            character = cipher.charAt(i);
         }
         keyLength++;
         i++;
         System.out.println("key " + keyLength + " char: " + character + " " + " i: " + i);
      }

      char character = cipher.charAt(i);
      while (!isLetter(character) && i < cipher.length()) {
         i++;
         character = cipher.charAt(i);
      }
      return i;
   }
}