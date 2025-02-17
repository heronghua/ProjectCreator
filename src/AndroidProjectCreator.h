/*************************************************************************
	 File Name: src/AndroidProjectCreator.h
	 Author: He Ronghua
	 Mail: heronghua1989@126.com
	 Created Time: Sun Feb 16 21:26:09 2025
 ************************************************************************/

#ifndef ANDROID_PROJECT_CREATOR
#define ANDROID_PROJECT_CREATOR 1

#include <iostream>
#include "IProjectCreator.h"
#include "IHelper.h"


#define INCBIN_STYLE INCBIN_STYLE_SNAKE
#define INCBIN_PREFIX g_
#include <incbin.h>


using namespace std;

/* Usage: INCBIN(<<LABLE>>, <<FILE>>)
 *
 * Symbols defined by INCBIN 
 * ------------------------------------------ 
 *  const unsigned char        g_asset_data[]  // g_<<LABLE>>_data 
 *  const unsigned char* const g_asset_end;    // g_<<LABEL>>_end 
 *  const unsinged int         g_asset_size;   // g_<<LABEL>>_size 
 */
INCBIN(asset, "../resource/TemplateAndroid/AndroidSdk/platforms/android-20/templates/strings.template");

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

class AndroidProjectCreator : public IProjectCreator
{
    public:
        void createProject() override 
        {
          std::cout << "creating android project" << std::endl;
          string content = string(g_asset_data, g_asset_data + g_asset_size);

          string key="At";
          string value="At=line";
          string destFilePath="t/df";
          ThreadPool pool(4); 

 //         auto result=
         pool.enqueue(replaceKeyWithValue,content, key, value, destFilePath);
//          result.get();



        }

};

#endif /* ifndef ANDROID_PROJECT_CREATOR */
