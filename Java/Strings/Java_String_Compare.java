import java.io.*;
import java.util.*;
import java.text.*;
import java.math.*;
import java.util.regex.*;

public class Solution {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String A = sc.next();
        int n = sc.nextInt();
        String minStr = A.substring(0, n);
        String maxStr = A.substring(0, n);
        for(int i = 0; i <= A.length() - n; i++) {
            String t = A.substring(i, i + n);
            if(minStr.compareTo(t) > 0) {
                minStr = t;
            }
            if(maxStr.compareTo(t) < 0) {
                maxStr = t;
            }
        }
        System.out.println(minStr);
        System.out.println(maxStr);
    }
}
