#include "strategyManager.hpp"

namespace ai {

struct StrategyManager::Impl
{};

StrategyManager::StrategyManager()
	: m_pImpl(new Impl)
{}

StrategyPtr StrategyManager::getStrategy(model::Message const &)
{
	return StrategyPtr(new RandomStrategy);
}

} // end of namespace ai

BIND_SELF_TO_IMPL_SINGLE(ai::StrategyManager);