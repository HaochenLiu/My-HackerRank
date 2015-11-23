import java.io.*;
import java.util.*;

public class Solution {
    public static String toUpper(String s) {
        if(s.isEmpty()) return s;
        char[] charArray = new char[s.length()];
        for(int i = 0; i < s.length(); i++) {
            charArray[i] = s.charAt(i);
        }
        if(charArray[0] >= 'a' && charArray[0] <= 'z') {
            charArray[0] = (char)((int)charArray[0] + 'A' - 'a');
        }
        String res = new String(charArray);
        return res;
    }

    public static void main(String[] args) {        
        Scanner sc = new Scanner(System.in);
        String A = sc.next();
        String B = sc.next();
        System.out.println(A.length() + B.length());
        if(A.compareTo(B) > 0) {
            System.out.println("Yes");
        } else {
            System.out.println("No");
        }
        System.out.println(toUpper(A) + " " + toUpper(B));
    }
}
