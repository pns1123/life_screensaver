#include<stdbool.h>
#include<stdlib.h>
#include<stdio.h>
//#include<X11/Xlib.h>

//#include "vroot.h"


void initialize_grid_A(bool *grid, size_t grid_size){
        for(size_t i=0; i<grid_size; ++i){
      	  grid[i] = false;
        }
        grid[241] = true;
        grid[242] = true;
        grid[243] = true;
}


void initialize_coordinates(size_t *arr, size_t nof_boxes, size_t nof_pixels){
        size_t offset = nof_pixels / nof_boxes;
        for(size_t i=0; i<nof_boxes; ++i){
      	  arr[i] = i*offset;
        }

}

size_t grid_index2x_index(size_t grid_index, size_t nof_horizontal_boxes,
      	            size_t nof_vertical_boxes){
        return grid_index % nof_horizontal_boxes;
}

size_t grid_index2y_index(size_t grid_index, size_t nof_horizontal_boxes,
      	            size_t nof_vertical_boxes){
        return grid_index / nof_horizontal_boxes;
}

size_t xy_index2grid_index(size_t x_index, size_t y_index, 
      	             size_t nof_horizontal_boxes){
        return y_index*nof_horizontal_boxes + x_index;
}

/* life */
bool on_grid(size_t x, size_t y, size_t x_max, size_t y_max){
   // return bool indicating if (x,y) index pair is on grid
   // lower bound (inclusive): 0
   // upper bound (exclusive): (x|y)_max
   return (0 <= x) && (x < x_max) && (0 <= y) && (y < y_max);
}

int sum_moore_neighboorhood(bool *life_grid, size_t grid_index, 
		            size_t nof_horizontal_boxes, size_t nof_vertical_boxes){
        int running_sum = 0;
        size_t x_index, y_index, neigh_grid_index;

        x_index = grid_index2x_index(grid_index, nof_horizontal_boxes, nof_vertical_boxes);
        y_index = grid_index2y_index(grid_index, nof_horizontal_boxes, nof_vertical_boxes);
        // arrays of x,y coordinates to traverse neighb. from top left clock-wise
        size_t x_neigh[8] = {x_index-1, x_index, x_index+1, x_index+1, 
      	               x_index+1, x_index, x_index-1, x_index-1};
        size_t y_neigh[8] = {y_index+1, y_index+1, y_index+1, y_index,
                             y_index-1, y_index-1, y_index-1, y_index};
        for(size_t neigh_index=0; neigh_index<8; ++neigh_index){
      
           if( on_grid(x_neigh[neigh_index], y_neigh[neigh_index], nof_horizontal_boxes,
      	         nof_vertical_boxes) ) {

              neigh_grid_index = xy_index2grid_index(x_neigh[neigh_index], 
      			                       y_neigh[neigh_index], 
      					       nof_horizontal_boxes);

              switch(life_grid[neigh_grid_index]) {
      	   case true: ++running_sum;
                 default: continue;
      	}
           }
        }
        return running_sum;
}

void swap(bool *a, bool *b){
	bool *temp = a;
	a = b;
	b = a;
}

void update_grid(bool *current_gen, bool *next_gen, size_t grid_len, size_t nof_horizontal_boxes,
		size_t nof_vertical_boxes){ 
    int neighboor_count;
    for(size_t grid_index=0; grid_index<grid_len; ++grid_index){
       neighboor_count = sum_moore_neighboorhood(current_gen, grid_index, 
		                                 nof_horizontal_boxes, nof_vertical_boxes);
       // a dead cell with exactly three living neighboors comes to life
       if ( !current_gen[grid_index] ){
          switch(neighboor_count) {
      	    case 3: next_gen[grid_index] = true; break;
            default: next_gen[grid_index] = false; break;
          }
	  //printf("(%zu FALSE %d, %d) \n", grid_index, neighboor_count, next_gen[grid_index]);
       // three cases for living cells
       } else {
          switch(neighboor_count){
      	    // fewer than 2 live neighboors => cell dies
      	    case 1: next_gen[grid_index] = false; break;
      	    // 2 or 3 live neighboors => cell continues to live
      	    case 2: next_gen[grid_index] = true; break;
      	    case 3: next_gen[grid_index] = true; break;
      	    // more than 3 live neighboors => cell dies
      	    case 4: next_gen[grid_index] = false; break;
      	    case 5: next_gen[grid_index] = false; break;
      	    case 6: next_gen[grid_index] = false; break;
      	    case 7: next_gen[grid_index] = false; break;
      	    case 8: next_gen[grid_index] = false; break;
      	    case 9: next_gen[grid_index] = false; break;
          }
	  //printf("(%zu TRUE %d, %d) \n", grid_index, neighboor_count, next_gen[grid_index]);

       }
    }
}

/*void display_grid(bool *current_gen, size_t grid_len){
    // draw a square 
    size_t x_index, y_index;
    for(size_t grid_index=0; grid_index<grid_len; ++grid_index){
       x_index = grid_index2x_index(grid_index, nof_horizontal_boxes, nof_vertical_boxes);
       y_index = grid_index2y_index(grid_index, nof_horizontal_boxes, nof_vertical_boxes);

       if( current_gen[grid_index] ){
          XFillRectangle (dpy, root, g, x_coordinates[x_index], y_coordinates[y_index], 
      	            box_length, box_length);

       }
    }
}*/





