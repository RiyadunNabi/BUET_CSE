// =========================
// BAD APPROACH 2: INTERFACE NIGHTMARE
// =========================

// 1. The Superclass (Keep common things here)
abstract class Duck {
    // All ducks swim, so this is fine here
    public void swim() {
        System.out.println("All ducks float, even decoys!");
    }
    
    // All ducks look different
    public abstract void display();
}

// 2. The Interfaces (To solve the "Rubber Ducks Flying" bug)
interface Flyable {
    void fly();
}

interface Quackable {
    void quack();
}

// 3. Concrete Ducks

class MallardDuck extends Duck implements Flyable, Quackable {
    @Override
    public void display() {
        System.out.println("I'm a real Mallard Duck");
    }

    // PAIN POINT: You have to manually implement this here.
    @Override
    public void fly() {
        System.out.println("I'm flying!!"); 
    }

    @Override
    public void quack() {
        System.out.println("Quack");
    }
}

class RedheadDuck extends Duck implements Flyable, Quackable {
    @Override
    public void display() {
        System.out.println("I'm a Redhead Duck");
    }

    // PAIN POINT: COPY-PASTE! 
    // You just wrote this exact code in MallardDuck. 
    // If you change one, you have to remember to change the other.
    @Override
    public void fly() {
        System.out.println("I'm flying!!"); 
    }

    @Override
    public void quack() {
        System.out.println("Quack");
    }
}

class RubberDuck extends Duck implements Quackable { 
    // GOOD: RubberDuck does NOT implement Flyable, so no flying bug.
    // BAD: We solved the bug, but at the cost of duplicate code above.
    
    @Override
    public void display() {
        System.out.println("I'm a Rubber Duck");
    }

    @Override
    public void quack() {
        System.out.println("Squeak");
    }
}

class DecoyDuck extends Duck { 
    // Implements nothing extra because it's wood. 
    // Just inherits swim() and implements display().
    @Override
    public void display() {
        System.out.println("I'm a wooden Decoy Duck");
    }
}

// 4. The Main Simulator
public class a_b_Interface_Nightmare_The_Copy_Paste_Hell {
    public static void main(String[] args) {
        System.out.println("--- Mallard Duck ---");
        MallardDuck mallard = new MallardDuck();
        mallard.display();
        mallard.swim();  // Inherited from Duck
        mallard.fly();   // Implemented from Flyable (Duplicate Code)
        mallard.quack(); 

        System.out.println("\n--- Redhead Duck ---");
        RedheadDuck redhead = new RedheadDuck();
        redhead.display();
        redhead.swim();  // Inherited from Duck
        redhead.fly();   // Implemented from Flyable (Duplicate Code)

        System.out.println("\n--- Rubber Duck ---");
        RubberDuck rubber = new RubberDuck();
        rubber.display();
        rubber.swim();   // Inherited from Duck
        rubber.quack();
        // rubber.fly(); // COMPILER ERROR: Fixed! Rubber ducks can't fly.
    }
}

// --- Mallard Duck ---
// I'm a real Mallard Duck
// All ducks float, even decoys!
// I'm flying!!
// Quack

// --- Redhead Duck ---
// I'm a Redhead Duck
// All ducks float, even decoys!
// I'm flying!!

// --- Rubber Duck ---
// I'm a Rubber Duck
// All ducks float, even decoys!
// Squeak