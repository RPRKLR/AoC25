// #include "../utils/utils.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include "../utils/utils.hpp"
#include <unordered_set>
using namespace std;

vector<string> solve(vector<string> rows)
{
    string output_row;
    vector<string> output_rows;
    int counter = 0;
    for (int i = 0; i < rows.size(); ++i)
    {
        for (int j = 0; j < rows[i].size(); j++)
        {
            if (rows[i][j] == '.')
            {
                output_row += rows[i][j];
                // cout << counter << endl;
                continue;
            }
            for (int x = j - 1; x <= j + 1; x++)
            {
                if (x < 0 || x > rows.size() - 1)
                    continue;
                for (int y = i - 1; y <= i + 1; y++)
                {
                    // cout << "x: " << x + 1 << " y: " << y + 1 << endl;
                    if (y < 0 || y > rows[i].size() - 1)
                        continue;
                    if (x == j && y == i)
                        continue;
                    if (rows[y][x] == '@')
                        counter++;
                }
            }
            // cout << counter << endl;
            if (counter < 4)
            {
                output_row += 'x';
            }
            else
            {
                output_row += rows[i][j];
            }
            counter = 0;
        }
        output_rows.push_back(output_row);
        output_row = "";
    }
    return output_rows;
}

int count(vector<string> input)
{
    int output = 0;
    for (int i = 0; i < input.size(); i++)
    {
        for (int j = 0; j < input[i].size(); j++)
        {
            if (input[i][j] == 'x')
            {
                output++;
            }
            cout << input[i][j];
        }
        cout << endl;
    }
    return output;
}

int main(int argc, char *argv[])
{
    fstream input("day4/input.txt");
    vector<string> rows;
    string input_str;
    int temp_int;
    while (getline(input, input_str))
    {
        rows.push_back(input_str);
        cout << input_str << endl;
    }
    vector<string> output_rows = solve(rows);

    part1_solution_ = count(output_rows);
    vector<string> p2_rows = rows;

    for (int i = 0; i < 85; i++)
    {
        p2_rows = solve(p2_rows);
    }

    part2_solution_ = count(p2_rows);

    printSolutionPart1();
    printSolutionPart2();

    return 0;
}