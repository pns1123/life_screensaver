#include<assert.h>
#include<stdbool.h>
#include<stdlib.h>
#include<stdio.h>


void initialize_coordinates(unsigned int *arr, unsigned int nof_boxes, unsigned int nof_pixels){
        unsigned int offset = nof_pixels / nof_boxes;
        for(unsigned int i=0; i<nof_boxes; ++i){
      	  arr[i] = i*offset;
        }

}

unsigned int grid_index2x_index(unsigned int grid_index, unsigned int nof_horizontal_boxes,
      	            unsigned int nof_vertical_boxes){
        return grid_index % nof_horizontal_boxes;
}

unsigned int grid_index2y_index(unsigned int grid_index, unsigned int nof_horizontal_boxes,
      	            unsigned int nof_vertical_boxes){
        return grid_index / nof_horizontal_boxes;
}

unsigned int xy_index2grid_index(unsigned int x_index, unsigned int y_index, 
      	             unsigned int nof_horizontal_boxes){
        return y_index*nof_horizontal_boxes + x_index;
}

/* life */
bool on_grid(unsigned int x, unsigned int y, unsigned int x_max, unsigned int y_max){
   // return bool indicating if (x,y) index pair is on grid
   // lower bound (inclusive): 0
   // upper bound (exclusive): (x|y)_max
   return (0 <= x) && (x < x_max) && (0 <= y) && (y < y_max);
}

int sum_moore_neighboorhood(bool *life_grid, unsigned int grid_index, 
		            unsigned int nof_horizontal_boxes, unsigned int nof_vertical_boxes){
        int running_sum = 0;
        unsigned int x_index, y_index, neigh_grid_index;

        x_index = grid_index2x_index(grid_index, nof_horizontal_boxes, nof_vertical_boxes);
        y_index = grid_index2y_index(grid_index, nof_horizontal_boxes, nof_vertical_boxes);
        // arrays of x,y coordinates to traverse neighb. from top left clock-wise
        unsigned int x_neigh[8] = {x_index-1, x_index, x_index+1, x_index+1, 
      	               x_index+1, x_index, x_index-1, x_index-1};
        unsigned int y_neigh[8] = {y_index+1, y_index+1, y_index+1, y_index,
                             y_index-1, y_index-1, y_index-1, y_index};
        for(unsigned int neigh_index=0; neigh_index<8; ++neigh_index){
      
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

void update_grid(bool *current_gen, bool *next_gen, unsigned int grid_len, unsigned int nof_horizontal_boxes,
		unsigned int nof_vertical_boxes){ 
    int neighboor_count;
    for(unsigned int grid_index=0; grid_index<grid_len; ++grid_index){
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

/*void display_grid(bool *current_gen, unsigned int grid_len){
    // draw a square 
    unsigned int x_index, y_index;
    for(unsigned int grid_index=0; grid_index<grid_len; ++grid_index){
       x_index = grid_index2x_index(grid_index, nof_horizontal_boxes, nof_vertical_boxes);
       y_index = grid_index2y_index(grid_index, nof_horizontal_boxes, nof_vertical_boxes);

       if( current_gen[grid_index] ){
          XFillRectangle (dpy, root, g, x_coordinates[x_index], y_coordinates[y_index], 
      	            box_length, box_length);

       }
    }
}*/





