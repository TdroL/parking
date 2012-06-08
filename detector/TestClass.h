#ifndef TESTCLASS_H
#define TESTCLASS_H

#include <vector>
#include <string>

class TestClass
{
public:
	void addResult(const char *name, bool status);
	void addResult(std::string &name, bool status);

	void run();
	virtual ~TestClass() {}
};

#endif