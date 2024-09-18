#ifndef mainheader_H
#define mainheader_H

// Before release, switch all SFML files from xxx-s-d.lib to xxx-s.lib

#define SOL_ALL_SAFTIES_ON 1

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


#endif