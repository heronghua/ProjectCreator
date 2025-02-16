/*************************************************************************
	 File Name: src/IProjectCreator.h
	 Author: He Ronghua
	 Mail: heronghua1989@126.com
	 Created Time: Sun Feb 16 21:40:06 2025
 ************************************************************************/

#ifndef I_PROJECT_CREATOR
#define I_PROJECT_CREATOR 1
class IProjectCreator
{
    public:
        virtual void createProject() = 0;
        virtual ~IProjectCreator() = default;
};
#endif /* ifndef I_PROJECT_CREATOR */
