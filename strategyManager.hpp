#ifndef STRATEGY_MANAGER_HPP
#define STRATEGY_MANAGER_HPP

#include <memory>

#include "singleton.hpp"
#include "strategy.hpp"
#include "configuration.hpp"

namespace ai {

/*	@brief:
		StrategyManager class suggests actual strategy
		regarding the message obtained from server.
	@note:
		g_strategyManager is singleton of StrategyManager */
class StrategyManager
{
public:
	StrategyManager();

	// Manager means singleton therefore special copy functions deleted
	StrategyManager(StrategyManager const &) = delete;
	StrategyManager & operator=(StrategyManager const &) = delete;

	~StrategyManager();

	StrategyPtr getStrategy(model::Message const &);
private:
	class Impl;
	std::unique_ptr<Impl> m_pImpl;
};

DECLARE_IMPL(StrategyManager);

An<StrategyManager> g_strategyManager;

} // end of namespace ai

#endif //STRATEGY_MANAGER_HPP