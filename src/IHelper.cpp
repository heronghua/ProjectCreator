/*************************************************************************
	 File Name: app.cpp
	 Author: He Ronghua
	 Mail: heronghua1989@126.com
	 Created Time: Sun Feb  9 14:03:52 2025
 ************************************************************************/
#include "IHelper.h"
#include <iostream>

void replaceKeyWithValue(string& content, std::shared_ptr<std::map<string,string>> contentMap, const string& destFilePathStr) 
{
    // Replace the key with its corresponding value in the stringstream contents
    string newContent = content;
    if (contentMap) {
        for (const auto& pair : *contentMap) {
            string key = pair.first;
            string value = pair.second;
            std::cout << "key:" << key << std::endl;
            std::cout << "value:" << value << std::endl;
            size_t pos = newContent.find(key);
            while (pos != string::npos) {
                newContent.replace(pos, key.length(), value);
                pos = newContent.find(key, pos + value.length());
            }
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

void replaceKeyWithValueMultipleContent(string& contentA,string& contentB, std::shared_ptr<std::map<string,string>> contentMap, const string& destFilePathStr) 
{
    // Replace the key with its corresponding value in the stringstream contents
    string newContentA = contentA;
    if (contentMap) {
        for (const auto& pair : *contentMap) {
            string key = pair.first;
            string value = pair.second;
            std::cout << "key:" << key << std::endl;
            std::cout << "value:" << value << std::endl;
            size_t pos = newContentA.find(key);
            while (pos != string::npos) {
                newContentA.replace(pos, key.length(), value);
                pos = newContentA.find(key, pos + value.length());
            }
        }

    }

    string newContentB = contentB;
    if (contentMap) {
        for (const auto& pair : *contentMap) {
            string key = pair.first;
            string value = pair.second;
            std::cout << "key:" << key << std::endl;
            std::cout << "value:" << value << std::endl;
            size_t pos = newContentB.find(key);
            while (pos != string::npos) {
                newContentB.replace(pos, key.length(), value);
                pos = newContentB.find(key, pos + value.length());
            }
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
    destFile << newContentA;
    destFile << newContentB;
}

