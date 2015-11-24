import java.io.*;
import java.util.*;

public class Solution {
    static char toLower(char c) {
        if(c >= 'A' && c <= 'Z') {
            return (char)((int)(c - 'A') + (int)'a');
        }
        return c;
    }

    static boolean isAnagram(String A, String B) {
        if(A.length() != B.length()) return false;
        int[] exist = new int[256];
        for(int i = 0; i < A.length(); i++) {
            exist[toLower(A.charAt(i))]++;
            exist[toLower(B.charAt(i))]--;
        }

        for(int i = 0; i < 256; i++) {
            if(exist[i] != 0) {
                return false;
            }
        }

        return true;
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String A = sc.next();
        String B = sc.next();
        boolean ret = isAnagram(A, B);
        if(ret) {
            System.out.println("Anagrams");
        } else {
            System.out.println("Not Anagrams");
        }
    }
}
