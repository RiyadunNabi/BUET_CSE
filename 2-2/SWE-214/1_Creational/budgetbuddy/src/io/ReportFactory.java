package io;

import java.io.IOException;

public class ReportFactory {

    public static ReportBuilder createBuilder(String type, String filePath) throws IOException {
        switch (type.toLowerCase()) {
            case "txt":
                // System.out.println("testingggggggggg");
                return new TxtReportBuilder(filePath);
            case "html":
                return new HtmlReportBuilder(filePath);
            default:
                throw new IllegalArgumentException("Unknown report type: " + type);
        }
    }
}