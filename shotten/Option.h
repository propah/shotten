#pragma once

template<typename T>
class Option
{
private:
	T* element;
	bool is_none;
public:
	operator int() { return !is_none; }
	bool isNone();
	T value();
	Option(T* element);
	Option();
};

template<typename T>
bool Option<T>::isNone()
{
	return this->is_none;
}

template<typename T>
T Option<T>::value()
{
	if (is_none) { throw "ERROR: Object was none"; }
	return *this->element;
}

template<typename T>
Option<T>::Option(T* element)
{
	this->element = element;
	this->is_none = false;
}

template<typename T>
Option<T>::Option()
{
	this->element = nullptr;
	this->is_none = true;
}

