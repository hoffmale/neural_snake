#pragma once

#include "controller.h"

#include <QObject>

class qt_controller : public QObject, public controller
{
	Q_OBJECT

	std::atomic<direction> current_direction{ direction::right };

public:
	qt_controller() = default;
	qt_controller(const qt_controller& other);

	direction next_move() override;

public slots:
	void up();
	void down();
	void left();
	void right();
};

Q_DECLARE_METATYPE(qt_controller)
Q_DECLARE_METATYPE(qt_controller*)