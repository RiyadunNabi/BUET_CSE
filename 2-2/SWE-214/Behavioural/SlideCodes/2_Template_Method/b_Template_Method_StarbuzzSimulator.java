// =========================
// 1. The Abstract Base Class (The Template)
// =========================

abstract class CaffeineBeverage {
    
    // THIS is the Template Method.
    // It is 'final' because we don't want subclasses changing the recipe order.
    // The algorithm is fixed: Boil -> Brew -> Pour -> Add Condiments.
    final void prepareRecipe() {
        boilWater();
        brew();
        pourInCup();
        addCondiments();
    }

    // Abstract methods: Subclasses MUST implement these
    // purely because Coffee and Tea do these differently.
    abstract void brew();
    abstract void addCondiments();

    // Concrete methods: These are the same for everyone,
    // so we write them once here.
    void boilWater() {
        System.out.println("Boiling water");
    }

    void pourInCup() {
        System.out.println("Pouring into cup");
    }
}

// =========================
// 2. The Concrete Subclasses
// =========================

class Tea extends CaffeineBeverage {
    // Implementing the specific way Tea is brewed
    @Override
    public void brew() {
        System.out.println("Steeping the tea");
    }

    // Implementing the specific condiments for Tea
    @Override
    public void addCondiments() {
        System.out.println("Adding Lemon");
    }
}

class Coffee extends CaffeineBeverage {
    // Implementing the specific way Coffee is brewed
    @Override
    public void brew() {
        System.out.println("Dripping Coffee through filter");
    }

    // Implementing the specific condiments for Coffee
    @Override
    public void addCondiments() {
        System.out.println("Adding Sugar and Milk");
    }
}

// =========================
// 3. Main Driver Class
// =========================

public class b_Template_Method_StarbuzzSimulator {
    public static void main(String[] args) {
        System.out.println("--- Making Tea ---");
        Tea myTea = new Tea();
        // We call the Template Method, which runs the whole algorithm
        myTea.prepareRecipe();

        System.out.println("\n--- Making Coffee ---");
        Coffee myCoffee = new Coffee();
        myCoffee.prepareRecipe();
    }
}

// --- Making Tea ---
// Boiling water
// Steeping the tea
// Pouring into cup
// Adding Lemon

// --- Making Coffee ---
// Boiling water
// Dripping Coffee through filter
// Pouring into cup
// Adding Sugar and Milk