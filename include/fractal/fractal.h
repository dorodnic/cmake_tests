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
int fractal_mandelbrot(double x, double y, int max_iterations);

/* 
* Fills the escape times in iterations of points (x..,y..) from the mandlebrot set
* \param[in] x                  X coordinates of the starting point
* \param[in] y                  Y coordinates of the starting point
* \param[in] count              Number of input points
* \param[in] results            Pointer to the array where to store escape times
* \param[in] max_iterations     Maximum number of iterations to perform
*/
void fractal_mandelbrot_bulk(double* x, double* y, int count, int* results, int max_iterations);

#ifdef __cplusplus
}
#endif

#endif /* FRACTAL_H */
