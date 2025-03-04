#include "Container.h"

int Container::_sum_non_odd(iterator begin, iterator end)   
{
    int count{};
    for (iterator ptr = begin; ptr != end; ptr++)
    {
        if (*ptr < 0)
            count += 1;
    }

    return count;
}

Container::Container(std::fstream& file)
{
    int x{};
    while (file >> x)
    {
        vector.push_back(x);
    }
}


std::vector<int> Container::modify_for(iterator begin, iterator end)
{
    std::vector<int> result;
    int count = _sum_non_odd(begin, end);

    result.reserve(std::distance(begin, end) + 1);

    for (iterator ptr = begin; ptr != end; ++ptr) {
        int val = *ptr > 0 ? *ptr + count : *ptr;
        result.push_back(val);
    }
        
    return result;
}

std::vector<int> Container::modify_transform(iterator begin, iterator end)
{
    std::vector<int> result(begin, end); 
    int count = _sum_non_odd(begin, end);

    std::transform(begin, end, result.begin(), [count](int x) {
        return x > 0 ? x + count : x; 
        });

    return result;
}

std::vector<int> Container::modify_for_each(iterator begin, iterator end)
{
    std::vector<int> result;
    int count = _sum_non_odd(begin, end);

    result.reserve(std::distance(begin, end)); 

    std::for_each(begin, end, [count, &result](int x) {
        if (x > 0) x += count; 
        result.push_back(x);   
        });

    return result;
}

iterator Container::get_iterator(const size_t number)
{
    iterator end = vector.end();
    size_t i{ 1 };
    for (iterator ptr = vector.begin(); ptr != end; ++ptr, ++i)
        if (i == number)
            return ptr;
    return end;
}

void Container::print_to_console()
{
    for (int elem : vector)
        std::cout << elem << " ";
    std::cout << std::endl;
}

void Container::print_to_file(const std::string& filename)
{
    std::ofstream file(filename);
    for (int elem : vector)
        file << elem << " ";
    file.close();
}




int Container::sum()
{
    int sum{};
    std::for_each(vector.begin(), vector.end(), [&sum](int x) {sum += x; });
    return sum;
}

double Container::average()
{
    int sum{}, count{};
    std::for_each(vector.begin(), vector.end(), [&sum, &count](int x) {sum += x; ++count; });
    if (!count)
        return 0;
    return static_cast<double>(sum) / count;
}

std::ostream& operator<<(std::ostream& out, const Container& cont)
{
    for (int elem : cont.vector)
        out << elem << ' ';
    out << std::endl;
    return out;
}
