#define _GNU_SOURCE
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <sched.h>
#include <signal.h>

/* Needed for wait(...) */
#include <sys/types.h>
#include <sys/wait.h>

/* Needed for semaphores */
#include <semaphore.h>

/* Include struct definitions and other libraries that need to be
 * included by both client and server */
#include "common.h"

/* Simple smoke test for key functions in imglib and md5lib. */
int main (int argc, char ** argv) {
	const char * input_path = argc > 1 ? argv[1] : "images/test1.bmp";
	uint8_t img_err;

	struct md5digest md5dig = file_md5sum(input_path);
	print_digest(md5dig);

	struct image * img_test = loadBMP(input_path);
	if (!img_test) {
	    perror("Unable to load image.");
	    return EXIT_FAILURE;
	}

	int err = saveBMP("build/sample_out.bmp", img_test);
	if (err) {
	    perror("Unable to save image.");
	}

	struct image * img_rot = rotate90Clockwise(img_test, NULL);

	err = saveBMP("build/sample_rot.bmp", img_rot);
	if (err) {
	    perror("Unable to save image.");
	}

	struct image * img_sharp = sharpenImage(img_test, &img_err);

	err = saveBMP("build/sample_sharp.bmp", img_sharp);
	if (err) {
	    perror("Unable to save image.");
	}

	struct image * img_blur = blurImage(img_test, &img_err);

	err = saveBMP("build/sample_blur.bmp", img_blur);
	if (err) {
	    perror("Unable to save image.");
	}

	struct image * img_vert = detectVerticalEdges(img_test, &img_err);

	err = saveBMP("build/sample_vert.bmp", img_vert);
	if (err) {
	    perror("Unable to save image.");
	}

	struct image * img_horiz = detectHorizontalEdges(img_test, &img_err);

	err = saveBMP("build/sample_horiz.bmp", img_horiz);
	if (err) {
	    perror("Unable to save image.");
	}

	deleteImage(img_test);
	deleteImage(img_rot);
	deleteImage(img_sharp);
	deleteImage(img_blur);
	deleteImage(img_vert);
	deleteImage(img_horiz);

	return EXIT_SUCCESS;
}
