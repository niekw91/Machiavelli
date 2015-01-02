#pragma once

#include <functional>
#include <string>

using namespace std;

class Option {
public:
	Option(string text, bool permanent, function<void()> &callback) : _text(text), _permanent(permanent), _callback(callback){ }

	string GetText() { return _text; }
	bool isPermanent() { return _permanent; }
	function<void()> &getCallback() { return _callback; }

	void doAction() { _callback(); }
protected:
	bool _permanent;
	string _text;
	function<void()> _callback;
};