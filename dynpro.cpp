#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

struct Item {
    std::string itemNumber;
    int profit;
    int weight;
    float profitPerUnit;
};

class Dynpro {
private:
    int N;
    int W;
    std::vector<Item> items;
    std::vector<std::vector<int>> DP;

public:
    void initializeMatrix() {
        DP.resize(N + 1, std::vector<int>(W + 1, 0));  // Initialize DP table with zeros
    }

    void readFile(const std::string& filePath) {
        std::ifstream inFile(filePath);
        if (!inFile) {
            std::cerr << "An error occurred while reading the file!" << std::endl;
            return;
        }
        std::string firstLine;
        std::getline(inFile, firstLine);
        std::istringstream iss(firstLine);
        iss >> N >> W;
        items.resize(N);
        for (int i = 0; i < N; ++i) {
            std::string line;
            std::getline(inFile, line);
            std::istringstream lineStream(line);
            lineStream >> items[i].itemNumber >> items[i].profit >> items[i].weight;
            items[i].profitPerUnit = static_cast<float>(items[i].profit) / items[i].weight;
        }
        inFile.close();
    }

    int refinedDynPro() {
        for (int i = 1; i <= N; i++) {
            for (int w = 1; w <= W; w++) {
                if (items[i - 1].weight <= w)
                    DP[i][w] = std::max(DP[i - 1][w], DP[i - 1][w - items[i - 1].weight] + items[i - 1].profit);
                else
                    DP[i][w] = DP[i - 1][w];
            }
        }
        return DP[N][W];
    }

    std::vector<Item> getOptimalSolItems() {
        std::vector<Item> selectedItems;
        int i = N, w = W;
        while (i > 0 && w > 0) {
            if (DP[i][w] != DP[i-1][w]) {
                selectedItems.push_back(items[i-1]);
                w -= items[i-1].weight;
                i -= 1;
            } else {
                i -= 1;
            }
        }
        std::reverse(selectedItems.begin(), selectedItems.end()); // Reverse to maintain the order of selection
        return selectedItems;
    }

    void writeOptimalItems(const std::string& filePath, const std::vector<Item>& optimalItems) {
        std::ofstream outFile(filePath);
        if (!outFile) {
            std::cerr << "Failed to open " << filePath << " for writing.\n";
            return;
        }
        for (const auto& item : optimalItems) {
            outFile << item.itemNumber << " " << item.profit << " " << item.weight << "\n";
        }
        outFile.close();
    }

    void run(const std::string& filePath) {
        readFile(filePath);
        initializeMatrix();
        refinedDynPro();
        auto optimalItems = getOptimalSolItems();
        writeOptimalItems("output2.txt", optimalItems);
    }
};

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Wrong Usage! \nCorrect Usage: " << argv[0] << " <file_path>" << std::endl;
        return 1;
    }
    Dynpro dp;
    dp.run(argv[1]);
    return 0;
}

