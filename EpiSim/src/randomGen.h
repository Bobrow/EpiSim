#pragma once
#include <boost/random.hpp>
#include <boost/random/random_device.hpp>

class randomGen
{
public:
	void seed(int type);
	double next();
	double nextBetween(double min, double max);
	enum
	{
		mersenne,
		device,
		taus
	};
private:
	boost::mt19937 genmersenne_;
	boost::random_device gendevice_;
	boost::taus88 gentaus_;
	int i_type_ = 0;
};

