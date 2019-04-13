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

class board_model : public QAbstractListModel, public virtual renderer
{
	Q_OBJECT

	Q_PROPERTY(int width   MEMBER width  CONSTANT)
	Q_PROPERTY(int height  MEMBER height CONSTANT)
	Q_PROPERTY(int score   MEMBER score  CONSTANT)

public:
	board_model(const board& board);

	void draw(const board& state, int score) override;
	void game_over() override;

	int rowCount(const QModelIndex& parent) const override;
	QVariant data(const QModelIndex& index, int role) const override;

signals:
	void game_finished();

protected:
	QHash<int, QByteArray> roleNames() const override;

private:
	const board& board;
	int score;
	int width;
	int height;
};

Q_DECLARE_METATYPE(board_model);
Q_DECLARE_METATYPE(board_model*);
