#include "structs.h"
map *create_map(int w, int h);
void print_map(map *grid);
void free_map(map *grid);
double ran_rad_vec();
map *prepear_map(map *grd);
double noise(map *grd,double x,double y);
map *perlin_noise_map(int w, int h,int sampling);
int val_to_colour(double val);
void create_image(map *noise);
double normalize_val(double val,double min,double max);