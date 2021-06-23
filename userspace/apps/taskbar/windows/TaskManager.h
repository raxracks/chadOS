#pragma once

#include <libasync/Timer.h>
#include <libwidget/Window.h>

#include "taskbar/model/TaskModel.h"

namespace Taskbar
{

struct Taskbar : public Widget::Window
{
private:
    RefPtr<TaskModel> _model;
    OwnPtr<Async::Timer> _update;

public:
    Taskbar();

    RefPtr<Widget::Element> build() override;
};

} // namespace TaskManager