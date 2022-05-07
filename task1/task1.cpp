#include <boost/lambda/lambda.hpp>
#include <iostream>
#include <iterator>
#include <algorithm>

int main()
{
    using namespace boost::lambda;
    typedef std::istream_iterator<int> in;


    std::cout << ("Arina is a great student that is how many times:");
    std::for_each(
        in(std::cin), in(), std::cout << (_1 * 5) << " ");
}
