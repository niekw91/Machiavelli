#pragma once

#include <functional>
#include <string>

using namespace std;

class Option {
public:
	Option(string key, string text, bool permanent, function<void()> &callback) : _key(key), _text(text), _permanent(permanent), _callback(callback){ }

	string GetKey() { return _key; }
	string GetText() { return _text; }
	bool isPermanent() { return _permanent; }
	function<void()> &getCallback() { return _callback; }

	void doAction() { _callback(); }
protected:
	string _key;
	string _text;
	bool _permanent;
	function<void()> _callback;
};