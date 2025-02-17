#include <iostream>
#include <string>

#define INCBIN_STYLE INCBIN_STYLE_SNAKE
#define INCBIN_PREFIX g_
#include <incbin.h>

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

// Read all lines from some input stream
// and print on stdout.
void print_lines(std::stream& is)
{
	std::string line;
	int n = 0;
	while(std::getline(is,line) && n < 25)
		std::out << " line[" << n++ << "] = " << line << std::endl;
	
}

int main()
{
	std::puts("\n [EXPERIMENT 1] ==> Read directly from symbols --");
	std::string text = std::string(g_asset_data,g_asset_data + g_asset_size);
	std::cout << " Content of the asset file is " << std::endl;
	std::cout << " => " << text << std::endl;
	
	std::puts("\n [EXPERIMENT 2] ==> Read from memory stream --");
	auto is = MEMORY_STREAM(asset);
	print_lines(is);
	
	return 0;
	
}