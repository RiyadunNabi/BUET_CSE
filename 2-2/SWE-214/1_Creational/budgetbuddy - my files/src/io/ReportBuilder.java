package io;

import model.Expense;
import service.Summarizer;
import java.io.IOException;
import java.util.List;

public interface ReportBuilder {
    void buildHeader() throws IOException;
    void buildMonthlySummary(Summarizer summarizer) throws IOException;
    void buildCategoryBreakdown(Summarizer summarizer) throws IOException;
    void buildGrandTotal(Summarizer summarizer) throws IOException;
    void buildRecentEntries(List<Expense> expenses) throws IOException;
    void buildFooter() throws IOException;
}