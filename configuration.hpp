#ifndef CONFIGURATION_HPP
#define CONFIGURATION_HPP

#include <vector>
#include <string>

namespace model {

using i64 = unsigned long int;
using f64 = double;

template <typename T>
using vector = std::vector<T>;

using string = std::string;

struct Point2D 
{
	f64 x, y;
};

struct Transform2D 
{
	f64 x, y;
	f64 angle;
};

struct Segment
{
	Point2D startPoint;
	Point2D endPoint;
};

struct ProtoMap
{
	i64 id;
	vector<Segment> segments;
};

struct ProtoCar
{
	i64 id;

	vector<Point2D> buttonPolygon;

	struct BodyConfiguration
	{
		vector<Point2D> polygon;
		i64 mass;
		f64 friction;
		f64 elasticity;
	};
	BodyConfiguration body;

	i64 maxSpeed;
	i64 maxAngularSpeed;
	f64 torque; // крутящий момент кузова в воздухе

	enum DriveType {
		FF = 1,
		FR = 2,
		AWD = 3
	};
	DriveType drive; // привод машины: передний, задний, полный (?)

	struct WheelConfiguration // настройки колеса
	{
		Point2D position; // относительно кузова машины
		Point2D joint; // положение жесткого соединения

		i64 mass;
		f64 friction; // трение
		f64 elasticity; 
		i64 radius;

		struct DampConfiguration // настройки пружины
		{
			Point2D position;
			i64 length;
			f64 stiffness; // жесткость
			f64 damping; // затухание
		};
		DampConfiguration damp;
	};
	WheelConfiguration rearWheel;
	WheelConfiguration frontWheel;

	bool isSquared;
};

struct Car
{
	enum Direction {
		Left = 1, Right = -1
	};

	Point2D position;
	f64 angle;
	Direction direction; // 1 | -1 - слева или справа находится машина
	Transform2D rearWheel; // левый нижний угол заднего колеса машины
	Transform2D frontWheel; // левый нижний угол заднего колеса машины
};

struct MessageParams
{
	i64 		myLives;
	i64 		enemyLives;
	ProtoMap 	protoMap;
	ProtoCar 	protoCar;
	Car 		myCar;
	Car 		enemyCar;
	f64			garbagePosition;
};

struct MessageType
{
	enum Type {
		MatchBegin, Tick	
	};
	Type value;
};

struct Message
{
	MessageType type;
	MessageParams params;
};

struct Command
{
	enum Type {
		Left = 0, Right, Stop, Count
	};
	Type value;
};

struct DebugMessage
{
	string msg;
};

struct Response
{
	Command command;
	DebugMessage debug;
};


} // model

#endif //CONFIGURATION_HPP