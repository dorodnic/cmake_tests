#ifndef FRACTAL_H
#define FRACTAL_H

#ifdef __cplusplus
extern "C" {
#endif

/* 
* Return the escape time in iterations of point (x,y) from the mandlebrot set
* \param[in] x                  X coordinate of the starting point
* \param[in] y                  Y coordinate of the starting point
* \param[in] max_iterations     Maximum number of iterations to perform
* \return                       Number of iterations until the point escapes
                                from the local neighborhood of zero
*/
int fractal_mandelbrot(float x, float y, int max_iterations);

#ifdef __cplusplus
}
#endif

#endif /* FRACTAL_H */
