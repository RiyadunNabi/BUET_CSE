package io;

public class HtmlReportWriter extends ReportWriter {
    @Override
    protected Report createReport(String type) {
        return new HtmlReport();
    }
}