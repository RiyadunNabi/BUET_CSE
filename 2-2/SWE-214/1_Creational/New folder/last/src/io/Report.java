package io;

import java.io.BufferedWriter;
import java.io.IOException;
import java.time.LocalDate;
import java.time.YearMonth;
import java.time.format.DateTimeFormatter;
import java.util.List;
import model.Expense;
import service.Summarizer;
import util.TextUtils;

public abstract class Report {
    protected final DateTimeFormatter dateFormatter;
    protected final DateTimeFormatter monthFormatter;

    public Report() {
        this.dateFormatter = DateTimeFormatter.ofPattern("yyyy-MM-dd");
        this.monthFormatter = DateTimeFormatter.ofPattern("yyyy-MM");
    }

    public abstract void writeHeader(BufferedWriter writer) throws IOException;
    public abstract void writeMonthlySummary(BufferedWriter writer, Summarizer summarizer) throws IOException;
    public abstract void writeCategoryBreakdown(BufferedWriter writer, Summarizer summarizer) throws IOException;
    public abstract void writeGrandTotal(BufferedWriter writer, Summarizer summarizer) throws IOException;
    public abstract void writeRecentEntries(BufferedWriter writer, List<Expense> expenses) throws IOException;
    public abstract void writeFooter(BufferedWriter writer) throws IOException;

    protected String formatDate(LocalDate date) {
        return date.format(dateFormatter);
    }

    protected String formatMonth(YearMonth month) {
        return month.format(monthFormatter);
    }

    protected String formatAmount(double amount) {
        return String.format("%.2f", amount);
    }

    protected String createBar(double value, double maxValue) {
        return TextUtils.createBar(value, maxValue, 30);
    }
}