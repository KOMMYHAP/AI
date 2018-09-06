#include "configuration.hpp"
#include "messageIO.hpp"

#include "strategyManager.hpp"

int main()
{
	using namespace model;
	using namespace ai;
	
	An<StrategyManager> strategyManagerPtr;
	StrategyPtr currentStrategyPtr = nullptr;
	while (true) {
		Message msg{};
		read(msg);

		currentStrategyPtr = strategyManagerPtr->getStrategy(msg);

		write(currentStrategyPtr->getResponse());
	}
}