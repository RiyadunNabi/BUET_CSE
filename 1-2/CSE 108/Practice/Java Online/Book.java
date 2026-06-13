public class Book {
    private String title;
    private String author;
    private String ISBN;
    private int total_copies;
    private int borrowed_copies;
    private int available;

    Book(String t,String a, String I, int tc, int bc)
    {
        title=t;
        ISBN=I;
        author=a;
        total_copies=tc;
        borrowed_copies=bc;
        available=tc-bc;
    }

    public String getISBN() {
        return ISBN;
    }

    public String getTitle()
    {
        return this.title;
    }

    // Method to borrow a book
    public boolean borrowBook() {
        if (available > 0) {
            borrowed_copies++;
            available--;
            return true;
        } else {
            System.out.println("No copies available to borrow.");
            return false;
        }
    }

    // Method to return a book
    public boolean returnBook() {
        if (borrowed_copies > 0) {
            borrowed_copies--;
            available++;
            return true;
        } else {
            System.out.println("No borrowed copies to return.");
            return false;
        }
    }

    public void displayInfo()
    {
        System.out.println("Book detail:\n - Title: " + title +"\n - Author: " + author + "\n - ISBN: " + ISBN + "\n - Available Copies: " + available + "\n");
        if(available==0)
        {
            System.out.println("Status: All copies are currently borrowed.\n");
        }
    }

    @Override
    public String toString() {
        return "Book [title=" + title + ", author=" + author + ", ISBN=" + ISBN + ", total_copies=" + total_copies
                + ", borrowed_copies=" + borrowed_copies + ", available=" + available + "]";
    }

    
}
