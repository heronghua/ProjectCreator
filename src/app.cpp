/*************************************************************************
	 File Name: app.cpp
	 Author: He Ronghua
	 Mail: heronghua1989@126.com
	 Created Time: Sun Feb  9 14:03:52 2025
 ************************************************************************/

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <thread>

#define INCBIN_STYLE INCBIN_STYLE_SNAKE
#define INCBIN_PREFIX g_
#include <incbin.h>
#include "ThreadPool.h"
#include "ProjectCreatorFactory.h"

using namespace std;

/* Usage: INCBIN(<<LABLE>>, <<FILE>>)
 *
 * Symbols defined by INCBIN 
 * ------------------------------------------ 
 *  const unsigned char        g_asset_data[]  // g_<<LABLE>>_data 
 *  const unsigned char* const g_asset_end;    // g_<<LABEL>>_end 
 *  const unsinged int         g_asset_size;   // g_<<LABEL>>_size 
 */
INCBIN(asset, "../resource/data.txt");

#define MEMORY_STREAM(label) \
  memstream( (char*) ((g_ ## label ## _data)),              \
             (char*) ((g_ ##label ## _data) + (g_ ## label ##_size)))

/// Credits: https://stackoverflow.com/a/13059195
/// https://stackoverflow.com/questions/13059091/
struct membuf: streambuf {
  membuf(char const* base, size_t size) {
    char* p(const_cast<char*>(base));
    this->setg(p, p, p + size);
  }
  virtual ~membuf() = default;
};

/// Credits: https://stackoverflow.com/a/13059195
/// https://stackoverflow.com/questions/13059091/
struct memstream: virtual membuf, istream {

  memstream(char const* base, char* const end)
    : membuf(base, reinterpret_cast<uintptr_t>(end) - reinterpret_cast<uintptr_t>(base) )
    , istream(static_cast<streambuf*>(this)) { }

  memstream(char const* base, size_t size)
    : membuf(base, size)
    , istream(static_cast<streambuf*>(this)) { }
};

void replaceKeyWithValue(string& content, const string& key, const string& value, const string& destFilePathStr) {

    // Replace the key with its corresponding value in the stringstream contents
    string newContent = content;
    size_t pos = newContent.find(key);
    while (pos != string::npos) {
        newContent.replace(pos, key.length(), value);
        pos = newContent.find(key, pos + value.length());
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

int main(int argc, char *argv[])
{
  string content = string(g_asset_data, g_asset_data + g_asset_size);

  string key="At";
  string value="At=line";
  string destFilePath="t/df";

  ThreadPool pool(4); 

  auto result=pool.enqueue(replaceKeyWithValue,content, key, value, destFilePath);
  auto android = ProjectCreatorFactory::Create(ProjectCreatorFactory::Type::Android);
  android->createProject();

  return 0;
}
