// ZBazar Custom Packages (Composite Pattern)
// CSE-214 Online - 2 (A2)
// Structural Design Pattern
// Duration: 25 minutes

// ZBazar is a subscription-based grocery delivery service 
// that lets customers set up a recurring monthly bazar bundle 
// that is automatically delivered to their homes. 
// The platform offers preset packages (such as Small, Family, and Mega) 
// and single grocery items (individual items like rice, oil, pulse, etc.).
// Preset packages consist of multiple single items. 
// Each item has its specific name, price, and weight. 
// Users can create or modify their own Custom Bazar by combining 
// one or more preset packages and/or single items. 
// A custom package may include only individual items, 
// only preset packages, or a mixture of both. 
// Users can also include their previously created custom packages. 
// The system must support calculating the total price and weight 
// of any configuration and displaying the complete structure 
// of the custom package.

// Task: Choose the appropriate design pattern to solve this problem 
// and implement a minimal demonstration.


import java.util.ArrayList;
import java.util.List;

// Component
interface GroceryComponent {
    String getName();
    double getPrice();
    double getWeight();
    void display(String indent);
}

// Leaf - Single Item
class GroceryItem implements GroceryComponent {
    private String name;
    private double price, weight;

    public GroceryItem(String name, double price, double weight) {
        this.name = name; this.price = price; this.weight = weight;
    }
    public String getName() { return name; }
    public double getPrice() { return price; }
    public double getWeight() { return weight; }
    public void display(String indent) {
        System.out.println(indent + "- " + name + " | Price: $" + price + " | Weight: " + weight + "kg");
    }
}

// Composite - Package
class GroceryPackage implements GroceryComponent {
    private String name;
    private List<GroceryComponent> items = new ArrayList<>();

    public GroceryPackage(String name) { this.name = name; }

    public void add(GroceryComponent c) { items.add(c); }
    public void remove(GroceryComponent c) { items.remove(c); }

    public String getName() { return name; }
    public double getPrice() {
        return items.stream().mapToDouble(GroceryComponent::getPrice).sum();
        // double total = 0;
        // for (GroceryComponent c : items) {
        //     total += c.getPrice();
        // }
        // return total;
    }
    public double getWeight() {
        return items.stream().mapToDouble(GroceryComponent::getWeight).sum();
    }
    public void display(String indent) {
        System.out.println(indent + "[" + name + "] Total Price: $" + getPrice()
                         + " | Total Weight: " + getWeight() + "kg");
        for (GroceryComponent c : items) c.display(indent + "  ");
    }
}

// Main
public class b_online_A2_ZBazarGroceryMain {
    public static void main(String[] args) {
        // Single items
        GroceryItem rice = new GroceryItem("Rice", 2.5, 1.0);
        GroceryItem oil  = new GroceryItem("Oil",  3.0, 0.9);
        GroceryItem pulse = new GroceryItem("Pulse", 1.5, 0.5);

        // Preset Small Package
        GroceryPackage small = new GroceryPackage("Small Package");
        small.add(rice);
        small.add(oil);

        // Preset Family Package
        GroceryPackage family = new GroceryPackage("Family Package");
        family.add(rice);
        family.add(oil);
        family.add(pulse);

        // Custom Package (mix of preset + single items)
        GroceryPackage custom = new GroceryPackage("Custom Bazar");
        custom.add(small);  // adding preset package
        custom.add(new GroceryItem("Sugar", 1.2, 0.5));

        System.out.println("=== Small Package ===");
        small.display("");

        System.out.println("\n=== Family Package ===");
        family.display("");

        System.out.println("\n=== Custom Package ===");
        custom.display("");
        System.out.printf("%nCustom Total Price: $%.2f | Total Weight: %.2fkg%n",
                custom.getPrice(), custom.getWeight());
    }
}