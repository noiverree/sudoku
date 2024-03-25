#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

class TemplateExtractor
{
    public:
        vector<vector<int>> ExtractTemplate(string path);

    private:
        string GetTemplate(string path);
        vector<int> ExtractArray(string data);
        vector<vector<int>> ConvertTo2D(const vector<int>& array, int rows, int cols);
};

string TemplateExtractor::GetTemplate(string path)
{
    ifstream file(path);
    string line;
    string templateContent = "";
    bool isTemplate = false;

    while (getline(file, line))
    {
        templateContent += line + "\n";
    }

    return templateContent;
}

vector<int> TemplateExtractor::ExtractArray(string data) 
{
    vector<int> result;
    istringstream iss(data.substr(1, data.size() - 2));

    char comma;
    int num;
    while (iss >> num) 
    {
        result.push_back(num);
        if (iss.peek() == ',')
            iss.ignore();
    }

    return result;
}

vector<vector<int>> TemplateExtractor::ConvertTo2D(const vector<int>& array, int rows, int cols) 
{
    vector<vector<int>> result(rows, vector<int>(cols));

    int index = 0;
    for (int i = 0; i < rows; ++i) 
    {
        for (int j = 0; j < cols; ++j) 
        {
            result[i][j] = array[index++];
        }
    }

    return result;
}

vector<vector<int>> TemplateExtractor::ExtractTemplate(string path)
{
    string data = GetTemplate(path);
    vector<int> extractedArray = ExtractArray(data);
    vector<vector<int>> array = ConvertTo2D(extractedArray, 9, 9);

    return array;
}