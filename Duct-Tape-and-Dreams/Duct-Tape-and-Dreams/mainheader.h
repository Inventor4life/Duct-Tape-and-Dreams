#ifndef mainheader_H
#define mainheader_H

// Before release, switch all SFML files from xxx-s-d.lib to xxx-s.lib

#define SOL_ALL_SAFTIES_ON 1
#define FILE_NOT_FOUND -20
#define FILE_ERROR -21
#define BAD_INPUT 10
#define INVALID_VALUE -10
#define SETTING_ALREADY_EXISTS -12
#define FAILED_ALLOC -30
#define SETTING_NOT_FOUND -11
#define _CRT_SECURE_NO_WARNINGS

#include <sol/sol.hpp>
#include <stdio.h>

//nice to have more libraries then ya need, no? ;3
#include <iostream>  
#include <ostream>
#include <string>      
#include <vector>    
#include <map>     
#include <algorithm>   
#include <stdexcept>  
#include <fstream>
#include <sstream>

//these are used QUITE frequently so might as well
using std::cout;
using std::cin;
using std::string;
using std::ifstream;
using std::ofstream;


//aight, so ENUM's are still a fucky concept to me, but i THINK this is how it goes
enum dataType {
	STRING = 1,
	INT = 2,
	DOUBLE = 3,
}; //i guess this works? who knows >.>

#endif