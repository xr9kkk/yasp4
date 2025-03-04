#include "Container.h"
#include <Windows.h>

//������ ���� ��������� 9 ������ 
//19.�) ��������� ��� ������������� ����� �� ���������� ��������������� ����� std::vector

std::fstream file_file_for(const std::string& fname, const int N, const int M);

std::fstream fill_file_generate(const std::string& fname, const int N, const int M);

void read_and_check(size_t& input, size_t min = 0, size_t max = MAXINT);


size_t menu();
size_t fill_menu();
size_t modify_menu();
size_t output_menu();

std::string choose_file();

std::pair<iterator, iterator> read_borders(Container& cont);

std::vector<int> modify(Container& cont);

int main()
{
	setlocale(LC_ALL, "ru");
	while (true)
	{
		std::cout << "\n��������� ���� ����������� N ������ ���������� ������� � ��������� �� -M �� M\n\n"
			<< "������� ����� N: ";
		size_t N{};
		read_and_check(N, 1);

		std::cout << "������� ����� M: ";
		size_t M{};
		read_and_check(M, 1);

		std::string fname = choose_file();
		std::fstream file = (fill_menu() == 1) ? file_file_for(fname, N, M) : fill_file_generate(fname, N, M);

		Container container(file);
		file.close();

		bool action = true;
		while (action)
		{
			switch (menu())
			{
			case 1: // modify
			{
				std::vector<int> new_vec = modify(container);
				if (new_vec.empty())
					std::cout << "���������������� ��������� ����";
				else
					for (int elem : new_vec)
						std::cout << elem << ' ';
				std::cout << '\n';
				break;
			}
			case 2: // sum
				std::cout << "����� ����� " << container.sum() << '\n';
				break;
			case 3: // average
				std::cout << "������� �������������� ����� " << container.average() << '\n';
				break;
			case 4: // print
				if (output_menu() == 1)
					container.print_to_file(choose_file());
				else
					container.print_to_console();
				break;
			case 0:
				action = false;
				break;
			}
		}

		char is_exit{};
		std::cout << "��������� ���������� ���������? 0, ���� ��\n-> ";
		std::cin >> is_exit;
		if (is_exit == '0')
			break;
	}
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

void read_and_check(size_t& input, size_t min, size_t max)
{
	while (!(std::cin >> input) || input > max || input < min)
	{
		std::cout << "peredelivay! \n";
		std::cin.clear();
		std::cin.ignore(255, '\n');
		std::cout << "->";
	}
}

size_t menu()
{
	std::cout << "�������� ��������:\n"
		<< "1. �������������� ���������\n"
		<< "2. ��������� ����� ���������\n"
		<< "3. ��������� ������� ��������������\n"
		<< "4. ������� ���������� ����������\n"
		<< "0. �����\n";
	size_t choice{};
	read_and_check(choice, 0, 4);
	return choice;
}

size_t fill_menu()
{
	std::cout << "�������� ����� ���������� �����:\n"
		<< "1. ������������ ����\n"
		<< "2. ������������ std::generate\n";
	size_t choice{};
	read_and_check(choice, 1, 2);
	return choice;
}

size_t modify_menu()
{
	std::cout << "�������� ����� �����������:\n"
		<< "1. ������������ ���� for\n"
		<< "2. ������������ std::transform\n"
		<< "3. ������������ std::for_each\n";
	size_t choice{};
	read_and_check(choice, 1, 3);
	return choice;
}

size_t output_menu()
{
	std::cout << "�������� ����� ������:\n"
		<< "1. � ����\n"
		<< "2. � �������\n";
	size_t choice{};
	read_and_check(choice, 1, 2);
	return choice;
}


std::pair<iterator, iterator> read_borders(Container& container)
{
	std::pair<iterator, iterator> result;
	while (true)
	{
		size_t left{}, right{};
		std::cout << "������� ����� ������� ���������: ";
		read_and_check(left, 0);
		std::cout << "������� ������ ������� ���������: ";
		read_and_check(right, 0);

		if (left > right && right)
			std::cout << "������: ����� ������� ������ ������. ��������� ����.\n";
		else
		{
			if (!left)
				result.first = container.begin();
			else
				result.first = container.get_iterator(left);

			if (!right)
				result.second = container.end();
			else
				result.second = container.get_iterator(right);

			break;
		}
	}
	return result;
}


std::vector<int> modify(Container& cont)
{
	std::pair<iterator, iterator> borders = read_borders(cont);
	size_t choice = modify_menu();
	if (choice == 1)
		return cont.modify_for(borders.first, borders.second);
	if (choice == 2)
		return cont.modify_transform(borders.first, borders.second);
	return cont.modify_for_each(borders.first, borders.second);
}

std::string choose_file()
{
	std::cout << "Input filename: ";
	std::string fname;
	std::cin >> fname;
	return fname;
}





