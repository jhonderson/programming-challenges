import java.util.Scanner;
import javax.script.ScriptEngineManager;
import javax.script.ScriptEngine;

public class Main {
    public static void main(String[] args) throws Exception {
        ScriptEngineManager mgr = new ScriptEngineManager();
        ScriptEngine engine = mgr.getEngineByName("JavaScript");
        Scanner sc = new Scanner(System.in);
        while (sc.hasNextLine())
            System.out.println(engine.eval(sc.nextLine()));
    }
}
