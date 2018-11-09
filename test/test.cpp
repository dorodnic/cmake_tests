#include <fractal/fractal.h>

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("Test zero", "[mandelbrot]") {
	const int iterations = 100;
    REQUIRE(fractal_mandelbrot(0.f, 0.f, iterations) > iterations);
}
