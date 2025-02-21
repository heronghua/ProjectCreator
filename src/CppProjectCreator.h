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
INCBIN(app, "../resource/TemplateCpp/src/App.cpp");
INCBIN(res, "../resource/TemplateCpp/resource/data.txt");
INCBIN(incbin, "../resource/TemplateCpp/_build/include/incbin.h");
INCBIN(vimconf, "../resource/TemplateCpp/.vim/qrc.vim");

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

            string appContent = string(g_app_data,g_app_data + g_app_size);
            string appFilePath = projectName + filesystem::path::preferred_separator + "src" + filesystem::path::preferred_separator + "App.cpp";
            pool.enqueue(replaceKeyWithValue,appContent, nullptr, nullptr, appFilePath);

            string resContent = string(g_res_data,g_res_data + g_res_size);
            string resFilePath = projectName + filesystem::path::preferred_separator + "resource" + filesystem::path::preferred_separator + "data.txt";
            pool.enqueue(replaceKeyWithValue,resContent, nullptr, nullptr, resFilePath);

            string incbinContent = string(g_incbin_data,g_incbin_data + g_incbin_size);
            string incbinFilePath = projectName + filesystem::path::preferred_separator + "_build" + filesystem::path::preferred_separator + "include" + filesystem::path::preferred_separator + "incbin.h";
            pool.enqueue(replaceKeyWithValue,incbinContent, nullptr, nullptr, incbinFilePath);

            string vimConfContent = string(g_vimconf_data,g_vimconf_data + g_vimconf_size);
            string vimConfFilePath = projectName + filesystem::path::preferred_separator + ".vim" + filesystem::path::preferred_separator + "qrc.vim";
            pool.enqueue(replaceKeyWithValue,vimConfContent, nullptr, nullptr, vimConfFilePath);

        }
};

#endif
