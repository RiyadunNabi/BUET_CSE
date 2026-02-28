// Online-3 on Structural Design Patterns (February 27, 2023). Problem StatementSuppose that Professor Severus Snape is one of the most skillful potions masters from Hogwarts School of Witchcraft and Wizardry. This year, he will teach Potions at the school and has planned to teach his pupils how to correctly brew 4 (four) different potions including Polyjuice Potion (transformation potion), Felix Felicis (liquid luck), Veritaserum (truth serum), and Skele-Gro (bone regrowing potion). However, each of these four potions uses as its base Maker's Solution (cough syrup), a mixture of white spirit ($1.23/10g) and castor oil ($2.47/10g). In addition to that, Polyjuice Potion requires poison ivy ($3.38/10g), Felix Felicis requires unicorn horn ($6.31/10g), Veritaserum requires dragon kidney ($5.86/10g), and Skele-Gro requires Chinese chomping cabbage ($4.13/10g) as an ingredient for the preparation. Note that 25 (twenty five) grams of each ingredient is used in a single jar of potion. Also, Professor Snape has come up with a penalty scheme to penalize students from Gryffindor house for wasting ingredients in their botched attempts to make potions. He has decided to deduct 2 (two) house points from Gryffindor for every gram of wasted ingredients.Now, Professor Snape has asked you, a Muggle software developer, to design and implement a system. This system is required to take as input the name and quantity (number of jars) of different potions from the professor. Then, the system has to output ingredients, total cost required, and total penalty points for each of the potions corresponding to professor's input. You have to implement necessary classes, following an appropriate design pattern, to capture the scenario above.


// Online-3 on Structural Design Patterns
// Date: February 27, 2023

// Problem Statement
// Suppose that Professor Severus Snape is one of the most skillful potions masters from Hogwarts School of Witchcraft and Wizardry. 
// This year, he will teach Potions at the school and has planned to teach his pupils how to correctly brew 4 (four) different potions 
// including Polyjuice Potion (transformation potion), Felix Felicis (liquid luck), Veritaserum (truth serum), and Skele-Gro (bone regrowing potion). 
// However, each of these four potions uses as its base Maker’s Solution (cough syrup), a mixture of white spirit ($1.23/10g) and castor oil ($2.47/10g). 
// In addition to that, Polyjuice Potion requires poison ivy ($3.38/10g), Felix Felicis requires unicorn horn ($6.31/10g), 
// Veritaserum requires dragon kidney ($5.86/10g), and Skele-Gro requires Chinese chomping cabbage ($4.13/10g) as an ingredient for the preparation. 
// Note that 25 (twenty five) grams of each ingredient is used in a single jar of potion. 
// Also, Professor Snape has come up with a penalty scheme to penalize students from Gryffindor house 
// for wasting ingredients in their botched attempts to make potions. 
// He has decided to deduct 2 (two) house points from Gryffindor for every gram of wasted ingredients.

// Now, Professor Snape has asked you, a Muggle software developer, to design and implement a system. 
// This system is required to take as input the name and quantity (number of jars) of different potions from the professor. 
// Then, the system has to output ingredients, total cost required, and total penalty points for each of the potions corresponding to professor's input. 
// You have to implement necessary classes, following an appropriate design pattern, to capture the scenario above.


// Component Interface
interface Potion {
    String getIngredients();
    double getCost();
    int getPenaltyPoints();
}

// Base Component - Maker's Solution
class MakersSolution implements Potion {
    private int jars;
    public MakersSolution(int jars) { this.jars = jars; }

    public String getIngredients() {
        return "White Spirit: " + (25 * jars) + "g, Castor Oil: " + (25 * jars) + "g";
    }
    public double getCost() {
        return jars * 25 * (1.23 + 2.47) / 10.0;
    }
    public int getPenaltyPoints() { return 0; }
}

// Abstract Decorator
abstract class PotionDecorator implements Potion {
    protected Potion potion;
    protected int jars;
    public PotionDecorator(Potion potion, int jars) {
        this.potion = potion;
        this.jars = jars;
    }
}

// Concrete Decorators
class PolyjuicePotion extends PotionDecorator {
    public PolyjuicePotion(Potion potion, int jars) { 
        super(potion, jars); 
    }
    public String getIngredients() {
        return potion.getIngredients() + ", Poison Ivy: " + (25 * jars) + "g";
    }
    public double getCost() { return potion.getCost() + jars * 25 * 3.38 / 10.0; }
    public int getPenaltyPoints() { return potion.getPenaltyPoints() + jars * 25 * 2; }
}

class FelixFelicis extends PotionDecorator {
    public FelixFelicis(Potion potion, int jars) { super(potion, jars); }
    public String getIngredients() {
        return potion.getIngredients() + ", Unicorn Horn: " + (25 * jars) + "g";
    }
    public double getCost() { return potion.getCost() + jars * 25 * 6.31 / 10.0; }
    public int getPenaltyPoints() { return potion.getPenaltyPoints() + jars * 25 * 2; }
}

class Veritaserum extends PotionDecorator {
    public Veritaserum(Potion potion, int jars) { super(potion, jars); }
    public String getIngredients() {
        return potion.getIngredients() + ", Dragon Kidney: " + (25 * jars) + "g";
    }
    public double getCost() { return potion.getCost() + jars * 25 * 5.86 / 10.0; }
    public int getPenaltyPoints() { return potion.getPenaltyPoints() + jars * 25 * 2; }
}

class SkeleGro extends PotionDecorator {
    public SkeleGro(Potion potion, int jars) { super(potion, jars); }
    public String getIngredients() {
        return potion.getIngredients() + ", Chinese Chomping Cabbage: " + (25 * jars) + "g";
    }
    public double getCost() { return potion.getCost() + jars * 25 * 4.13 / 10.0; }
    public int getPenaltyPoints() { return potion.getPenaltyPoints() + jars * 25 * 2; }
}

// Main
public class b_online_21batch_PotionsMain {
    public static void main(String[] args) {
        int jars = 2;

        Potion polyjuice = new PolyjuicePotion(new MakersSolution(jars), jars);
        System.out.println("=== Polyjuice Potion ===");
        System.out.println("Ingredients: " + polyjuice.getIngredients());
        System.out.printf("Total Cost: $%.2f%n", polyjuice.getCost());
        System.out.println("Penalty Points: " + polyjuice.getPenaltyPoints());

        Potion felix = new FelixFelicis(new MakersSolution(jars), jars);
        System.out.println("\n=== Felix Felicis ===");
        System.out.println("Ingredients: " + felix.getIngredients());
        System.out.printf("Total Cost: $%.2f%n", felix.getCost());
        System.out.println("Penalty Points: " + felix.getPenaltyPoints());
    }
}

