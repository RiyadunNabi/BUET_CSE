import java.util.ArrayList;
import java.util.List;

public class Student {
    public final String id;
    public final String name;
    private final List<Course> enrolledCourses = new ArrayList<>();
    private final List<Course> waitlistedCourses = new ArrayList<>();

    public Student(String id, String name) {
        this.id = id;
        this.name = name;
    }

    public boolean isEnrolledIn(Course c) { return enrolledCourses.contains(c); }
    public boolean isWaitlistedIn(Course c) { return waitlistedCourses.contains(c); }


    public void addCourseDirect(Course c) {
        if (!enrolledCourses.contains(c)) enrolledCourses.add(c);
        waitlistedCourses.remove(c);
    }

    public void addWaitlistDirect(Course c) {
        if (!waitlistedCourses.contains(c)) waitlistedCourses.add(c);
    }


    public void removeCourseDirect(Course c) {
        enrolledCourses.remove(c);
        waitlistedCourses.remove(c);
    }

    public void printSchedule() {
        System.out.println("Schedule for " + name + " (" + id + "):");
        System.out.println("  Enrolled:");
        if (enrolledCourses.isEmpty()) {
            System.out.println("    [none]");
        } else {
            for (Course c : enrolledCourses) {
                System.out.println("    " + c.code + " - " + c.title + " (" + c.getStatus().name() + ")");
            }
        }
        System.out.println("  Waitlisted:");
        if (waitlistedCourses.isEmpty()) {
            System.out.println("    [none]");
        } else {
            for (Course c : waitlistedCourses) {
                System.out.println("    " + c.code + " - " + c.title + " (" + c.getStatus().name() + ")");
            }
        }
    }
}
