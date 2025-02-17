/*************************************************************************
	 File Name: app.cpp
	 Author: He Ronghua
	 Mail: heronghua1989@126.com
	 Created Time: Sun Feb  9 14:03:52 2025
 ************************************************************************/


#include "ThreadPool.h"
#include "ProjectCreatorFactory.h"


int main(int argc, char *argv[])
{

  auto android = ProjectCreatorFactory::Create(ProjectCreatorFactory::Type::Android);
  android->createProject();

  return 0;
}
