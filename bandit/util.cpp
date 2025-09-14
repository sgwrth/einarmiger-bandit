#include "util.h"
#include <filesystem>
#include <fstream>
#include <string>

void Util::copy_file(std::ifstream& file_in, std::ofstream& file_out)
{
	std::string line;
	while (std::getline(file_in, line)) {
		file_out << line << "\n";
	}
}

void Util::delete_file(const std::string& filepath)
{
	bool success = std::filesystem::remove(std::filesystem::path(filepath));
}

void Util::rename_file(
		const std::string& old_filename,
		const std::string& new_filename)
{
	auto old_filepath = std::filesystem::path(old_filename);
	auto new_filepath = std::filesystem::path(new_filename);
	std::filesystem::rename(old_filepath, new_filepath);
}
