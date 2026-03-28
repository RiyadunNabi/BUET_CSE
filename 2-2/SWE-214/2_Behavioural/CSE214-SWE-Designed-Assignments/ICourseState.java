public interface ICourseState {
    CourseStatus getStatus();
    boolean canTransitionTo(CourseStatus nextStatus);

    boolean enroll(Course c, Student s);
    boolean waitlist(Course c, Student s);
}