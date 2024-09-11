#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>

struct Item {
    std::string itemNumber;
    int profit;
    int weight;
    float profitPerUnit;

    // Custom constructor
    Item() : profit(0), weight(0), profitPerUnit(0.0f) {}

    // Comparator function for sorting
    bool operator<(const Item& other) const {
        return profitPerUnit > other.profitPerUnit;  // Descending order
    }
};

class IGreedy {
private:
    int N;
    int W;
    std::vector<Item> items;

public:
    void readFile(const std::string& filePath) {
        std::ifstream file(filePath);
        if (!file.is_open()) {
            std::cerr << "An error occurred while reading the file!" << std::endl;
            return;
        }
        file >> N >> W;
        items.resize(N);
        for (int i = 0; i < N; i++) {
            file >> items[i].itemNumber >> items[i].profit >> items[i].weight;
            items[i].profitPerUnit = static_cast<float>(items[i].profit) / items[i].weight;
        }
        file.close();
    }

    std::vector<Item> greedy4() {
        std::vector<Item> sortedItems = items; // Copy items to sort them
        std::sort(sortedItems.begin(), sortedItems.end()); // Sort based on profitPerUnit

        std::vector<Item> selectedItems;
        int sumOfWeights = 0;
        for (const auto& item : sortedItems) {
            if (sumOfWeights + item.weight <= W) {
                selectedItems.push_back(item);
                sumOfWeights += item.weight;
            }
        }
        return selectedItems;
    }

    Item getMaxBItem() {
        Item maxB;
        for (const auto& item : items) {
            if (item.profit > maxB.profit && item.weight <= W) {
                maxB = item;
            }
        }
        return maxB;
    }

    void writeToFile(const std::string& filename, const std::vector<Item>& itemsWithMaxProfit) {
        std::ofstream outFile(filename);
        if (!outFile.is_open()) {
            std::cerr << "Failed to open file for writing." << std::endl;
            return;
        }
        for (const auto& item : itemsWithMaxProfit) {
            outFile << item.itemNumber << " " << item.profit << " " << item.weight << "\n";
        }
        outFile.close();
    }

    int getSumOfProfits(const std::vector<Item>& items) {
        int sum = 0;
        for (const auto& item : items) {
            sum += item.profit;
        }
        return sum;
    }

    void run(const std::string& filePath) {
        readFile(filePath);
        auto itemsWithGreedy4Profit = greedy4();
        int greedy4Profit = getSumOfProfits(itemsWithGreedy4Profit);
        auto maxBItem = getMaxBItem();

        std::vector<Item> itemsWithMaxProfit;
        if (greedy4Profit > maxBItem.profit) {
            itemsWithMaxProfit = itemsWithGreedy4Profit;
        } else {
            itemsWithMaxProfit.push_back(maxBItem);
        }

        writeToFile("output3.txt", itemsWithMaxProfit);
    }
};

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Wrong Usage! \nCorrect Usage: " << argv[0] << " <file_path>" << std::endl;
        return 1;
    }
    IGreedy igreedy;
    igreedy.run(argv[1]);
    return 0;
}

