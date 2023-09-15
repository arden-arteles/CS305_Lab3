#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* player struct */
struct player {
  /* lab exercise: define member variables here */
  int x_loc;
  int y_loc;
  int points;
  char *name;
  
};

typedef struct player player;

/* returns the index of the player in game_state that has the
 * highest score; if there is a tie, the lowest index is 
 * returned */
int find_max(player * game_state, int len) {
  int i = 0;
  int to_return = 0;
  if(len <= 0) {
    return -1;
  }
  // int max_points = game_state[0].points;
  /* lab exercise:  complete the rest of the function to return the index
     of the player with the highest score */
  for(i = 0; i < len; i++){
    if (game_state[i].points > game_state[0].points)
    {
      to_return = i;
      // ok so the following was NOT the objective of the function
      // see: lowest *index*
      // max_points = max_points + game_state[i].points;
    }
    // write code to check if game_state[i].points is bigger than max so far
    // if so, then update max_points and to_return appropriately
   
    
  }
  return to_return;
  // return max_points;
}

/* usage: player <input file name> <output file name>
 * reads game player state from input file, finds player with
 * highest score and writes the player's information to the
 * output file name 
 */
int main(int argc, char * argv[]) {
  // check that there are exactly 3 command-line arguments
  if(argc != 3) {
    fprintf(stderr, "Usage: player input_file_name output_file_name.\nExiting program.\n");
    return 1;  //error code
  }
  // open file and check for null
  FILE* fp = fopen(argv[1], "r");
  if(fp == NULL) {
    fprintf(stderr, "File cannot be opened.\n");
    return 1;  //error code
  }

  // read first line
  size_t bytes_read = 0;
  size_t num_bytes = 0;
  char *first_line = NULL;

  bytes_read = getline(&first_line, &num_bytes, fp);
  if(bytes_read == -1) {
    fprintf(stderr, "First line of file is invalid.\nExiting program\n");
    return 1;
  }

  // convert string to int
  int count = atoi(first_line);
  
  // read rest of file: file contents are (per line)
  // name
  // x_loc
  // y_loc
  // points
  //
  // note: should really error check each call to getline
  // to exit gracefully, but for the purpose of this lab,
  // we are keeping the code short

  player * game_state = malloc(sizeof(player)*count);
  int i;
  char * name_read = NULL;
  char * x_loc_read = NULL;
  char * y_loc_read = NULL;
  char * points_read = NULL;
  for(i=0; i<count; i++) {
    // get name
    // getline(&name_read, &num_bytes, fp);
    // game_state[i].name = name_read;
    //part 3, question 8, comment out the above two lines and
    // uncomment the first or the second line below (not both). 
    // recompile and re-run your code.
    // game_state[i].name = strdup(name_read);
    fscanf(fp,"%ms\n", &(game_state[i].name));
    // get x location
    getline(&x_loc_read, &num_bytes, fp);
    game_state[i].x_loc = atoi(x_loc_read);
    // get y location
    getline(&y_loc_read, &num_bytes, fp);
    game_state[i].y_loc = atoi(y_loc_read);
    // get points
    getline(&points_read, &num_bytes, fp);
    game_state[i].points = atoi(points_read);
    //printf("just read: %s %d %d %d\n", game_state[i].name,game_state[i].x_loc,game_state[i].y_loc, game_state[i].points);
  }
  // close input file since we are done with it
  fclose(fp);

  // find player with highest score
  int max = find_max(game_state, count);

  // print the player's information to an output file
  FILE *out;

  /* lab exercise:  open argv[2] for writing and set it to out */
  out = fopen(argv[2], "w");

  if(out == NULL) {
    fprintf(stderr, "Cannot open high_score.txt for writing.\n");
    return 1;  //error code
  }

  /* lab exercise:  write highest score player to output file here */
  /* use fprintf to print to file instead of printf */
  fprintf(out, "Hightest scoring player:\n");
  fprintf(out, "Name: %s\n", game_state[max].name);
  fprintf(out, "X position: %d\n", game_state[max].x_loc);
  fprintf(out, "Y position: %d\n", game_state[max].y_loc);
  fprintf(out, "Points: %d\n", game_state[max].points);

  // close output file
  fclose(out);
  return EXIT_SUCCESS;
}
