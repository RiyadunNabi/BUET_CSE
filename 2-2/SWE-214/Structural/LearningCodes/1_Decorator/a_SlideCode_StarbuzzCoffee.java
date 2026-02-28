// =========================
// 1. The Component (Abstract Base Class)
// =========================

abstract class Beverage {
    String description = "Unknown Beverage";

    public String getDescription() {
        return description;
    }

    public abstract double cost();
}

// =========================
// 2. Concrete Components (The Base Drinks)
// =========================

class Espresso extends Beverage {
    public Espresso() {
        description = "Espresso";
        // super.
    }

    @Override
    public double cost() {
        return 1.99;
    }
}

class HouseBlend extends Beverage {
    public HouseBlend() {
        description = "House Blend Coffee";
    }

    @Override
    public double cost() {
        return 0.89;
    }
}

class DarkRoast extends Beverage {
    public DarkRoast() {
        description = "Dark Roast Coffee";
    }

    @Override
    public double cost() {
        return 0.99;
    }
}

// =========================
// 3. The Decorator (The Wrapper)
// =========================

abstract class CondimentDecorator extends Beverage {
    // We force all decorators to reimplement getDescription
    // because they need to append their name to it.
    @Override
    public abstract String getDescription();
    @Override
    public abstract double cost();
}

// =========================
// 4. Concrete Decorators (The Condiments)
// =========================

class Mocha extends CondimentDecorator {
    // COMPOSITION: The decorator HOLDS the beverage it is wrapping
    Beverage beverage;

    public Mocha(Beverage beverage) {
        this.beverage = beverage;
    }

    @Override
    public String getDescription() {
        // Delegate to the wrapped object, then add self
        return beverage.getDescription() + ", Mocha";
    }

    @Override
    public double cost() {
        // Delegate cost calculation, then add self
        return .20 + beverage.cost();
    }
}

class Whip extends CondimentDecorator {
    Beverage beverage;

    public Whip(Beverage beverage) {
        this.beverage = beverage;
    }

    @Override
    public String getDescription() {
        return beverage.getDescription() + ", Whip";
    }

    @Override
    public double cost() {
        return .10 + beverage.cost();
    }
}

class Soy extends CondimentDecorator {
    Beverage beverage;

    public Soy(Beverage beverage) {
        this.beverage = beverage;
    }

    @Override
    public String getDescription() {
        return beverage.getDescription() + ", Soy";
    }

    @Override
    public double cost() {
        return .15 + beverage.cost();
    }
}

// =========================
// 5. Main Driver Class
// =========================

public class a_SlideCode_StarbuzzCoffee {
    public static void main(String[] args) {
        // Order 1: Plain Espresso
        System.out.println("--- Order 1 ---");
        Beverage beverage = new Espresso();
        System.out.println(beverage.getDescription() + " $" + beverage.cost());

        // Order 2: Dark Roast with Double Mocha and Whip
        System.out.println("\n--- Order 2 ---");
        Beverage beverage2 = new DarkRoast(); // Start with base
        beverage2 = new Mocha(beverage2);     // Wrap in Mocha
        beverage2 = new Mocha(beverage2);     // Wrap in Mocha AGAIN (Double Mocha!)
        beverage2 = new Whip(beverage2);      // Wrap in Whip
        
        // The object is now: Whip(Mocha(Mocha(DarkRoast)))
        System.out.println(beverage2.getDescription() + " $" + beverage2.cost());

        // Order 3: House Blend with Soy and Mocha
        System.out.println("\n--- Order 3 ---");
        Beverage beverage3 = new HouseBlend();
        beverage3 = new Soy(beverage3);
        beverage3 = new Mocha(beverage3);
        
        System.out.println(beverage3.getDescription() + " $" + beverage3.cost());
    }
}






/*
// =========================
// ❌ THE PROBLEM: Superclass Bloat
// =========================

class BeverageBad {
    public String description;
    // PAIN POINT: Hardcoding condiments as booleans
    public boolean milk;
    public boolean soy;
    public boolean mocha;
    public boolean whip;

    public float cost() {
        float condimentCost = 0.0f;
        if (milk) condimentCost += 0.10f;
        if (soy) condimentCost += 0.15f;
        if (mocha) condimentCost += 0.20f;
        if (whip) condimentCost += 0.10f;
        return condimentCost;
    }
    
    // Getters and setters for every single condiment...
    // What if we add "Caramel"? We have to Open this class and Modify it (Violates Open/Closed Principle)
}

class DarkRoastBad extends BeverageBad {
    @Override
    public float cost() {
        return 1.99f + super.cost(); // Logic is scattered
    }
}

*/