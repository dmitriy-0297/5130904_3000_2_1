#ifndef COMANDS_H
#define COMANDS_H
#include<regex>
#include<functional>
#include<algorithm>
#include"Structs.h"

const std::string ERROR_OF_COMMAND = "<INVALID COMAND>";


int isIntOrDigit( std::string str);
void area( std::vector<sevostyanova::Polygon> & data, std::string & str);
void max( std::vector<sevostyanova::Polygon> & data, std::string & str);
void min( std::vector<sevostyanova::Polygon> & data, std::string & str);
void count( std::vector<sevostyanova::Polygon> & data, std::string & str);
void maxSeq( std::vector<sevostyanova::Polygon> & data);
void lessArea( std::vector<sevostyanova::Polygon> & data);

#endif
