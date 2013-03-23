#ifndef __G_MATRIX_TIER1_STATS_H
#define __G_MATRIX_TIER1_STATS_H

#include <iostream>
#include <ctime>

class FuncTimer {
	time_t start;
	double *_milliseconds;
	
	public:
	FuncTimer(double &__milliseconds) 
	: _milliseconds(&__milliseconds)
	{ 
		start = clock(); 
	};

	~FuncTimer()
	{
		*_milliseconds = ((double)clock() - start) / CLOCKS_PER_SEC;
	}
};

class Timer {
	time_t c;
	
	public:
	Timer() 
	{ start(); };

	void start()
	{
		c = clock();
	}

	double getValue()
	{
		return ((double)clock() - c) / CLOCKS_PER_SEC;
	}
};

struct Stats {
    unsigned long adds, subtracts, multiplies, divides, assigns, compares, loops;
    double function, runtime;

    Stats() { reset(); };
    
    void reset() 
	{ 
		adds = subtracts = multiplies = divides = assigns = compares = loops = 0;
		runtime = function = 0;
	};
};

inline Stats &getStats() 
{
    static Stats stats;
    return stats;
}

#ifdef _G_MATRIX_USE_STATS
#define GMATRIX_STATS(STAT,X) getStats().STAT += X
#define GMATRIX_FUNC FuncTimer timer_##__FILE__##__LINE__(getStats().function)
#else
#define GMATRIX_STATS(STAT, X) 
#define GMATRIX_FUNC
#endif

inline std::ostream &operator <<(std::ostream &out, const Stats &s)
{
    out << "Adds=" << s.adds << std::endl
        << "Subtracts=" << s.subtracts << std::endl
        << "Multiplies=" << s.multiplies << std::endl
        << "Divides=" << s.divides << std::endl
        << "Assigns=" << s.assigns << std::endl
        << "Compares=" << s.compares << std::endl
        << "Loops=" << s.loops << std::endl
        << "Function=" << s.function << std::endl
        << "Runtime=" << s.runtime << std::endl;
}


#endif
