#ifndef STRATEGY_HPP
#define STRATEGY_HPP

#include "configuration.hpp"

namespace ai {

/*	@brief:
		Strategy provides interface for bot behavior. 
		The same interface may be used for simple 
		strategy like random choosing command or
		complex like recurrent strategy which
		allows to use details of old message. */
struct Strategy
{
	virtual model::Response getResponse() = 0;
};

/* Forward declarations of strategy will place here */

} // end of namespace ai

#endif //STRATEGY_HPP