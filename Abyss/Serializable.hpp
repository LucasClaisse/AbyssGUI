#pragma once

#include <fstream>

namespace Abyss {
    class Serializable;
}

class Abyss::Serializable {
public:
	virtual ~Serializable() = default;

    template <typename T>
    static auto pack(std::ostream &os, const T &val) -> void;

	template <typename T>
    static auto unpack(std::istream &is, T &val) -> T &;

    template <typename T>
    [[nodiscard]] static auto unpack(std::istream &is) -> T;

    virtual auto serialize(std::ostream &os) const -> void;
    virtual auto deserialize(std::istream &is) -> void;
};

template <typename T>
inline auto Abyss::Serializable::pack(std::ostream &os, const T &val) -> void
{
    os.write(reinterpret_cast<const char*>(&val), sizeof(T));
}

template <typename T>
inline auto Abyss::Serializable::unpack(std::istream &is, T &val) -> T &
{
    is.read(reinterpret_cast<char*>(&val), sizeof(T));
	return val;
}

template <typename T>
inline auto Abyss::Serializable::unpack(std::istream &is) -> T
{
	T val{};
    is.read(reinterpret_cast<char*>(&val), sizeof(T));
	return val;
}

inline auto Abyss::Serializable::serialize(std::ostream &) const -> void
{
}

inline auto Abyss::Serializable::deserialize(std::istream &) -> void
{
}
