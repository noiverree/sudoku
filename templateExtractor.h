#ifndef TEMPLATEEXTRACTOR_H
#define TEMPLATEEXTRACTOR_H

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

#endif // TEMPLATEEXTRACTOR_H