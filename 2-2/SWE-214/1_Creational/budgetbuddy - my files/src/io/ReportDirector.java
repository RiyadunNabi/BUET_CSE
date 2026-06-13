package io;

import model.Expense;
import service.ExpenseRepository;
import service.Summarizer;

import java.io.IOException;
import java.util.List;

public class ReportDirector {
    private final ReportBuilder builder;

    public ReportDirector(ReportBuilder builder) {
        this.builder = builder;
    }

    public void constructReport(ExpenseRepository repository) throws IOException {
        List<Expense> allExpenses = repository.findAll();
        Summarizer summarizer = new Summarizer(allExpenses);

        builder.buildHeader();
        builder.buildMonthlySummary(summarizer);
        builder.buildCategoryBreakdown(summarizer);
        builder.buildGrandTotal(summarizer);
        builder.buildRecentEntries(allExpenses);
        builder.buildFooter();
    }
}