// =========================
// THE PROBLEM: Code Duplication
// =========================

class Coffee {
    void prepareRecipe() {
        boilWater();         // DUPLICATE
        brewCoffeeGrinds();  // Specific to Coffee
        pourInCup();         // DUPLICATE
        addSugarAndMilk();   // Specific to Coffee
    }

    public void boilWater() {
        System.out.println("Boiling water");
    }

    public void brewCoffeeGrinds() {
        System.out.println("Dripping Coffee through filter");
    }

    public void pourInCup() {
        System.out.println("Pouring into cup");
    }

    public void addSugarAndMilk() {
        System.out.println("Adding Sugar and Milk");
    }
}

class Tea {
    void prepareRecipe() {
        boilWater();        // COPY-PASTE!
        steepTeaBag();      // Specific to Tea
        pourInCup();        // COPY-PASTE!
        addLemon();         // Specific to Tea
    }

    public void boilWater() {
        System.out.println("Boiling water");
    }

    public void steepTeaBag() {
        System.out.println("Steeping the tea");
    }

    public void pourInCup() {
        System.out.println("Pouring into cup");
    }

    public void addLemon() {
        System.out.println("Adding Lemon");
    }
}

public class a_Bad_Code {
    
}
