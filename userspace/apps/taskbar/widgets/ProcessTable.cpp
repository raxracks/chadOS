#include "task-manager/widgets/ProcessTable.h"

using namespace Widget;

namespace Taskbar
{

ProcessTableComponent::ProcessTableComponent(RefPtr<Widget::TableModel> model)
    : _model{model}
{
}

RefPtr<Element> ProcessTableComponent::build()
{
    return table(_model);
}

} // namespace TaskManager
