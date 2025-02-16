#ifndef PROJECT_CREATOR_FACTORY
#define PROJECT_CREATOR_FACTORY 1

#include "AndroidProjectCreator.h"
#include "CppProjectCreator.h"

class ProjectCreatorFactory
{
public:
    enum class Type {Cpp,Android,Java};

    static std::unique_ptr<IProjectCreator> Create(Type type)
    {
        switch(type) {
            case Type::Android :
                return std::make_unique<AndroidProjectCreator>();
            case Type::Cpp :
                return std::make_unique<CppProjectCreator>();
            default:
                return nullptr;
        }

    }

};

#endif /* ifndef PROJECT_CREATOR_FACTORY */
