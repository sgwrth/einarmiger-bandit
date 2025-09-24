#ifndef UTIL_H
#define UTIL_H
#include <fstream>
#include <string>
#include <vector>

class Util
{
public:
	static void copy_file(std::ifstream& file_in, std::ofstream& file_out);
	static void delete_file(const std::string& filepath);
	static void rename_file(
		const std::string& filepath,
		const std::string& new_file_name
	);
	static std::string get_str_input();
	static void print_msg(const std::string& msg);
	static std::vector<std::string> split(const std::string& str, char delimiter);
	static struct tm get_time_tm();
};

#endif
