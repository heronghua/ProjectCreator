/*************************************************************************
  File Name: app.cpp
Author: He Ronghua
Mail: heronghua1989@126.com
Created Time: Sun Feb  9 14:03:52 2025
 ************************************************************************/


#include "ThreadPool.h"
#include "ProjectCreatorFactory.h"
#include <string>

using namespace std;


int main(int argc, char *argv[])
{

    string type;
    string ProjectName;
    string packageName;

    //parsing the parameters
    for (int i = 1; i < argc; i++) {
        string option = argv[i];
        if (option.find("--type") == 0) {
            size_t equalsPos = option.find('=');
            if (equalsPos != string::npos) {
                type = option.substr(equalsPos + 1);
            }
        } else if (option.find("--ProjectName") == 0){
            size_t equalsPos = option.find('=');
            if (equalsPos != string::npos) {
                ProjectName = option.substr(equalsPos + 1);
            }
        } else if (option.find("--packageName") == 0){
            size_t equalsPos = option.find('=');
            if (equalsPos != string::npos) {
                packageName = option.substr(equalsPos + 1);
            }
        }
    }
    if (type == "android" && &ProjectName && &packageName) {
        auto android = ProjectCreatorFactory::Create(ProjectCreatorFactory::Type::Android);
        android->createProject(ProjectName,packageName);
        return 0;

    }
    if (type == "cpp" && &ProjectName) {
        //TODO
        auto cppProjectCreator = ProjectCreatorFactory::Create(ProjectCreatorFactory::Type::Cpp);
        cppProjectCreator->createProject(ProjectName,packageName);
        return 0;

    }

    return 0;
}
