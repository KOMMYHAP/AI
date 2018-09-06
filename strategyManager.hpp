#ifndef STRATEGY_MANAGER_HPP
#define STRATEGY_MANAGER_HPP

#include <memory>

#include "strategy.hpp"
#include "configuration.hpp"

#include "singleton.hpp"

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

	~StrategyManager() = default;

	StrategyPtr getStrategy(model::Message const &);
private:
	class Impl;
	std::unique_ptr<Impl> m_pImpl;
};

} // end of namespace ai

DECLARE_IMPL(ai::StrategyManager);

#endif //STRATEGY_MANAGER_HPP