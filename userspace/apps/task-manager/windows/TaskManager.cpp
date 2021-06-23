#include "task-manager/windows/TaskManager.h"
#include "task-manager/widgets/CPUGraph.h"
#include "task-manager/widgets/ProcessTable.h"
#include "task-manager/widgets/RAMGraph.h"

#include <libio/Streams.h>
#include <libsystem/io/Stream.h>    

using namespace Widget;

namespace TaskManager
{

TaskManager::TaskManager() : Window(WINDOW_RESIZABLE, 0, 100)
{
    _model = make<TaskModel>();

    _update = own<Async::Timer>(1000, [this] {
        _model->update();
    });

    _update->start();
}

RefPtr<Element> TaskManager::build()
{
    // clang-format off

    IOCallDisplayModeArgs framebuffer_info;

    Stream *device = stream_open(FRAMEBUFFER_DEVICE_PATH, HJ_OPEN_READ);
    if (stream_call(device, IOCALL_DISPLAY_GET_MODE, &framebuffer_info) != SUCCESS)
    {
        IO::errln("Ioctl to " FRAMEBUFFER_DEVICE_PATH " failed");
    }

    return min_size({framebuffer_info.width, 20},
        vflow({
            /*titlebar(Graphic::Icon::get("memory"), "Task Manager"),
            fill(process_table(_model)),
            separator(),
            min_height(128,
                panel(
                    hflow({
                        fill(cpu_graph(_model)),
                        separator(),
                        fill(ram_graph(_model)),
                    })
                )
            ),*/
            fill(process_table(_model)),
            separator(),
        })
    );

    // clang-format on
}

} // namespace TaskManager
