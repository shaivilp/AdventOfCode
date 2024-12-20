#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <sstream>

using namespace std;

int main(){
    // Part 1
    // Read input
    ifstream infile("input.txt");
    if (!infile) {
        cerr << "File could not be opened";
        exit(1);
    }
    
    stringstream buffer;

    buffer << infile.rdbuf();
    string memory = buffer.str();

    int sum = 0;
    regex mul_regex(R"(mul\([0-9]{1,3},[0-9]{1,3}\)|do\(\)|don't\(\))");
    auto mul_regex_iter_begin = std::sregex_iterator(memory.begin(), memory.end(), mul_regex);
    auto mul_regex_iter_end = std::sregex_iterator();
    regex num_regex(R"(\b[0-9]{1,3}\b)");
    bool mulEnabled = true;

    for (sregex_iterator i = mul_regex_iter_begin; i != mul_regex_iter_end; i++) {
        smatch match = *i;
        string s_match = match.str();
        if (s_match == "do()") mulEnabled = true;
        if (s_match == "don't()") mulEnabled = false;
        auto num_regex_iter_begin = sregex_iterator(s_match.begin(), s_match.end(), num_regex);
        auto num_regex_iter_end = sregex_iterator();
        vector<int> two_num;
        for (sregex_iterator j = num_regex_iter_begin; j != num_regex_iter_end; j++) {
            smatch num = *j;
            string num_s_match = num.str();
            two_num.push_back(stoi(num_s_match)); 
        }
        if (two_num.size() == 2 && mulEnabled){
           sum += two_num[0]*two_num[1];
        }
    } 

    cout << "Total sum after mul: " << sum << endl;

    return 0;
}
