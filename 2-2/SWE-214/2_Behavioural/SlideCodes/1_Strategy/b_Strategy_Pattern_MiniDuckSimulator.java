// =========================
// 1. The Strategy Interfaces
// =========================

// The interface that all flying behavior classes implement
interface FlyBehavior {
    void fly();
}

// The interface that all quacking behavior classes implement
interface QuackBehavior {
    void quack();
}

// =========================
// 2. Concrete Strategies (The Algorithms)
// =========================

// Implementation for ducks that DO fly
class FlyWithWings implements FlyBehavior {
    @Override
    public void fly() {
        System.out.println("I'm flying!!");
    }
}

// Implementation for ducks that can't fly (like Rubber or Decoy ducks)
class FlyNoWay implements FlyBehavior {
    @Override
    public void fly() {
        System.out.println("I can't fly.");
    }
}

// Rocket powered flying (to demonstrate dynamic behavior change)
class FlyRocketPowered implements FlyBehavior {
    @Override
    public void fly() {
        System.out.println("I'm flying with a rocket!");
    }
}

// Normal quack
class Quack implements QuackBehavior {
    @Override
    public void quack() {
        System.out.println("Quack");
    }
}

// Squeak for rubber ducks
class Squeak implements QuackBehavior {
    @Override
    public void quack() {
        System.out.println("Squeak");
    }
}

// Mute for decoy ducks
class MuteQuack implements QuackBehavior {
    @Override
    public void quack() {
        System.out.println("<< Silence >>");
    }
}

// =========================
// 3. The Context (The Duck Superclass)
// =========================

abstract class Duck {
    // COMPOSITION: Duck HAS-A FlyBehavior and QuackBehavior
    FlyBehavior flyBehavior;
    QuackBehavior quackBehavior;

    public Duck() {
    }

    public abstract void display();

    // Delegate the behavior to the interface
    public void performFly() {
        flyBehavior.fly();
    }

    public void performQuack() {
        quackBehavior.quack();
    }

    public void swim() {
        System.out.println("All ducks float, even decoys!");
    }

    // DYNAMIC BEHAVIOR: Setter methods to change strategy at runtime
    public void setFlyBehavior(FlyBehavior fb) {
        flyBehavior = fb;
    }

    public void setQuackBehavior(QuackBehavior qb) {
        quackBehavior = qb;
    }
}

// =========================
// 4. Concrete Clients (Specific Ducks)
// =========================

class MallardDuck extends Duck {
    public MallardDuck() {
        // Mallard uses specific strategies by default
        quackBehavior = new Quack();
        flyBehavior = new FlyWithWings();
    }

    @Override
    public void display() {
        System.out.println("I'm a real Mallard Duck");
    }
}

class RubberDuck extends Duck {
    public RubberDuck() {
        // Rubber ducks squeak and can't fly
        quackBehavior = new Squeak();
        flyBehavior = new FlyNoWay();
    }

    @Override
    public void display() {
        System.out.println("I'm a Rubber Duck");
    }
}

class ModelDuck extends Duck {
    public ModelDuck() {
        flyBehavior = new FlyNoWay(); // Starts off unable to fly
        quackBehavior = new Quack();
    }

    @Override
    public void display() {
        System.out.println("I'm a Model Duck");
    }
}

// =========================
// 5. Main Driver Class
// =========================

public class b_Strategy_Pattern_MiniDuckSimulator {
    public static void main(String[] args) {
        // --- Test 1: Mallard Duck ---
        System.out.println("--- Testing Mallard Duck ---");
        Duck mallard = new MallardDuck();
        mallard.display();
        mallard.performQuack(); // Delegates to Quack class
        mallard.performFly();   // Delegates to FlyWithWings class

        // --- Test 2: Rubber Duck ---
        System.out.println("\n--- Testing Rubber Duck ---");
        Duck rubber = new RubberDuck();
        rubber.display();
        rubber.performQuack(); // Delegates to Squeak class
        rubber.performFly();   // Delegates to FlyNoWay class

        // --- Test 3: Dynamic Behavior Change (Model Duck) ---
        System.out.println("\n--- Testing Model Duck (Dynamic Behavior) ---");
        Duck model = new ModelDuck();
        model.display();
        model.performFly(); // Initially: I can't fly.

        System.out.println("-> Attaching Rocket...");
        // Dynamically changing behavior at runtime!
        model.setFlyBehavior(new FlyRocketPowered());
        
        model.performFly(); // Now: I'm flying with a rocket!
    }
}


// --- Testing Mallard Duck ---
// I'm a real Mallard Duck
// Quack
// I'm flying!!

// --- Testing Rubber Duck ---
// I'm a Rubber Duck
// Squeak
// I can't fly.

// --- Testing Model Duck (Dynamic Behavior) ---
// I'm a Model Duck
// I can't fly.
// -> Attaching Rocket...
// I'm flying with a rocket!