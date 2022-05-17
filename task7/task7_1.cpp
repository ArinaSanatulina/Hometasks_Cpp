#include<iostream>
#include<random>
#include<chrono>
#include<vector>
#include<thread>
#include<algorithm>
#include<future>

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

class Threads_Guard
{
public:

	explicit Threads_Guard(std::vector < std::thread >& threads) :
		m_threads(threads)
	{}

	Threads_Guard(Threads_Guard const&) = delete;

	Threads_Guard& operator=(Threads_Guard const&) = delete;

	~Threads_Guard() noexcept
	{
		try
		{
			for (std::size_t i = 0; i < m_threads.size(); ++i)
			{
				if (m_threads[i].joinable())
				{
					m_threads[i].join();
				}
			}
		}
		catch (...)
		{
			// std::abort();
		}
	}

private:

	std::vector < std::thread >& m_threads;
};


double pi(int number_of_dots)
{
	auto seed = std::chrono::system_clock::now().time_since_epoch().count();

	std::default_random_engine engine(seed);

	std::uniform_real_distribution <> distribution(-1, 1);

	std::vector<std::pair<double,double>> dots(number_of_dots);

	std::generate(std::begin(dots), std::end(dots), [&distribution, &engine]() {  return std::pair<double,double> (distribution(engine), distribution(engine)); });

	auto dots_in_circle = std::count_if(std::begin(dots), std::end(dots), [](auto x) {if ((x.first * x.first + x.second * x.second) <= 1) { return 1; } else { return 0; }});

	return dots_in_circle*4.0/number_of_dots;

}

struct count_block 
{
	int operator()(int number_of_dots, int seed)
	{
		std::default_random_engine engine(seed);

		std::uniform_real_distribution <> distribution(-1, 1);

		std::vector<std::pair<double, double>> dots(number_of_dots);

		std::generate(std::begin(dots), std::end(dots), [&distribution, &engine]() {  return std::pair<double, double>(distribution(engine), distribution(engine)); });

		return  std::count_if(std::begin(dots), std::end(dots), [](auto x) {if ((x.first * x.first + x.second * x.second) <= 1) { return 1; } else { return 0; }});
	}

};
	

double parallel_pi(int number_of_dots)
{
	const auto num_threads =
		std::thread::hardware_concurrency();

	const auto dots_thread = number_of_dots / num_threads + 1;

	std::vector < std::future < int > > futures(num_threads - 1);
	std::vector < std::thread >		  threads(num_threads - 1);

	Threads_Guard guard(threads);

	for (auto i = 0; i < (num_threads - 1); ++i)
	{
		
		std::packaged_task < int(int, int) > task{
			count_block() };

		futures[i] = task.get_future();
		threads[i] = std::thread(std::move(task), dots_thread , std::chrono::system_clock::now().time_since_epoch().count()+i);

	}

	auto result = count_block()(dots_thread, std::chrono::system_clock::now().time_since_epoch().count() + num_threads);


	for (auto i = 0; i < num_threads - 1; ++i)
	{
		result += futures[i].get();
	}

	return result * 4.0 / number_of_dots;

}

int main()
{
	auto number_of_dots = 10000000;

	double p1;

	double p2;

	{
		Timer t("default");

		p1 = pi(number_of_dots);
	}

	{
		Timer t("parallel");

		p2 = parallel_pi(number_of_dots);
	}

	std::cout << p1 << '\n' << p2;
	
	return 0;
}