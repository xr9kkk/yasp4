#include "Container.h"
#include <Windows.h>

std::fstream file_file_for(const std::string& fname, const int N, const int M);

std::fstream fill_file_generate(const std::string& fname, const int N, const int M);

template <typename T>
T get_valid_input(const std::string& prompt, size_t min = 0, size_t max = MAXINT);

size_t menu();
size_t fill_menu();
size_t modify_menu();
size_t output_menu();

std::string choose_file();

std::pair<iterator, iterator> read_borders(Container& cont);

std::vector<int> modify(Container& cont);

int main()
{
	std::cout << "Penis\n" << std::endl;
	return 0;
}



std::fstream file_file_for(const std::string& fname, const int N, const int M)
{
	srand(GetTickCount());
	std::fstream result(fname, std::ios::in | std::ios::out | std::ios::trunc);
	for (int i = 0; i < N; ++i)
		result << rand() % (M * 2) - M << ' ';
	result.seekg(0);
	return result;
}

std::fstream fill_file_generate(const std::string& fname, const int N, const int M)
{
	srand(GetTickCount());
	std::fstream result(fname, std::ios::in | std::ios::out | std::ios::trunc);
	std::generate_n(std::ostream_iterator<int>(result, " "), N,
		[M]() {return rand() % (M * 2) - M; });
	result.seekg(0);
	return result;
}

template <typename T>
T get_valid_input(const std::string& prompt)
{
	T value;
	while (true) {
		std::cout << prompt;
		std::cin >> value;

		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Failed to open.\n";
		}
		else {
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			return value;
		}
	}
}