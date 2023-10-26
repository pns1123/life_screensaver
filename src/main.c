#include<stdbool.h>
#include<stdlib.h>
#include<stdio.h>
#include<X11/Xlib.h>
#include<unistd.h>

#include "vroot.h"
#include "life.c"
#include "parser.c"

//Display *dpy;
//Window root;
//GC g;

#define BOX_LENGTH 10
#define NOF_HORIZONTAL_BOXES 192
#define NOF_VERTICAL_BOXES 108

void display_grid(bool *current_gen, unsigned int grid_len, 
		  unsigned int nof_horizontal_boxes, unsigned int nof_vertical_boxes,
		  unsigned int box_length,
		  Display *dpy, Window root, GC g,
		  unsigned int *x_coordinates,
		  unsigned int *y_coordinates){
    /* draw a square */
    unsigned int x_index, y_index;
    for(unsigned int grid_index=0; grid_index<grid_len; ++grid_index){
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
	//unsigned int box_length = 10;
	//unsigned int nof_vertical_boxes = (/*wa.height*/ 1080 / box_length);
	//unsigned int nof_horizontal_boxes = (/*wa.width*/ 1920 / box_length);
	//unsigned int nof_boxes = nof_horizontal_boxes * nof_vertical_boxes;
	bool grid_A[NOF_HORIZONTAL_BOXES * NOF_VERTICAL_BOXES] = { false };

	char *filename = "/home/philipp/.life_patterns/glider.rle";

	struct GridSize pattern_size = parse_grid_size(filename);                 
                                                                               
	bool pattern_arr[pattern_size.vertical * pattern_size.horizontal];                               
	parse_pattern(filename, pattern_arr, pattern_size.horizontal, pattern_size.vertical); 

	initialize_grid(grid_A, NOF_HORIZONTAL_BOXES, NOF_VERTICAL_BOXES,
	                pattern_arr, pattern_size.horizontal, pattern_size.vertical);
	
	unsigned int generation_counter = 0;
	//initialize_grid_A(grid_A, nof_boxes);

	bool grid_B[NOF_HORIZONTAL_BOXES * NOF_VERTICAL_BOXES];

	unsigned int x_coordinates[NOF_HORIZONTAL_BOXES];
	unsigned int y_coordinates[NOF_VERTICAL_BOXES];

	initialize_coordinates(x_coordinates, NOF_HORIZONTAL_BOXES, wa.width);
	initialize_coordinates(y_coordinates, NOF_VERTICAL_BOXES, wa.height);

	while (1){

    		//printf("%zu (%zu, %zu) - (%zu, %zu)  \n", 
           	//       grid_index, x_index, y_index, x_coordinates[x_index], y_coordinates[y_index]);
    
    
    
    		display_grid(grid_A, NOF_HORIZONTAL_BOXES * NOF_VERTICAL_BOXES, NOF_HORIZONTAL_BOXES, NOF_VERTICAL_BOXES, BOX_LENGTH, dpy, root, g, x_coordinates, y_coordinates);
		update_grid(grid_A, grid_B, NOF_HORIZONTAL_BOXES * NOF_VERTICAL_BOXES, NOF_HORIZONTAL_BOXES, NOF_VERTICAL_BOXES);

    		/* flush changes and sleep */
    		XFlush(dpy);
    		usleep (1000000);
    		XClearWindow(dpy, root);
    		++generation_counter;

    		display_grid(grid_B, NOF_HORIZONTAL_BOXES * NOF_VERTICAL_BOXES, NOF_HORIZONTAL_BOXES, NOF_VERTICAL_BOXES, BOX_LENGTH, dpy, root, g, x_coordinates, y_coordinates);
		update_grid(grid_B, grid_A, NOF_HORIZONTAL_BOXES * NOF_VERTICAL_BOXES, NOF_HORIZONTAL_BOXES, NOF_VERTICAL_BOXES);

    		/* flush changes and sleep */
    		XFlush(dpy);
    		usleep (1000000);
    		XClearWindow(dpy, root);
    		++generation_counter;
  	}
	XCloseDisplay (dpy);
}
