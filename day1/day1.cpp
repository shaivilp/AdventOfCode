#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>

using namespace std;

int main(){
    //Part 1
    vector<int> L1;
    vector<int> L2;

    //Read input
    ifstream infile("input.txt");
    if(!infile){
        cerr << "File could not be opened";
        exit(1);
    }

    string line;
    while(getline(infile, line)){
        istringstream iss(line);
        int left, right;

        if(iss >> left >> right){
            L1.push_back(left);
            L2.push_back(right);
        } else {
            cerr << "Error: Malformed line: " << line << endl;
            exit(1);
        }
    }

    infile.close();

    //Sort the lists
    sort(L1.begin(), L1.end());
    sort(L2.begin(), L2.end());

    int total_distance = 0;
    for(int i = 0; i < L1.size(); i++){
        total_distance += abs(L1[i] - L2[i]);
    }

    cout << "[Part 1] Total distance: " << total_distance << endl;

    //Part 2
    int similarity_score = 0;

    for(int i = 0; i < L1.size(); i++){
        int num = L1[i];
        
        //Find the number of times num appears in L2
        int num_count = count(L2.begin(), L2.end(), num);

        similarity_score += num * num_count;
    }

    cout << "[Part 2] Similarity score: " << similarity_score << endl;

    return 0;
}   