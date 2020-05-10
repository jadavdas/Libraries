#ifndef Exception_HANDLING_H
#define Exception_HANDLING_H
//#pragma once

#include<string>
#include<exception>

struct myLibException
{
	myLibException(std::string m) : message(m) {}
	std::string what() const { return message; }
	std::string message;
};

class MatrixException : public myLibException
{
public:
	MatrixException(std::string s = std::string()) : myLibException(s) {	}
};

#endif //Exception_HANDLING_H
