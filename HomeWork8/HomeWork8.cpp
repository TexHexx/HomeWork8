#include <iostream>
#include <string>
#include <vector>
#include <exception>
#include <algorithm>
//First task
class DivisionByZero : public std::exception {
private:
	std::string _error;
public:
	explicit DivisionByZero(const std::string& error = "Can not divide by zero") : _error(error) {};
	const char* what() const noexcept { return _error.c_str(); };
};

template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
const T& div(const T& a, const T& b) {
	if (b == 0)
		throw DivisionByZero();
	return a / b;
};

void FirstTask() {
	try {
		auto c = div<double>(5.0f, 0.0f);
		std::cout << c << std::endl;
	}
	catch (DivisionByZero ex) {
		std::cout << "Crash bang: " << ex.what() << std::endl;
	};
};
//First task

//Second task
class Ex : public std::exception {
private:
	double _x;
	std::string _error;
public:
	explicit Ex(double x) : _x(x), _error(std::to_string(_x)) {};
	const char* what() const noexcept { return _error.c_str(); };
};

class Bar {
private:
	double _y;
public:
	Bar() : _y(0) {};
	void set(double a) {
		if (_y + a > 100)
			throw Ex(a * _y);
		_y = a;
	};
};

void SecondTask() {
	double y = 0;
	Bar bar;
	do {
		std::cout << "Enter a number(0 for exit): ";
		std::cin >> y;
		if (std::cin.fail()) {
			std::cout << "Input string is not a number, try again" << std::endl;
			continue;
		}
		try {
			bar.set(y);
			std::cout << "All is ok, lets continue" << std::endl;
		}
		catch (Ex ex) {
			std::cout << "Crash bang: " << ex.what() << std::endl;
		};
	} while (y != 0);
};

//Second task

//Third task
enum class moveDirection {
	right = 0,
	left = 1,
	up = 2,
	down = 3
};

const std::vector<std::string> printDirections{ "right", "left", "up", "down" };

class IllegalCommand : public std::exception {
private:
	std::string _error;
	std::pair<int, int> _position;
	moveDirection _direction;
public:
	explicit IllegalCommand(const std::pair<int, int>& position, const moveDirection& direction, const std::string& error = "Direction not supported") : _error(error + ". Current position: (" + std::to_string(position.first) + ", " + std::to_string(position.second) + "). Current direction: " + printDirections[static_cast<int>(direction)]), _position(position), _direction(direction) {};
	const char* what() const noexcept { return _error.c_str(); };
};

class OffTheField : public std::exception {
private:
	std::string _error;
	std::pair<int, int> _position;
	moveDirection _direction;
public:
	explicit OffTheField(const std::pair<int, int>& position, const moveDirection& direction, const std::string& error = "Can not move out the field") : _error(error + ". Current position: (" + std::to_string(position.first) + ", " + std::to_string(position.second) + "). Current direction: " + printDirections[static_cast<int>(direction)]), _position(position), _direction(direction) {};
	const char* what() const noexcept { return _error.c_str(); };
};

class Robot {
private:
	std::string _printState;
	std::pair<int, int> _position;
	moveDirection _direction;
public:
	Robot() : _position(std::pair<int, int>(0, 0)), _direction(moveDirection::right) {};
	void move(const moveDirection& direction) {
		switch (direction) {
			case moveDirection::up:
				if (_direction == moveDirection::down)
					throw IllegalCommand(_position, _direction);
				if(_position.second == 9)
					throw OffTheField(_position, _direction);
				++_position.second;
				break;
			case moveDirection::down:
				if (_direction == moveDirection::up)
					throw IllegalCommand(_position, _direction);
				if (_position.second == 0)
					throw OffTheField(_position, _direction);
				--_position.second;
				break;
			case moveDirection::left:
				if (_direction == moveDirection::right)
					throw IllegalCommand(_position, _direction);
				if (_position.first == 0)
					throw OffTheField(_position, _direction);
				--_position.first;
				break;
			case moveDirection::right:
				if (_direction == moveDirection::left)
					throw IllegalCommand(_position, _direction);
				if (_position.first == 9)
					throw OffTheField(_position, _direction);
				++_position.first;
				break;
		};
		_direction = direction;
		_printState = "Position: (" + std::to_string(_position.first) + "," + std::to_string(_position.second) + "). Direction: " + printDirections[static_cast<int>(_direction)];
	};
	const std::string& getState() const {
		return _printState;
	};
};

void ThirdTask() {
	Robot robot;
	std::cout << "Lets play a game" << std::endl;
	while (true) {
		char direction;
		std::cout << "Enter direction(a,w,s,d): ";
		std::cin >> direction;
		try {
			switch (direction) {
			case 'a':
				robot.move(moveDirection::left);
				break;
			case 'w':
				robot.move(moveDirection::up);
				break;
			case 's':
				robot.move(moveDirection::down);
				break;
			case 'd':
				robot.move(moveDirection::right);
				break;
			default:
				std::cout << "Unknown command, try again." << std::endl;
				continue;
			};
			std::cout << robot.getState() << std::endl;
		}
		catch (IllegalCommand ex) {
			std::cout << ex.what() << std::endl;
		}
		catch (OffTheField ex) {
			std::cout << ex.what() << std::endl;
		}
	};
};

//Third task
int main() {
	//FirstTask();
	//SecondTask();
	//ThirdTask();
}
