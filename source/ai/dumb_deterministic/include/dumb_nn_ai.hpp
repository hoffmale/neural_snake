#include <network.hpp>
#include <simulation.h>

class dumb_nn_ai : public simulation
{
	network brain;

public:
	dumb_nn_ai();

protected:
	direction next_move() override;
};
