#pragma once
#include <memory>
template<typename T>
class Option
{
private:
	std::unique_ptr<T> element;
	bool is_none;
public:
	operator int() { return !is_none; }
	bool isNone() const;
	T value() const;
	Option(std::unique_ptr<T> element);
	Option();
};

template<typename T>
bool Option<T>::isNone() const
{
	return this->is_none;
}

template<typename T>
T Option<T>::value() const
{
	if (is_none) { throw "ERROR: Object was none"; }
	return *this->element;
}

template<typename T>
Option<T>::Option(std::unique_ptr<T> element)
{
	this->element = std::move(element);
	this->is_none = false;
}

template<typename T>
Option<T>::Option()
{
	this->element = nullptr;
	this->is_none = true;
}

