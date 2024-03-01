#include <stdio.h>
#include <complex.h>
#include <math.h>
#include "ppm.h"

#define TRSH 2.0         // Convergence threshold for the Mandelbrot set.
#define ITER 1024ull     // Maximum number of iterations to determine if a point belongs to the Mandelbrot set.
#define SIZEX 1500       // Image X dimension.
#define SIZEY 1500       // Image Y dimension.

/**
 * @brief Computes the real part corresponding to the x coordinate on the Mandelbrot scale.
 * @param x The x coordinate.
 * @return The real part of the x coordinate on the Mandelbrot scale.
 */
double cx(int x) {
    static const double qx = 3.0 / (double)SIZEX;
    return -2.0 + x * qx;
}

/**
 * @brief Computes the imaginary part corresponding to the y coordinate on the Mandelbrot scale.
 * @param y The y coordinate.
 * @return The imaginary part of the y coordinate on the Mandelbrot scale.
 */
double cy(int y) {
    static const double qy = 2.0 / (double)SIZEY;
    return -1.0 + y * qy;
}


int main(int argc, char *argv[]) {
    struct ppm_image im;
    ppm_image_init(&im, SIZEX, SIZEY);

    int i, j;
    double colref = 255.0 / log(ITER);    // Computes a color reference based on the maximum number of iterations.

    // Iterates over all pixels of the image.
    for (i = 0; i < SIZEX; ++i) {
        for (j = 0; j < SIZEY; ++j) {

            unsigned long int iter = 0;

            double complex c = cx(i) + cy(j) * I;    // Computes the complex number corresponding to the pixel coordinates.
            double complex z = 0;

            // Iteration loop to determine the point's membership to the Mandelbrot set.
            while (iter < ITER) {
                double mod = cabs(z);

                if (TRSH < mod) {
                    break;
                }

                z = z * z + c;

                iter++;
            }

            int grey = colref * log(iter);    // Computes a grayscale value based on the number of iterations.
            ppm_image_setpixel(&im, i, j, grey, grey, grey);
        }
    }

    ppm_image_dump(&im, "m.ppm");    // Saves the generated PPM image to a file.
    ppm_image_release(&im);

    return 0;
}
