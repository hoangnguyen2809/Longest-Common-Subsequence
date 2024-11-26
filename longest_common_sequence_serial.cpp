#include "core/utils.h"
#include <iomanip>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <cmath>
#include <fstream>


void lcs(std::string &s1, std::string &s2) {
    timer t1;
    double time_taken = 0.0;
    
    int m = s1.size();
    int n = s2.size();

    // Initializing a matrix of size (m+1)*(n+1)
    std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, 0));

    t1.start();
    // -------------------------------------------------------------------
    // Building dp[m+1][n+1] 
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (s1[i - 1] == s2[j - 1])
                dp[i][j] = dp[i - 1][j - 1] + 1;
            else
                dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
        }
    }
    // -------------------------------------------------------------------
    time_taken = t1.stop();

    std::cout << "thread_id, start_row, end_row, time_taken" << std::endl;
    std::cout << "0, " << time_taken << std::endl;

    std::cout << "Length of LCS: " << dp[m][n] << std::endl;
    std::cout << "Time taken (in seconds) : " << time_taken << "\n";
    
}

int main(int argc, char *argv[]) {
    cxxopts::Options options("Longest Common Subsequence", "Find the longest common subsequence between two strings");
    options.add_options("",
    {
        {"nThreads", "Number of Threads",
        cxxopts::value<uint>()->default_value(DEFAULT_NUMBER_OF_THREADS)},
        {"inputFile", "Input file path",
        cxxopts::value<std::string>()->default_value(
        "sample_inputs/input1.txt")},
    });

    auto cl_options = options.parse(argc, argv);
    uint n_threads = cl_options["nThreads"].as<uint>();
    std::string input_file_path = cl_options["inputFile"].as<std::string>();
    
    std::cout << "Number of Threads : " << 1 << std::endl;
    std::cout << "Reading input file\n";
    std::string filename = input_file_path;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open the file " << filename << std::endl;
        return 1;
    }

    std::string s1, s2;
    getline(file, s1);  // Read the first line
    getline(file, s2);  // Read the second line
    file.close();

    std::cout << "Length of String 1: " << s1.size() << std::endl;
    std::cout << "Length of String 2: " << s2.size() << std::endl;

    lcs(s1, s2);

    return 0;
}
