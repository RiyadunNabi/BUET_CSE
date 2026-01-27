public interface ICourseRegistrationMediator {
    void registerStudent(String studentId, String courseCode);
    void unregisterStudent(String studentId, String courseCode);
    void waitlistStudent(String studentId, String courseCode);
}