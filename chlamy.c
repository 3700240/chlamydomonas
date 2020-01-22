#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "globales.h"
#include "structures.h"
void delete_world();

Chlamydomonas *head_chlam = NULL;
Aggregate *head_aggregate = NULL;

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
		delete_world();
		return NULL;
	}
	new->x = x;
	new->y = y;
	new->z = z;
	new->prev = NULL;
	new->next = NULL;
	new->distance_in_aggregate = 0.0;
	new->direction = rand() % 6;
	new->food = food;

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
	if (head == NULL)
		return elem;
	elem->next = head;
	head->prev = elem;

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
	new_elem->distance_in_aggregate = length;

	float minima = list->distance_in_aggregate;
	Chlamydomonas *temp_center = list;

	Chlamydomonas *temp = list->next;
	while (temp != NULL) {
		length = distance(temp, new_elem);
		temp->distance_in_aggregate += length;
		new_elem->distance_in_aggregate += length;
		if (minima > temp->distance_in_aggregate) {
			minima = temp->distance_in_aggregate;
			temp_center = temp;
		}
		temp = temp->next;
	}
	*radius = minima;
	return temp_center;
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
	if (head == NULL)
		return new;
	new->next = head;
	head->prev = new;
	return new;
} /*Adds an aggregate to our Aggregate list*/

Aggregate *adding_chlam_to_agg(Aggregate *head, Aggregate *aggreg, Chlamydomonas **elem)
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

	if (*elem == NULL)
		return head;
	if (aggreg == NULL) {
		aggreg = (Aggregate *) malloc(sizeof(Aggregate));
		if (aggreg == NULL) {
			NO_MORE_MEMORY = 1;
			delete_world();
			return NULL;
		}
		if ((*elem)->prev == NULL) { /* No ancestor */
			if ((*elem)->next != NULL) /*Follower*/
				(*elem)->next->prev = NULL;
			aggreg->center = aggreg->head = *elem;
			aggreg->number = 1;
			aggreg->radius = 0;
			if (head == NULL) { /*List leader, yay!*/
				aggreg->next = aggreg->prev =  NULL;
				*elem = (*elem)->next;
				aggreg->center->next = aggreg->center->prev = NULL;	
				return aggreg;
			} /*Take the chief's seat!*/
			aggreg->next = head;
			aggreg->prev = NULL;
			head->prev = aggreg;
			*elem = (*elem)->next;
			aggreg->center->next = aggreg->center->prev = NULL;
			return aggreg;
		} /*Now has an ancestor*/
		(*elem)->prev->next = (*elem)->next;
		if ((*elem)->next != NULL) /*Minion*/
			(*elem)->next->prev = (*elem)->prev;
		(*elem)->next = (*elem)->prev = NULL; /*Cutting off the world*/
		aggreg->center = aggreg->head = *elem;
		aggreg->number = 1;
		aggreg->radius = 0;
		*elem = (*elem)->next;
		if (head == NULL){/*No boss*/
			aggreg->next = aggreg->prev = NULL;
			return aggreg;
		}/*Boss to take care of*/
		aggreg->next = head;
		head->prev = aggreg;
		aggreg->prev = NULL;
		return aggreg;
	}

	/*Addind to an existing aggregate*/
	aggreg->number ++;
	float radius = 0;
	aggreg->center = find_center(aggreg->head, *elem, &radius);
	aggreg->radius = radius / aggreg->number;
	if ((*elem)->prev == NULL) {
		(*elem)->prev = (*elem)->next;
		(*elem)->next = aggreg->head;
		aggreg->head->prev = *elem;
		aggreg->head = *elem;
		*elem = (*elem)->prev;
		aggreg->head->prev = NULL;
		aggreg->number ++;

		if ((*elem) != NULL)
			(*elem)->prev = NULL;
		return head;
	}
	(*elem)->prev->next = (*elem)->next;
	(*elem)->next->prev = (*elem)->prev;
	(*elem)->next = aggreg->head;
	aggreg->head->prev = *elem;
	aggreg->head = *elem;
	*elem = (*elem)->prev->next;
	aggreg->head->prev = NULL;
	return head;
/*Adding the Chlamydomonas to the aggregate, taking it off the list
That specific aggregate already is in our list, so all good*/
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

	for (int i = 0; i < NB_INIT; i++) {
		head_chlam = adding_chlam(head_chlam, create_chlam((rand() % (XMAX - XMIN + 1)) + XMIN, (rand() % (YMAX - YMIN + 1)) + YMIN,(rand() % (ZMAX - ZMIN + 1)) + ZMIN, FOOD_INIT));
	}
//	printf("Initialisation SUCCESS");///////////////////////////////////////////////
}/*Creating the specified number of Chlamydomonas randomly positioned in the given coordinates
Also, initiating the seed for random*/

Chlamydomonas *exhaust(Chlamydomonas *elem)
{
	/*------------------------------------------------------------------------
	//
	// exhaust
	// Food supply and takes the cell off the list if necessary
	//
	// Takes as a parameter the Chlamydomonas it must check
	// Returns the last Chlam that went through hunger process and survived
	//
	------------------------------------------------------------------------*/

	if (elem == NULL)
		return NULL;
	if (rand() % prob_max < prob_eat)
		elem->food += food_increase;
	else elem->food -= food_decrease;
	if (elem->food <= 0) {
		Chlamydomonas *temp = elem->next;
		if (elem->prev == NULL) {
			free(elem);
			if (temp != NULL)
				temp->prev = NULL;
			return exhaust(temp);
		}
		elem->prev->next = temp;
		if (temp != NULL)
			temp->prev = elem->prev;
		free(elem);
		return exhaust(temp);
	}
	return elem;
}

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
				elem->x --;
			}
/*			else { 
				force_change_dir(elem); 
				move(elem); 
			} //Uncomment those lines if you don't want them to 'run into walls'
*/
			break;
		case 1:
			if (elem->x < XMAX) {
				elem->x ++;
			}
/*			else { 
				force_change_dir(elem); 
				move(elem); 
			} //Uncomment those lines if you don't want them to 'run into walls'
*/
			break;
		case 2:
			if (elem->y > YMIN) {
				elem->y --;
			}
/*			else { 
				force_change_dir(elem); 
				move(elem); 
			} //Uncomment those lines if you don't want them to 'run into walls'
*/
			break;
		case 3:
			if (elem->y < YMAX) {
				elem->y ++;
			}
/*			else { 
				force_change_dir(elem); 
				move(elem); 
			} //Uncomment those lines if you don't want them to 'run into walls'
*/
			break;
		case 4:
			if (elem->z > ZMIN) {
				elem->z --;
			}
/*			else { 
				force_change_dir(elem); 
				move(elem); 
			} //Uncomment those lines if you don't want them to 'run into walls'
*/
			break;
		case 5:
			if (elem->z < ZMAX) {
				elem->z ++;
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

Aggregate *spawn_Aggregate(Aggregate *head, Chlamydomonas **first_chlam, Chlamydomonas **second_chlam)
{
	/*------------------------------------------------------------------------
	//
	// spawn_Aggregate
	// Creates an aggregate from 2 existing Chlamydomonas, taking them off their list, and adds that one to the aggregate list
	//
	// Takes as parameters the aggregate list, and the 2 chlamydomonas that aggregate
	// Returns the updated aggregate list. The center of the new aggregate is the first one given or the first in the list if they are next to each other
	//
	------------------------------------------------------------------------*/

	Chlamydomonas *first = *first_chlam;
	Chlamydomonas *second = *second_chlam;
	if (first == NULL || second == NULL)
		return head;
	Aggregate *aggreg = (Aggregate *) malloc(sizeof(Aggregate));
	if (aggreg == NULL) {
		NO_MORE_MEMORY = 1;
		delete_world();
		return NULL;
	}
	if (first == second) { 
		if (first->prev == NULL) {
			*first_chlam = *second_chlam = first->next;
		}
		else 
			first->prev->next = first->next;
		if (first->next != NULL)
			first->next->prev = first->prev;
		aggreg->number = 1;
		aggreg->center = first;
		aggreg->head = first;
		aggreg->radius = 0;
		return add_aggreg(head,aggreg);
	}
	aggreg->number = 2;
	float dist = distance(first, second);
	aggreg->radius = dist/2.0;
	first->distance_in_aggregate = dist;
	second->distance_in_aggregate = dist;
	if (first->next == second) {
		aggreg->head = first;
		aggreg->center = first;
		if (first->prev != NULL)
			first->prev->next = second->next;
		if (second->next != NULL) {
			second->next->prev = first->prev;
			second->next = NULL;
		}
		aggreg->head->prev = NULL;
		*first_chlam = *second_chlam = second->next;
		return add_aggreg(head,aggreg);
	}
	if (second->next == first) {
		aggreg->head = second;
		aggreg->center = second;
		if (second->prev != NULL)
			second->prev->next = first->next;
		if (first->next != NULL) {
			first->next->prev = second->prev;
			first->next = NULL;
		}
		aggreg->head->prev = NULL;
		*second_chlam = *first_chlam = first->next;
		return add_aggreg(head,aggreg);
	}
	aggreg->head = first;
	aggreg->center = first;
	if (first->prev != NULL)
		first->prev->next = first->next;
	if (first->next != NULL)
		first->next->prev = first->prev;
	first->prev = NULL;
	first->next = second;
	if (second->prev != NULL)
		second->prev->next = second->next;
	if (second->next != NULL)
		second->next->prev = second->prev;
	second->next = NULL;
	second->prev = first;

	*first_chlam = first->next;
	*second_chlam = second->next;

	return add_aggreg(head, aggreg);
}

void kill_chlam(Chlamydomonas **elem)
{
	/*------------------------------------------------------------------------
	//
	// kill_chlam
	// Checks if a chlamydomonas is to die (stress reason) and takes it off the list if necessary, freeing it
	//
	// Takes as parameter the Chlamydomonas that is to be checked. If it dies, goes for the next one
	// Void function, changes the elements around that dude
	//
	------------------------------------------------------------------------*/
	if (elem == NULL) 
		return;

	if (rand() % prob_max < prob_die) {
		Chlamydomonas *temp = (*elem)->next;
		if ((*elem)->prev != NULL)
			(*elem)->prev->next = temp;
		if ((*elem)->next != NULL)
			temp->prev = (*elem)->prev;
		free(*elem);
		*elem = exhaust(temp);

		return kill_chlam(elem);
	}
}/*Kills one precise Chlamydomonas if conditions were too harsh for it to live*/

Aggregate *gathering(Aggregate *head, Chlamydomonas **head_Chlam, Chlamydomonas **elem)
{
	/*------------------------------------------------------------------------
	//
	// gathering
	// Tries to make aggregates from one Chlamydomonas to: first off existing aggregates; then other Chlamydomonas in their surrounding
	// If it managed to make an aggregate, exhausts the next guy, makes him move and tries to kill him and make him aggregate
	//
	// Takes as parameters the aggregate list, the chlamydomonas list, the 'ancestor' of the Chlamydomonas we will try to aggregate
	// Returns the updated aggregate list
	//
	------------------------------------------------------------------------*/

	if (*elem == NULL)
		return head;
	if (head != NULL) {
		Aggregate *temp_aggreg = head;
		while (temp_aggreg != NULL) {
			if (distance(*elem, temp_aggreg->center) <= temp_aggreg->radius + DIST_AGGREGATE) {
				head = adding_chlam_to_agg(head, temp_aggreg, elem);
				*elem = exhaust(*elem);
				kill_chlam(elem);
				check_change_dir(*elem);
				move(*elem);
				return gathering(head, head_Chlam, elem);
			}
			temp_aggreg = temp_aggreg->next;
		}
	}
	Chlamydomonas *temp_chlam = *head_Chlam;
	while (temp_chlam != NULL) {
		if (temp_chlam != *elem)
			if ((distance(*elem, temp_chlam) <= DIST_AGGREGATE) && (rand() % prob_max < prob_aggregation_between_cells)) {
				head = spawn_Aggregate(head, &temp_chlam, elem);
				*elem = exhaust(*elem);
				kill_chlam(elem);
				check_change_dir(*elem);
				move(*elem);
				return gathering(head, head_Chlam, elem);
			}
		temp_chlam = temp_chlam->next;
	}
	return head;
}

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

Chlamydomonas *desaggregate(Chlamydomonas *head_Chlam, Aggregate **aggreg)
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

	Aggregate *temp_aggreg = *aggreg;

	if (temp_aggreg == NULL)
		return head_Chlam;
	if (temp_aggreg->prev != NULL)
		temp_aggreg->prev->next = temp_aggreg->next;
	if (temp_aggreg->next != NULL)
		temp_aggreg->next->prev = temp_aggreg->prev;
	*aggreg = temp_aggreg->next;

	Chlamydomonas *temp = temp_aggreg->head;
	free(temp_aggreg);
	if (head_Chlam == NULL) {
		(*aggreg)->prev = NULL;
		if (rand() % prob_max < prob_disaggregation)
			return desaggregate(temp, aggreg);
		return temp;
	}
	Chlamydomonas *temp2 = temp;
	while (temp2->next != NULL) 
		temp2 = temp2->next;
	temp2->next = head_Chlam;
	head_Chlam->prev = temp2;
	return temp;
}

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

Aggregate *mitosis_in_aggregate(Aggregate *head, Aggregate *elem)
{
	/*------------------------------------------------------------------------
	//
	// mitosis_in_aggregate
	// For all Chlamydomonas in a given aggregate, checks if they can go through mitosis
	//
	// Takes as parameters the aggregate that is to be checked
	// Void function
	//
	------------------------------------------------------------------------*/

	if (elem == NULL)
		return head;
	Chlamydomonas *temp = elem->head;
	int number = elem->number;
	int new_prob = prob_init_clonage - (number * dimin_prob_clonage);
	Chlamydomonas *temp_chlam = NULL;
	for (int i = 0; i < number; i++) {
		if (new_prob <= 0)
			i = number;
		else {
			if (rand() % prob_max < new_prob) {
				temp->food /= 2;
				temp_chlam = create_chlam(temp->x,temp->y,temp->z, temp->food);
				head = adding_chlam_to_agg(head, elem, &temp_chlam);
				new_prob -= dimin_prob_clonage;
			}			
		}
		temp = temp->next;
	}
	return head;
}

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

Aggregate *hunger_in_aggregate(Aggregate *elem)
{
	/*------------------------------------------------------------------------
	//
	// hunger_in_aggregate
	// Makes sure every Chlamydomonas in the aggregate tries to eat, loses energy, and starves if necessary. If the aggregate turns out to be empty, checks for the next one
	//
	// Takes as parameter the aggregate that needs to be checked
	// Returns the last aggregate that ate
	//
	------------------------------------------------------------------------*/

	if (elem == NULL)
		return NULL;
	Chlamydomonas *temp = elem->head;
	if (temp == NULL) {
		if (elem->prev != NULL)
			elem->prev->next = elem->next;
		if (elem->next != NULL)
			elem->next->prev = elem->prev;
		Aggregate *temp_aggreg = elem->next;
		free(elem);
		if (rand() % prob_max < prob_disaggregation)
			head_chlam = desaggregate(head_chlam, &temp_aggreg);
		return hunger_in_aggregate(temp_aggreg);
	}
	if (rand() % prob_max < prob_eat)
		temp->food += food_increase;
	else temp->food -= food_decrease;
	if (temp->food <= 0) {
		elem->number --;
		elem->head = temp->next;
		if (elem->head == NULL) {
			if (elem->prev != NULL)
				elem->prev->next = elem->next;
			if (elem->next != NULL)
				elem->next->prev = elem->prev;
			Aggregate *temp_aggreg = elem->next;
			free(elem);
			if (rand() % prob_max < prob_disaggregation)
				head_chlam = desaggregate(head_chlam, &temp_aggreg);/*We changed aggregate so gotta make sure it doesn't explode*/
			return hunger_in_aggregate(temp_aggreg); 
		}
		elem->head->prev = NULL;
		elem->center = modify_distances_in_aggregate(elem, temp);
		free(temp);
		return hunger_in_aggregate(elem);
	}
	temp = temp->next;
	while (temp != NULL) {
		if (rand() % prob_max < prob_eat)
			temp->food += food_increase;
		else temp->food -= food_decrease;
		if (temp->food <= 0) {
			elem->number --;
			temp->prev->next = temp->next;
			if (temp->next != NULL)
				temp->next->prev = temp->prev;
			Chlamydomonas *temp2 = temp;
			elem->center = modify_distances_in_aggregate(elem, temp2);
			temp = temp->next;
			free(temp2);
		}
		else temp = temp->next;
	}
	return elem;
}

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
		if (rand() % prob_max < prob_disaggregation)
			*head_Chlam = desaggregate(*head_Chlam, head_Aggregate);
		*head_Aggregate = hunger_in_aggregate(*head_Aggregate);
		*head_Aggregate = mitosis_in_aggregate(*head_Aggregate, *head_Aggregate);
	
		Aggregate *temp_aggreg = (*head_Aggregate)->next;
		while (temp_aggreg != NULL) {
			if (rand() % prob_max < prob_disaggregation)
				*head_Chlam = desaggregate(*head_Chlam, &temp_aggreg);
			temp_aggreg = hunger_in_aggregate(temp_aggreg);
			*head_Aggregate = mitosis_in_aggregate(*head_Aggregate, temp_aggreg);
		}
	}

	Chlamydomonas *temp = NULL;
	*head_Chlam = exhaust(*head_Chlam);
	kill_chlam(head_Chlam);
	check_change_dir(*head_Chlam);
	move(*head_Chlam);
	*head_Aggregate = gathering(*head_Aggregate, head_Chlam, head_Chlam);
	mitosis(*head_Chlam, *head_Chlam);

	if (*head_Chlam != NULL)
		temp = (*head_Chlam)->next;
	while (temp != NULL) {
		temp = exhaust(temp);
		kill_chlam(&temp);
		check_change_dir(temp);
		move(temp);
		*head_Aggregate = gathering(*head_Aggregate, head_Chlam, &temp);
		mitosis(*head_Chlam, temp);
		if (temp != NULL)
			temp = temp->next;
	}
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