#include "strategy.hpp"

#include <random>

namespace ai {

model::Response RandomStrategy::getResponse()
{
	return {
		model::Command{static_cast<model::Command::Type>(rand() % model::Command::Count)},
		model::DebugMessage{"random command"}
	};
}

bool RandomStrategy::isDone() const
{
	return false;
}

} // end of namespace ai