#pragma once

#include "Abyss/GUI/Layout.hpp"

namespace Abyss {
    namespace GUI {
        namespace Widgets {
            class RelativeLayout;
        }
    }
}

class Abyss::GUI::Widgets::RelativeLayout : public Layout {
public:
    auto onChildChange(const Child &child) -> void override;
};

inline auto Abyss::GUI::Widgets::RelativeLayout::onChildChange(const Child &child) -> void
{
}
