/*************************************************************************
	 File Name: app.cpp
	 Author: He Ronghua
	 Mail: heronghua1989@126.com
	 Created Time: Sun Feb  9 14:03:52 2025
 ************************************************************************/
#include "IHelper.h"
#include <iostream>
using namespace std;

void replaceKeyWithValue(string& content, string* key, string* value, const string& destFilePathStr) 
{

    std::cout << "key" << key << std::endl;
    std::cout << "value:" << value << std::endl;

    // Replace the key with its corresponding value in the stringstream contents
    string newContent = content;
    if (key && value) {
        size_t pos = newContent.find(*key);
        while (pos != string::npos) {
            newContent.replace(pos, key->length(), *value);
            pos = newContent.find(*key, pos + value->length());
        }

    }

    // Write the updated contents to the destination file
    filesystem::path destFilePath(destFilePathStr);
    filesystem::path dir=destFilePath.parent_path();
    if (!filesystem::exists(dir)) {
        filesystem::create_directories(dir);    
    }
    ofstream destFile(destFilePathStr);
    if (!destFile.is_open()) {
        throw runtime_error("Failed to open destination file for writing.");
    }
    destFile << newContent;
}

