/**
 * @file ppm.h
 * @brief Library for PPM image file generation.
 */

#ifndef PPM_H
#define PPM_H

/**
 * @struct ppm_pixel
 * @brief Structure representing a single pixel in a PPM image.
 */
struct ppm_pixel {
  unsigned char r; /**< Red channel value */
  unsigned char g; /**< Green channel value */
  unsigned char b; /**< Blue channel value */
};

/**
 * @brief Sets the RGB values of a pixel.
 * @param px Pointer to the pixel to be set.
 * @param r Red channel value.
 * @param g Green channel value.
 * @param b Blue channel value.
 */
static inline void ppm_setpixel(struct ppm_pixel *px, unsigned char r,
                                unsigned char g, unsigned char b) {
  px->r = r;
  px->g = g;
  px->b = b;
}

/**
 * @struct ppm_image
 * @brief Structure representing a PPM image.
 */
struct ppm_image {
  unsigned int width; /**< Width of the image */
  unsigned int height; /**< Height of the image */
  struct ppm_pixel *px; /**< Pixel data */
};

/**
 * @brief Initializes a PPM image with specified width and height.
 * @param im Pointer to the ppm_image structure to initialize.
 * @param w Width of the image.
 * @param h Height of the image.
 * @return 0 on success, -1 on failure.
 */
int ppm_image_init(struct ppm_image *im, int w, int h);

/**
 * @brief Releases memory allocated for a PPM image.
 * @param im Pointer to the ppm_image structure to release.
 * @return 0 on success, -1 on failure.
 */
int ppm_image_release(struct ppm_image *im);

/**
 * @brief Sets the RGB values of a pixel in a PPM image.
 * @param im Pointer to the ppm_image structure.
 * @param x X-coordinate of the pixel.
 * @param y Y-coordinate of the pixel.
 * @param r Red channel value.
 * @param g Green channel value.
 * @param b Blue channel value.
 */
static inline void ppm_image_setpixel(struct ppm_image *im, int x, int y,
                                      unsigned char r, unsigned char g,
                                      unsigned char b) {
  struct ppm_pixel *px = im->px + im->width * y + x;
  ppm_setpixel(px, r, g, b);
}

/**
 * @brief Writes the contents of a PPM image to a file.
 * @param im Pointer to the ppm_image structure.
 * @param path Path to the file where the image will be written.
 * @return 0 on success, -1 on failure.
 */
int ppm_image_dump(struct ppm_image *im, char *path);

#endif /* PPM_H */
