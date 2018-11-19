#include <fractal/fractal.h>
#include <iostream>

int main() 
{
    std::cout << fractal_mandelbrot(0.f, 0.f, 100) << std::endl;
}
