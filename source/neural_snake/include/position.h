#pragma once

#include <unordered_set>

struct position
{
	int x;
	int y;

	bool operator==(const position other) const noexcept { return x == other.x && y == other.y; }
	bool operator!=(const position other) const noexcept { return !(*this == other); }

	position down(int steps = 1) const
	{
		return position{ x, y + steps };
	}

	position up(int steps = 1) const
	{
		return position{ x, y - steps };
	}

	position left(int steps = 1) const
	{
		return position{ x - steps, y };
	}

	position right(int steps = 1) const
	{
		return  position{ x + steps, y };
	}
};

namespace std
{
	template<>
	struct hash<position>
	{
		size_t operator()(const position& pos) const noexcept
		{
			return pos.x << 16 | pos.y;
		}
	};
}