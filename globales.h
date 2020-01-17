extern int XMIN;
extern int XMAX;
extern int YMIN;
extern int YMAX;
extern int ZMIN;
extern int ZMAX;
extern int NB_INIT;
extern int FOOD_INIT;
extern float DIST_AGGREGATE;
extern int food_increase;
/* The food increase amount is how much energy eating gives minus the energy depleted per "round"*/
extern int food_decrease;
extern float size;
extern int test_options;
extern int id_window;
extern int patches_per_draw;
extern int coord_maxima;
extern int coord_minima;
extern char NO_MORE_MEMORY;
extern float radius;

extern float angle_up_down;
extern float angle_right_left;
extern int camera_x;
extern int camera_y;
extern int camera_z;


extern int prob_aggregation_between_cells; 
extern int prob_self_aggregating;
extern int dimin_prob_clonage; 
extern int prob_init_clonage;
extern int prob_eat;
extern int prob_change_direction;
extern int prob_die;
extern int prob_disaggregation;
extern int prob_max;
//Basically here the prob to eat is 10%, the one to divide is 8%, aggregates lose a 1.6% chance to divide per individual,...

#define NO_COORD -1E2