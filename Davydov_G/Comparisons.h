#ifndef �omparisons_HPP
#define �omparisons_HPP


#include <iostream>
#include <vector>
#include <string>

using namespace std;


struct System {
	int b;
	int m;
};


class �omparisons {
public:
	void Computer();

private:
	void transform(string expression, vector<System>& systems, int& error);
	bool validation(string expression);
	void Notation_Rules();
	void remove_spaces(string& expression);
	bool compatibility_check(vector<System> systems);
};

#endif