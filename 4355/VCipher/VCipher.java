import java.util.*;
import java.io.File;
import java.io.FileWriter;
import java.io.FileNotFoundException;

public class VCipher {

   /*
    * Key length = 4 is given
      Cipher: OOFWGTXYE - FKVY MHIULX WTOGLE TH AMBELFS MV XAIAAPL, KQSDAAPL, ZQROLD AGK YUVO YOKL - FONJT NXHDLR LHEKF MSILOT HM PABSK LBMQ IG AADT- F’E MHKQRG DAREK. FEVOZOEVSY BZ BOPLDEW UAT CBET UF EIEPOOG JTIIZ MN- W LXEVADIVPFY, UBF BR ATE VYQAMPHIMF MNW PZGXUGIMF AF VVYPNAQR LJUE- GAUSMZ IHH ADAGZXAML EOVPQTR’Z ZEXKE AGK IAGAE IGAA PKVPUVAE TAHF CTU UMIYAVX IATA ZACBLFY TUP TAL QCHUAMR.
    */
   public static void main(String args[]) {

      try {
         Scanner in = new Scanner(new File(args[0]));
         
         //grabs entire file
         String cipher = in.nextLine();

         // Relative Frequency array holds the relative frequency values of each letter of the alphabet
         // CipherFrequency is used to find out the relative frequency of a cipher text sub block
         //CK is used to keep track of 
         //buffer is where the plain text will go
         //key period is the length of the key used
         double RelativeFrequency[] = initRF();
         double CipherFrequency[] = new double[26];
         double CK[] = new double[26];
         char buffer[] = new char[1000];
         int keyPeriod = 4;

         

         // C(k) = from i=0 to 25 -> CipherFrequency[i] * PF[(i-k + 26)mod26] , k = 0,1,...25
         // a subBlock is a block of letters that have been shifted by the cipher
         for (int subBlock = 0; subBlock < keyPeriod; subBlock++) {
            int cipherKeyIndex = 0;

            CipherLetterFreq(CipherFrequency, subBlock, keyPeriod, cipher);
            System.out.println("Freq");
            
            for(double num : CipherFrequency){
               System.out.println(num);
               
            }

            int ckIndex = 0;
            for (int k = 0; k < 26; k++) {
               double total = 0;
               for (int i = 0; i < 26; i++) {
                  total += CipherFrequency[i] * RelativeFrequency[(i - k + 26) % 26];
               }
               CK[ckIndex] = total;
               ckIndex++;
            } // k shift from 0-25
              // find largest shift and then shift each letter by that amount in the sub block
            shiftBlock(CK, subBlock, keyPeriod, cipher, buffer);
         }

         // All letters have been shifted and stored in buffer[]. Print the message
         System.out.println("Decrypted Message:\n");
         for (int i = 0; i < 1000; i++) {
            System.out.print(buffer[i]);
         }
         
         in.close();
         
      } catch (FileNotFoundException e) {
         System.out.println("Enter a file name. ex: cipher.txt");
         e.printStackTrace();
      }
      
   }// endmain


   //relative frequencies of all letters
   public static double[] initRF() {
      double RF[] = new double[] { 0.082, 0.015, 0.028, 0.043, 0.127, 0.022, 0.02, 0.061, 0.07, 0.002, 0.008, 0.04, 0.024, 0.067, 0.075, 0.019, 0.001, 0.06, 0.063, 0.091, 0.028, 0.01, 0.024, 0.002, 0.02, 0.001 };
      return RF;
   }

   /*
      findLetterFreq: Finds the amount of times a letter occurs in a
      particular sub block and divides the number of times that letter occurred by the length of the sub block to get a frequency percentage
    */
   public static void CipherLetterFreq(double CipherFrequency[], int subBlock, int keyPeriod, String cipher) {
      // initialize CipherFrequency array to 0
      initCF(CipherFrequency);
      double subBlockLen = 0;
      
      // sub block is 0 to 3 since key length is 4
      int index = subBlock;
      while (index < cipher.length()) {
         char cipherLetter = cipher.charAt(index);
         int pos = cipherLetter - 65;

         CipherFrequency[pos] = CipherFrequency[pos] + 1;
         subBlockLen++;
         index = findNextLetter(index, keyPeriod, cipher);
      }

      System.out.println("subBlockLen: " + subBlockLen);
      // after counting occurence of each alphabetic letter (A-Z)
      // divide by the length of the block
      for (int i = 0; i < 26; i++) {
         CipherFrequency[i] = CipherFrequency[i] / subBlockLen;
      }
   }

   /*
      initCF: makes sure that all values in the array are initialized to 0 for use
      in each subBlock
    */
   public static void initCF(double CipherFrequency[]) {
      for (int i = 0; i < 26; i++) {
         CipherFrequency[i] = 0;
      }
   }

   /*
      shiftBlock: First finds the largest C(k) value that was previously calculated
      and stored then shifts all the letters in the subBlock by that amount
    */
   public static void shiftBlock(double CK[], int subBlock, int kp, String cipher, char buffer[]) {
      double largest = CK[0];
      // k is shift
      int k = 0;
      for (int i = 1; i < CK.length; i++) {
         if (CK[i] > largest) {
            largest = CK[i];
            k = i;
         }
      }

      for (int i = subBlock; i < cipher.length(); i = i + kp) {
         char eLetter = cipher.charAt(i);
         int dLetter = eLetter - 65;
         dLetter = ((dLetter - k) + 26) % 26;
         dLetter += 65;
         eLetter = (char) dLetter;
         buffer[i] = eLetter;
      }
   }

   public static int findNextLetter(int i, int key, String cipher) {
      // Index is at the end. need to return
      if (i == cipher.length() - 1) {
         return cipher.length();
      }
      int keyLength = 0;
      char character;

      while (keyLength < key) {
         i++;
         character = cipher.charAt(i);

         while (!isLetter(character)) {
            i++;
            // 380 = R 381 = . END = 382
            if (i == cipher.length()) {
               return cipher.length();
            }
            character = cipher.charAt(i);
         }
         keyLength++;
      }
      return i;
   }

      public static boolean isLetter(char character){
      if (character >= 65 && character <=90){
         return true;
      } else{
         return false;
      }
   }

}// end class


