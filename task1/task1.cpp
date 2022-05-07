#include <boost/lambda/lambda.hpp>
#include <iostream>
#include <iterator>
#include <algorithm>

int main()
{
    using namespace boost::lambda;
    typedef std::istream_iterator<int> in;

    
    std::cout << ("Arina and her groupmates are great students that is how many times:");
    std::for_each(
        in(std::cin), in(), std::cout << "  Or so many: " << (_1 * 100)<< " \n  ");

}
