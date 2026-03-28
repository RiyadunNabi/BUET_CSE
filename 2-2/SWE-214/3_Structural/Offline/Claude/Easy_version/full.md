I'll analyze the requirements and provide a complete solution using appropriate structural design patterns.

## Pattern Analysis

Let me break down which patterns are needed:

1. **Composite Pattern** (Requirement 1) - For the hierarchical structure (Module → Course → Lesson)
2. **Decorator Pattern** (Requirement 2) - For optional add-ons (Practice Set, Live Support)
3. **Decorator Pattern** (Requirement 3) - For discount system

Let me create the complete Java implementation:Let me check the available tools:I apologize for the technical difficulty. Let me provide you with the complete Java code solution that you can directly use. I'll organize it by pattern and requirement:

## Complete Java Solution

### **Pattern Mapping:**
- **Composite Pattern**: Module → Course → Lesson hierarchy (Req 1)
- **Decorator Pattern**: Add-ons and Discounts (Req 2 & 3)

---

### **1. EduItem.java** (Base Interface)
```java
/**
 * Base interface for all educational items (Lesson, Course, Module)
 * Composite Pattern - Component interface
 */
public interface EduItem {
    String getName();
    double getPrice();
    double getDuration(); // in hours
    void displayDetails(String indent);
}
```

---

### **2. Lesson.java** (Leaf Component)
```java
/**
 * Leaf component in Composite pattern
 * Represents individual lesson
 */
public class Lesson implements EduItem {
    private String name;
    private double duration;
    private double price;

    public Lesson(String name, double duration, double price) {
        this.name = name;
        this.duration = duration;
        this.price = price;
    }

    @Override
    public String getName() {
        return name;
    }

    @Override
    public double getPrice() {
        return price;
    }

    @Override
    public double getDuration() {
        return duration;
    }

    @Override
    public void displayDetails(String indent) {
        System.out.println(indent + "Lesson: " + name + 
                         " | Duration: " + duration + " hrs | Price: $" + price);
    }
}
```

---

### **3. Course.java** (Composite Component)
```java
import java.util.ArrayList;
import java.util.List;

/**
 * Composite component - contains multiple Lessons
 */
public class Course implements EduItem {
    private String name;
    private double basePrice;
    private List<EduItem> lessons;

    public Course(String name, double basePrice) {
        this.name = name;
        this.basePrice = basePrice;
        this.lessons = new ArrayList<>();
    }

    public void addLesson(EduItem lesson) {
        lessons.add(lesson);
    }

    public void removeLesson(EduItem lesson) {
        lessons.remove(lesson);
    }

    @Override
    public String getName() {
        return name;
    }

    @Override
    public double getPrice() {
        return basePrice;
    }

    @Override
    public double getDuration() {
        double totalDuration = 0;
        for (EduItem lesson : lessons) {
            totalDuration += lesson.getDuration();
        }
        return totalDuration;
    }

    @Override
    public void displayDetails(String indent) {
        System.out.println(indent + "Course: " + name + 
                         " | Duration: " + getDuration() + " hrs | Price: $" + getPrice());
        for (EduItem lesson : lessons) {
            lesson.displayDetails(indent + "  ");
        }
    }
}
```

---

### **4. Module.java** (Higher-level Composite)
```java
import java.util.ArrayList;
import java.util.List;

/**
 * Higher-level Composite - contains multiple Courses
 */
public class Module implements EduItem {
    private String name;
    private List<EduItem> courses;

    public Module(String name) {
        this.name = name;
        this.courses = new ArrayList<>();
    }

    public void addCourse(EduItem course) {
        courses.add(course);
    }

    public void removeCourse(EduItem course) {
        courses.remove(course);
    }

    @Override
    public String getName() {
        return name;
    }

    @Override
    public double getPrice() {
        double totalPrice = 0;
        for (EduItem course : courses) {
            totalPrice += course.getPrice();
        }
        return totalPrice;
    }

    @Override
    public double getDuration() {
        double totalDuration = 0;
        for (EduItem course : courses) {
            totalDuration += course.getDuration();
        }
        return totalDuration;
    }

    @Override
    public void displayDetails(String indent) {
        System.out.println(indent + "Module: " + name + 
                         " | Duration: " + getDuration() + " hrs | Price: $" + getPrice());
        for (EduItem course : courses) {
            course.displayDetails(indent + "  ");
        }
    }
}
```

---

### **5. EduItemDecorator.java** (Abstract Decorator)
```java
/**
 * Abstract Decorator for adding features/discounts
 * Decorator Pattern - Base Decorator
 */
public abstract class EduItemDecorator implements EduItem {
    protected EduItem wrappedItem;

    public EduItemDecorator(EduItem item) {
        this.wrappedItem = item;
    }

    @Override
    public String getName() {
        return wrappedItem.getName();
    }

    @Override
    public double getPrice() {
        return wrappedItem.getPrice();
    }

    @Override
    public double getDuration() {
        return wrappedItem.getDuration();
    }

    @Override
    public void displayDetails(String indent) {
        wrappedItem.displayDetails(indent);
    }
}
```

---

### **6. PracticeSetAddon.java** (Concrete Decorator for Add-on)
```java
/**
 * Decorator for Practice Set add-on ($10)
 */
public class PracticeSetAddon extends EduItemDecorator {
    private static final double PRACTICE_SET_PRICE = 10.0;

    public PracticeSetAddon(EduItem item) {
        super(item);
    }

    @Override
    public double getPrice() {
        return wrappedItem.getPrice() + PRACTICE_SET_PRICE;
    }

    @Override
    public void displayDetails(String indent) {
        wrappedItem.displayDetails(indent);
        System.out.println(indent + "[Add-on] Practice Question Set: $" + PRACTICE_SET_PRICE);
    }
}
```

---

### **7. LiveMentorAddon.java** (Concrete Decorator for Add-on)
```java
/**
 * Decorator for Live Mentor Support add-on ($20)
 */
public class LiveMentorAddon extends EduItemDecorator {
    private static final double LIVE_MENTOR_PRICE = 20.0;

    public LiveMentorAddon(EduItem item) {
        super(item);
    }

    @Override
    public double getPrice() {
        return wrappedItem.getPrice() + LIVE_MENTOR_PRICE;
    }

    @Override
    public void displayDetails(String indent) {
        wrappedItem.displayDetails(indent);
        System.out.println(indent + "[Add-on] Live Mentor Support: $" + LIVE_MENTOR_PRICE);
    }
}
```

---

### **8. MultiModuleDiscount.java** (Concrete Decorator for Discount)
```java
/**
 * Decorator for Multi-Module Discount ($15 off for 2+ modules)
 */
public class MultiModuleDiscount extends EduItemDecorator {
    private static final double DISCOUNT_AMOUNT = 15.0;
    private int moduleCount;

    public MultiModuleDiscount(EduItem item, int moduleCount) {
        super(item);
        this.moduleCount = moduleCount;
    }

    @Override
    public double getPrice() {
        double originalPrice = wrappedItem.getPrice();
        if (moduleCount >= 2) {
            return originalPrice - DISCOUNT_AMOUNT;
        }
        return originalPrice;
    }

    @Override
    public void displayDetails(String indent) {
        wrappedItem.displayDetails(indent);
        if (moduleCount >= 2) {
            System.out.println(indent + "[Discount] Multi-Module Discount: -$" + DISCOUNT_AMOUNT);
        }
    }
}
```

---

### **9. DurationBasedDiscount.java** (Concrete Decorator for Discount)
```java
/**
 * Decorator for Duration-based Discount ($12 off for 5+ hours)
 */
public class DurationBasedDiscount extends EduItemDecorator {
    private static final double DISCOUNT_AMOUNT = 12.0;
    private static final double DURATION_THRESHOLD = 5.0;

    public DurationBasedDiscount(EduItem item) {
        super(item);
    }

    @Override
    public double getPrice() {
        double originalPrice = wrappedItem.getPrice();
        if (wrappedItem.getDuration() >= DURATION_THRESHOLD) {
            return originalPrice - DISCOUNT_AMOUNT;
        }
        return originalPrice;
    }

    @Override
    public void displayDetails(String indent) {
        wrappedItem.displayDetails(indent);
        if (wrappedItem.getDuration() >= DURATION_THRESHOLD) {
            System.out.println(indent + "[Discount] Special Duration Discount (5+ hrs): -$" + DISCOUNT_AMOUNT);
        }
    }
}
```

---

### **10. DevelopingCountryDiscount.java** (Concrete Decorator for Discount)
```java
/**
 * Decorator for Developing Country Student Discount ($10 off)
 */
public class DevelopingCountryDiscount extends EduItemDecorator {
    private static final double DISCOUNT_AMOUNT = 10.0;

    public DevelopingCountryDiscount(EduItem item) {
        super(item);
    }

    @Override
    public double getPrice() {
        return wrappedItem.getPrice() - DISCOUNT_AMOUNT;
    }

    @Override
    public void displayDetails(String indent) {
        wrappedItem.displayDetails(indent);
        System.out.println(indent + "[Discount] Developing Country Student: -$" + DISCOUNT_AMOUNT);
    }
}
```

---

### **11. CheckoutSystem.java** (Client/Context)
```java
/**
 * Checkout system demonstrating unified interface
 */
public class CheckoutSystem {
    
    public void processCheckout(EduItem item) {
        System.out.println("\n" + "=".repeat(60));
        System.out.println("CHECKOUT DETAILS");
        System.out.println("=".repeat(60));
        
        item.displayDetails("");
        
        System.out.println("=".repeat(60));
        System.out.printf("TOTAL PRICE: $%.2f\n", item.getPrice());
        System.out.printf("TOTAL DURATION: %.2f hours\n", item.getDuration());
        System.out.println("=".repeat(60) + "\n");
    }
}
```

---

### **12. Main.java** (Demo Application)
```java
/**
 * Main class demonstrating all features
 */
public class Main {
    
    public static void main(String[] args) {
        CheckoutSystem checkout = new CheckoutSystem();
        
        // Demo 1: Single Course Purchase
        System.out.println("\n### DEMO 1: Single Course Purchase ###");
        Course javaCourse = createJavaCourse();
        checkout.processCheckout(javaCourse);
        
        // Demo 2: Module with Practice Set (Requirement 2)
        System.out.println("\n### DEMO 2: Module with Practice Set Add-on ###");
        Module webDevModule = createWebDevModule();
        EduItem moduleWithPractice = new PracticeSetAddon(webDevModule);
        checkout.processCheckout(moduleWithPractice);
        
        // Demo 3: Module with Both Add-ons (Requirement 2)
        System.out.println("\n### DEMO 3: Module with Both Add-ons ###");
        Module dataModule = createDataScienceModule();
        EduItem moduleWithBothAddons = new LiveMentorAddon(
            new PracticeSetAddon(dataModule)
        );
        checkout.processCheckout(moduleWithBothAddons);
        
        // Demo 4: Multiple Discounts - Developing Country + Duration (Requirement 3)
        System.out.println("\n### DEMO 4: Module with Multiple Discounts ###");
        Module aiModule = createAIModule();
        EduItem discountedModule = new DevelopingCountryDiscount(
            new DurationBasedDiscount(aiModule)
        );
        checkout.processCheckout(discountedModule);
        
        // Demo 5: Complete Purchase - 2 Modules + Add-ons + All Discounts
        System.out.println("\n### DEMO 5: Complex Purchase - Multiple Modules with Add-ons and Discounts ###");
        Module combinedModules = new Module("Complete Web & Data Science Bundle");
        combinedModules.addCourse(createWebDevModule());
        combinedModules.addCourse(createDataScienceModule());
        
        EduItem fullPackage = new DevelopingCountryDiscount(
            new DurationBasedDiscount(
                new MultiModuleDiscount(
                    new LiveMentorAddon(
                        new PracticeSetAddon(combinedModules)
                    ), 2
                )
            )
        );
        checkout.processCheckout(fullPackage);
        
        // Demo 6: Single Lesson Purchase (demonstrates flexibility)
        System.out.println("\n### DEMO 6: Single Lesson Purchase ###");
        Lesson singleLesson = new Lesson("Introduction to Python", 1.5, 15.0);
        checkout.processCheckout(singleLesson);
    }
    
    private static Course createJavaCourse() {
        Course course = new Course("Java Programming Fundamentals", 50.0);
        course.addLesson(new Lesson("Introduction to Java", 1.0, 0));
        course.addLesson(new Lesson("OOP Concepts", 2.0, 0));
        course.addLesson(new Lesson("Collections Framework", 1.5, 0));
        return course;
    }
    
    private static Module createWebDevModule() {
        Module module = new Module("Web Development Module");
        
        Course htmlCss = new Course("HTML & CSS", 40.0);
        htmlCss.addLesson(new Lesson("HTML Basics", 1.5, 0));
        htmlCss.addLesson(new Lesson("CSS Styling", 2.0, 0));
        
        Course javascript = new Course("JavaScript Essentials", 60.0);
        javascript.addLesson(new Lesson("JS Fundamentals", 2.0, 0));
        javascript.addLesson(new Lesson("DOM Manipulation", 1.5, 0));
        
        module.addCourse(htmlCss);
        module.addCourse(javascript);
        
        return module;
    }
    
    private static Module createDataScienceModule() {
        Module module = new Module("Data Science Module");
        
        Course python = new Course("Python for Data Science", 70.0);
        python.addLesson(new Lesson("NumPy Basics", 2.0, 0));
        python.addLesson(new Lesson("Pandas Introduction", 2.5, 0));
        
        Course ml = new Course("Machine Learning Basics", 80.0);
        ml.addLesson(new Lesson("Supervised Learning", 3.0, 0));
        ml.addLesson(new Lesson("Unsupervised Learning", 2.0, 0));
        
        module.addCourse(python);
        module.addCourse(ml);
        
        return module;
    }
    
    private static Module createAIModule() {
        Module module = new Module("AI & Deep Learning Module");
        
        Course dl = new Course("Deep Learning", 100.0);
        dl.addLesson(new Lesson("Neural Networks", 3.0, 0));
        dl.addLesson(new Lesson("CNNs", 2.5, 0));
        dl.addLesson(new Lesson("RNNs", 2.0, 0));
        
        module.addCourse(dl);
        
        return module;
    }
}
```

---

## **Design Pattern Explanation**

### **1. Composite Pattern (Requirement 1 - Unified Interface)**
- **Purpose**: Handle Module → Course → Lesson hierarchy uniformly
- **Classes**: `EduItem` (interface), `Lesson` (leaf), `Course` (composite), `Module` (composite)
- **Benefit**: `calculatePrice()` works at ANY level - no if-else needed!

### **2. Decorator Pattern (Requirement 2 - Add-ons)**
- **Purpose**: Add optional features dynamically
- **Classes**: `EduItemDecorator` (base), `PracticeSetAddon`, `LiveMentorAddon`
- **Benefit**: Can stack multiple add-ons without modifying original classes

### **3. Decorator Pattern (Requirement 3 - Discounts)**
- **Purpose**: Apply multiple discounts flexibly
- **Classes**: `MultiModuleDiscount`, `DurationBasedDiscount`, `DevelopingCountryDiscount`
- **Benefit**: Can combine any discounts - fully extensible!

---

## **How to Compile & Run**

```bash
# Navigate to src directory
cd src

# Compile all files
javac *.java

# Run the demo
java Main
```

---

## **Key Features Demonstrated**

✅ **Unified Interface** - Single `getPrice()` method works for everything  
✅ **Multiple Discounts** - Stack as many as needed  
✅ **Transparency** - `displayDetails()` shows complete breakdown  
✅ **No if-else spaghetti** - Clean OOP design  
✅ **Extensible** - Easy to add new add-ons/discounts

This solution perfectly addresses all requirements using proper structural design patterns!