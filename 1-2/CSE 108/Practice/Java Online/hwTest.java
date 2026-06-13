public class hwTest {
    public static void main(String[] args) {
        Book book = new Book("Java Programming", "James Gosling", "123456789", 5, 2);
        book.displayInfo();

        System.out.println("\nAttempting to borrow a book...");
        book.borrowBook();
        book.displayInfo();

        System.out.println("\nAttempting to return a book...");
        book.returnBook();
        book.displayInfo();

        System.out.println("\nUsing toString to display book details:");
        System.out.println(book);
    }
    
}



