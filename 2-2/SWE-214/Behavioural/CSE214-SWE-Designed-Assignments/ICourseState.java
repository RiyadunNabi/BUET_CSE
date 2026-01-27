public interface ICourseState {
    // Lifecycle management
    CourseStatus getStatus();
    boolean canTransitionTo(CourseStatus nextStatus);

    // Core behaviors that change based on state
    boolean enroll(Course c, Student s);
    boolean waitlist(Course c, Student s);
}