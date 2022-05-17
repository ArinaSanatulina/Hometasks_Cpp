#include <iostream>
#include <vector>
#include <set>
#include <random>
#include <chrono>

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

			/*std::cout << m_name << ": " << m_duration.count() << " microseconds" << std::endl;*/
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
			is_working = false;
		}
	}

	void start()
	{
		if (!is_working)
		{
			is_working = true;
			m_begin = clock_t::now();
		}
	}

	void restart()
	{
		is_working = true;
		m_duration = std::chrono::microseconds::zero();
		m_begin = clock_t::now();
	}

	int get_time()
	{
		stop();
		start();

		return m_duration.count();

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
	const int length = 1000000;						//длина контейнера
	
	const int iterations = 20;						//количество итераций
	
	double avg_vector_time = 0;						//переменная для среднего времени вектора
		
	double avg_set_time = 0;						//переменная для среднего времени set'a

	std::vector<int> filler(length);			//создание контейнера под филлер

	std::vector<int> vector_time(iterations);	//создание контейнера для времени вектора в каждую итерацию

	std::vector<int> set_time(iterations);	//создание контейнера для времени set'a в каждую итерацию

	std::vector <int> vector;			//создание контейнера типа vector для исследования

	std::set <int> set;					//создание контейнера типа set для исследования

	for (auto i = 0; i < length; ++i)	//цикл по заполнению filler'a
	{
		filler[i] = i;
	}

	std::shuffle(std::begin(filler), std::end(filler), std::default_random_engine(length)); //перемешивание элементов filler'a

	for(auto i = 0; i<iterations;++i)		//цикл на iterations итераций
	{
		{
			Timer t("vector");			//запуск отчета времени

			for (auto n : filler)		//вставка в vector length раз
			{
				vector.push_back(n);
			}

			std::sort(std::begin(vector), std::end(vector)); //сортировка vector

			vector_time[i] = t.get_time(); // конец отчета времени
		}

		vector = std::vector<int>();	//очистка контейнера vector

		{								//всё аналогично vector'у
			Timer t("set");

			for (auto n : filler)
			{
				set.insert(n);
			}

			set_time[i] = t.get_time();
		}

		set = std::set<int>();

	}

	std::cout <<"Vector time: ";


	for (auto n : vector_time)			
	{
		avg_vector_time += n * 1.0;			//подсчет среднего времени vector

		std::cout << n << ' ';				//вывод времени для каждой итерации vector'a
	}

	std::cout << std::endl;

	avg_vector_time /= iterations * 1.0;

	std::cout << "Set time: ";


	for (auto n : set_time)				//аналогично vector'у
	{
		avg_set_time += n * 1.0;

		std::cout << n << ' ';
	}

	std::cout << std::endl;

	avg_set_time /= iterations * 1.0;

	std::cout << "Average vector time: " << avg_vector_time << std::endl;

	std::cout << "Average set time: " << avg_set_time << std::endl;

	if (avg_set_time < avg_vector_time)	//определение лидера
		{
		std::cout << "leader is set";
		}
	else 
		{
		std::cout << "leader is vector";
		}
		 
	return 0;
}