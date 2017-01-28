
#include "Application.h"

#include "examples/TestGameScene1.h"

int main(int argc, char* argv[])
{
    Application::GetSingleton().Init();

    Ref<TestGameScene1> rootScene = memnew(TestGameScene1);
    Application::GetSingleton().RunScene(rootScene);

    return Application::GetSingleton().Run(argc, argv);
}
