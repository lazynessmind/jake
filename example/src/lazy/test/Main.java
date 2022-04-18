package lazy.test;

import java.io.BufferedReader;
import java.io.InputStreamReader;

import lazy.math.MathLib;

public class Main {

    public static void main(String[] args){
        System.out.println("> Test class loader:");
        Hmm.print();
        System.out.println("> Test calling external lib code 'Kinda':");
        System.out.println(MathLib.sum(34, 35));
        System.out.println("> Test if files are present within the jar:");
        assertExistence("/assets/java.png");
        assertExistence("/assets/other/secrets.txt");
        assertExistence("/LICENSE.txt");
        System.out.println("> Test if files aren't present within the jar:");
        assertNonExistence("/assets/dont.md");
        assertNonExistence("/assets/other/dont2.js");
        System.out.println("Done!");
    }

    private static boolean hasFileWithinJar(String path) {
        try(var in = Main.class.getResourceAsStream(path); BufferedReader reader = new BufferedReader(new InputStreamReader(in))) {
            return true;
        } catch (Exception e) {
            return false;
        }
    }

    private static void assertExistence(String path) {
        if(hasFileWithinJar(path)) System.out.println("File was found! " + path);
        else System.out.println("WARN! Files wasn't found! " + path);
    }

    private static void assertNonExistence(String path) {
        if(!hasFileWithinJar(path)) System.out.println("File wasn't found! " + path);
        else System.out.println("WARN! Files was found! " + path);
    }
}