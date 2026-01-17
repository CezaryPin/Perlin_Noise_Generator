#define _USE_MATH_DEFINES
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdio.h>
#include "utils.h"
#include "structs.h"
#include "map_gen.h"

int main(){
    map *perlin=perlin_noise_map( 10, 10, 100);
    //print_map(perlin);
    create_image(perlin);
    free_map(perlin);


    return 0;

}

map *create_map(int w, int h){
    map *grd=malloc(sizeof(map));
    grd->vector_map=calloc(w,sizeof(double*));
    grd->w=w;
    grd->h=h;
    for(int i=0;i<w;i++)
        grd->vector_map[i]=calloc(h,sizeof(double)); 
    return grd;
}
void print_map(map *grid){
    printf("w: %d   h:%d\n",grid->w,grid->h);
    for(int i=0;i<grid->w;i++){
        for(int j=0;j<grid->h;j++){
            printf("%f ",grid->vector_map[i][j]);
        }
        printf("\n");
    }
}

void free_map(map *grid){
    for(int i=0;i<grid->w;i++)
        free(grid->vector_map[i]);
    free(grid->vector_map);
    free(grid);
}

double ran_rad_vec(){
    return M_PI*rand_percent();
}
map *prepear_map(map *grd){
    for(int i=0;i<grd->w;i++){
        for(int j=0;j<grd->h;j++){
            grd->vector_map[i][j]=ran_rad_vec();
        }    
    }
    return grd;
}

double noise(map *grd, double x, double y) {
    int x0 = (int)floor(x);
    int x1 = x0 + 1;
    int y0 = (int)floor(y);
    int y1 = y0 + 1;

    if (x1 >= grd->w || x0 < 0 || y1 >= grd->h || y0 < 0)
        return 0;

    
    double tx = x - (double)x0;
    double ty = y - (double)y0;
    // Wygładzanie wag (Fade function)
    double stx = tx * tx * (3 - 2 * tx);
    double sty = ty * ty * (3 - 2 * ty);




    
    // Bottom-Left (x0, y0)
    double g0 = grd->vector_map[x0][y0];
    double d0 = (tx - 0.0) * cos(g0) + (ty - 0.0) * sin(g0);

    // Bottom-Right (x1, y0)
    double g1 = grd->vector_map[x1][y0];
    double d1 = (tx - 1.0) * cos(g1) + (ty - 0.0) * sin(g1);

    // Top-Left (x0, y1)
    double g2 = grd->vector_map[x0][y1];
    double d2 = (tx - 0.0) * cos(g2) + (ty - 1.0) * sin(g2);

    // Top-Right (x1, y1)
    double g3 = grd->vector_map[x1][y1];
    double d3 = (tx - 1.0) * cos(g3) + (ty - 1.0) * sin(g3);

    
    double lerp_bottom = d0 + stx * (d1 - d0);
    double lerp_top    = d2 + stx * (d3 - d2);


    double final = lerp_bottom + sty * (lerp_top - lerp_bottom);

    return final;
}

map *perlin_noise_map(int w, int h, int sampling) {
    init_rand();
    
    map *grid = create_map(w + 1, h + 1);
    grid = prepear_map(grid);
    
    int target_w = w * sampling;
    int target_h = h * sampling;
    map *noise_map = create_map(target_w, target_h);
    
    for (int i = 0; i < target_w; i++) {
        for (int j = 0; j < target_h; j++) {
            double x = ((double)i + 0.1) / sampling; 
            double y = ((double)j + 0.1) / sampling;
            
            noise_map->vector_map[i][j] = noise(grid, x, y);
        }
    }
    
    free_map(grid); 
    return noise_map;
}

int val_to_colour(double val){
    int tmp=round((val+1)*0.5*255);
    if(tmp<0)
        return 0;
    if(tmp>255)
        return 255;
    return tmp;
}

void create_image(map *noise){
    FILE *fptr=fopen("image.ppm","w+");
    fprintf(fptr,"P3\n");
    fprintf(fptr,"%d %d\n",noise->w,noise->h);
    fprintf(fptr,"255\n");

    for(int i=0;i<noise->h;i++){
        for(int j=0;j<noise->w;j++){
            int x=val_to_colour(noise->vector_map[j][i]);
            if(j!=noise->w-1){
                fprintf(fptr,"%d %d %d ",x,x,x);
            }
            else
                fprintf(fptr,"%d %d %d\n",x,x,x);
        }
    }
    fclose(fptr);
}