#ifndef MESSAGE_IO_HPP
#define MESSAGE_IO_HPP

#include "configuration.hpp"
#include "json.hpp"

namespace model {

using json = nlohmann::json;

/*	Declare required functions to_json for types which
	will be serialized */
void to_json(json &, Command const &);
void to_json(json &, DebugMessage const &);
void to_json(json &, Response const &);


/*	Declare required functions for types which
	will be parsed */
void from_json(json const &, Point2D &);
void from_json(json const &, Transform2D &);
void from_json(json const &, Segment &);
void from_json(json const &, ProtoMap &);
void from_json(json const &, ProtoCar &);
void from_json(json const &, Car &);
void from_json(json const &, MessageParams &);
void from_json(json const &, MessageType &);
void from_json(json const &, Message &);


// Read Message from stdin in json format using from_json functions
void read(Message &message);


// Write Response to stdout in json format using to_json functions
void write(Response const &response);

} // model


#endif //MESSAGE_IO_HPP