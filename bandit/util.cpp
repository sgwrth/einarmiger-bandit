#include "util.h"
#include <filesystem>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

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

std::string Util::get_str_input()
{
	std::string input;
	std::cin >> input;
	std::cin.clear();
	std::cin.ignore();
	return input;
}

void Util::print_msg(const std::string& msg)
{
	std::cout << msg;
}

std::vector<std::string> Util::split(const std::string& str, char delimiter)
{
	std::vector<std::string> tokens;
	std::stringstream ss(str);
	std::string token;

	while (std::getline(ss, token, delimiter)) {
		tokens.push_back(token);
	}

	return tokens;
}

struct tm Util::get_time_tm()
{
	auto now = std::chrono::system_clock::now();
	auto time_t = std::chrono::system_clock::to_time_t(now);
	struct tm time_tm;

	/*
	 * As per https://en.cppreference.com/w/c/chrono/localtime:
	 * "The implementation of localtime_s in Microsoft CRT is incompatible
	 * with the C standard since it has reversed parameter order and
	 * returns errno_t."
	 */
	auto err = localtime_s(&time_tm, &time_t); /* TODO: Handle error. */
	return time_tm;
}
