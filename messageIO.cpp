#include "messageIO.hpp"

#include <cassert>
#include <iostream>
#include <iomanip>

#include <fstream>

namespace model {

using json = nlohmann::json;

void to_json(json &js, Response const &response)
{
	static constexpr auto left_cstr  = "left";
	static constexpr auto right_cstr = "right";
	static constexpr auto stop_cstr  = "stop";

	js["command"] 	= 
		response.command ==  Response::Left ?  	left_cstr  :
		response.command ==  Response::Right ? 	right_cstr :
												stop_cstr  ;
	js["debug"] = response.debug.msg;
}

void from_json(json const &js, Point2D &point) 
{	
	point.x = js[0].get<f64>();
	point.y = js[1].get<f64>();
}

void from_json(json const &js, Transform2D &transform) 
{
	transform.x = js[0].get<f64>();
	transform.y = js[1].get<f64>();
	transform.angle = js[2].get<f64>();
}

void from_json(json const &js, Segment &segment) 
{
	segment.startPoint 	= js[0].get<Point2D>();
	segment.endPoint 	= js[1].get<Point2D>();
}

void from_json(json const &js, ProtoMap &protoMap) 
{
	protoMap.id = js["external_id"].get<i64>();
	protoMap.segments = js["segments"].get<vector<Segment>>();
}

void from_json(json const &js, ProtoCar &protoCar)
{	
	protoCar.id = js["external_id"].get<i64>();
	protoCar.buttonPolygon = js["button_poly"].get<vector<Point2D>>();
	{
		protoCar.body.polygon = js["car_body_poly"].get<vector<Point2D>>();
		protoCar.body.mass = js["car_body_mass"].get<i64>();
		protoCar.body.friction = js["car_body_friction"].get<f64>();
		protoCar.body.elasticity = js["car_body_elasticity"].get<f64>();
	}
	protoCar.maxSpeed = js["max_speed"].get<i64>();
	// we need consider that this parameter may be removed in future
	if (auto it = js.find("max_angular_speed");
			it != js.end()) {
		protoCar.maxAngularSpeed = (*it).get<i64>();	
	}
	protoCar.drive = js["drive"].get<ProtoCar::DriveType>();
	{
		protoCar.rearWheel.radius = js["rear_wheel_radius"].get<i64>();
		protoCar.rearWheel.mass = js["rear_wheel_mass"].get<i64>();
		protoCar.rearWheel.position = js["rear_wheel_position"].get<Point2D>();
		protoCar.rearWheel.friction = js["rear_wheel_friction"].get<f64>();
		protoCar.rearWheel.elasticity = js["rear_wheel_elasticity"].get<f64>();
		protoCar.rearWheel.joint = js["rear_wheel_joint"].get<Point2D>();
		{
			protoCar.rearWheel.damp.position = js["rear_wheel_damp_position"].get<Point2D>();
			protoCar.rearWheel.damp.length = js["rear_wheel_damp_length"].get<i64>();
			protoCar.rearWheel.damp.stiffness = js["rear_wheel_damp_stiffness"].get<f64>();
			protoCar.rearWheel.damp.damping = js["rear_wheel_damp_damping"].get<f64>();
		}
	}
	{
		protoCar.frontWheel.radius = js["front_wheel_radius"].get<i64>();
		protoCar.frontWheel.mass = js["front_wheel_mass"].get<i64>();
		protoCar.frontWheel.position = js["front_wheel_position"].get<Point2D>();
		protoCar.frontWheel.friction = js["front_wheel_friction"].get<f64>();
		protoCar.frontWheel.elasticity = js["front_wheel_elasticity"].get<f64>();
		protoCar.frontWheel.joint = js["front_wheel_joint"].get<Point2D>();
		{
			protoCar.frontWheel.damp.position = js["front_wheel_damp_position"].get<Point2D>();
			protoCar.frontWheel.damp.length = js["front_wheel_damp_length"].get<i64>();
			protoCar.frontWheel.damp.stiffness = js["front_wheel_damp_stiffness"].get<f64>();
			protoCar.frontWheel.damp.damping = js["front_wheel_damp_damping"].get<f64>();
		}
	}
	if (auto it = js.find("squared_wheels");
			it != js.end()) {
		protoCar.isSquared = (*it).get<bool>(); 
	}
		
}

void from_json(json const &js, Car &car)
{	
	// Order does matter:
	car.position 	= js[0].get<Point2D>();
	car.angle 		= js[1].get<f64>();
	car.direction 	= js[2].get<Car::Direction>();
	car.rearWheel 	= js[3].get<Transform2D>();
	car.frontWheel 	= js[4].get<Transform2D>();
}

void from_json(json const &js, MessageParams &params) 
{	
	// caching iterator is secondary task:
	auto const myCarIterator = js.find("my_car");
	// the first task is defining message type:
	bool const isTick = myCarIterator != js.end();
	if (isTick) {
		params.myCar 			= (*myCarIterator)	.get<Car>();
		params.enemyCar 		= js["enemy_car"]	.get<Car>();
		params.garbagePosition 	= js["deadline_position"].get<f64>();
	} else {
		params.myLives 			= js["my_lives"]	.get<i64>(); 
		params.enemyLives 		= js["enemy_lives"]	.get<i64>();
		params.protoMap 		= js["proto_map"]	.get<ProtoMap>();
		params.protoCar 		= js["proto_car"]	.get<ProtoCar>();
	}
}

void from_json(json const &js, Message &msg) 
{
	string const type = js["type"].get<string>();
	msg.type = type == "tick" ? Message::Tick : Message::MatchBegin;
	msg.params = js["params"].get<MessageParams>();
}

void read(Message &message)
{
	json js{};
	std::cin >> js;
	message = js;
}

void write(Response const &response)
{
	json js = response;
	std::cout << js << std::endl;
}

} // model namespace