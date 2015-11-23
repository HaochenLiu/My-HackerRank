import java.io.*;
import java.util.*;
import java.text.*;
import java.math.*;
import java.util.regex.*;

public class Solution {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int t = sc.nextInt();
        for(int i = 0; i < t; i++) {
            int a = sc.nextInt();
            int b = sc.nextInt();
            int n = sc.nextInt();
            int tmp = a + b;
            System.out.print(tmp + " ");
            for(int j = 0; j < n - 1; j++) {
                tmp = 2 * tmp + b - a;
                System.out.print(tmp + " ");
            }
            System.out.println("");
        }
    }
}
