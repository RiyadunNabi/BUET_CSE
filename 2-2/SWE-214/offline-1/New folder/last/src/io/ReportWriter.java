package io;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.util.List;
import model.Expense;
import service.ExpenseRepository;
import service.Summarizer;

public abstract class ReportWriter {

    protected abstract Report createReport(String type);

    public void writeReport(String filePath, ExpenseRepository repository, String type) throws IOException {
        List<Expense> allExpenses = repository.findAll();
        Summarizer summarizer = new Summarizer(allExpenses);

        try (BufferedWriter writer = new BufferedWriter(new FileWriter(filePath))) {

            Report report = createReport(type);

            report.writeHeader(writer);
            report.writeMonthlySummary(writer, summarizer);
            report.writeCategoryBreakdown(writer, summarizer);
            report.writeGrandTotal(writer, summarizer);
            report.writeRecentEntries(writer, allExpenses);
            report.writeFooter(writer);
        }

        System.out.println("Report written to: " + filePath);
    }
}