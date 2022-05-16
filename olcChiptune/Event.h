#pragma once
class Event {
public:

	/// <summary>
	/// Defines a FUNCTION to be called as a result of an event occurring
	/// </summary>
	typedef bool CallbackFunction(int);

	Event(CallbackFunction func);

private:


};

