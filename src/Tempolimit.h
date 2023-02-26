#ifndef TEMPOLIMIT_H_
#define TEMPOLIMIT_H_

#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
using namespace std; 

enum class Tempolimit
{
	Innerorts = 50,
	Landstrasse = 100,
	Autobahn = std::numeric_limits<int>::max()
};

#endif
