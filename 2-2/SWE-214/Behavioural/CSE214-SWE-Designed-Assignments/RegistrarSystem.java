import java.util.Collection;
import java.util.HashMap;
import java.util.Map;

public class RegistrarSystem implements ICourseRegistrationMediator {
    private final Map<String, Student> students = new HashMap<>();
    private final Map<String, Course> courses = new HashMap<>();

    public void addStudent(Student s) {
        if (s != null) students.put(s.id, s);
    }

    public void addCourse(Course c) {
        if (c != null) courses.put(c.code, c);
    }

    public Student getStudent(String id) {
        return students.get(id);
    }

    public Course getCourse(String code) {
        return courses.get(code);
    }

    public Collection<Student> getAllStudents() {
        return students.values();
    }

    public Collection<Course> getAllCourses() {
        return courses.values();
    }


    @Override
    public void registerStudent(String studentId, String courseCode) {
        Student s = getStudent(studentId);
        Course c = getCourse(courseCode);

        if (s == null || c == null) {
            System.out.println("Invalid student or course.");
            return;
        }

        if (!c.isVisibleToStudents()) {
            System.out.println("Course " + c.code + " is not available(not visible) for student enrollment.");
            return;
        }
        if (s.isEnrolledIn(c)) {
            System.out.println("Already enrolled: " + s.name + " in " + c.code);
            return;
        }
        boolean success = c.tryEnroll(s); 
        if (success) {
            s.addCourseDirect(c);
        }
    }

    @Override
    public void waitlistStudent(String studentId, String courseCode) {
        Student s = getStudent(studentId);
        Course c = getCourse(courseCode);
        if (s == null || c == null) return;

        if (!c.isVisibleToStudents()) {
            System.out.println("Course " + c.code + " is not available(not visible).");
            return;
        }
        if (s.isWaitlistedIn(c)) {
            System.out.println("Already waitlisted: " + s.name + " for " + c.code);
            return;
        }
        if (s.isEnrolledIn(c)) {
            System.out.println("Already enrolled; no need to waitlist: " + s.name + " for " + c.code);
            return;
        }

        boolean success = c.addToWaitlist(s);
        if (success) {
            s.addWaitlistDirect(c);
        }
    }

    @Override
    public void unregisterStudent(String studentId, String courseCode) {
        Student s = getStudent(studentId);
        Course c = getCourse(courseCode);
        if (s == null || c == null) return;

        boolean wasEnrolled = s.isEnrolledIn(c);
        boolean wasWaitlisted = s.isWaitlistedIn(c);

        if (!wasEnrolled && !wasWaitlisted) {
            System.out.println(s.name + " is neither enrolled nor waitlisted for " + c.code);
            return;
        }
        s.removeCourseDirect(c);

        c.removeStudent(s);
        
        if(wasEnrolled && !wasWaitlisted) {
            System.out.println("Dropped from enrolled: " + s.name + " from " + c.code);
        } else if(!wasEnrolled && wasWaitlisted){
            System.out.println("Removed from waitlist: " + s.name + " for " + c.code);
        }

        if (wasEnrolled && c.hasSpace() && c.hasWaitlist()) {
            promoteNextStudent(c);
        }
    }

    private void promoteNextStudent(Course c) {
        Student promoted = c.popNextWaitlisted();
        if (promoted != null) {
            promoted.removeCourseDirect(c);
            
            c.addStudentDirect(promoted); 
            promoted.addCourseDirect(c);
            
            System.out.println("Promoted from waitlist: " + promoted.name + " into " + c.code);
        }
    }
}
