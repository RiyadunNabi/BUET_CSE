public class Branch {

    private int id;
    private String name;
    private Account accounts[];
    private int accountCount;
    // add your code here
    // there can be at most 20 branches
    private static int branchCount;
    private static Branch[] branches = new Branch[20];

    // you are not allowed to write any other constructor
    public Branch(int id, String name) {
        this.id = id;
        this.name = name;
        this.accounts = new Account[10];
        // add your code here
        branches[branchCount++] =this;
    }

    public void addAccount(Account a) {
        accounts[accountCount++] = a;
    }

    // add your code here
    public double getBranchBalance() {
        double totalBalance = 0;
        for (int i = 0; i < accountCount; i++) {
            totalBalance += accounts[i].getBalance();
        }
        return totalBalance;
    }

    public Account getMinBalanceAccount() {
        Account a = accounts[0];
        for (int i = 1; i < accountCount; i++) {
            if (a.getBalance() > accounts[i].getBalance()) {
                a = accounts[i];
            }
        }
        return a;

    }

    public static void transferBalance(Account a, Account b, double tk) {
        a.setBalance(a.getBalance() - tk);
        b.setBalance(b.getBalance() + tk);
    }

    public static void printAllBranchesInfo() {
        for (int i = 0; i < branchCount; i++) {
            System.out.println("Branch Id: "+ branches[i].id +", Branch Name: " + branches[i].name );
            for (int j = 0; j < branches[i].accountCount; j++) {
                System.out.println(branches[i].accounts[j]);
            }
        }
    }
}
