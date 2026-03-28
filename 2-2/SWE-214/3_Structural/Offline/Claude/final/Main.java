// Checkout system demonstrating unified interface
class CheckoutSystem {
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


public class Main {
    private static Course createJavaCourse() {
        Course course = new Course("Java Programming Fundamentals",40);
        course.add(new Lesson("Introduction to Java", 1.0));
        course.add(new Lesson("OOP Concepts", 2.0));
        course.add(new Lesson("JavaFX Concepts", 1.5));
        return course;
    }
    
    private static Module createWebDevModule() {
        Module module = new Module("Web Development Module");
        
        Course htmlCss = new Course("HTML & CSS",30);
        htmlCss.add(new Lesson("HTML Basics", 1.5));
        htmlCss.add(new Lesson("CSS Styling", 2.0));
        
        Course javascript = new Course("JavaScript Essentials",35);
        javascript.add(new Lesson("JS Fundamentals", 2.0));
        javascript.add(new Lesson("DOM Manipulation", 1.5));
        // javascript.

        module.add(htmlCss);
        module.add(javascript);
        
        return module;
    }
    
    private static Module createDataScienceModule() {
        Module module = new Module("Data Science Module");
        
        Course python = new Course("Python for Data Science",50);
        python.add(new Lesson("NumPy Basics", 2.0));
        python.add(new Lesson("Pandas Introduction", 2.5));
        
        Course ml = new Course("Machine Learning Basics",70);
        ml.add(new Lesson("Supervised Learning", 3.0));
        ml.add(new Lesson("Unsupervised Learning", 2.0));
        
        module.add(python);
        module.add(ml);
        
        return module;
    }
    
    private static Module createAIModule() {
        Module module = new Module("AI & Deep Learning Module");
        
        Course dl = new Course("Deep Learning",90);
        dl.add(new Lesson("Neural Networks", 3.0));
        dl.add(new Lesson("CNNs", 2.5));
        dl.add(new Lesson("RNNs", 2.0));
        
        module.add(dl);
        
        return module;
    }
    
    public static void main(String[] args) {
        CheckoutSystem checkout = new CheckoutSystem();

        // ============================================================
        // Demo 1: Single Course Purchase
        System.out.println("\n### DEMO 1: Single Course Purchase ###");
        Course javaCourse = createJavaCourse();
        checkout.processCheckout(javaCourse);

        //============================================================ 
        // Demo 2: Module with Practice Set (Requirement 2)
        System.out.println("\n### DEMO 2: Module with Practice Set Add-on ###");
        Module webDevModule = createWebDevModule();
        EduItem moduleWithPractice = new PracticeSetAddon(webDevModule);
        checkout.processCheckout(moduleWithPractice);
        
        //============================================================
        // Demo 3: Module with Both Add-ons (Requirement 2)
        System.out.println("\n### DEMO 3: Module with Both Add-ons ###");
        Module dataModule = createDataScienceModule();
        EduItem moduleWithBothAddons = new LiveMentorAddon(new PracticeSetAddon(dataModule));
        checkout.processCheckout(moduleWithBothAddons);
        
        //============================================================
        // Demo 4: Multiple Discounts - Developing Country + Duration (Requirement 3)
        System.out.println("\n### DEMO 4: Module with Multiple Discounts ###");
        Module aiModule = createAIModule();
        EduItem discountedModule = new DevelopingCountryDiscount(new DurationBasedDiscount(aiModule));
        checkout.processCheckout(discountedModule);
        
        //============================================================
        // Demo 5: Complete Purchase - 2 Modules + Add-ons + All Discounts
        System.out.println("\n### DEMO 5: Complex Purchase - Multiple Modules with Add-ons and Discounts ###");
        Module combinedModules = new Module("Complete Web & Data Science Bundle");
        combinedModules.add(createWebDevModule());
        combinedModules.add(createDataScienceModule());
        
        EduItem fullPackage = new DevelopingCountryDiscount(
            new DurationBasedDiscount(
                new MultiModuleDiscount(
                    new LiveMentorAddon(
                        new PracticeSetAddon(combinedModules)
                    )
                )
            )
        );
        checkout.processCheckout(fullPackage);
        
        //============================================================
        // Demo 6: Single Lesson Purchase (demonstrates flexibility)
        System.out.println("\n### DEMO 6: Single Lesson Purchase ###");
        Lesson singleLesson = new Lesson("Introduction to Python", 1.5);
        checkout.processCheckout(singleLesson);
    }
    
}