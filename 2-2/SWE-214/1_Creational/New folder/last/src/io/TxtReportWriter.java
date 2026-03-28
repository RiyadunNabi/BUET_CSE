package io;

public class TxtReportWriter extends ReportWriter {
    @Override
    protected Report createReport(String type) {
        System.out.println("its workinggggg");
        return new TxtReport();
    }
}