#pragma once

#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>

using iterator = std::vector<int>::iterator;


class Container
{
private:
	std::vector <int> vector{};
	int _sum_non_odd(iterator begin, iterator end);

public:

	Container() {};
	Container(std::fstream& file);
	std::vector<int> modify_for(iterator begin, iterator end);
	std::vector<int> modify_transform(iterator begin, iterator end);
	std::vector<int> modify_for_each(iterator begin, iterator end);
	
	iterator end() { return vector.end(); };
	iterator begin() { return vector.begin(); };

	iterator get_iterator(const size_t number);
	
	void print_to_console();
	void print_to_file(const std::string& filename);
	friend std::ostream& operator<<(std::ostream& out, const Container& cont);

	int sum();
	double average();



};

