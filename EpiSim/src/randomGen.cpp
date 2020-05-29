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
	unsigned int max_num = 0;
	//Get highest possible value
	switch (i_type_)
	{
	case 0:
		max_num = genmersenne_.max();
		break;
	case 1:
		max_num = gendevice_.max();
		break;
	case 2:
		max_num = gentaus_.max();
		break;
	default:
		max_num = -1;
		break;
	}
	//Get the random number and divide by max value
	double rand = next();
	double factor = rand/max_num;
	//Perform the Lerp
	return (1 - factor) * min + factor*max;
}



