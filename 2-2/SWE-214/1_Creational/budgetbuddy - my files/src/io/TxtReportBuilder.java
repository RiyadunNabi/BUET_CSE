package io;

import model.Expense;
import service.Summarizer;
import util.TextUtils;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
// import java.time.LocalDate;
import java.time.YearMonth;
import java.time.format.DateTimeFormatter;
import java.util.List;
import java.util.Map;

public class TxtReportBuilder implements ReportBuilder {

    private final BufferedWriter writer;
    private static final DateTimeFormatter DATE_FORMATTER = DateTimeFormatter.ofPattern("yyyy-MM-dd");
    private static final DateTimeFormatter MONTH_FORMATTER = DateTimeFormatter.ofPattern("yyyy-MM");

    public TxtReportBuilder(String filePath) throws IOException {
        this.writer = new BufferedWriter(new FileWriter(filePath));
    }

    @Override
    public void buildHeader() throws IOException {
        writer.write("=====================================\n");
        writer.write("       BUDGETBUDDY EXPENSE REPORT    \n");
        writer.write("=====================================\n\n");
    }

    @Override
    public void buildMonthlySummary(Summarizer summarizer) throws IOException {
        writer.write("MONTHLY SUMMARY\n");
        writer.write(TextUtils.separator(60) + "\n");

        Map<YearMonth, Double> monthlyTotals = summarizer.monthlyTotals();
        for (Map.Entry<YearMonth, Double> entry : monthlyTotals.entrySet()) {
            String monthStr = entry.getKey().format(MONTH_FORMATTER);
            String amountStr = String.format("%.2f", entry.getValue());
            writer.write(String.format("%-10s : %12s\n", monthStr, amountStr));
        }
        writer.write("\n");
        
        
        // writer.write("MONTHLY SUMMARY\n");
        // writer.write(TextUtils.separator(60) + "\n");
        
        // for (Map.Entry<YearMonth, Double> entry : summarizer.monthlyTotals().entrySet()) {
        //     writer.write(String.format("%-10s : %12s\n", 
        //         entry.getKey().format(MONTH_FORMATTER), 
        //         String.format("%.2f", entry.getValue())));
        // }
        // writer.write("\n");
    }

    @Override
    public void buildCategoryBreakdown(Summarizer summarizer) throws IOException {
        writer.write("CATEGORY BREAKDOWN (All Time)\n");
        writer.write(TextUtils.separator(60) + "\n");

        Map<String, Double> categoryTotals = summarizer.categoryTotals(null);
        double maxAmount = categoryTotals.values().stream()
                .max(Double::compareTo)
                .orElse(1.0);

        for (Map.Entry<String, Double> entry : categoryTotals.entrySet()) {
            String category = entry.getKey();
            double amount = entry.getValue();
            String amountStr = String.format("%.2f", entry.getValue());
            String bar = createBar(amount, maxAmount);
            writer.write(String.format("%-15s %12s  %s\n", category, amountStr, bar));
        }
        writer.write("\n");
        
        
        // writer.write("CATEGORY BREAKDOWN (All Time)\n");
        // writer.write(TextUtils.separator(60) + "\n");
        
        // Map<String, Double> totals = summarizer.categoryTotals(null);
        // double max = totals.values().stream().max(Double::compareTo).orElse(1.0);

        // for (Map.Entry<String, Double> entry : totals.entrySet()) {
        //     String bar = TextUtils.createBar(entry.getValue(), max, 30);
        //     writer.write(String.format("%-15s %12s  %s\n", 
        //         entry.getKey(), 
        //         String.format("%.2f", entry.getValue()), 
        //         bar));
        // }
        // writer.write("\n");
    }

    @Override
    public void buildGrandTotal(Summarizer summarizer) throws IOException {
        writer.write(TextUtils.separator(60) + "\n");
        writer.write(String.format("GRAND TOTAL: %s\n", String.format("%.2f", summarizer.grandTotal())));
        writer.write(TextUtils.separator(60) + "\n");
    }

    @Override
    public void buildRecentEntries(List<Expense> expenses) throws IOException {
        writer.write("\nRECENT ENTRIES (Last 10)\n");
        writer.write(TextUtils.separator(60) + "\n");

        int count = 0;
        for (int i = expenses.size() - 1; i >= 0 && count < 10; i--, count++) {
            Expense exp = expenses.get(i);
            String dateStr = exp.getDate().format(DATE_FORMATTER);
            writer.write(String.format("%s  %-12s %10s  %s\n",
                    dateStr,
                    exp.getCategory(),
                    String.format("%.2f", exp.getAmount()),
                    exp.getNotes()));
        }
    }

    @Override
    public void buildFooter() throws IOException {
        writer.close();
    }

    private String createBar(double value, double maxValue) {
        return TextUtils.createBar(value, maxValue, 30);
    }
}