import java.util.ArrayList;
import java.util.List;

/**
 * Base interface for all educational items (Lesson, Course, Module)
 * Composite Pattern - Component interface
 */
public interface EduItem {
    String getName();
    //main methods for all
    double getPrice();
    double getDuration(); // in hours
    void displayDetails(String indent);
}

/**
 * Leaf component in Composite pattern
 * Represents individual lesson
 */
class Lesson implements EduItem {
    private String name;
    private double duration;

    public Lesson(String name, double duration) {
        this.name = name;
        this.duration = duration;
    }

    @Override
    public String getName() {
        return name;
    }

    @Override
    public double getPrice() {
        return 0;
    }
    @Override
    public double getDuration() {
        return duration;
    }
    @Override
    public void displayDetails(String indent) {
        System.out.println(indent + "Lesson: " + name + 
                         " | Duration: " + duration + " hrs |");
    }
}


abstract class CompositeEduItem implements EduItem{
    protected String name;
    protected List<EduItem> children=new ArrayList<>();

    public CompositeEduItem(String name){
        this.name=name;
    }

    //methods for composite items
    public void add(EduItem item){
        children.add(item);
    }
    // public void remove(EduItem item){
    //     children.remove(item);
    // }
    public List<EduItem> getChildren(){
        return children;
    }

    //methods for all
     @Override
    public String getName() {
        return name;
    }
    @Override
    public double getDuration(){
        double duration=0;
        for(EduItem item : children){
            duration+=item.getDuration();
        }
        return duration;
    }
}

/**
 * Composite component - contains multiple Lessons
 */
class Course extends CompositeEduItem{
    private double basePrice;
    public Course(String name, double basePrice) {
        super(name);
        this.basePrice=basePrice;
    }

    @Override
    public double getPrice(){
        return basePrice;
    }

    @Override
    public void displayDetails(String indent) {
        System.out.println(indent + "Course: " + name + 
                         " | Duration: " + getDuration() + " hrs | Price: $" + getPrice());
        for (EduItem lesson : children) {
            lesson.displayDetails(indent + "  ");
        }
    }
}


/**
 * Higher-level Composite - contains multiple Courses
 */
class Module extends CompositeEduItem {
    public Module(String name) {
        super(name);
    }

    @Override
    public double getPrice(){
        double price=0;
        for(EduItem item : children){
            price+=item.getPrice();
        }
        return price;
    }
    @Override
    public void displayDetails(String indent) {
        System.out.println(indent + "Module: " + name + 
                         " | Duration: " + getDuration() + " hrs | Price: $" + getPrice());
        for (EduItem course : children) {
            course.displayDetails(indent + "  ");
        }
    }
}