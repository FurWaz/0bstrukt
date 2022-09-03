#include "Callback.h"

void Callback::setCallback(void (*c)())
{
	this->callback = c;
}

void Callback::call()
{
	if (this->callback != nullptr)
		this->callback();
}