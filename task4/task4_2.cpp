#include<iostream>
#include <vector>
#include <chrono>
#include <random>
#include <set>
#include <string>
#include <functional>
#include <unordered_set>
#include <fstream>

template < typename T >
void hash_combine(std::size_t& seed, const T& value) noexcept       //функция генерирования хэша
{
    seed ^= std::hash < T >()(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

template < typename T >
void hash_value(std::size_t& seed, const T& value) noexcept //функция вычисления хэша
{
    hash_combine(seed, value);
}

template < typename T, typename ... Types >
void hash_value(std::size_t& seed, const T& value, const Types & ... args) noexcept
{
    hash_combine(seed, value);
    hash_value(seed, args...);
}

template < typename ... Types >
std::size_t hash_value(const Types & ... args) noexcept
{
    std::size_t seed = 0;
    hash_value(seed, args...);
    return seed;
}

std::set < std::string > make_random_words(std::size_t N, std::size_t length) // функция создания рандомных слов, length = 10 - достаточно хорошо
{
    std::uniform_int_distribution <> letter(97, 122);
    std::default_random_engine e(static_cast <std::size_t> (
        std::chrono::system_clock::now().time_since_epoch().count()));

    std::set < std::string > words;

    for (std::string s(length, '_'); std::size(words) < N; words.insert(s))
        for (auto& c : s)
            c = letter(e);

    return words;
}

int main()
{
    const int dot_count = 100; //количество точек

    const int step = 10000; //шаг

    const int word_length = 10; //длина слова


    std::vector<int> N(dot_count);  //вектор точек

    N[0] = 1;

    for (auto i = 1; i < dot_count; ++i)    //заполнение вектора точек
    {
        N[i] = i * step;
    }

    std::set<std::string> words = make_random_words(dot_count * step, word_length);

    std::ofstream result;

    result.open("C:\\Progs_c\\cols.txt");

    for (auto n : N) //цикл по точкам
    {
        std::set<std::size_t>hashes; //контейнер для Хэшей

        int count = 0;

        int collisions = 0;

        for (auto word : words) //цикл по каждому слову
        {
            if (count >= n) 
            {
                break;
            }

            ++count;

            if (!(hashes.insert(hash_value(word, rand())).second))
            {
                ++collisions;
            }

        }

        result << collisions << ' ';
    }

    result.close();

    return 0;
}