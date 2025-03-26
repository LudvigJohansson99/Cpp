#include "bintree.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <array>
#include <climits>
#include <iomanip>
#include <chrono>
using namespace std;

void fill_binary_tree(Node*& root, const std::vector<int>& v) {
    for (int val : v) {
        insert(root, val, val);
    }
}

int main(){
    //std::vector<int> numbers(9000);
    std::vector<int> numbers(5000);
    std::array<std::pair<int, int>, 800> results; //Görs till 800

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 rng(seed);
    //std::shuffle(numbers.begin(), numbers.end(), rng);

    for (int l = 0; l < numbers.size(); l++) {
        numbers[l] = l + 1;
    }

    //std::mt19937 rng(990401);
    std::shuffle(numbers.begin(), numbers.end(), rng);
    int resultIndex = 0;
    for (int i = 0; i < results.size(); i++) {
        //Skapar nod och fyller trädet med siffror från vectorn
        std::shuffle(numbers.begin(), numbers.end(), rng);
        //std::next_permutation(numbers.begin(), numbers.end());

        //std::shuffle(numbers.begin(), numbers.end(), rng);
        Node *root = nullptr;
        fill_binary_tree(root, numbers);

        //Kollar max och minHeight och lägger till dom i result arrayn
        unsigned int maxHeight = max_height(root);
        unsigned int minHeight = min_height(root);

        results[resultIndex] = std::make_pair(maxHeight, minHeight);
        resultIndex++;
    
        delete_tree(root);
    }

    //The average height of the tree in 800 iterations
    double sumMaxHeight = 0.0;
    for (int j = 0; j < results.size(); j++) {
        sumMaxHeight += results[j].first;
    }
    double avgMaxHeight = (sumMaxHeight / results.size());
    cout << "Average max height is: " << std::fixed << std::setprecision(2) << avgMaxHeight << endl;
    

    //The average minimum height
    double sumMinHeight = 0;
    for (int k = 0; k < results.size(); k++) {
        sumMinHeight += results[k].second;
    }
    double avgMinHeight = (sumMinHeight) / results.size();
    cout << "Average min height is: " << std::fixed << std::setprecision(2) << avgMinHeight << endl;

    //The highest maximum height of tree
    unsigned int highestMaxHeight = 0;
    for (const auto& result : results) {
        unsigned int maxHeight = result.first;
        if (maxHeight > highestMaxHeight) {
            highestMaxHeight = maxHeight;
        }
    }
    cout << "The highest maximum height of tree: " << highestMaxHeight << endl;


    //The lowest minimum height
    unsigned int lowestMinHeight = results[0].second;
    for (const auto& result : results) {
        if (result.second < lowestMinHeight) {
            lowestMinHeight = result.second;
        }
    }
    cout << "The lowest minimum height of tree: " << lowestMinHeight << endl;

    //The average difference between minimum and maximum height
    double sumHeightDiff = 0.0;
    for (int i = 0; i < results.size(); i++) {
        int heightDiff = results[i].first - results[i].second;
        sumHeightDiff += heightDiff;
    }
    double avgHeightDiff = sumHeightDiff / results.size();
    cout << "Average height difference is: " << std::fixed << std::setprecision(2) << avgHeightDiff << endl;


    //The greatest difference between minimum and maximum height
    //The lowest difference between minimum and maximum height
    int greatestDiff = 0;
    //Säkerställ att första jämförelsen blir true
    int lowestDiff = INT_MAX;

    for (int i = 0; i < results.size(); i++) {
        int minHeight = results[i].second;
        int maxHeight = results[i].first;

        // calculate the difference between min and max heights
        int diff = maxHeight - minHeight;

        // update greatestDiff if necessary
        if (diff > greatestDiff) {
            greatestDiff = diff;
        }

        // update lowestDiff if necessary
        if (diff < lowestDiff) {
            lowestDiff = diff;
        }
    }

    // print the greatest and lowest differences
    std::cout << "The greatest difference between minimum and maximum height is: " << greatestDiff << std::endl;
    std::cout << "The lowest difference between minimum and maximum height is: " << lowestDiff << std::endl;
}