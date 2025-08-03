#include "Application.h"

int main(int, char**) {
    std::unique_ptr<Application> app = Application::New();
    if (app == nullptr)
        return -1;

    app->Run();

    return 0;
}
