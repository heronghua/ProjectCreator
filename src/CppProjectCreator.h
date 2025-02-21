/*************************************************************************
  File Name: src/CppProjectCreator.h
Author: He Ronghua
Mail: heronghua1989@126.com
Created Time: Sun Feb 16 21:48:39 2025
 ************************************************************************/

#ifndef CPP_PROJECT_CREATOR
#define CPP_PROJECT_CREATOR 1
#include <filesystem>
#include "IHelper.h"

#define INCBIN_STYLE INCBIN_STYLE_SNAKE
#define INCBIN_PREFIX g_
#include <incbin.h>

using namespace std;

INCBIN(gitignore, "../resource/TemplateCpp/.gitignore");
INCBIN(cmakelists, "../resource/TemplateCpp/CMakeLists.txt");

class CppProjectCreator : public IProjectCreator
{

    public:
        void createProject(string& projectName,string& packageName) override
        {
            std::cout << "creating cpp project" << std::endl;
            if (!filesystem::create_directories(projectName)){
                std::cerr << "Creating project directory fail "<< std::endl;
            }
            if (!filesystem::create_directories(projectName+filesystem::path::preferred_separator+"src")){
                std::cerr << "Creating src directory fail"<< std::endl;
            }
            if (!filesystem::create_directories(projectName+filesystem::path::preferred_separator+"resource")){
                std::cerr << "Creating resource directory fail"<< std::endl;
            }

            ThreadPool pool(4); 

            string destFilePath = projectName + filesystem::path::preferred_separator + ".gitignore";
            string content = string(g_gitignore_data, g_gitignore_data + g_gitignore_size);
            pool.enqueue(replaceKeyWithValue,content, nullptr, nullptr, destFilePath);

            string cmakeListsContent = string(g_cmakelists_data,g_cmakelists_data + g_cmakelists_size);
            string cmakeFilePath = projectName + filesystem::path::preferred_separator + "CMakeLists.txt";
            pool.enqueue(replaceKeyWithValue,cmakeListsContent, nullptr, nullptr, cmakeFilePath);



        }
};

#endif
