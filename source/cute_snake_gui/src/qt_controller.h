#pragma once

#include <QObject>
#include "simulation.h"

class qt_controller : public QObject, public simulation
{
	Q_OBJECT

	std::atomic<direction> current_direction{ direction::right };

public:
	qt_controller() = default;
	qt_controller(const qt_controller& other);

protected:
	direction next_move() override;

public slots:
	void up();
	void down();
	void left();
	void right();
};

Q_DECLARE_METATYPE(qt_controller)
Q_DECLARE_METATYPE(qt_controller*)