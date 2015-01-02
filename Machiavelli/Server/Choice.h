#pragma once

#include <functional>
#include <string>

using namespace std;

class Choice {
public:
	Choice(string text, function<void()> &callback) : _text(text), _callback(callback){ }

	string GetText(){ return _text; }
	function<void()> &getCallback() { return _callback; }

	void doAction() { _callback(); }
protected:
	string _text;
	function<void()> _callback;
};