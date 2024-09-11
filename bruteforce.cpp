#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <string>
#include <sstream>

struct Item {
    std::string itemNumber;
    int profit;
    int weight;
};

class Bruteforce {
    int N;
    int W;
    std::vector<Item> items;

public:
    // Function to get the sum of weights of the given items
    int getSumOfWeights(const std::vector<Item>& items) {
        int sum = 0;
        for (const auto& item : items) {
            sum += item.weight;
        }
        return sum;
    }

    // Function to get the sum of profits of the given items
    int getSumOfProfits(const std::vector<Item>& items) {
        int sum = 0;
        for (const auto& item : items) {
            sum += item.profit;
        }
        return sum;
    }

    // Function to read the input file
    void readFile(const std::string& filePath) {
        std::ifstream myFile(filePath);
        if (!myFile.is_open()) {
            std::cerr << "An error occurred while reading the file!" << std::endl;
            return;
        }

        std::string firstLine;
        std::getline(myFile, firstLine);
        std::istringstream ss(firstLine);
        std::string buffer;

        ss >> N >> W;
        items.resize(N);

        for (int i = 0; i < N && std::getline(myFile, buffer); i++) {
            std::istringstream lineStream(buffer);
            lineStream >> items[i].itemNumber >> items[i].profit >> items[i].weight;
        }

        myFile.close();
    }

    // Function to write into the file
    void writeToFile(const std::string& filePath, const std::vector<Item>& itemsWithMaxProfit) {
        std::ofstream myWriter(filePath);
        if (!myWriter) {
            std::cerr << "An error occurred while writing into file!" << std::endl;
            return;
        }

        myWriter << itemsWithMaxProfit.size() << " " << getSumOfProfits(itemsWithMaxProfit) << " " << getSumOfWeights(itemsWithMaxProfit) << "\n";
        for (const auto& item : itemsWithMaxProfit) {
            myWriter << item.itemNumber << " " << item.profit << " " << item.weight << "\n";
        }

        myWriter.close();
    }

    // Function to return the items with max profit by bruteforce approach
    std::vector<Item> knapSackBruteForce(int n, int knapsackCapacity) {
        std::vector<Item> itemsWithMaxProfit;
        int maxProfit = 0;

        for (int j = 0; j < (1 << n); j++) {
            int sumOfWeights = 0;
            int sumOfProfits = 0;
            std::vector<Item> currentlySelectedItems;

            for (int i = 0; i < n; i++) {
                if ((j >> i) & 1) {
                    if ((sumOfWeights + items[i].weight) <= knapsackCapacity) {
                        sumOfWeights += items[i].weight;
                        sumOfProfits += items[i].profit;
                        currentlySelectedItems.push_back(items[i]);
                    } else {
                        break;
                    }
                }
            }

            if (maxProfit < sumOfProfits) {
                maxProfit = sumOfProfits;
                itemsWithMaxProfit = currentlySelectedItems;
            }
        }

        return itemsWithMaxProfit;
    }

    void run(const std::string& filePath) {
        readFile(filePath);
        auto itemsWithMaxProfit = knapSackBruteForce(N, W);
        writeToFile("output1.txt", itemsWithMaxProfit);
    }
};

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Wrong Usage! \nCorrect Usage: " << argv[0] << " <file_path>" << std::endl;
        return 1;
    }

    Bruteforce obj;
    obj.run(argv[1]);

    return 0;
}

