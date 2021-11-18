#ifndef RANDOM_GENERATOR_H
#define RANDOM_GENERATOR_H
#include <ctime>
#include <cmath>
#include <cstdlib>
#include <iostream>

#define RandomDouble() RandomGenerator::getInstance().random()
#define RandomNormal() RandomGenerator::getInstance().randomNormal()

/** Class providing random numbers
*/
class RandomGenerator 
{
public:
	static RandomGenerator& getInstance() 
	{
		//TODO PS L czy to aby napewno jest dobra implementacja wzorca singleton?
		static RandomGenerator instance;
		return instance;
	}
	/** returns random double number from <0,1)
	*/
	double random() {
		return (double)rand() / (double) RAND_MAX;
	}

	/** return random floats with normal distribution
	mean m, standard deviation s
	*/
	float randomNormal(float m = 0.0, float s = 1.0)
	{
		float x1, x2, w, y1;
		static float y2;
		static int use_last = 0;

		if (use_last)		        /* use value from previous call */
		{
			y1 = y2;
			use_last = 0;
		}
		else
		{
			do {
				x1 = 2.0 * random() - 1.0;
				x2 = 2.0 * random() - 1.0;
				w = x1 * x1 + x2 * x2;
			} while ( w >= 1.0 );

			w = sqrt( (-2.0 * log( w ) ) / w );
			y1 = x1 * w;
			y2 = x2 * w;
			use_last = 1;
		}

		return( m + y1 * s );
	}
private:
	RandomGenerator() {
		srand(time(NULL));
	}
};

#endif //RANDOM_GENERATOR_H