#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include "../utils/utils.hpp"
using namespace std;

int main(int argc, char *argv[])
{
    fstream input("day5/input.txt");
    vector<string> banks;
    string temp_str;
    int temp_int;
    vector<long long> min, max;
    vector<long long> items, full_items;
    vector<long long> full_min, full_max;
    char splitter = '-';
    while (getline(input, temp_str))
    {
        std::size_t found = temp_str.find("-");
        if (found != std::string::npos)
        {
            stringstream ss(temp_str);
            int i = 0;
            string separation;
            while (getline(ss, separation, splitter))
            {
                if (i == 0)
                {
                    min.push_back(stoll(separation) / 100000000);
                    full_min.push_back(stoll(separation));
                    i++;
                }
                else
                {
                    max.push_back(stoll(separation) / 100000000);
                    full_max.push_back(stoll(separation));
                    i--;
                }
            }
        }
        else if (temp_str == "")
        {
            continue;
        }
        else
        {
            items.push_back(stoll(temp_str) / 100000000);
            full_items.push_back(stoll(temp_str));
        }
    }

    for (int i = 0; i < items.size(); i++)
    {
        for (int j = 0; j < min.size(); j++)
        {
            if (max[j] < items[i])
                continue;

            if (items[i] >= min[j] && items[i] <= max[j])
            {
                part1_solution_++;
                break;
            }
        }
    }

    // long long biggest = 0;
    // long long smallest = INFINITY;
    // for (int i = 0; i < full_min.size(); i++)
    // {
    //     if (biggest <= full_max[i])
    //         biggest = full_max[i];
    //     if (smallest >= full_min[i])
    //         smallest = full_min[i];
    // }
    // cout << "smallest: " << smallest << " biggest: " << biggest;
    // vector<long long> available_ranges;
    // for (int i = 0; i < min.size(); i++)
    // {
    //     for (long long j = min[i]; j <= max[i]; j++)
    //     {
    //         if (std::find(available_ranges.begin(), available_ranges.end(), j) == available_ranges.end())
    //         {
    //             available_ranges.push_back(j);
    //             part2_solution_++;
    //         }
    //     }
    // }
    printSolutionPart1();
    printSolutionPart2();
    return 0;
}