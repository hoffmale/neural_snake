#include "board_model.h"

board_model::board_model(const board* state)
	: state{ *state }
	, score{ 0 }
	, width{ state->width() }
	, height{ state->height() }
{
}

board_model::board_model(const board_model& other)
	: state{ other.state }
	, score{ other.score }
	, width{ other.width }
	, height{ other.height }
{
}

board_model::board_model(board_model&& other) noexcept
	: state{ other.state }
	, score{ other.score }
	, width{ other.width }
	, height{ other.height }
{
}

board_model::~board_model() = default;

board_model& board_model::operator=(const board_model& other)
{
	state = other.state;
	score = other.score;
	width = other.width;
	height = other.height;

	return *this;
}

board_model& board_model::operator=(board_model&& other) noexcept
{
	state = other.state;
	score = other.score;
	width = other.width;
	height = other.height;

	return *this;
}

void board_model::draw(const ::board& state, int score)
{
	beginResetModel();

	this->score = score;
	this->state = state;

	endResetModel();
}

void board_model::game_over()
{
}

int board_model::rowCount(const QModelIndex& parent) const
{
	return width * height;
}

QVariant board_model::data(const QModelIndex& index, int role) const
{
	auto x = index.row() % width;
	auto y = index.row() / width;

	if (role == roles::tile) {
		return QVariant::fromValue(static_cast<int>(state.tile(position{ x, y })));
	}

	return QVariant();
}

QHash<int, QByteArray> board_model::roleNames() const
{
	auto roleHashes = QHash<int, QByteArray>();
	roleHashes[roles::tile] = "tile";
	return roleHashes;
}


