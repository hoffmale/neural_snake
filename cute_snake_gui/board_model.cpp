#include "board_model.h"

board_model::board_model(const ::board& board)
	: board{ board }
	, width{ board.width() }
	, height{ board.height() }
{
}

void board_model::draw(const ::board& state, int score)
{
	this->score = score;

	beginResetModel();
	endResetModel();
}

void board_model::game_over()
{
	emit game_finished();
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
		return QVariant::fromValue(board.tile(position{ x, y }));
	}

	return QVariant();
}

QHash<int, QByteArray> board_model::roleNames() const
{
	auto roleHashes = QHash<int, QByteArray>();
	roleHashes[roles::tile] = "tile";
	return roleHashes;
}


