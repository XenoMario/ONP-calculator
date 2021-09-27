#pragma once

template<typename T>
class Stack
{
	int size = 0;

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

	bool isempty() const { return size > 0 ? 0 : 1 };
};
