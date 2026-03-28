
// Base Decorator
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
    public double getDuration() {
        return wrappedItem.getDuration();
    }
    // //Needs to be overriden for Optional Add-ons
    // @Override         
    // public double getPrice() {
    //     return wrappedItem.getPrice();
    // }
    // @Override
    // public void displayDetails(String indent) {
    //     wrappedItem.displayDetails(indent);
    // }
    public abstract double getPrice();
    public abstract void displayDetails(String indent);
}

//================================= Task-2 =======================================

// Decorator for Practice Set add-on
class PracticeSetAddon extends EduItemDecorator {
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


// Decorator for Live Mentor Support add-on
class LiveMentorAddon extends EduItemDecorator {
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

//================================= Task-3 =======================================
//  Decorator for Multi-Module Discount
class MultiModuleDiscount extends EduItemDecorator {
    private static final double DISCOUNT_AMOUNT = 15.0;
    // private int moduleCount;
    public MultiModuleDiscount(EduItem item) {
        super(item);
    }

    @Override
    public double getPrice() {
        double originalPrice = wrappedItem.getPrice();
        int moduleCount = CountModules(wrappedItem);
        if (moduleCount >= 2) {
            return originalPrice - DISCOUNT_AMOUNT;
        }
        return originalPrice;
    }

    @Override
    public void displayDetails(String indent) {
        wrappedItem.displayDetails(indent);
        int moduleCount = CountModules(wrappedItem);
        if (moduleCount >= 2) {
            System.out.println(indent + "[Discount] Multi-Module Discount: -$" + DISCOUNT_AMOUNT);
        }
    }

    private int CountModules(EduItem item) {
        int count = 0;

        if (item instanceof EduItemDecorator) {
            return CountModules(((EduItemDecorator) item).wrappedItem);
        }

        if (item instanceof CompositeEduItem) {
            for (EduItem child : ((CompositeEduItem) item).getChildren()) {
                if (child instanceof Module) count++;
                else count += CountModules(child);
            }
        }
        return count;
    }
}


// Decorator for Duration-based Discount
class DurationBasedDiscount extends EduItemDecorator {
    private static final double DISCOUNT_AMOUNT = 12.0;
    private static final double DURATION_THRESHOLD = 5; // 5 hours
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


//Decorator for Developing Country Student Discount
class DevelopingCountryDiscount extends EduItemDecorator {
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