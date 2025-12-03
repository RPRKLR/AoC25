// #include "../utils/utils.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include "../utils/utils.hpp"
#include <unordered_set>
using namespace std;

long long sum_invalid_ids(
    const std::vector<std::string> &min_val,
    const std::vector<std::string> &max_val)
{
    long long total = 0;

    static long long pow10[20];
    static bool init = false;
    if (!init)
    {
        pow10[0] = 1;
        for (int i = 1; i < 20; i++)
            pow10[i] = pow10[i - 1] * 10LL;
        init = true;
    }

    auto digit_count = [](long long x)
    {
        int d = 1;
        while (x >= 10)
        {
            x /= 10;
            d++;
        }
        return d;
    };

    for (size_t idx = 0; idx < min_val.size(); idx++)
    {
        long long a = stoll(min_val[idx]);
        long long b = stoll(max_val[idx]);

        int da = digit_count(a);
        int db = digit_count(b);

        unordered_set<long long> seen;
        seen.reserve(4096);

        for (int digits = da; digits <= db; digits++)
        {
            for (int L = 1; L <= digits / 2; L++)
            {
                if (digits % L != 0)
                    continue;

                int k = digits / L;
                if (k < 2)
                    continue;

                long long start = pow10[L - 1];
                long long end = pow10[L] - 1;

                long long tenL = pow10[L];

                for (long long base = start; base <= end; base++)
                {
                    long long X = 0;

                    for (int rep = 0; rep < k; rep++)
                    {
                        // overflow-safe multiply
                        if (X > (LLONG_MAX - base) / tenL)
                        {
                            X = LLONG_MAX;
                            break;
                        }
                        X = X * tenL + base;
                    }

                    if (X < a || X > b)
                        continue;

                    if (seen.insert(X).second)
                        total += X;
                }
            }
        }
    }

    return total;
}

int main(int argc, char *argv[])
{
    fstream input("day2/input.txt");
    vector<int> right, left;
    string input_str;
    int temp_int;
    getline(input, input_str);
    cout << input_str << endl;
    char separator = ',';
    char splitter = '-';
    stringstream ss(input_str);
    string temp_str;
    vector<string> separated_values;
    vector<string> min_val;

    vector<string> max_val;
    while (getline(ss, temp_str, separator))
    {
        string separation;
        stringstream sss(temp_str);
        int i = 0;
        while (getline(sss, separation, splitter))
        {
            if (i == 0)
            {
                min_val.push_back(separation);
                i++;
            }
            else
            {
                max_val.push_back(separation);
                i--;
            }
        }
    }

    for (size_t i = 0; i < min_val.size(); i++)
    {
        long long minv = stoll(min_val[i]);
        long long maxv = stoll(max_val[i]);

        int min_digits = to_string(minv).size();
        int max_digits = to_string(maxv).size();

        for (int digits = min_digits; digits <= max_digits; digits++)
        {
            if (digits % 2 != 0)
                continue;

            int half = digits / 2;
            long long start = pow(10, half - 1);
            long long end = pow(10, half) - 1;

            for (long long h = start; h <= end; h++)
            {
                long long number = h * pow(10, half) + h;

                if (number < minv || number > maxv)
                    continue;

                part1_solution_ += number;
                std::cout << number << "\n";
            }
        }
    }
    part2_solution_ = sum_invalid_ids(min_val, max_val);

    printSolutionPart1();
    printSolutionPart2();

    return 0;
}