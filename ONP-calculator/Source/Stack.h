#pragma once

template<typename T>
class Stack
{
	struct Element
	{
		T value;
		Element* next = nullptr;
		Element* prior = nullptr;
	};

	Element* top = nullptr;

public:

	void push(const T&);
	T pop();
};
