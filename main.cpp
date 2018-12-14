#include <iostream>
#include <iterator>
#include <algorithm>
#include <string>
#include <vector>
#include <list>
#include <chrono>
#include "partitions.hpp"

namespace {
    template<typename T>
    void prepareRndInput(std::vector<T>& data, std::size_t size) {
        auto tp = std::chrono::system_clock::now();
        std::srand(tp.time_since_epoch().count());
        for(std::size_t i = 0; i < size; ++i) {
            std::size_t len = std::size_t(1) + std::rand() % 100;
            T t;
            for(std::size_t i = 0; i < len; ++i) {
                char c = 'a' + std::rand() % 26;
                t += c;
            }
            data.emplace_back(t);
        }
    }

    void prepareRndInput(std::vector<int>& data, std::size_t size, int modulo = 1000) {
        auto tp = std::chrono::system_clock::now();
        std::srand(tp.time_since_epoch().count());
        for(std::size_t i = 0; i < size; ++i) {
            std::size_t num = std::rand() % modulo;
            data.emplace_back(num);
        }
    }

    template<typename T>
    void printInput(const std::vector<T>& data) {
        std::cout << "Input:" << std::endl;
        std::copy(data.begin(), data.end(), std::ostream_iterator<T>(std::cout, " "));
        std::cout << std::endl << std::endl;
    }
}

int main(int /*argc*/, char** /*argv*/)
{
    std::vector<std::string> input;
    //std::vector<int> input;

    prepareRndInput(input, 100);
    printInput(input);

    //Divide integers with respect to remainder after division by 17
    //extstd::partition<int> partitions(input, [](int x) { return x % 17; });

    //Divide strings with respect to length
    //extstd::partition<std::string> partitions(input, [](const std::string& x) { return x.length(); });

    //Divide strings with respect to whether or not they contain substring 'foo'
    //extstd::partition<std::string> partitions(input, [](const std::string& x) { return std::string::npos != x.find("foo"); });

    //Divide strings with respect to first character
    extstd::partition<std::string, char> partitions(input, [](const std::string& x) {
                                                                try {
                                                                    return x.at(0);
                                                                } catch(const std::out_of_range& e) {
                                                                    return ' ';
                                                                }
                                                            });

    partitions.print();


    partitions.for_each([](const char& /* key */, std::string& val) {
        std::transform(val.begin(), val.end(), val.begin(), ::toupper);
    });

    partitions.print();


    try {
        partitions.for_each_nth(2, [](const char& /* key */, std::string& val) {
            val = "!!!";
        });
    } catch(const std::out_of_range& e) {
        std::cout << e.what() << std::endl;
    }

    partitions.print();


    partitions.for_each_nth_nonthrow(2, [](const char& /* key */, std::string& val) {
        val = "???";
    });

    partitions.print();

    return 0;
}
