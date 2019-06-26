#pragma once

#include "Abyss/Serializable.hpp"
#include "Abyss/Vector.hpp"
#include "Abyss/Color.hpp"

namespace Abyss {
    namespace GUI {
        class Theme;
    }
}

class Abyss::GUI::Theme final : public Abyss::Serializable {
private:
	Color m_primaryColor{0, 0, 0};
	Color m_secondaryColor{0, 0, 0};

public:
	auto getPrimaryColor() const noexcept -> const decltype(m_primaryColor) &;
	auto getSecondaryColor() const noexcept -> const decltype(m_secondaryColor) &;

    auto serialize(std::ostream &os) const -> void final;
    auto deserialize(std::istream &is) -> void final;
};

inline auto Abyss::GUI::Theme::serialize(std::ostream &os) const -> void
{
	pack(os, m_primaryColor);
	pack(os, m_secondaryColor);
}

inline auto Abyss::GUI::Theme::deserialize(std::istream &is) -> void
{
	unpack(is, m_primaryColor);
	unpack(is, m_secondaryColor);
}
