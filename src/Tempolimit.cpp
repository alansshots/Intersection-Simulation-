#pragma once
#include <limits>

//Definiert von Benutzer Datentyp fuer Tempolimit--------
enum class Tempolimit
{
	Innerorts = 50,
	Landstrasse = 100,
	Autobahn = std::numeric_limits<int>::max()
};
