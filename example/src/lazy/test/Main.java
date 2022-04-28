package lazy.test;

import java.io.BufferedReader;
import java.io.InputStreamReader;

import lazy.math.MathLib;

public class Main {

    private static final String GREEN = "\u001b[32m";
    private static final String RED = "\u001b[31m";
    private static final String CYAN = "\u001b[36m";
    private static final String RESET = "\u001b[0m";

    public static void main(String[] args) {
        System.out.println(CYAN + "> Test class loader:" + RESET);
        Hmm.print();
        System.out.println(CYAN + "> Test calling external lib code 'Kinda':" + RESET);
        System.out.println(MathLib.sum(34, 35));
        System.out.println(CYAN + "> Test if files are present within the jar:" + RESET);
        assertExistence("/assets/java.png");
        assertExistence("/meta/a.txt");
        assertExistence("/LICENSE.txt");
        assertExistence("/other/how.md");
        assertExistence("/other/info/other.md");
        assertExistence("/include/also/add.this");
        assertExistence("/include/add.this");
        assertExistence("/assets/res/layout.xml");
        System.out.println(CYAN + "> Test if files aren't present within the jar:" + RESET);
        assertNonExistence("/assets/dont.md");
        assertNonExistence("/assets/other/secrets.txt");
        assertNonExistence("/assets/other/dont2.js");
        assertNonExistence("/meta/a.txt.copy");
        assertNonExistence("/meta/copy/b.txt.copy");
        assertNonExistence("/meta/copy/b.txt");
        System.out.println(CYAN + "Done!" + RESET);
    }

    private static boolean hasFileWithinJar(String path) {
        try (var in = Main.class.getResourceAsStream(path);
                BufferedReader reader = new BufferedReader(new InputStreamReader(in))) {
            return true;
        } catch (Exception e) {
            return false;
        }
    }

    private static void assertExistence(String path) {
        if (hasFileWithinJar(path))
            System.out.println(GREEN + "File was found! " + path + RESET);
        else
            System.out.println(RED + "WARN! Files wasn't found! " + path + RESET);
    }

    private static void assertNonExistence(String path) {
        if (!hasFileWithinJar(path))
            System.out.println(GREEN + "File wasn't found! " + path + RESET);
        else
            System.out.println(RED + "WARN! Files was found! " + path + RESET);
    }
}