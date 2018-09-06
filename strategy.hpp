#ifndef STRATEGY_HPP
#define STRATEGY_HPP

#include <memory>

#include "configuration.hpp"

namespace ai {

/*	@brief:
		Strategy provides interface for bot behavior. 
		The same interface may be used for simple 
		strategy like random choosing command or
		complex like recurrent strategy which
		allows to use details of old message. */
class Strategy
{
public:
	virtual model::Response getResponse() = 0;
	virtual ~Strategy() = default;
};

using StrategyPtr = std::shared_ptr<Strategy>;

/* Forward declarations of strategy implementation: */
class RandomStrategy : public Strategy
{
public:
	model::Response getResponse() override;
	~RandomStrategy() override = default;	
};

} // end of namespace ai

#endif //STRATEGY_HPP