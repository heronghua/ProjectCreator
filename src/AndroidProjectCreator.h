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


class AndroidProjectCreator : public IProjectCreator
{
    public:
        void createProject() override 
        {
            std::cout << "creating android project" << std::endl;

        }

};

#endif /* ifndef ANDROID_PROJECT_CREATOR */
