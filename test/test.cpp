#include <fractal/fractal.h>

#include <random>

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("Test zero", "[mandelbrot]") {
	const int iterations = 100;
    REQUIRE(fractal_mandelbrot(0.f, 0.f, iterations) > iterations);
}

TEST_CASE("Test bulk", "[mandelbrot]") {
    const int iterations = 100;
    const int MAX = 10;
    double xs[MAX];
    double ys[MAX];
    int res[MAX];

    std::uniform_real_distribution<double> unif(-10.0, 10.0);
    std::default_random_engine re;

    for (int i = 0; i < MAX; i++)
    {
        xs[i] = unif(re);
        ys[i] = unif(re);
    }
    
    fractal_mandelbrot_bulk(xs, ys, MAX, res, iterations);
    for (int i = 0; i < MAX; i++)
    {
        REQUIRE(res[i] == fractal_mandelbrot(xs[i], ys[i], iterations));
    }
}

