#include <fractal/fractal.h>

#include <complex>

int fractal_mandelbrot(float x, float y, int max_iterations)
{
    using namespace std;

    complex<float> point(x, y);
    complex<float> z(0, 0);

    int iteration = 0;
    while (abs (z) < 2 && iteration <= max_iterations) 
    {
        z = z * z + point;
        iteration++;
    }
    return iteration;
}
