#pragma once

#include "renderer.h"

#include <QObject>

class qt_renderer : public QObject, public renderer
{
	Q_OBJECT

public slots:
	void draw(const board& state, int score) override;
	void game_over() override;

signals:
	void render(const board& state, int score);
	void finish();
};

