// =========================
// 1. The Implementation Interface (The "Bridge" Target)
// =========================
// This hierarchy deals with HOW the color is applied.
interface Color {
    void applyColor();
}

// =========================
// 2. Concrete Implementations
// =========================

class Red implements Color {
    @Override
    public void applyColor() {
        System.out.println("Applying Red Color");
    }
}

class Blue implements Color {
    @Override
    public void applyColor() {
        System.out.println("Applying Blue Color");
    }
}

// Bonus: Easy to add Green without touching Shapes!
class Green implements Color {
    @Override
    public void applyColor() {
        System.out.println("Applying Green Color");
    }
}

// =========================
// 3. The Abstraction (The "Bridge" Holder)
// =========================
// This hierarchy deals with WHAT the object is (Shape).
abstract class Shape {
    // COMPOSITION: This is the "Bridge" to the other hierarchy.
    protected Color color;

    public Shape(Color color) {
        this.color = color;
    }

    abstract void draw();
}

// =========================
// 4. Refined Abstractions
// =========================

class Circle extends Shape {
    public Circle(Color color) {
        super(color);
    }

    @Override
    public void draw() {
        System.out.print("Drawing Circle -> ");
        // Delegate the coloring work to the implementation object
        color.applyColor();
    }
}

class Square extends Shape {
    public Square(Color color) {
        super(color);
    }

    @Override
    public void draw() {
        System.out.print("Drawing Square -> ");
        color.applyColor();
    }
}

// =========================
// 5. Main Driver Class
// =========================

public class a_slide_code_BridgePatternTest {
    public static void main(String[] args) {
        // 1. Create Colors (Implementations)
        Color red = new Red();
        Color blue = new Blue();
        Color green = new Green();

        // 2. Create Shapes (Abstractions) bridging to Colors
        // Notice we can mix and match dynamically!
        Shape redCircle = new Circle(red);
        Shape blueSquare = new Square(blue);
        Shape greenCircle = new Circle(green);

        // 3. Draw them
        System.out.println("--- Drawing Shapes ---");
        redCircle.draw();
        blueSquare.draw();
        greenCircle.draw();
    }
}







/*
// =========================
// ❌ THE PROBLEM: Class Explosion
// =========================

class Shape {}
class Circle extends Shape {}
class Square extends Shape {}

// BAD: Hardcoding combinations into the class name
class RedCircle extends Circle {}
class BlueCircle extends Circle {}
class RedSquare extends Square {}
class BlueSquare extends Square {}

// If you add "Green" and "Triangle", you need 5 new classes immediately!


*/