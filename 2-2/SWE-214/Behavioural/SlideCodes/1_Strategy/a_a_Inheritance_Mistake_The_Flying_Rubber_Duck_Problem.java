// =========================
// BAD APPROACH 1: Inheritance
// =========================

abstract class Duck {
    public void quack() {
        System.out.println("Quack");
    }
    
    public void swim() {
        System.out.println("Swimming...");
    }
    
    // THE PROBLEM: You added this here, thinking it was a good idea.
    // Now ALL ducks inherit this.
    public void fly() {
        System.out.println("I am flying!!"); 
    }
    
    public abstract void display();
}

class MallardDuck extends Duck {
    @Override
    public void display() {
        System.out.println("I look like a mallard.");
    }
}

class RubberDuck extends Duck {
    @Override
    public void display() {
        System.out.println("I look like a rubber duck.");
    }
    // RubberDuck inherits fly()... wait, rubber ducks don't fly!
    // Now you have to Override it to do nothing? 
    // What about a Wooden Decoy duck? You have to override it again?
}

public class a_a_Inheritance_Mistake_The_Flying_Rubber_Duck_Problem {
    public static void main(String[] args) {
        Duck rubber = new RubberDuck();
        rubber.display();
        
        // BUG: The rubber duck flies around the room!
        rubber.fly(); 
    }
}

// I look like a rubber duck.
// I am flying!!