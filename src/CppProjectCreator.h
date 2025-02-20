/*************************************************************************
	 File Name: src/CppProjectCreator.h
	 Author: He Ronghua
	 Mail: heronghua1989@126.com
	 Created Time: Sun Feb 16 21:48:39 2025
 ************************************************************************/

#ifndef CPP_PROJECT_CREATOR
#define CPP_PROJECT_CREATOR 1
#include <filesystem>
using namespace std;

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
            
            

        }
};
#endif
