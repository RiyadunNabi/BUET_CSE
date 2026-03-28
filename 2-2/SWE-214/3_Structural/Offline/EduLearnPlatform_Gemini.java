// package Offline;
import java.util.ArrayList;
import java.util.List;

// -----------------------------------------------------------
// 1. The Component Interface (Unified Interface)
// -----------------------------------------------------------
/**
 * Defines the common interface for all learning items (Lessons, Courses, Modules)
 * and their decorators. Addresses Requirement 1[cite: 26].
 */
interface LearningItem {
    double getPrice();
    double getDuration(); // In minutes
    void display(String indent); // For Transparency [cite: 30]
}

// -----------------------------------------------------------
// 2. Leaf Class (The smallest unit)
// -----------------------------------------------------------
class Lesson implements LearningItem {
    private String title;
    private double price;
    private double duration; // in minutes

    public Lesson(String title, double price, double duration) {
        this.title = title;
        this.price = price;
        this.duration = duration;
    }

    @Override
    public double getPrice() {
        return price;
    }

    @Override
    public double getDuration() {
        return duration; // [cite: 7]
    }

    @Override
    public void display(String indent) {
        System.out.println(indent + "- Lesson: " + title + " ($" + price + ", " + duration + " mins)");
    }
}

// -----------------------------------------------------------
// 3. Composite Classes (Groupings)
// -----------------------------------------------------------

// Base Composite to reduce code duplication
abstract class CompositeItem implements LearningItem {
    protected String title;
    protected List<LearningItem> children = new ArrayList<>();

    public CompositeItem(String title) {
        this.title = title;
    }

    public void add(LearningItem item) {
        children.add(item);
    }

    public List<LearningItem> getChildren() {
        return children;
    }

    @Override
    public double getPrice() {
        // Price is sum of children [cite: 14]
        return children.stream().mapToDouble(LearningItem::getPrice).sum();
    }

    @Override
    public double getDuration() {
        // Duration is sum of children [cite: 8, 13]
        return children.stream().mapToDouble(LearningItem::getDuration).sum();
    }
}

// Course: Contains Lessons
class Course extends CompositeItem {
    public Course(String title) {
        super(title);
    }

    @Override
    public void display(String indent) {
        System.out.println(indent + "+ Course: " + title + " (Total: $" + getPrice() + ", " + getDuration() + " mins)");
        for (LearningItem item : children) {
            item.display(indent + "  ");
        }
    }
}

// Module: Contains Courses
class Module extends CompositeItem {
    public Module(String title) {
        super(title);
    }

    @Override
    public void display(String indent) {
        System.out.println(indent + "## MODULE: " + title + " (Total: $" + getPrice() + ", " + getDuration() + " mins)");
        for (LearningItem item : children) {
            item.display(indent + "  ");
        }
    }
}

// -----------------------------------------------------------
// 4. Decorators (Add-ons and Discounts)
// -----------------------------------------------------------

// Abstract Decorator
abstract class LearningItemDecorator implements LearningItem {
    protected LearningItem wrappedItem;

    public LearningItemDecorator(LearningItem item) {
        this.wrappedItem = item;
    }

    @Override
    public double getDuration() {
        return wrappedItem.getDuration();
    }

    @Override
    public void display(String indent) {
        wrappedItem.display(indent);
    }
}

// --- ADD-ONS [cite: 15] ---

class PracticeQuestionDecorator extends LearningItemDecorator {
    public PracticeQuestionDecorator(LearningItem item) {
        super(item);
    }

    @Override
    public double getPrice() {
        return wrappedItem.getPrice() + 10.0; // [cite: 16]
    }

    @Override
    public void display(String indent) {
        super.display(indent);
        System.out.println(indent + "  + Add-on: Practice Question Set ($10)");
    }
}

class LiveMentorDecorator extends LearningItemDecorator {
    public LiveMentorDecorator(LearningItem item) {
        super(item);
    }

    @Override
    public double getPrice() {
        return wrappedItem.getPrice() + 20.0; // [cite: 17]
    }

    @Override
    public void display(String indent) {
        super.display(indent);
        System.out.println(indent + "  + Add-on: Live Mentor Support ($20)");
    }
}

// --- DISCOUNTS [cite: 18] ---

class StudentDiscountDecorator extends LearningItemDecorator {
    public StudentDiscountDecorator(LearningItem item) {
        super(item);
    }

    @Override
    public double getPrice() {
        return wrappedItem.getPrice() - 10.0; // [cite: 21]
    }

    @Override
    public void display(String indent) {
        super.display(indent);
        System.out.println(indent + "  * Discount: Developing Country Student (-$10)");
    }
}

class SpecialDurationDiscountDecorator extends LearningItemDecorator {
    public SpecialDurationDiscountDecorator(LearningItem item) {
        super(item);
    }

    @Override
    public double getPrice() {
        // 5 hours = 300 minutes
        if (wrappedItem.getDuration() >= 300) {
            System.out.println("  (Qualifies for Special Duration Discount: > 5 hours)");
            return wrappedItem.getPrice() - 12.0; // [cite: 20]
        }
        return wrappedItem.getPrice();
    }

    @Override
    public void display(String indent) {
        super.display(indent);
        // Display logic handled in getPrice purely for console clarity in this example,
        // or we could print here if the condition matches.
    }
}

class MultiModuleDiscountDecorator extends LearningItemDecorator {
    public MultiModuleDiscountDecorator(LearningItem item) {
        super(item);
    }

    @Override
    public double getPrice() {
        // Logic: Check if the wrapped item is a Composite that contains 2 or more Modules
        long moduleCount = 0;
        
        // We peek inside to see if we qualify for the discount
        if (wrappedItem instanceof CompositeItem) {
            moduleCount = ((CompositeItem) wrappedItem).getChildren().stream()
                .filter(child -> findModuleRecursively(child))
                .count();
        }

        // Note: In a stricter interpretation, this might wrap a "Cart" object.
        // For this assignment, assuming we wrap a "Bundle" of courses/modules.
        // If the structure is strictly Module -> Course, this applies to a Cart/Root.
        // Simpler check: If this is a wrapper around a LIST of items, check count.
        // For demonstration, we assume wrappedItem is a root bundle.
        
        if (moduleCount >= 2) {
             return wrappedItem.getPrice() - 15.0; // [cite: 19]
        }
        return wrappedItem.getPrice();
    }
    
    // Helper to identify modules inside decorators/composites
    private boolean findModuleRecursively(LearningItem item) {
        if (item instanceof Module) return true;
        if (item instanceof LearningItemDecorator) {
            // Unwrap to check if the underlying item is a module
            // This is a simplified check for the sake of the example
            return findModuleRecursively(((LearningItemDecorator) item).wrappedItem);
        }
        return false;
    }

    @Override
    public void display(String indent) {
        super.display(indent);
        // Indication of discount is usually done at total calculation
    }
}

// -----------------------------------------------------------
// 5. Main Driver Class (Demonstration)
// -----------------------------------------------------------
public class EduLearnPlatform_Gemini {
    public static void main(String[] args) {
        System.out.println("--- EduLearn Platform Checkout System ---\n");

        // 1. Create Lessons (Leaves)
        Lesson l1 = new Lesson("Intro to Java", 15.0, 45);
        Lesson l2 = new Lesson("OOP Principles", 20.0, 60);
        Lesson l3 = new Lesson("Design Patterns", 25.0, 90);
        
        Lesson l4 = new Lesson("Data Structures", 20.0, 60);
        Lesson l5 = new Lesson("Algorithms", 30.0, 120);

        // 2. Create Courses (Composite)
        Course javaCourse = new Course("Java Mastery");
        javaCourse.add(l1);
        javaCourse.add(l2);
        javaCourse.add(l3); 
        // JavaCourse Duration = 195 mins (3.25 hrs), Price = $60

        Course dsaCourse = new Course("DSA Bootcamp");
        dsaCourse.add(l4);
        dsaCourse.add(l5);
        // DSA Duration = 180 mins (3 hrs), Price = $50

        // 3. Create Modules (Composite)
        Module backendModule = new Module("Backend Engineering");
        backendModule.add(javaCourse);
        backendModule.add(dsaCourse);
        // Module Duration = 375 mins (6.25 hrs), Price = $110
        // This duration > 5 hours, so it qualifies for Special Discount

        System.out.println("--- SCENARIO 1: Buying a basic Module ---");
        backendModule.display("");
        System.out.println("Total Price: $" + backendModule.getPrice());
        System.out.println("\n-----------------------------------------");

        // 4. Apply Decorators (Add-ons and Discounts)
        // Scenario: Student buys Backend Module + Practice Set + Student Discount
        // + Special Duration Discount (Auto-applied because duration > 5 hrs)
        
        LearningItem cartItem = backendModule;
        
        // Add Practice Set ($10)
        cartItem = new PracticeQuestionDecorator(cartItem);
        
        // Add Student Discount (-$10)
        cartItem = new StudentDiscountDecorator(cartItem);
        
        // Add Special Duration Discount (Check duration >= 5 hours, -$12)
        cartItem = new SpecialDurationDiscountDecorator(cartItem);

        System.out.println("\n--- SCENARIO 2: Module with Add-ons & Discounts ---");
        // [cite: 30] - Transparency: displaying everything
        cartItem.display(""); 
        
        System.out.println("\nFINAL CHECKOUT PRICE CALCULATION:");
        System.out.println("Base Price (110) + Practice(10) - Student(10) - SpecialDuration(12)");
        System.out.println("Expected: $98.0");
        System.out.println("Calculated: $" + cartItem.getPrice());
    }
}