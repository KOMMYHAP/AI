#include "strategyManager.hpp"

namespace ai {

class StrategyManager::Impl
{
public:
	// Initialize current strategy by RandomStrategy
	Impl();
	// StrategyManager is singleton therefore its implementation too
	Impl(Impl const &) = delete;
	Impl & operator=(Impl const &) = delete;

	~Impl() = default;

	StrategyPtr getStrategy() const;
	void setStrategy(StrategyPtr);
private:
	StrategyPtr m_currentStrategy;
};

StrategyManager::Impl::Impl()
	: m_currentStrategy(new RandomStrategy)
{}

StrategyPtr StrategyManager::Impl::getStrategy() const
{
	return m_currentStrategy;
}

void StrategyManager::Impl::setStrategy(StrategyPtr currentStrategy)
{
	if (currentStrategy != nullptr) {
		m_currentStrategy = currentStrategy;
	}
}

StrategyManager::StrategyManager()
	: m_pImpl(new Impl)
{}

StrategyPtr StrategyManager::getStrategy(model::Message const &)
{
	if (m_pImpl->getStrategy()->isDone()) {
		// investigating of input message for choosing new strategy
		m_pImpl->setStrategy(StrategyPtr(new RandomStrategy));
	}
	return m_pImpl->getStrategy();
}

} // end of namespace ai

BIND_SELF_TO_IMPL_SINGLE(ai::StrategyManager);