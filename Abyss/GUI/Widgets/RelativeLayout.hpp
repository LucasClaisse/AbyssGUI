#pragma once

#include "Abyss/GUI/Layout.hpp"

namespace Abyss {
	namespace Widgets {
		class RelativeLayout;
	}
}

class Abyss::Widgets::RelativeLayout : public Layout {
public:
	auto childrenUpdate() -> void override;
};

auto Abyss::Widgets::RelativeLayout::childrenUpdate() -> void
{

}
