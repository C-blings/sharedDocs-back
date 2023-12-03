#include "FileWriter.hpp"
#include <fstream>

namespace file_helpers{
    FileWriter::FileWriter(const std::filesystem::path &file_path) : file_path_(file_path) {}
}