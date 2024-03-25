#include <iostream>
#include <vector>
#include <sstream>

std::vector<int> extractArray(const std::string& data) 
{
    std::vector<int> result;
    std::istringstream iss(data.substr(1, data.size() - 2));

    char comma;
    int num;
    while (iss >> num) {
        result.push_back(num);
        if (iss.peek() == ',')
            iss.ignore(); // Ignore comma
    }

    return result;
}

std::vector<std::vector<int>> convertTo2D(const std::vector<int>& array, int rows, int cols) 
{
    std::vector<std::vector<int>> result(rows, std::vector<int>(cols));

    int index = 0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            result[i][j] = array[index++];
        }
    }

    return result;
}

void print2DArray(const std::vector<std::vector<int>>& array) 
{
    for (const auto& row : array) 
    {
        for (int num : row) 
        {
            std::cout << num << " ";
        }

        std::cout << std::endl;
    }
}

int main() 
{
    std::string data = "[3,0,1,5,9,10,2]";

    std::vector<int> extractedArray = extractArray(data);

    // Output the extracted array
    std::cout << "Extracted Array: [";
    for (size_t i = 0; i < extractedArray.size(); ++i) {
        std::cout << extractedArray[i];
        if (i != extractedArray.size() - 1)
            std::cout << ",";
    }
    std::cout << "]\n";

    std::vector<int> array = {3, 0, 1, 3, 2, 1, 4, 5, 6, 3, 0, 1, 3, 2, 1, 4, 5, 6, 3, 0, 1, 3, 2, 1, 4, 5, 6, 3, 0, 1, 3, 2, 1, 4, 5, 6, 3, 0, 1, 3, 2, 1, 4, 5, 6, 3, 0, 1, 3, 2, 1, 4, 5, 6, 3, 0, 1, 3, 2, 1, 4, 5, 6, 3, 0, 1, 3, 2, 1, 4, 5, 6, 3, 0, 1, 3, 2, 1, 4, 5, 6};

    // Convert to 2D array
    std::vector<std::vector<int>> array2D = convertTo2D(array, 9, 9);

    // Print the 2D array
    std::cout << "2D Array:\n";
    print2DArray(array2D);

    return 0;
}