#include <iostream>
#include <chrono>
#include <string>
#include <algorithm>
#include <random>
#include <array>
#include <vector>
#include <deque>
#include <list>
#include <forward_list>

class Timer
{
public:
	using clock_t = std::chrono::steady_clock;

	using time_point_t = clock_t::time_point;

	explicit Timer() : m_begin(clock_t::now()), m_duration(std::chrono::microseconds::zero()), is_working(true), m_name("Timer")
	{}

	explicit Timer(std::string name) :m_begin(clock_t::now()), m_duration(std::chrono::microseconds::zero()), is_working(true), m_name(name)
	{}

	~Timer() noexcept
	{
		try
		{
			stop();

			std::cout << m_name << ": " << m_duration.count() << " microseconds" << std::endl;
		}

		catch (const std::exception& e)
		{
			std::cerr << e.what() << '\n';
		}

		catch (...)
		{
			std::cerr << "Unknown timer error" << '\n';
		}

	}

	void stop()
	{
		if (is_working)
		{
			m_duration += std::chrono::duration_cast<std::chrono::microseconds> (clock_t::now() - m_begin);
		}

		is_working = false;
		
	}

	void start()
	{
		is_working = true;
		m_begin = clock_t::now();
	}

	void restart()
	{
		is_working = true;
		m_duration = std::chrono::microseconds::zero();
		m_begin = clock_t::now();
	}

	bool work()
	{
		return is_working;

	}
	std::string name()
	{
		return m_name;
	}

private:

	std::chrono::microseconds m_duration;
	time_point_t m_begin;
	std::string m_name;
	bool is_working;
};

int main()
{
	const int length = 100000;		 //������� ����� ������������������
	std::vector<int> filler(length);	//�������� ������� ������� ����� (�������)

	for (auto i = 0; i < length; ++i)		//���������� ������� ������� �� 0 �� length
	{
		filler[i] = i;
	}

	std::shuffle(std::begin(filler),std::end(filler), std::default_random_engine(length));	//������������ ������������������

	std::array<int, length> array;				//������ ������������������ ���� array

	std::vector<int> vector(filler);			//������� ������ � �������� � ���� ���������� filler

	std::deque<int> deque;						//������ ������������������ ���� deque

	std::list<int> list;						//������ ������������������ ���� list

	std::forward_list<int> forward_list;		//������ ������������������ ���� forward_list

	for (auto i = 0; i < length; ++i)			//������� ��������� filler �� ��� ��������� ���� �������������������
	{
		array[i] = filler[i];

		deque.push_back(filler[i]);

		list.push_back(filler[i]);

		forward_list.push_front(filler[length-1-i]);
	}

	{
		Timer t("array");								//������ ������ �������

		std::sort(std::begin(array),std::end(array));	//������ ����������
	}

	{
		Timer t("vector");

		std::sort(std::begin(vector), std::end(vector));
	}

	{
		Timer t("deque");

		std::sort(std::begin(deque), std::end(deque));
	}

	{
		Timer t("list");

		list.sort();
	}

	{
		Timer t("forward_list");

		forward_list.sort();
	}

	return 0;
}