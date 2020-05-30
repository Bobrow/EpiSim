#include "randomGen.h"

void randomGen::seed(int type)
{
	//Set internal type to type given as parameter
	i_type_ = type;
	//Go through and seed selected generator using the random device
	switch (type)
	{
	case 0:
		genmersenne_.seed(gendevice_());
		break;

	case 1:
		break;

	case 2:
		gentaus_.seed(gendevice_());
		break;

	default:
		break;
	}
}

double randomGen::next()
{
	//Get type and return random number using that generator
	switch (i_type_)
	{
	case 0:
		return  static_cast<double>(genmersenne_());

	case 1:
		return static_cast<double>(gendevice_());

	case 2:
		return static_cast<double>(gentaus_());

	default:
		return static_cast<double>(0);

	}
}

double randomGen::nextBetween(double min, double max)
{
	//Based on i_type_ generate random number and use uniform distribution
	boost::uniform_int<> min_to_max(min, max);
	switch (i_type_)
	{
	case 0:
		return min_to_max(genmersenne_);
		break;
	case 1:
		return min_to_max(gendevice_);
		break;
	case 2:
		return min_to_max(gentaus_);
		break;
	default:
		return -1;
		break;
	}
}



