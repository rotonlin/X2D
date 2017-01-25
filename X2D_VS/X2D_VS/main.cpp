#ifndef _DEBUG
#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")
#endif // _DEBUG

#include "Application.h"

int main(int argc, char *argv[])
{
	Ref<Application> app = memnew(Application);

	app->Run(argc, argv);

    return 0;
}

