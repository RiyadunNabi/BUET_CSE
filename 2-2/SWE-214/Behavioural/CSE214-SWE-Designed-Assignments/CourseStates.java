class DraftState implements ICourseState {
    @Override
    public CourseStatus getStatus() { return CourseStatus.DRAFT; }

    @Override
    public boolean canTransitionTo(CourseStatus nextStatus) {
        // Can go to OPEN or CANCELLED
        return nextStatus == CourseStatus.OPEN || nextStatus == CourseStatus.CANCELLED || nextStatus== CourseStatus.CLOSED;
    }

    @Override
    public boolean enroll(Course c, Student s){
        System.out.println("Cannot enroll; course is DRAFT (not visible): " + c.code);
        return false;
    }

    @Override
    public boolean waitlist(Course c, Student s){
        System.out.println("Cannot waitlist;course not accepting waitlist: " + c.code);
        return false;
    }
}

class OpenState implements ICourseState {
    @Override
    public CourseStatus getStatus() { return CourseStatus.OPEN; }
    
    @Override
    public boolean canTransitionTo(CourseStatus nextStatus) {
        return nextStatus == CourseStatus.CLOSED || nextStatus == CourseStatus.DRAFT || nextStatus == CourseStatus.CANCELLED || nextStatus == CourseStatus.FULL;
    }

    @Override
    public boolean enroll(Course c, Student s) {
        if (c.enrolled.size() < c.getCapacity()) {
            c.enrolled.add(s);
            System.out.println("Enrolled: " + s.name + " in " + c.code);
            
            if (c.enrolled.size() >= c.getCapacity()) {
                c.setState(new FullState());
                System.out.println(c.code + " is now FULL.");
            }
            return true;
        } 
        else {
            System.out.println(c.code + " reached capacity; status set to FULL. Try waitlisting.");
            c.setState(new FullState());
            return false;
        }
    }

    @Override
    public boolean waitlist(Course c, Student s) {
        System.out.println("Course is OPEN; try enrolling instead: " + c.code);
        return false;
    }

}

class FullState implements ICourseState {
    @Override
    public CourseStatus getStatus() { return CourseStatus.FULL; }

    @Override
    public boolean canTransitionTo(CourseStatus nextStatus) {
        return nextStatus == CourseStatus.CLOSED || nextStatus == CourseStatus.CANCELLED;
    }

    @Override
    public boolean enroll(Course c, Student s) {
        System.out.println("Cannot enroll; course is FULL. You may waitlist: " + c.code);
        return false;
    }

    @Override
    public boolean waitlist(Course c, Student s) {
        c.waitlist.add(s);
        System.out.println("Waitlisted: " + s.name + " for " + c.code);
        return true;
    }

}

class ClosedState implements ICourseState {
    @Override
    public CourseStatus getStatus() { return CourseStatus.CLOSED; }

    @Override
    public boolean canTransitionTo(CourseStatus nextStatus) {
        return nextStatus == CourseStatus.OPEN || nextStatus == CourseStatus.DRAFT || nextStatus == CourseStatus.CANCELLED;
    }

    @Override
    public boolean enroll(Course c, Student s) {
        System.out.println("Cannot enroll; course is CLOSED: " + c.code);
        return false;
    }

    @Override
    public boolean waitlist(Course c, Student s){
        System.out.println("Cannot waitlist; course not accepting waitlist: " + c.code);
        return false;
    }

}

class CancelledState implements ICourseState {
    @Override
    public CourseStatus getStatus() { return CourseStatus.CANCELLED; }

    @Override
    public boolean canTransitionTo(CourseStatus nextStatus) {
        return nextStatus == CourseStatus.DRAFT;
    }

    @Override
    public boolean enroll(Course c, Student s) {
        System.out.println("Cannot enroll; course is CANCELLED: " + c.code);
        return false;
    }
    @Override
    public boolean waitlist(Course c, Student s){
        System.out.println("Cannot waitlist; course not accepting waitlist: " + c.code);
        return false;
    }
}