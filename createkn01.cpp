#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

class createkn01 {

public:
    static const int N_UPPER_LIMIT = 10;
    static const int N_LOWER_LIMIT = 5;
    static const int WEIGHT_UPPER_LIMIT = 5;
    static const int WEIGHT_LOWER_LIMIT = 20;
    static const int PROFIT_UPPER_LIMIT = 10;
    static const int PROFIT_LOWER_LIMIT = 30;
    // Function to Calculate the sum of the array
    int calculateSum(const int arr[], int size) {
        int sum = 0;
        for (int i = 0; i < size; i++) {
            sum += arr[i];
        }
        return sum;
    }

    // Function to generate random values
    void generateRandomValues(int arr[], int n, int lowerLimit, int upperLimit) {
        for (int i = 0; i < n; i++) {
            arr[i] = rand() % (upperLimit - lowerLimit + 1) + lowerLimit;
        }
    }

    // Function to write into the file
    void writeToFile(const std::string& filePath, int n, int weight[], int profit[], int knapsackCapacity) {
        std::ofstream myWriter(filePath);
        if (myWriter.is_open()) {
            myWriter << n << " " << knapsackCapacity << "\n";
            for (int i = 0; i < n; i++) {
                myWriter << "item" << (i + 1) << " " << profit[i] << " " << weight[i] << "\n";
            }
            myWriter.close();
        } else {
            std::cerr << "An error occurred while writing into file!" << std::endl;
        }
    }
};

int main(int argc, char* argv[]) {
    // Initialize random seed
    srand(time(NULL));

    // Pre-checks for valid usage
    if (argc != 2) {
        std::cout << "Wrong Usage! \nCorrect Usage: " << argv[0] << " <file_path>" << std::endl;
        return 1;
    }

    // Getting filepath from command line argument
    std::string filePath = argv[1];

    // Generating random value for n
    int n = rand() % (createkn01::N_UPPER_LIMIT - createkn01::N_LOWER_LIMIT + 1) + createkn01::N_LOWER_LIMIT;

    // Creating object for the class
    createkn01 obj;

    // Arrays for weights and profits
    int weight[n], profit[n];

    // Generating random values for weights for given n
    obj.generateRandomValues(weight, n, createkn01::WEIGHT_LOWER_LIMIT, createkn01::WEIGHT_UPPER_LIMIT);

    // Generating random values for profits for given n
    obj.generateRandomValues(profit, n, createkn01::PROFIT_LOWER_LIMIT, createkn01::PROFIT_UPPER_LIMIT);

    // Calculating knapsack capacity
    int knapsackCapacity = static_cast<int>(0.6 * obj.calculateSum(weight, n));

    // Writing the calculated values into file
    obj.writeToFile(filePath, n, weight, profit, knapsackCapacity);

    return 0;
}

