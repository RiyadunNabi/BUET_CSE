public class Library {
    private int noOfBooks;
    private Book book_array[];

    Library(int n)
    {
        noOfBooks=0;
        book_array=new Book[n];
    }

    public void addBook(Book b)
    {
        if (noOfBooks >= book_array.length) {
            System.out.println("Library is full. Cannot add more books.");
            return;
        }
        
        // book_array[noOfBooks]=new Book;
        book_array[noOfBooks++]=b;
        System.out.printf("Book added successfully!\n");

    }

    public void searchBook(String t)
    {
        for(int i=0; i<noOfBooks; i++)
        {
            if(t.equals(book_array[i].getTitle()))
            {
                book_array[i].displayInfo();
                return;
            }
        }
        System.out.println("Not found");
    }

    public boolean isISBN(String isbn)
    {
        for(int i=0; i<noOfBooks; i++)
        {
            if(isbn.equals(book_array[i].getISBN()))
            {
                book_array[i].displayInfo();
                return true;
            }
        }
        return false;
    }

    public void displayAll()
    {
        for(int i=0; i<noOfBooks; i++)
        {
            book_array[i].displayInfo();
        }
    }

}
