// ROADMAP
// 1) write tests
// 2) simplify parser:
//    - figure out how to return arrays from function
//    - use max to merge conditional cases
//    - goal 0: separate parsing of dimension and keep global grid of constant size w/ padding
//    - goal 1: only write through function
//    - goal 2: invoke write function from as few distinct positions as possible
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void write_k(bool *arr, bool literal, int k){
	for(int i=0; i<k; ++i){
		arr[i] = literal;
	}
}


int grid_pos(int row_index, int col_index, int H_LEN){
	return row_index * H_LEN + col_index;
}

bool literal2flag(char literal){
	switch (literal){
		case 'b': return false; break;
	        case 'o': return true; break;
	        //default: return false; break;
	}
}


struct GridSize {
	unsigned int horizontal;
	unsigned int vertical;
};


struct GridSize parse_grid_size(char* filename){
    struct GridSize grid_size;

    FILE *fp = fopen(filename, "r");

    if (fp == NULL)
    {
        printf("Error: could not open file %s\n", filename);
	exit(1);
    }

    char rule[10];
    fscanf(fp, "x = %u, y = %u, rule = %s", 
           &grid_size.horizontal, 
	   &grid_size.vertical, 
	   rule);
    return grid_size;


}

void parse_pattern(char *filename, bool grid[], unsigned int horizontal, unsigned int vertical)
{
    //char *filename = "test.rle";
    FILE *fp = fopen(filename, "r");

    if (fp == NULL)
    {
        printf("Error: could not open file %s\n", filename);
        exit(1);
    }

    //int H_LEN, V_LEN;
    //char rule[10];
    //fscanf(fp, "x = %d, y = %d, rule = %s", &H_LEN, &V_LEN, rule);
    //printf("x = %d, y = %d \n\n", H_LEN, V_LEN);
    // read one character at a time and
    // display it to the output

    fscanf(fp, "%*[^\n]\n");

    unsigned int row_index = 0;
    unsigned int col_index = 0;
    unsigned int block_len = 0;
    unsigned int char_digit;
    char last_literal;

    char c;
    while ((c = fgetc(fp)) != EOF)
    {
	//printf("%d, %d\n", col_index, horizontal);
	if(c == '\n'){
		continue;
	} 
	else if (c == '$' || c == '!'){
		if (col_index < horizontal){
			last_literal = grid[grid_pos(row_index, col_index, horizontal)-1];

			//printf("write %c from pos. %d to %d\n", 
			//       literal2flag(last_literal),
			//       grid_pos(row_index, col_index, horizontal), 
			//       grid_pos(row_index, col_index, horizontal) + horizontal-col_index);
			write_k(&grid[grid_pos(row_index, col_index, horizontal)],
			        literal2flag(last_literal), 
				horizontal- col_index );
		}
		col_index = 0;
		row_index += 1;
		assert(row_index <= vertical);
	}
    	else if(c == 'b'){
		if (block_len==0){
			//printf("write X to pos. %d\n", grid_pos(row_index, col_index, horizontal));
			grid[grid_pos(row_index, col_index, horizontal)] = literal2flag(c);
			col_index += 1;
		} else {
			//printf("write X from pos. %d to %d\n", 
			//       grid_pos(row_index, col_index, horizontal), 
			//       grid_pos(row_index, col_index, horizontal)+block_len);
			write_k(&grid[grid_pos(row_index, col_index, horizontal)],
			        literal2flag(c), 
				block_len );
			col_index += block_len;
			block_len = 0;
		}
		//printf("CHECK: col_index = %d, block_len = %d, sum= %d\n", col_index, block_len, col_index + block_len);
		assert(col_index <= horizontal);
	}
	else if(c == 'o'){

		if (block_len==0){
			//printf("write O to pos. %d\n", grid_pos(row_index, col_index, horizontal));
			grid[grid_pos(row_index, col_index, horizontal)] = literal2flag(c);
			col_index += 1;
		} else {
			//printf("write O from pos. %d to %d\n", 
			//       grid_pos(row_index, col_index, horizontal), 
			//       grid_pos(row_index, col_index, horizontal));
			write_k(&grid[grid_pos(row_index, col_index, horizontal)],
			        literal2flag(c), 
				block_len );
			//printf("CHECK: col_index = %d, block_len = %d, sum= %d\n", col_index, block_len, col_index + block_len);
			col_index += block_len;
			block_len = 0;
		}
		assert(col_index <= horizontal);
	}
	else if(isdigit(c)){
		char_digit = (int)(c-'0');
		block_len = block_len * 10 + (unsigned char)char_digit;	
	}
	else {
        	break;
	}
    }

    // print linear view of grid
    // for (int i=0; i<V_LEN; ++i){
    //    for (int j=0; j<H_LEN; ++j){
    //	    	putchar(GRID[i * H_LEN + j] ? 'X' : 'O');
    //	    }
    //	    putchar('\n');
    //}
    //putchar('\n');
}

