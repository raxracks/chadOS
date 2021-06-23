#include <libwidget/Application.h>

#include "taskbar/windows/TaskManager.h"

namespace Taskbar
{

struct Application : public Widget::Application
{
    OwnPtr<Widget::Window> build() override
    {
        return own<Taskbar>();
    }
};

} // namespace TaskManager

int main(int argc, char const *argv[])
{
    UNUSED(argc);
    UNUSED(argv);

    Taskbar::Application app;
    return app.run();
}