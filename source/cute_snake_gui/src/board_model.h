#pragma once

#include "renderer.h"

#include <QAbstractListModel>

namespace roles
{
	enum roles : int
	{
		tile = Qt::UserRole + 1
	};
}

class board_model : public QAbstractListModel
{
	Q_OBJECT

	Q_PROPERTY(int width   MEMBER width  CONSTANT)
	Q_PROPERTY(int height  MEMBER height CONSTANT)
	Q_PROPERTY(int score   MEMBER score  CONSTANT)

public:
	board_model();
	board_model(const board_model& other);
	board_model(board_model&& other) noexcept;
	~board_model();

	board_model& operator=(const board_model& other);
	board_model& operator=(board_model&& other) noexcept;

public slots:
	void draw(const board& state, int score);
	void game_over();

	int rowCount(const QModelIndex& parent) const override;
	QVariant data(const QModelIndex& index, int role) const override;

protected:
	QHash<int, QByteArray> roleNames() const override;

private:
	board state;
	int score;
	int width;
	int height;
};

Q_DECLARE_METATYPE(board)
Q_DECLARE_METATYPE(board_model)
Q_DECLARE_METATYPE(board_model*)
Q_DECLARE_METATYPE(tile_content)