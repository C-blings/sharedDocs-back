#include <gtest/gtest.h>
#include <file_helpers/FileReader.hpp>
#include <file_helpers/FileWriter.hpp>


TEST(CheckFileReading, FileReaderTest){
    const std::string first_part = "Hello from shareDocs!";
    const std::string second_part = "Sliderer and AKSUM";

    file_helpers::FileWriter file_writer("tests/helpers/files/input.txt");
    file_writer.WriteToFile(first_part, second_part);
    file_helpers::FileReader file_reader("tests/helpers/files/input.txt");
    
    EXPECT_EQ(file_reader.GetFileText(), first_part + second_part);
}