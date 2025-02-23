/*************************************************************************
	 File Name: app.cpp
	 Author: He Ronghua
	 Mail: heronghua1989@126.com
	 Created Time: Sun Feb  9 14:03:52 2025
 ************************************************************************/
#ifndef I_HELPER
#define I_HELPER 1
#include <string>

#include <string>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <map>

using namespace std;

void replaceKeyWithValue(string& content, std::shared_ptr<std::map<string,string>> map, const string& destFilePathStr);

#endif /** ifndef I_HELPER */
