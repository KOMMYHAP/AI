#include "configuration.hpp"
#include "messageIO.hpp"

#include "strategy.hpp"

int main()
{
	using namespace model;

	StrategyPtr currentStrategy = nullptr;
	while (true) {
		Message msg{};
		read(msg);

		currentStrategy = g_strategyManager.getStrategy(msg);

		write(currentStrategy->getResponse());
	}
}