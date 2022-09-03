#pragma once
class Callback
{
private:
	void (*callback)() = nullptr;

public:
	Callback() {}
	Callback(void (*c)()) { this->setCallback(c); }

	void setCallback(void (*)());
	void call();
};