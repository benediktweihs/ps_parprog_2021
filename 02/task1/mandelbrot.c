#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Include that allows to print result as an image
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

// Default size of image
#define X 1280
#define Y 720
#define X_MAX 1.
#define X_MIN -2.5
#define Y_MAX 1.
#define Y_MIN -1.
#define PX_RANGE 255.
#define MAX_ITER 10000

void calc_mandelbrot(uint8_t image[Y][X]) {
	// parallel executino should not be a problem for this problem
	// all iterations are completely independent from each other
	// each process could be assigned to a certain (range of) pixel(s)
	double x, y, x_tmp, norm_iteration, cx, cy;
	int iteration;
	for(int i = 0; i < X; i++){
		for(int j = 0; j < Y; j++){
            x = 0.;
			y = 0.;
            cx = (X_MAX - X_MIN) * ((double) i/X) + X_MIN;
            cy = (Y_MAX - Y_MIN) * ((double) j/Y) + Y_MIN;
			iteration = 0;

			while((x*x + y*y <= 2*2) & (iteration < MAX_ITER)){
				x_tmp = x*x - y*y + cx;
				y = 2*x*y + cy;
				x = x_tmp;
				iteration++;
			}

			norm_iteration = ((double) iteration) / ((double) MAX_ITER) * PX_RANGE;
		    image[j][i] = norm_iteration;
		}
	}
}

int main() {
	uint8_t image[Y][X];
    struct timespec s, ending;
    clock_gettime(CLOCK_REALTIME, &s);
	calc_mandelbrot(image);
    clock_gettime(CLOCK_REALTIME, &ending);
    double start = (double) s.tv_sec + (double) s.tv_nsec * 1e-9;
    double end = (double) ending.tv_sec + (double) ending.tv_nsec * 1e-9;


	const int channel_nr = 1, stride_bytes = 0;
	stbi_write_png("mandelbrot.png", X, Y, channel_nr, image, stride_bytes);
	printf("exec-time: %2.5f\n", end - start);
	return EXIT_SUCCESS;
}