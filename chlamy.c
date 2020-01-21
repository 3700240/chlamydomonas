#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "globales.h"
#include "structures.h"
void delete_world();

Chlamydomonas *head_chlam = NULL;
Aggregate *head_aggregate = NULL;
Numb_per_coord numb_per_coord;

/*
int XMIN = 1;
int XMAX = 30;
int YMIN = 1;
int YMAX = 30;
int ZMIN = 1;
int ZMAX = 30;
int NB_INIT = 20;
int FOOD_INIT = 15;
float DIST_AGGREGATE = 1.0;
int food_increase = 2;
int food_decrease = 1;
float size = 0.05;
int id_window = 0;
int patches_per_draw = 1;
int coord_maxima = 0;
int coord_minima = 0;
char NO_MORE_MEMORY = 0;

int prob_aggregation_between_cells = 45; 
int prob_self_aggregating = 200;
int dimin_prob_clonage = 16; 
int prob_init_clonage = 100;
int prob_eat = 1000;
int prob_change_direction = 100;
int prob_die = 0;
int prob_disaggregation = 1;
int prob_max = 1000;
*/


void init_stats() 
{
	/*------------------------------------------------------------------------
	//
	// init_prob
	// To be used whenever you want to reset probs. Will initiate every probability and other data at the base values
	//
	// Takes no parameters
	// Void function. Modifies global variables though
	//
	------------------------------------------------------------------------*/

	XMIN = 1;
	XMAX = 30;
	YMIN = 1;
	YMAX = 30;
	ZMIN = 1;
	ZMAX = 30;
	NB_INIT = 20;
	FOOD_INIT = 15;
	DIST_AGGREGATE = 1.0;
	food_increase = 2;
/* The food increase amount is how much energy eating gives minus the energy depleted per "round"*/
	food_decrease = 1;

	prob_aggregation_between_cells = 45; 
	prob_self_aggregating = 200;
	dimin_prob_clonage = 16; 
	prob_init_clonage = 1000;
	prob_eat = 100;
	prob_change_direction = 100;
	prob_die = 1;
	prob_disaggregation = 0;
	prob_max = 1000;
/*Basically here the prob to eat is 10%, the one to divide is 8%, aggregates lose a 1.6% chance to divide per individual,...*/
}

Chlamydomonas *create_chlam(int x, int y, int z, int food)
{
	/*------------------------------------------------------------------------
	//
	// create_chlam
	// This function creates a new Chlamydomonas given its coordinates and its energy to start with
	//
	// Takes the int values of 3D coordinates, and an int containing its energy value
	// Returns a pointer to the created Chlamydomonas
	//
	------------------------------------------------------------------------*/

	Chlamydomonas *new = (Chlamydomonas *) malloc(sizeof(Chlamydomonas));
	if (new == NULL) {
		NO_MORE_MEMORY = 1;
		return NULL;
	}
	new->x = x;
	if ((x >= XMIN) && (x <= XMAX)) /*Needs to be checked for the situation where one is created outside the borders (will be a necessity)*/
		numb_per_coord.numb_per_x[x - XMIN] += 1;
	new->y = y;
	if ((y >= YMIN) && (y <= YMAX))
		numb_per_coord.numb_per_y[y - YMIN] += 1;
	new->z = z;
	if ((z >= ZMIN) && (z <= ZMAX))
		numb_per_coord.numb_per_z[z - ZMIN] += 1;
/*Those should allow us to know how many Chlamydomonas are in vicinity*/
	new->next = NULL;
	new->direction = rand() % 6;
	new->food = food;
	new->distance_in_aggregate = 0.0;
	return new;
}

Chlamydomonas *adding_chlam(Chlamydomonas *head, Chlamydomonas *elem)
{
	/*------------------------------------------------------------------------
	//
	// adding_chlam
	// Adds a Chlamydomonas to a single-chained list of Chlamydomonas. List is not sorted in any way
	//
	// Takes the head of a first element of a next-chained list, and an element to insert 
	// Returns a pointer to the new list (basically the new element, chained to the list)
	//
	------------------------------------------------------------------------*/

	if (elem == NULL)
		return head;
	elem->next = head;
	return elem;
} /*Adds a new Chlamydomonas to our list*/

float distance(Chlamydomonas *numb1, Chlamydomonas *numb2)
{
	/*------------------------------------------------------------------------
	//
	// distance
	// Measures the distance between 2 cells
	//
	// Takes as parameters the 2 cells
	// Returns a float of the distance between them (Euclidian norm)
	//
	------------------------------------------------------------------------*/

	return sqrt((double) ((numb1->x - numb2->x) * (numb1->x - numb2->x) + (numb1->y - numb2->y) * (numb1->y - numb2->y) + (numb1->z - numb2->z) * (numb1->z - numb2->z)));
} /*Finds the distance between 2 Chlamydomonas, using the Euclidian norm*/

Chlamydomonas *find_center(Chlamydomonas *list, Chlamydomonas *new_elem, float *radius)
{
	/*------------------------------------------------------------------------
	//
	// find_center
	// Locates the center of a Chlamydomonas list + the one that will be integrated within: the center minimizes the sum of distance
	//
	// Takes as parameters the list, the cell that will be added to the group (referred to as aggregates) and a pointer to a float giving the average distance
	// Changes the value of the average distance in the aggregate, returns the Chlamydomonas closest to the center
	//
	------------------------------------------------------------------------*/

	float length = distance(list, new_elem);
	list->distance_in_aggregate += length;
	float minima = list->distance_in_aggregate;
	Chlamydomonas *center = list;
	new_elem->distance_in_aggregate = length;
	Chlamydomonas *temp = list->next;
	while (temp != NULL) {
		length = distance(temp, new_elem);
		temp->distance_in_aggregate += length;
		new_elem->distance_in_aggregate += length;
		if (temp->distance_in_aggregate < minima) {
			minima = temp->distance_in_aggregate;
			center = temp;
		}
		temp = temp->next;
	}
	*radius = minima;
	return center;
} /*Finds the center, returns it and gives out the radius (WARNING: a radius's address must be given)*/

Aggregate *add_aggreg(Aggregate *head, Aggregate *new)
{
	/*------------------------------------------------------------------------
	//
	// add_aggreg
	// Adds an aggregate to an existing (or not) list of aggregates
	//
	// Takes as parameters the list, the aggregate that is to be added
	// Returns a new list including all pre-existing aggregates and the new one
	//
	------------------------------------------------------------------------*/

	if (new == NULL)
		return head;
	new->next = head;
	return new;
} /*Adds an aggregate to our Aggregate list*/

Aggregate *adding_chlam_to_agg(Aggregate *head, Aggregate *aggreg, Chlamydomonas *elem_prev)
{
	/*------------------------------------------------------------------------
	//
	// adding_chlam_to_agg
	// Adds a Chlamydomonas to an aggregate in our list (may create the aggregate in the meantime). Takes it off the Chlamydomonas list. Checks for the center of the aggregate
	//
	// Takes as parameters the list of aggregates, the aggregate we want to insert our Chlamydomonas in, the 'ancestor' of the said Chlamydomonas
	// Returns the completed list of aggregate with infos updated
	//
	------------------------------------------------------------------------*/

	if (aggreg == NULL) {
		aggreg = (Aggregate *) malloc(sizeof(Aggregate));
		if (aggreg == NULL) {
			NO_MORE_MEMORY = 1;
			delete_world();
			return NULL;
		}
		Chlamydomonas *temp = elem_prev->next;
		aggreg->center = temp;
		aggreg->head = temp;
		elem_prev->next = temp->next;
		temp->next = NULL;
		numb_per_coord.numb_per_x[temp->x - XMIN] --;
		numb_per_coord.numb_per_y[temp->y - YMIN] --;
		numb_per_coord.numb_per_z[temp->z - ZMIN] --;
		aggreg->number = 1;
		aggreg->radius = 0;
		return add_aggreg(head, aggreg);
	} /*Creating an aggregate, adding it to the Aggregate list*/
	Chlamydomonas *temp = elem_prev->next;
	aggreg->number ++;
	float radius = 0;
	aggreg->center = find_center(aggreg->head, temp, &radius);
	aggreg->radius = radius/(aggreg->number);
/*Finding the new center and radius*/
	elem_prev->next = temp->next;
	temp->next = aggreg->head;
	aggreg->head = temp;
	numb_per_coord.numb_per_x[temp->x - XMIN] --;
	numb_per_coord.numb_per_y[temp->y - YMIN] --;
	numb_per_coord.numb_per_z[temp->z - ZMIN] --;
/*Adding the Chlamydomonas to the aggregate, taking it off the list
That specific aggregate already is in our list, so all good*/
	return head;
}/*Adds a Chlamydomonas to a given aggregate, takes it off the list, recalculates the center and radius*/


void init_world()
{
	/*------------------------------------------------------------------------
	//
	// init_world
	// Initializes the world with the given number of Chlamydomonas randomly positionned. Sets the seed for rand
	//
	// Takes no input parameters
	// The lists are global variables, as is the memo to know the number of Chlamydomonas per given paralleloid. However the function is void type
	//
	------------------------------------------------------------------------*/

	head_chlam = NULL;
	head_aggregate = NULL;

	srand((unsigned) time(NULL));

	numb_per_coord.numb_per_x = (int *) malloc((XMAX - XMIN + 1) * sizeof(int));
	if (numb_per_coord.numb_per_x == NULL) {
		NO_MORE_MEMORY = 1;
		printf("ERREUR");
		return;
	}
	numb_per_coord.numb_per_y = (int *) malloc((YMAX - YMIN + 1) * sizeof(int));
	if (numb_per_coord.numb_per_y == NULL) {
		NO_MORE_MEMORY = 1;
		printf("ERREUR");
		return;
	}
	numb_per_coord.numb_per_z = (int *) malloc((ZMAX - ZMIN + 1) * sizeof(int));
	if (numb_per_coord.numb_per_z == NULL) {
		NO_MORE_MEMORY = 1;
		printf("ERREUR");
		return;
	}
	for (int i = 0; i < XMAX - XMIN + 1; i++) 
		numb_per_coord.numb_per_x[i] = 0;
	for (int i = 0; i < YMAX - YMIN + 1; i++)
		numb_per_coord.numb_per_y[i] = 0;
	for (int i = 0; i < ZMAX - ZMIN + 1; i++)
		numb_per_coord.numb_per_z[i] = 0;
/* Those should help us make the distance check faster*/

	for (int i = 0; i < NB_INIT; i++) {
		head_chlam = adding_chlam(head_chlam, create_chlam((rand() % (XMAX - XMIN + 1)) + XMIN, (rand() % (YMAX - YMIN + 1)) + YMIN,(rand() % (ZMAX - ZMIN + 1)) + ZMIN, FOOD_INIT));
	}
//	printf("Initialisation SUCCESS");///////////////////////////////////////////////
}/*Creating the specified number of Chlamydomonas randomly positioned in the given coordinates
Also, initiating the seed for random*/

void exhaust(Chlamydomonas *elem_prev)
{
	/*------------------------------------------------------------------------
	//
	// exhaust
	// Checks a Chlamydomonas for energy, erasing them from the list and freeing them
	//
	// Takes as a parameter the 'ancestor' of the Chlamydomonas it must check
	// Void function. Although, it changes the 'ancestor' of the Chlamydomonas so it refers to the next Chlamydomonas
	//
	------------------------------------------------------------------------*/

	if (elem_prev == NULL)
		return;
	if (elem_prev->next == NULL)
		return;
	if (elem_prev->next->food <= 0) {
		Chlamydomonas *temp = elem_prev->next;
		elem_prev->next = temp->next;
		numb_per_coord.numb_per_x[temp->x - XMIN] --;
		numb_per_coord.numb_per_y[temp->y - YMIN] --;
		numb_per_coord.numb_per_z[temp->z - ZMIN] --;
/*Those should allow us to make the distance check faster*/
		free (temp);
		return exhaust(elem_prev);
	}
} /*Checks the energy of the next Chlamydomonas in the list and takes it off if necessary
The head of the list has to be checked manually though as it has no predecessor (or create a predecessor beforehand)*/

void check_change_dir(Chlamydomonas *elem)
{
	/*------------------------------------------------------------------------
	//
	// check_change_dir
	// Checks if the given Chlamydomonas can change its direction, and forces a change if so
	//
	// Takes as parameter the Chlamydomonas that is to be checked
	// Void function. The said Chlamydomonas is (or not) modified
	//
	------------------------------------------------------------------------*/

	if (elem == NULL)
		return;
	if (rand() % prob_max < prob_change_direction)
		elem->direction = (elem->direction + 1 + rand() % 5) % 6; 
} /*Randomly changes the direction if it is supposed to*/

void force_change_dir(Chlamydomonas *elem)
{
	/*------------------------------------------------------------------------
	//
	// force_change_dir
	// Forces a changement of direction for the said Chlamydomonas. Used if you don't want them to be stuck running into walls
	//
	// Takes as parameter the Chlamydomonas that is to be forced to change its direction
	// Void function. The Chlamydomonas is modified
	//
	------------------------------------------------------------------------*/

	if (elem == NULL)
		return;
	elem->direction = (elem->direction + 1 + rand() % 5) % 6;
} /*Forces the element to change its direction
Use it if you don't want them to 'run into walls'*/

void move(Chlamydomonas *elem)
{
	/*------------------------------------------------------------------------
	//
	// move
	// Moves a Chlamydomonas in a specified direction (either x or y or z)
	//
	// Takes as parameter the Chlamydomonas to be moved
	// Void function. The Chlamydomonas is modified
	//
	------------------------------------------------------------------------*/

	if (elem == NULL)
		return;
	switch (elem->direction) {
		case 0:
			if (elem->x > XMIN) {
				numb_per_coord.numb_per_x[elem->x - XMIN] --;
				elem->x --;
				numb_per_coord.numb_per_x[elem->x - XMIN] ++;
			}
/*			else { 
				force_change_dir(elem); 
				move(elem); 
			} //Uncomment those lines if you don't want them to 'run into walls'
*/
			break;
		case 1:
			if (elem->x < XMAX) {
				numb_per_coord.numb_per_x[elem->x - XMIN] --;
				elem->x ++;
				numb_per_coord.numb_per_x[elem->x - XMIN] ++;
			}
/*			else { 
				force_change_dir(elem); 
				move(elem); 
			} //Uncomment those lines if you don't want them to 'run into walls'
*/
			break;
		case 2:
			if (elem->y > YMIN) {
				numb_per_coord.numb_per_y[elem->y - YMIN] --;
				elem->y --;
				numb_per_coord.numb_per_y[elem->y - YMIN] ++;
			}
/*			else { 
				force_change_dir(elem); 
				move(elem); 
			} //Uncomment those lines if you don't want them to 'run into walls'
*/
			break;
		case 3:
			if (elem->y < YMAX) {
				numb_per_coord.numb_per_y[elem->y - YMIN] --;
				elem->y ++;
				numb_per_coord.numb_per_y[elem->y - YMIN] ++;
			}
/*			else { 
				force_change_dir(elem); 
				move(elem); 
			} //Uncomment those lines if you don't want them to 'run into walls'
*/
			break;
		case 4:
			if (elem->z > ZMIN) {
				numb_per_coord.numb_per_z[elem->z - ZMIN] --;
				elem->z --;
				numb_per_coord.numb_per_z[elem->z - ZMIN] ++;
			}
/*			else { 
				force_change_dir(elem); 
				move(elem); 
			} //Uncomment those lines if you don't want them to 'run into walls'
*/
			break;
		case 5:
			if (elem->z < ZMAX) {
				numb_per_coord.numb_per_z[elem->z - ZMIN] --;
				elem->z ++;
				numb_per_coord.numb_per_z[elem->z - ZMIN] ++;
			}
/*			else { 
				force_change_dir(elem); 
				move(elem); 
			} //Uncomment those lines if you don't want them to 'run into walls'
*/
			break;
		default : printf("Error during the movements\n");
	}
}

Aggregate *spawn_Aggregate(Aggregate *head, Chlamydomonas *numb1_prev, Chlamydomonas *numb2_prev)
{
	/*------------------------------------------------------------------------
	//
	// spawn_Aggregate
	// Creates an aggregate from 2 existing Chlamydomonas, taking them off their list, and adds that one to the aggregate list
	//
	// Takes as parameters the aggregate list, and the 2 chlamydomonas that aggregate
	// Returns the updated aggregate list. The center of the new aggregate is the first one given or the first in thz list if they are next to each other
	//
	------------------------------------------------------------------------*/

	if ((numb1_prev->next == NULL) || (numb2_prev->next == NULL))
			return head;
	Aggregate *aggreg = (Aggregate *) malloc(sizeof(Aggregate));
	if (aggreg == NULL) {
		NO_MORE_MEMORY = 1;
		delete_world();
		return NULL;
	}
	if (numb1_prev == numb2_prev)
		return adding_chlam_to_agg(head, NULL, numb1_prev);
	if (numb1_prev == numb2_prev->next) {
		aggreg->center = numb1_prev;
		aggreg->head = aggreg->center;
		numb2_prev->next = numb1_prev->next->next;
		numb1_prev->next->next = NULL;
	}
	else {
		aggreg->center = numb1_prev->next;
		aggreg->head = aggreg->center;
		if (numb2_prev == numb1_prev->next) {
			numb1_prev->next = numb2_prev->next->next;
			numb2_prev->next->next = NULL;
		}
		else {
			numb1_prev->next = numb1_prev->next->next;
			aggreg->head->next = numb2_prev->next;
			numb2_prev->next = numb2_prev->next->next;
			aggreg->head->next->next = NULL;
		}
	}
	float temp_distance = distance(aggreg->head, aggreg->head->next);
	aggreg->head->distance_in_aggregate = temp_distance;
	aggreg->head->next->distance_in_aggregate = temp_distance;
	numb_per_coord.numb_per_x[aggreg->head->x - XMIN] --;
	numb_per_coord.numb_per_y[aggreg->head->y - YMIN] --;
	numb_per_coord.numb_per_z[aggreg->head->z - ZMIN] --;
	numb_per_coord.numb_per_x[aggreg->head->next->x - XMIN] --;
	numb_per_coord.numb_per_y[aggreg->head->next->y - YMIN] --;
	numb_per_coord.numb_per_z[aggreg->head->next->z - ZMIN] --;
	aggreg->number = 2;
	aggreg->radius = temp_distance/2.0;
	head = add_aggreg(head, aggreg);
	return head;
}/*Creates an aggregate from 2 existing cells. The center is the first cell*/

Aggregate *gathering(Aggregate *head, Chlamydomonas **head_Chlam, Chlamydomonas *elem_prev)
{
	/*------------------------------------------------------------------------
	//
	// gathering
	// Tries to make aggregates from one Chlamydomonas to: first off existing aggregates; then other Chlamydomonas in their surrounding
	//
	// Takes as parameters the aggregate list, the chlamydomonas list, the 'ancestor' of the Chlamydomonas we will try to aggregate
	// Returns the updated aggregate list
	//
	------------------------------------------------------------------------*/

	if (elem_prev == NULL)
		return head;
	Chlamydomonas *elem = elem_prev->next;
	if (elem == NULL)
		return head;
	if (head != NULL) {
		Aggregate *temp_aggreg = head;
		while (temp_aggreg != NULL) {
			if (distance(temp_aggreg->center, elem) <= temp_aggreg->radius + DIST_AGGREGATE) {
				if (elem == *head_Chlam) 
					*head_Chlam = elem->next;
				return adding_chlam_to_agg(head, temp_aggreg, elem_prev);
			}
			temp_aggreg = temp_aggreg->next;
		}
	}
	int min = 0, tempy = 0, tempz = 0;
	for (int i = - (int) DIST_AGGREGATE; i <= (int) DIST_AGGREGATE; i++) {
		if ((elem->x + i >= XMIN) && (elem->x + i <= XMAX))
			min += numb_per_coord.numb_per_x[elem->x + i - XMIN];
		if ((elem->y + i >= YMIN) && (elem->y + i <= YMAX))
			tempy += numb_per_coord.numb_per_y[elem->y + i - YMIN];
		if ((elem->z + i >= ZMAX) && (elem->z + i <= ZMAX))
			tempz += numb_per_coord.numb_per_z[elem->z + i - ZMIN];
	}
	int val_coord = 1;
	if (min > tempy) {
		min = tempy;
		val_coord = 2;
	}
	if (min > tempz) {
		min = tempz;
		val_coord = 3;
	}
	min --;
	Chlamydomonas *temp = *head_Chlam;
	if (elem != temp)
		if ((distance(temp, elem) <= DIST_AGGREGATE) && (rand() % prob_max < prob_aggregation_between_cells)) {
			Chlamydomonas *mothership = create_chlam(NO_COORD, NO_COORD, NO_COORD, 0);
			mothership->next = temp;
			head = spawn_Aggregate(head, mothership, elem_prev);
			*head_Chlam = mothership->next;
			free (mothership);
			return head;
/*Because we ask for the previous one, we must create a non existent Chlamydomonas that will be that previous one*/
		}
	while (min > 0) {
		if (temp->next == NULL) return head;
/*Because of our conditions, we should never be able to reach the end of the list and get a segfault*/
		if (elem != temp->next) {
			if (distance(temp->next, elem) <= DIST_AGGREGATE)
				if (rand() % prob_max < prob_aggregation_between_cells) {
					head = spawn_Aggregate(head, temp, elem_prev);
					return head;
				}
		}
		switch (val_coord) {
			case 1 : for (int i = - (int) DIST_AGGREGATE; i <=  (int) DIST_AGGREGATE; i++) {
					if (elem->x + i == temp->next->x) {
						min --;
						i = (int) DIST_AGGREGATE + 1;
					}
				}
				break;
			case 2 : for (int i = - (int) DIST_AGGREGATE; i <=  (int) DIST_AGGREGATE; i++) {
					if (elem->y + i == temp->next->y) {
						min --;
						i = (int) DIST_AGGREGATE + 1;
					}
				}
				break;
			case 3 : for (int i = - (int) DIST_AGGREGATE; i <=  (int) DIST_AGGREGATE; i++) {
					if (elem->z + i == temp->next->z) {
						min --;
						i = (int) DIST_AGGREGATE + 1;
					}
				}
				break;
			}
		temp = temp->next;
	}
	return head;
}/*Checks for Chlamydomonas in vicinity, checks for aggregation*/

void destroy_chlam(Chlamydomonas *head)
{
	/*------------------------------------------------------------------------
	//
	// destroy_chlam
	// Destroys the full list of Chlamydomonas, frees every space taken
	//
	// Takes as parameter the list of Chlamydomonas that is to be destroyed
	// No output
	//
	------------------------------------------------------------------------*/

	if (head == NULL)
		return;
	Chlamydomonas *temp = head->next;
	free(head);
	return destroy_chlam(temp);
}/*Destroys our Chlamydomonas list*/

void kill_chlam(Chlamydomonas *elem_prev)
{
	/*------------------------------------------------------------------------
	//
	// kill_chlam
	// Checks if a chlamydomonas is to die (stress reason) and takes it off the list if necessary, freeing it
	//
	// Takes as parameter the 'ancestor' of the Chlamydomonas that is to be checked
	// Void function, changes the 'ancestor'
	//
	------------------------------------------------------------------------*/
	if (elem_prev == NULL) 
		return;
	if (elem_prev->next == NULL) 
		return;

	if (rand() % prob_max < prob_die) {
		Chlamydomonas *temp = elem_prev->next;
		elem_prev->next = temp->next;
		free (temp);
		exhaust(elem_prev);
		return kill_chlam(elem_prev);
	}
}/*Kills one precise Chlamydomonas if conditions were too harsh for it to live*/

void destroy_aggregates(Aggregate *head)
{
	/*------------------------------------------------------------------------
	//
	// destroy_aggregates
	// Destroys the full list of aggregates, freeing every Chlamydomonas in the aggregates, and every aggregate in the list
	//
	// Takes as parameter the list of aggregates
	// Void function
	//
	------------------------------------------------------------------------*/

	if (head == NULL)
		return;
	destroy_chlam(head->head);
	Aggregate *temp = head->next;
	free (head);
	destroy_aggregates(temp);
}/*Destroys our aggregate list and all Chlamydomonas in the list*/

Chlamydomonas *desaggregate(Chlamydomonas *head_Chlam, Aggregate **head, Aggregate *aggreg_prev)
{
	/*------------------------------------------------------------------------
	//
	// desaggregate
	// Liberates the Chlamydomonas in a given aggregate, adding them to the Chlamydomonas list
	//
	// Takes as parameter the Chlamydomonas list, a pointer to the aggregate list, a pointer to the aggregate to remove
	// Returns the updated Chlamydomonas list, modifies the aggregate list
	//
	------------------------------------------------------------------------*/

	if (aggreg_prev->next == NULL)
		return head_Chlam;
	Aggregate *aggreg = aggreg_prev->next;
	if (*head == aggreg) {
		*head = aggreg->next;
		if (head_Chlam == NULL) {
			Chlamydomonas *temp = aggreg->head;
			free(aggreg);
			aggreg_prev->next = *head;
			if (rand() % prob_max < prob_disaggregation)
				return desaggregate(temp, head, aggreg_prev);
			return temp;
		}
		Chlamydomonas *temp = head_Chlam;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = aggreg->head;
		free (aggreg);
		return head_Chlam;
	}
	if (head_Chlam == NULL) {
		Chlamydomonas *temp = aggreg->head;
		aggreg_prev->next = aggreg->next;
		free(aggreg);
		return temp;
	}
	Chlamydomonas *temp = head_Chlam;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = aggreg->head;
	aggreg_prev->next = aggreg->next;
	free (aggreg);
	return head_Chlam;
}/*Frees the space taken by the previous aggregate, changes the head, puts the Chlamydomonas back in the list*/

void delete_world()
{
	/*------------------------------------------------------------------------
	//
	// delete_world
	// Destroys and frees all of the lists
	//
	// Takes as parameters the two lists (aggregates and Chlamydomonas)
	// Void function
	//
	------------------------------------------------------------------------*/

	destroy_chlam(head_chlam);
	destroy_aggregates(head_aggregate);
	if (numb_per_coord.numb_per_x != NULL) {
		free(numb_per_coord.numb_per_x);
		free(numb_per_coord.numb_per_y);
		free(numb_per_coord.numb_per_z);
	}
}/*Makes sure all the memory we took is freed*/

Chlamydomonas *mitosis(Chlamydomonas *head, Chlamydomonas *elem)
{
	/*------------------------------------------------------------------------
	//
	// mitosis
	// Checks for the possibility of a mitosis for a given Chlamydomonas, creates the clone, energy is splitted and rounded down
	//
	// Takes as parameter the Chlamydomonas that can run into mitosis, and the list of Chlamydomonas
	// Returns the updated list of Chlamydomonas
	//
	------------------------------------------------------------------------*/

	if (elem == NULL)
		return NULL;
	if ((elem->food > 3) && (rand() % prob_max < prob_init_clonage)) {
		head = adding_chlam(head, create_chlam(elem->x,elem->y,elem->z,elem->food / 2));
		elem->food /= 2;
/* Yes there is a loss if the food supply is odd. Works as intended*/
	}
	return head;
}/*If conditions are met, we create a new individual*/

Aggregate *mitosis_in_aggregate(Aggregate *head, Aggregate *elem_prev)
{
	/*------------------------------------------------------------------------
	//
	// mitosis_in_aggregate
	// For all Chlamydomonas in a given aggregate, checks if they can go through mitosis
	//
	// Takes as parameters the list of aggregate and the aggregate that is to be checked
	// Returns the updated list of aggregate
	//
	------------------------------------------------------------------------*/

	Aggregate *elem = elem_prev->next;
	int number = elem->number;
	int new_prob = prob_init_clonage - number * dimin_prob_clonage;
	Chlamydomonas *temp = elem->head;
	if (temp == NULL) {
		if (elem == head) {
			head = elem->next;
			free(elem);
			elem_prev->next = head;
			return mitosis_in_aggregate(head, elem_prev);
		}
		elem_prev->next = elem->next;
		free(elem);
		return head;
	}
	Chlamydomonas *mothership = NULL;
	Chlamydomonas *offspring = NULL;
	for (int i = 0; i < number; i++) {
		if (new_prob > 0) {
			if (temp->food > 3)
				if (rand() % prob_max < new_prob) {
					temp->food /= 2;
					offspring = create_chlam(temp->x, temp->y, temp->z, temp->food);
					mothership = create_chlam(NO_COORD, NO_COORD, NO_COORD, 0);
					mothership->next = offspring;
					head = adding_chlam_to_agg(head, elem, mothership);
					free(mothership);
					new_prob -= dimin_prob_clonage;
				}
		}
		else 
			i = number;
		temp = temp->next;
	}
	return head;
}/* Checks if vicinity doesn't prevent Chlamydomonas from going under mitosis, and does that*/

Chlamydomonas *modify_distances_in_aggregate(Aggregate *elem, Chlamydomonas *individual)
{
	/*------------------------------------------------------------------------
	//
	// modify_distances_in_aggregate
	// Takes off the distance between all Chlamydomonas of an aggregate and an individual
	//
	// Receives the Chlamydomonas that is to be taken off an aggregate and that aggregate
	// Void function. Modifies the aggregate and the Chlamydomonas
	//
	------------------------------------------------------------------------*/

	if (elem == NULL)
		return NULL;
	Chlamydomonas *new_center = elem->head;
	float minima = new_center->distance_in_aggregate;
	Chlamydomonas *temp = elem->head;
	while (temp != NULL){
		temp->distance_in_aggregate -= distance(temp,individual);
		if (minima > temp->distance_in_aggregate) {
			minima = temp->distance_in_aggregate;
			new_center = temp;
		}
		temp = temp->next;
	}
	elem->radius = minima/elem->number;
	return new_center;
}

Aggregate *hunger_in_aggregate(Aggregate *elem_prev)
{
	/*------------------------------------------------------------------------
	//
	// hunger_in_aggregate
	// Makes sure every Chlamydomonas in the aggregate tries to eat, loses energy, and starves if necessary. If the aggregate turns out to be empty, checks for the next one
	//
	// Takes as parameter the 'ancestor' of the aggregate that needs to be checked
	// Returns the aggregate tthat was checked
	//
	------------------------------------------------------------------------*/

	Aggregate *elem = elem_prev->next;
	if (elem == NULL)
		return NULL;
	Chlamydomonas *temp = elem->head;
	if (temp == NULL) {
		elem_prev->next = elem->next;
		free(elem);
		return hunger_in_aggregate(elem_prev);
	}
	if (rand() % prob_max < prob_eat)
		temp->food += food_increase;
	else temp->food -= food_decrease;
	if (temp->food <= 0) {
		elem->number --;
		elem->head = temp->next;
		if (elem->head == NULL) {
			free(temp);
			elem_prev->next = elem->next;
			free (elem);
			return hunger_in_aggregate(elem_prev);
		}
		elem->center = modify_distances_in_aggregate(elem, temp);
		free(temp);
		return hunger_in_aggregate(elem_prev);
	}
	while (temp->next != NULL) {
		if (rand() % prob_max < prob_eat)
			temp->next->food += food_increase;
		else temp->next->food -= food_decrease;
		if (temp->next->food <= 0) {
			elem->number --;
			Chlamydomonas * temp2 = temp->next;
			temp->next = temp2->next;
			elem->center = modify_distances_in_aggregate(elem, temp2);
			free(temp2);
		}
		else 
			temp = temp->next;
	}
	return elem;
}/*Goes through the Chlamydomonas in the aggregate, makes them eat and starve, corrects the distance and about everything else*/

Aggregate *hunger_all_aggregates(Aggregate *head)
{
	/*------------------------------------------------------------------------
	//
	// hunger_all_aggregates
	// Makes sure all the aggregates in the list go through the eat-hunger-starving process
	//
	// Takes as parameter the list of aggregates
	// Returns the updated list of aggregates
	//
	------------------------------------------------------------------------*/

	if (head == NULL)
		return NULL;
	Aggregate *mothership = (Aggregate *) malloc(sizeof(Aggregate));
	if (mothership == NULL) {
		if (head->head == NULL) {
			Aggregate *temp = head;
			head = hunger_in_aggregate(head);
			free(temp);
		}
/*Because if that happens then somehow head is empty and is the prev of our 2nd aggregate, hence "head->next" is our head and "head" is our mothership*/
		else {
			Chlamydomonas *temp = head->head;
			if (rand() % prob_max < prob_eat)
				temp->food += food_increase;
			else temp->food -= food_decrease;
			if (temp->food <= 0) {
				head->number --;
				head->head = temp->next;
				if (head->head == NULL) {
					Aggregate *free_head = head->next;
					free(head);
					return hunger_all_aggregates(free_head);
				}
				head->center = modify_distances_in_aggregate(head, temp);
				free(temp);
				return hunger_all_aggregates(head);
			}
			while (temp->next != NULL) {
				if (rand() % prob_max < prob_eat)
					temp->next->food += food_increase;
				else temp->next->food -= food_decrease;
				if (temp->next->food <= 0) {
					head->number --;
					Chlamydomonas * temp2 = temp->next;
					temp->next = temp2->next;
					head->center = modify_distances_in_aggregate(head, temp2);
					free(temp2);
				}
				else 
					temp = temp->next;
			}
		}
/*This is a copy paste of the hunger_in_aggregate function, slightly adapted*/
		Aggregate *temp_aggreg = hunger_in_aggregate(head);
		while (temp_aggreg != NULL)
			temp_aggreg = hunger_in_aggregate(temp_aggreg);
		Aggregate *test = (Aggregate *) malloc(sizeof(Aggregate));
		if (test == NULL) {
			NO_MORE_MEMORY = 1;
			delete_world();
			return NULL;
		} 
		free(test);
	}
	else {
		mothership->next = head;
		head = hunger_in_aggregate(mothership);
		free(mothership);
		mothership = head;
		while (mothership != NULL)
			mothership = hunger_in_aggregate(mothership);
	}
	return head;
}/*Makes sure every aggregate goes through the hunger process
We keep going if having no more memory because with a bit of "luck" we'll free some
However we still test at the end to make sure we did make space*/

void patch(Chlamydomonas **head_Chlam, Aggregate **head_Aggregate)
{
	/*------------------------------------------------------------------------
	//
	// patch
	// Updates all our individuals
	//
	// Takes pointer of the lists
	// Void function. Modifies the lists though
	//
	------------------------------------------------------------------------*/

	if (*head_Aggregate != NULL) {
		Aggregate *mothership_aggregate = (Aggregate *) malloc(sizeof(Aggregate));
		if (mothership_aggregate == NULL) {
			NO_MORE_MEMORY = 1;
			delete_world();
			return;
		}
		mothership_aggregate->next = *head_Aggregate;
		if (rand() % prob_max < prob_disaggregation)
			*head_Chlam = desaggregate(*head_Chlam, head_Aggregate, mothership_aggregate);
		*head_Aggregate = mitosis_in_aggregate(*head_Aggregate, mothership_aggregate);
		free(mothership_aggregate);
		Aggregate *temp_aggreg = (*head_Aggregate);
		if (temp_aggreg != NULL) {
			*head_Aggregate = hunger_all_aggregates(*head_Aggregate);
			while (temp_aggreg->next != NULL) {
				*head_Aggregate = mitosis_in_aggregate(*head_Aggregate, temp_aggreg);
				if (rand() % prob_max < prob_disaggregation)
					*head_Chlam = desaggregate(*head_Chlam, head_Aggregate, temp_aggreg);
				else temp_aggreg = temp_aggreg->next;
			}
		}
	}
	Chlamydomonas *mothership = create_chlam(NO_COORD,NO_COORD,NO_COORD, 0);
	mothership->next = *head_Chlam;	
	exhaust(mothership);
	kill_chlam(mothership);
	*head_Chlam = mothership->next;
	*head_Aggregate = gathering(*head_Aggregate, head_Chlam, mothership);
	free(mothership);

	mothership = *head_Chlam;
	while (mothership != NULL) {
		check_change_dir(mothership);
		move(mothership);
		exhaust(mothership);
		kill_chlam(mothership);
		*head_Aggregate = gathering(*head_Aggregate, head_Chlam, mothership);
		*head_Chlam = mitosis(*head_Chlam, mothership);
		mothership = mothership->next;
	}
//	printf("Patch over\n");
}

/*
int main()
{
	init_world();
	while (getchar() != 'k')
	{
		if (getchar() == 'a') {
			delete_world();
			init_world();
		}
		else  {
			patch(&head_chlam, &head_aggregate);
			if (NO_MORE_MEMORY == 1)
				printf("NO_MORE_MEMORY");
		}
	}
	delete_world();
}
*/