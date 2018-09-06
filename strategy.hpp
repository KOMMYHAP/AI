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
		allows to use details of old message. 
		
		getResponse() returns response based on
		implementation of strategy.

		isDone() returns true if strategy completed
		and false otherwise.
		*/
class Strategy
{
public:
	virtual model::Response getResponse() = 0;
	virtual bool isDone() const = 0;
	virtual ~Strategy() = default;
};

using StrategyPtr = std::shared_ptr<Strategy>;

/*	@brief:
		There is the easiest strategy and may be
		base strategy for not null pointer */
class RandomStrategy : public Strategy
{
public:
	model::Response getResponse() override;
	bool isDone() const override;
	~RandomStrategy() override = default;	
};

} // end of namespace ai

#endif //STRATEGY_HPP