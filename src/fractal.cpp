#include <fractal/fractal.h>

#include <complex>

int fractal_mandelbrot(double x, double y, int max_iterations)
{
    using namespace std;

    complex<double> point(x, y);
    complex<double> z(0, 0);

    int iteration = 0;
    while (abs (z) < 2 && iteration <= max_iterations) 
    {
        z = z * z + point;
        iteration++;
    }
    return iteration;
}

void fractal_mandelbrot_bulk(double* x, double* y, int count, int* results, int max_iterations)
{
	#pragma omp parallel for
	for (int i = 0; i < count; i++)
	{
		results[i] = fractal_mandelbrot(x[i], y[i], max_iterations);
	}
}
