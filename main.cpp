#include <application.h>

int main(int argc, char * argv[])
{
    Application * application = new Application(argc, argv);

    int result = application->exec();

    delete application;

    return result;
}

