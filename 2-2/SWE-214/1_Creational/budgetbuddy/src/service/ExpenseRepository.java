package service;

import model.Expense;

import java.time.YearMonth;
import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;

/**
 * In-memory repository for expense data.
 */
public class ExpenseRepository {
//---------------------------------------------------------------------
    private static ExpenseRepository uniqueInstance;
    private final List<Expense> expenses;

    /**
     * Creates a new empty repository.
     */
    private ExpenseRepository() {
        this.expenses = new ArrayList<>();
        System.out.println("Created new ExpenseRepository instance");
    }

    public static ExpenseRepository getInstance(){
        if(uniqueInstance==null){
            uniqueInstance=new ExpenseRepository();
        }
        return uniqueInstance;
    }
//-----------------------------------------------------------------
    /**
     * Adds multiple expenses to the repository.
     *
     * @param expenseList the list of expenses to add
     */
    public void addAll(List<Expense> expenseList) {
        this.expenses.addAll(expenseList);
    }

    /**
     * Adds a single expense to the repository.
     *
     * @param expense the expense to add
     */
    public void add(Expense expense) {
        this.expenses.add(expense);
    }

    /**
     * Returns all expenses in the repository.
     *
     * @return list of all expenses
     */
    public List<Expense> findAll() {
        return new ArrayList<>(expenses);
    }

    /**
     * Returns all expenses for a specific month.
     *
     * @param yearMonth the year-month to filter by
     * @return list of expenses in the specified month
     */
    public List<Expense> findByMonth(YearMonth yearMonth) {
        return expenses.stream()
                .filter(e -> YearMonth.from(e.getDate()).equals(yearMonth))
                .collect(Collectors.toList());
    }

    /**
     * Returns the count of expenses in the repository.
     *
     * @return number of expenses
     */
    public int count() {
        return expenses.size();
    }

    /**
     * Clears all expenses from the repository.
     */
    public void clear() {
        expenses.clear();
    }
}
