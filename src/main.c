#include<stdbool.h>
#include<stdlib.h>
#include<stdio.h>
#include<X11/Xlib.h>
#include<unistd.h>

#include "vroot.h"
#include "life.c"

//Display *dpy;
//Window root;
//GC g;

void display_grid(bool *current_gen, size_t grid_len, 
		  size_t nof_horizontal_boxes, size_t nof_vertical_boxes,
		  size_t box_length,
		  Display *dpy, Window root, GC g,
		  size_t *x_coordinates,
		  size_t *y_coordinates){
    /* draw a square */
    size_t x_index, y_index;
    for(size_t grid_index=0; grid_index<grid_len; ++grid_index){
       x_index = grid_index2x_index(grid_index, nof_horizontal_boxes, nof_vertical_boxes);
       y_index = grid_index2y_index(grid_index, nof_horizontal_boxes, nof_vertical_boxes);

       if( current_gen[grid_index] ){
          XFillRectangle (dpy, root, g, x_coordinates[x_index], y_coordinates[y_index], 
      	            box_length, box_length);

       }
    }
}

int main(){
	/* open the display (connect to the X server) */
	Display *dpy = XOpenDisplay (getenv ("DISPLAY"));
	
	/* get the root window */
	Window root = DefaultRootWindow (dpy);
	
	/* get attributes of the root window */
	XWindowAttributes wa;
	XGetWindowAttributes(dpy, root, &wa);
	
	/* create a GC for drawing in the window */
	GC g = XCreateGC (dpy, root, 0, NULL);
	
	/* set foreground color */
	XSetForeground(dpy, g, WhitePixelOfScreen(DefaultScreenOfDisplay(dpy)) );
	
	/* translation: coordinates to life grid */
	size_t box_length = 120 / 10;
	size_t nof_vertical_boxes = (/*wa.height*/1080 / box_length);
	size_t nof_horizontal_boxes = (/*wa.width*/ 1920 / box_length);
	size_t nof_boxes = nof_horizontal_boxes * nof_vertical_boxes;
	
	size_t generation_counter = 0;
	bool grid_A[nof_boxes];
	initialize_grid_A(grid_A, nof_boxes);

	bool grid_B[nof_boxes];

	size_t x_coordinates[nof_horizontal_boxes];
	size_t y_coordinates[nof_vertical_boxes];

	initialize_coordinates(x_coordinates, nof_horizontal_boxes, wa.width);
	initialize_coordinates(y_coordinates, nof_vertical_boxes, wa.height);

	while (1){

    		//printf("%zu (%zu, %zu) - (%zu, %zu)  \n", 
           	//       grid_index, x_index, y_index, x_coordinates[x_index], y_coordinates[y_index]);
    
    
    
    		display_grid(grid_A, nof_boxes, nof_horizontal_boxes, nof_vertical_boxes, box_length, dpy, root, g, x_coordinates, y_coordinates);
		update_grid(grid_A, grid_B, nof_boxes, nof_horizontal_boxes, nof_vertical_boxes);

    		/* flush changes and sleep */
    		XFlush(dpy);
    		usleep (1000000);
    		XClearWindow(dpy, root);
    		++generation_counter;

    		display_grid(grid_B, nof_boxes, nof_horizontal_boxes, nof_vertical_boxes, box_length, dpy, root, g, x_coordinates, y_coordinates);
		update_grid(grid_B, grid_A, nof_boxes, nof_horizontal_boxes, nof_vertical_boxes);

    		/* flush changes and sleep */
    		XFlush(dpy);
    		usleep (1000000);
    		XClearWindow(dpy, root);
    		++generation_counter;
  	}
	XCloseDisplay (dpy);
}
