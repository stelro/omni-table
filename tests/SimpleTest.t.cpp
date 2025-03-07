#include <gtest/gtest.h>

#include <cstring>
#include <cstdlib>
#include <cstdio>

#include "table.h"

using namespace omni;

namespace {

TEST(TableTest, SingleCellPrint) {
    Table table;
    table[0][0] = "Hello";
    
    testing::internal::CaptureStdout();
    table.print();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_NE(output.find("Hello"), std::string::npos);
    EXPECT_NE(output.find("+"), std::string::npos);
    EXPECT_NE(output.find("|"), std::string::npos);
}

TEST(TableTest, MultipleRowsAndColumns) {
    Table table;
    table[0][0] = "Cell 1";
    table[0][1] = "Cell 2";
    table[1][0] = "Cell 3";
    table[1][1] = "Cell 4";
    
    testing::internal::CaptureStdout();
    table.print();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_NE(output.find("Cell 1"), std::string::npos);
    EXPECT_NE(output.find("Cell 2"), std::string::npos);
    EXPECT_NE(output.find("Cell 3"), std::string::npos);
    EXPECT_NE(output.find("Cell 4"), std::string::npos);
    EXPECT_NE(output.find("|"), std::string::npos);
}

TEST(TableTest, TextWrapping) {
    Table table;
    table.set_max_column_width(5);
    table[0][0] = "LongWordWithoutSpaces";
    
    testing::internal::CaptureStdout();
    table.print();
    std::string output = testing::internal::GetCapturedStdout();

    // With a max width of 5, parts of the long word should appear in separate segments.
    EXPECT_NE(output.find("LongW"), std::string::npos);
    EXPECT_NE(output.find("ordWi"), std::string::npos);
    
    // Check that the output contains more than one line (wrapped text).
    size_t newlineCount = std::count_if(output.begin(), output.end(), [](char c) { return c == '\n'; });
    EXPECT_GT(newlineCount, 1);
}

TEST(TableTest, VerticalCentering) {
    Table table;
    table[0][0] = "Short";
    table[0][1] = "This is a longer text that will wrap over multiple lines.";
    
    table.enable_vertical_centering(true);
    table.set_max_column_width(10);
    
    testing::internal::CaptureStdout();
    table.print();
    std::string output = testing::internal::GetCapturedStdout();
    
    // Since vertical centering is enabled, the shorter cell ("Short")
    // should have blank lines (or extra vertical padding) in its area.
    // Here we simply check that the printed row spans multiple lines.
	size_t newlineCount = std::count_if(output.begin(), output.end(), [](char c) { return c == '\n'; });

    EXPECT_GT(newlineCount, 1);
}

TEST(TableTest, BorderColorEnabled) {
    Table table;
    table[0][0] = "Test";
    table.enable_border_style(format::style::red);

    testing::internal::CaptureStdout();
    table.print();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_NE(output.find("\033[31m"), std::string::npos);
    EXPECT_NE(output.find("\033[0m"), std::string::npos);
}
    
}
