#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

// Function to check if a vector of numbers is decreasing or increasing
bool isSafe(const vector<int>& numbers) {
    if (numbers.size() < 2){
        return true;
    }

    bool isIncreasing = true;
    bool isDecreasing = true;

    for(int i = 1; i < numbers.size(); ++i){
        int diff = numbers[i] - numbers[i - 1];
        
        // Check if the difference satisfies the condition
        if(diff < 1 || diff > 3){
            isIncreasing = false;
        }

        if(diff > -1 || diff < -3){
            isDecreasing = false;
        }

        // Early exit if neither increasing nor decreasing
        if(!isIncreasing && !isDecreasing){
            return false;
        }
    }

    return isIncreasing || isDecreasing;
}

// Function to determine if the report is safe (with Problem Dampener)
bool isSafeWithDampener(const vector<int>& report) {
    // Safe without removing any level
    if (isSafe(report)) {
        return true;
    }

    // Try removing each level and check if the remaining sequence is safe
    for (size_t i = 0; i < report.size(); ++i) {
        vector<int> modifiedReport = report;
        modifiedReport.erase(modifiedReport.begin() + i);
        if (isSafe(modifiedReport)) {
            return true;
        }
    }

    return false;
}

int main(){
    int num_safe = 0;
    int num_safe_after_dampener = 0;
    vector<string> records;

    //Read input
    ifstream infile("input.txt");
    if(!infile){
        cerr << "File could not be opened";
        exit(1);
    }

    string line;
    while(getline(infile, line)){
        records.push_back(line);
    }

    //Parse input line by line
    for(int i = 0; i < records.size(); i++){
        vector<int> nums;

        istringstream iss(records[i]);
        int num;

        while(iss >> num){
            nums.push_back(num);
        }

        // Check if the sequence is valid [Part 1]
        if(isSafe(nums)){
            num_safe++;
        }
        
        // Check if the sequence is valid after dampening one element [Part 2]
        if(isSafeWithDampener(nums)){
            num_safe_after_dampener++;
        }
    }

    cout << "[Part 1] Number of safe reports " << num_safe << endl;
    cout << "[Part 2] Number of safe reports after dampener " << num_safe_after_dampener << endl;

    return 0;
}