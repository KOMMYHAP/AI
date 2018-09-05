#include "messageIO.hpp"

int main()
{
	using namespace model;

	while (true) {
		Message msg{};
		read(msg);

		Response response {Command::Left, "left"};
		write(response);
	}
}