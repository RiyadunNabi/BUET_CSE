// =========================
// 1. The Target Interface (Duck)
// =========================
// This is what our system expects to see.
interface Duck {
    void quack();
    void fly();
}

// =========================
// 2. The Adaptee Interface (Turkey)
// =========================
// This is the new class we want to use, but it doesn't fit.
interface Turkey {
    void gobble();
    void fly(); 
}

// Concrete Adaptee
class WildTurkey implements Turkey {
    @Override
    public void gobble() {
        System.out.println("Gobble gobble");
    }

    @Override
    public void fly() {
        System.out.println("I'm flying a short distance");
    }
}

// =========================
// 3. The Adapter (TurkeyAdapter)
// =========================
// Implements the Target (Duck) so it looks like a Duck.
// Holds a reference to the Adaptee (Turkey) to do the actual work.

class TurkeyAdapter implements Duck {
    Turkey turkey;

    public TurkeyAdapter(Turkey turkey) {
        this.turkey = turkey;
    }

    @Override
    public void quack() {
        // Translate quack() to gobble()
        turkey.gobble();
    }

    @Override
    public void fly() {
        // Translate long flight to multiple short flights
        // Turkeys can't fly far, so we make it flap 5 times to match a Duck.
        for(int i=0; i < 5; i++) {
            turkey.fly();
        }
    }
}

// =========================
// 4. Main Driver Class (The Client)
// =========================

public class a_slide_code_DuckTestDrive {
    public static void main(String[] args) {
        // 1. Create a Turkey (The incompatible object)
        WildTurkey turkey = new WildTurkey();

        // 2. Wrap the Turkey in a Duck Adapter
        // Now it looks and acts like a Duck!
        Duck turkeyAdapter = new TurkeyAdapter(turkey);

        System.out.println("The Turkey says...");
        turkey.gobble();
        turkey.fly();

        System.out.println("\nThe Duck Adapter says...");
        testDuck(turkeyAdapter); // It passes the test!
    }

    // This method ONLY accepts Ducks. It doesn't know about Turkeys.
    static void testDuck(Duck duck) {
        duck.quack();
        duck.fly();
    }
}










/*

// =========================
// ❌ THE PROBLEM: Incompatible Interfaces
// =========================

interface Duck {
    void quack();
    void fly();
}

interface Turkey {
    void gobble();
    void flyShortDistance(); // Method names don't match Duck!
}

class WildTurkey implements Turkey {
    public void gobble() { System.out.println("Gobble gobble"); }
    public void flyShortDistance() { System.out.println("I'm flying a short distance"); }
}

class DuckSimulator {
    public void testDuck(Duck duck) {
        duck.quack();
        duck.fly();
    }

    public static void main(String[] args) {
        WildTurkey turkey = new WildTurkey();
        // duckSimulator.testDuck(turkey); // COMPILER ERROR! Turkey is NOT a Duck.
    }
}

*/