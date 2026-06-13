import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        // int n= (int)(args[0].charAt(0) - '0');
        // int n = 2;

        int n=Integer.parseInt(args[0]);
        Library library = new Library(n);

        Scanner sc = new Scanner(System.in);

        for (int i = 0; i < n; i++) {
            System.out.printf("Enter details for book %d:\n", i + 1);
            System.out.print("Title: ");
            String t = sc.nextLine();
            System.out.print("Author: ");
            String a = sc.nextLine();
            System.out.print("ISBN: ");
            String I = sc.nextLine();
            while(library.isISBN(I))
            {
                System.out.print("ISBN matched! Try again! \nISBN: ");
                I=sc.nextLine();
            }
            System.out.print("Total copies: ");
            int tc = sc.nextInt();
            System.out.print("Borrowed copies: ");
            int bc = sc.nextInt();
            while (bc > tc) {
                System.out.print("Invalid value, borrowed copies cannot exceed total copies. Please try again: ");
                bc = sc.nextInt();
            }
            sc.nextLine(); // Consume leftover newline

            Book obj = new Book(t, a, I, tc, bc);

            library.addBook(obj);
        }

        String s = "";
        while (true) {
            System.out.print("Search for a book by title: ");
            s = sc.nextLine();
            if(s.equals("0"))
            {
                System.out.println("Exiting Search, Goodbye!!!");
                break;
            }
            library.searchBook(s);
        }

        sc.close();
    }
}
