#include <iostream>
#include <string>
#include <iterator>
#include <chrono>
#include <random>
#include <vector>
#include <algorithm>
#include <numeric>

bool is_prime (int x)
{
	if (x < 2) return false;
	if (x == 2) return true;
	if (x % 2 == 0) return false;
	for (int i = 3; (i * i) <= x; i += 2)
	{
		if (x % i == 0) return false;
	}
	return true;
};


int main()
{
	// ¹1
	std::vector<int> p1(10);

	std::iota(std::begin(p1), std::end(p1), 1);

	//¹2

	std::copy(std::istream_iterator < int >(std::cin),std::istream_iterator < int >(), std::back_inserter(p1));

	//¹3

	std::shuffle(std::begin(p1), std::end(p1), std::default_random_engine(std::chrono::system_clock::now().time_since_epoch().count()));

	//¹4

	std::sort(std::begin(p1), std::end(p1));

	p1.erase(std::unique(std::begin(p1), std::end(p1)), std::end(p1));

	//¹5
	
	std::cout << "Number of odd numbers in p1: " << std::count_if(std::begin(p1), std::end(p1), [](auto x) { return x % 2 == 1; }) << std::endl;

	//¹6

	auto result = std::minmax_element(std::begin(p1), std::end(p1));

	std::cout << "Min in p1: " << *result.first << " Max in p1: " << *result.second << std::endl;

	//¹7

	std::cout << "The first prime number in p1: " << *std::find_if(std::begin(p1), std::end(p1), [](int x) {if (x < 2) return false;
	if (x == 2) return true;
	if (x % 2 == 0) return false;
	for (int i = 3; (i * i) <= x; i += 2)
	{
		if (x % i == 0) return false;
	}
	return true; }) << std::endl;

	//¹8

	std::transform(std::begin(p1), std::end(p1), std::begin(p1), [](auto x) {return x * x; });

	//¹9

	std::vector<int> p2(std::size(p1));

	std::generate(std::begin(p2), std::end(p2), std::default_random_engine(std::chrono::system_clock::now().time_since_epoch().count()));

	//¹10

	std::cout << "The sum of the numbers in p2: " << std::accumulate(std::begin(p2), std::end(p2), 0) << std::endl;

	//¹11

	std::fill(std::begin(p2), std::next(std::begin(p2), 3), 1);

	//¹12

	std::vector<int> p3(std::size(p1));

	std::transform(std::begin(p1), std::end(p1), std::begin(p2),
		std::begin(p3), [](auto lhs, auto rhs) { return lhs - rhs; });

	//¹13

	std::replace_if(std::begin(p3), std::end(p3), [](auto x) {return x < 0; }, 0);

	//¹14

	p3.erase(std::remove_if(std::begin(p3), std::end(p3), [](auto x) { return x  == 0; }), std::end(p3));

	//¹15

	std::reverse(std::begin(p3), std::end(p3));

	//¹16

	std::partial_sort(std::begin(p3), std::next(std::begin(p3), 3), std::end(p3),std::greater());

	std::cout << "Top 3 largest elements in p3: ";

	std::copy(std::begin(p3), std::next(std::begin(p3), 3), std::ostream_iterator < int >(std::cout, " "));

	std::cout << std::endl;

	//¹17

	std::sort(std::begin(p1), std::end(p1));

	std::sort(std::begin(p2), std::end(p2));

	//¹18
	std::vector<int>p4(std::size(p1)+std::size(p2));

	std::merge(std::begin(p1), std::end(p1), std::begin(p2), std::end(p2), std::begin(p4));

	//¹19

	auto range = std::equal_range(std::begin(p4), std::end(p4), 1);

	std::cout << '[' << std::distance(std::begin(p4),range.first) << ';' << std::distance(std::begin(p4),range.second) << ')';

	std::cout << std::endl;

	//¹20

	std::copy(std::cbegin(p1), std::cend(p1), std::ostream_iterator < int >(std::cout, " "));

	std::cout << std::endl;

	std::copy(std::cbegin(p2), std::cend(p2), std::ostream_iterator < int >(std::cout, " "));

	std::cout << std::endl;

	std::copy(std::cbegin(p3), std::cend(p3), std::ostream_iterator < int >(std::cout, " "));

	std::cout << std::endl;

	std::copy(std::cbegin(p4), std::cend(p4), std::ostream_iterator <int >(std::cout, " "));

	std::cout << std::endl;

	return 0;
}