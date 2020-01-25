#include <math.h>
#include <stdlib.h>
#include <time.h>

#include "globales.h"
#include "structures.h"
void delete_World();

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

Chlamydomonas *create_Chlam(int x, int y, int z, int food)
{
	Chlamydomonas *new = (Chlamydomonas *) malloc(sizeof(Chlamydomonas));
	if (new == NULL) {
		NO_MORE_MEMORY = 1;
		delete_World();
		return NULL;
	}
	new->x = x;
	new->y = y;
	new->z = z;
	new->prev = NULL;
	new->next = NULL;
	new->food = food;
	new->distance_in_aggregate = 0.0;
	new->direction = rand() % 6;

	return new;
}

Aggregate *create_Aggreg(Chlamydomonas *center)
{
	Aggregate *new = (Aggregate *) malloc(sizeof(Aggregate));
	if (new == NULL) {
		NO_MORE_MEMORY = 1;
		delete_World();
		return NULL;
	}
	if (center == head_chlam) {
		head_chlam = center->next;
		if (head_chlam != NULL)
			head_chlam->prev = NULL;
	}
	else {
		center->prev->next = center->next;
		if (center->next != NULL)
			center->next->prev = center->prev;
	}
	center->next = center->prev = NULL;
	new->number = 1;
	new->center = new->head = center;
	new->radius = 0;
	new->prev = new->next = NULL;

	return new;
}

float find_Distance(Chlamydomonas *first, Chlamydomonas *second)
{
	return sqrt((double)((first->x - second->x) * (first->x - second->x) + (first->y - second->y) * (first->y - second->y) + (first->z - second->z) * (first->z - second->z)));
}

Chlamydomonas *find_Center(Chlamydomonas *list, Chlamydomonas *new, float *radius)
{
	float distance = find_Distance(list, new);
	*radius = list->distance_in_aggregate += distance;
	new->distance_in_aggregate = distance;
	Chlamydomonas *center = list;
	list = list->next;
	while (list != NULL) {
		distance = find_Distance(list, new);
		list->distance_in_aggregate += distance;
		new->distance_in_aggregate += distance;
		if (list->distance_in_aggregate < *radius) {
			*radius = list->distance_in_aggregate;
			center = list;
		}
		list = list->next;
	}
	return center;
}

void add_Chlam(Chlamydomonas *elem)
{
	if (head_chlam == NULL) {
		head_chlam = elem;
		return;
	}
	if (elem == NULL)
		return;
	elem->next = head_chlam;
	head_chlam->prev = elem;
	head_chlam = elem;
}

void add_Aggreg(Aggregate *elem)
{
	if (head_aggregate == NULL) {
		head_aggregate = elem;
		return;
	}
	if (elem == NULL)
		return;
	head_aggregate->prev = elem;
	elem->next = head_aggregate;
	head_aggregate = elem;
}

Aggregate *Take_Chlam_From_Agg(Chlamydomonas *target, Aggregate *host)
{
	if (host == NULL)
		return NULL;
	if (host->head == target){
		host->head = target->next;
		if (host->head == NULL) {
			if (head_aggregate == host) {
				head_aggregate = head_aggregate->next;
				free(target);
				free(host);
				return head_aggregate;
			}
			Aggregate *next = host->next;
			host->prev->next = host->next;
			if (host->next != NULL)
				host->next->prev = host->prev;
			free(target);
			free(host);
			return next;
		}
	}
	else {
		target->prev->next = target->next;
		if (target->next != NULL)
			target->next->prev = target->prev;
	}
	host->number --;
	Chlamydomonas *temp = host->head;
	temp->distance_in_aggregate -= find_Distance(temp, target);
	float distance = temp->distance_in_aggregate;
	Chlamydomonas *center = temp;
	while (temp != NULL) {
		temp->distance_in_aggregate -= find_Distance(temp, target);
		if (temp->distance_in_aggregate < distance) {
			distance = temp->distance_in_aggregate;
			center = temp;
		}
		temp = temp->next;
	}
	free(target);
	host->center = center;
	host->radius = distance / host->number;
	return host;
}

void add_Chlam_To_Agg(Aggregate *target, Chlamydomonas *elem)
{
	if (elem == head_chlam) {
		head_chlam = head_chlam->next;
		if (head_chlam != NULL)
			head_chlam->prev = NULL;
	}
	else {
		if (elem->prev != NULL)
			elem->prev->next = elem->next;
		if (elem->next != NULL)
			elem->next->prev = elem->prev;
	}
	target->center = find_Center(target->head, elem, &(target->radius));
	target->number ++;
	target->radius /= target->number;
	elem->next = target->head;
	target->head->prev = elem;
	target->head = elem;
	elem->prev = NULL;
}

Aggregate *disaggregation(Aggregate *target)
{
	Aggregate *next = target->next;

	if (head_aggregate == target) {
		head_aggregate = next;
		if (head_aggregate != NULL)
			head_aggregate->prev = NULL;
	}
	else { 
		target->prev->next = next;
		if (next != NULL)
			next->prev = target->prev;
	}
	Chlamydomonas *temp = target->head;
	if (temp == NULL) {
		free(target);
		return next;
	}
	Chlamydomonas *temp2 = temp;
	while (temp2->next != NULL) {
		temp2 = temp2->next;
	}
	temp2->next = head_chlam;
	if (head_chlam != NULL)
		head_chlam->prev = temp2;
	head_chlam = temp;
	free(target);
	return next;
}

void check_Change_Dir(Chlamydomonas *elem)
{
	if (elem == NULL)
		return;
	if (rand() % prob_max < prob_change_direction)
		elem->direction = (elem->direction + 1 + (rand() % 5)) % 6; 
}

void force_Change_Dir(Chlamydomonas *elem)
{
	if (elem == NULL)
		return;
	elem->direction = (elem->direction + 1 +(rand() % 5)) % 6;
}

void move(Chlamydomonas *elem)
{
	if (elem == NULL)
		return;
	switch (elem->direction) {
		case 0: if (elem->x > XMIN)
				elem->x --;
/*
			else {
				force(Change_Dir(elem));
				move(elem);
			}
*/ //Uncomment if you don't want them to 'run' into walls
			break;
		case 1: if (elem->y < XMAX)
				elem->x ++;
/*
			else {
				force(Change_Dir(elem));
				move(elem);
			}
*/ //Uncomment if you don't want them to 'run' into walls
			break;
		case 2: if (elem->y > YMIN)
				elem->y --;
/*
			else {
				force(Change_Dir(elem));
				move(elem);
			}
*/ //Uncomment if you don't want them to 'run' into walls
			break;
		case 3: if (elem->y < YMAX)
				elem->y ++;
/*
			else {
				force(Change_Dir(elem));
				move(elem);
			}
*/ //Uncomment if you don't want them to 'run' into walls
			break;
		case 4: if (elem->z > ZMIN)
				elem->z --;
/*
			else {
				force(Change_Dir(elem));
				move(elem);
			}
*/ //Uncomment if you don't want them to 'run' into walls
			break;
		case 5: if (elem->z < ZMAX)
				elem->z ++;
/*
			else {
				force(Change_Dir(elem));
				move(elem);
			}
*/ //Uncomment if you don't want them to 'run' into walls
			break;
	}
}

Aggregate *spawn_Aggreg(Chlamydomonas *first, Chlamydomonas *second)
{
	if (first == second)
		return create_Aggreg(first);

	Aggregate *new = (Aggregate *) malloc(sizeof(Aggregate));
	if (new == NULL) {
		NO_MORE_MEMORY = 1;
		delete_World();
		return NULL;
	}

	if (first->next == second) {
		if (head_chlam == first) {
			head_chlam = second->next;
			if (head_chlam != NULL)
				head_chlam->prev = NULL;
		}
		else {
			first->prev->next = second->next;
			if (second->next != NULL)
				second->next->prev = first->prev;
		}
		second->next = NULL;
		new->head = new->center = first;
		new->radius = first->distance_in_aggregate = second->distance_in_aggregate = find_Distance(first, second);
		new->number = 2;
		new->prev = new->next = NULL;
		return new;
	}
	if (second->next == first) {
		if (head_chlam == second) {
			head_chlam = first->next;
			if (head_chlam != NULL)
				head_chlam->prev = NULL;
		}
		else {
			second->prev->next = first->next;
			if (first->next != NULL)
				first->next->prev = second->prev;
		}
		first->next = NULL;
		new->head = new->center = second;
		new->radius = second->distance_in_aggregate = first->distance_in_aggregate = find_Distance(second, first);
		new->number = 2;
		new->prev = new->next = NULL;
		return new;
	}
	if (head_chlam == first) {
		head_chlam = first->next;
		if (head_chlam != NULL)
			head_chlam->prev = NULL;
	}
	else {
		first->prev->next = first->next;
		if (first->next != NULL)
			first->next->prev = first->prev;
	}
	if (head_chlam == second) {
		head_chlam = second->next;
		if (head_chlam != NULL)
			head_chlam->prev = NULL;
	}
	else {
		second->prev->next = second->next;
		if (second->next != NULL)
			second->next->prev = second->prev;
	}
	new->head = new->center = first;
	new->radius = first->distance_in_aggregate = second->distance_in_aggregate = find_Distance(first, second);
	new->number = 2;
	new->prev = new->next = NULL;
	first->next = second;
	second->next = first->prev = NULL;
	second->prev = first;
	return new;
}

void kill_Chlam(Chlamydomonas *elem)
{
	if (elem == NULL)
		return;
	if (head_chlam == elem) {
		head_chlam = elem->next;
		if (head_chlam != NULL)
			head_chlam->prev = NULL;
	}
	else {
		elem->prev->next = elem->next;
		if (elem->next != NULL)
			elem->next->prev = elem->prev;
	}
	free(elem);
}

Chlamydomonas *hunger_Chlamydomonas(Chlamydomonas *elem)
{
	if (elem == NULL)
		return NULL;
	if (rand() % prob_max < prob_eat)
		elem->food += food_increase;
	else 
		elem->food -= food_decrease;
	if (elem->food <= 0) {
		Chlamydomonas *temp = elem->next;
		kill_Chlam(elem);
		if (temp == NULL)
			return NULL;
		elem = temp;
		while (elem != NULL && rand() % prob_max < prob_die) {
			temp = elem->next;
			kill_Chlam(elem);
			elem = temp;
		}
		return hunger_Chlamydomonas(elem);
	}
	return elem;
} //Will return the first guy in the list to survive hunger process

Chlamydomonas *aggregation(Chlamydomonas *elem)
{
	if (elem == NULL)
		return NULL;
	int test = 0;
	if (elem == head_chlam)
		test = 1;
	Chlamydomonas *next = elem->next;

	if (head_aggregate != NULL) {
		Aggregate *temp_aggreg = head_aggregate;
		while (temp_aggreg != NULL) {
			if (find_Distance(elem, temp_aggreg->center) <= temp_aggreg->radius + DIST_AGGREGATE) {
				add_Chlam_To_Agg(temp_aggreg, elem);
				elem = next;
				while (elem != NULL && rand() % prob_max < prob_die) {
					next = elem->next;
					kill_Chlam(elem);
					elem = next;
				}
				elem = hunger_Chlamydomonas(elem);
				check_Change_Dir(elem);
				move(elem);
				if (test)
					head_chlam = elem;
				return aggregation(elem);
			}
			temp_aggreg = temp_aggreg->next;
		}
	}

	Chlamydomonas *temp = head_chlam;
	while (temp != NULL) {
		if (temp != elem) {
			if (find_Distance(elem, temp) <= DIST_AGGREGATE && rand() % prob_max < prob_aggregation_between_cells) {
				if (temp == next) 
					next = next->next;
				add_Aggreg(spawn_Aggreg(temp, elem));
				elem = next;
				while (elem != NULL && rand() % prob_max < prob_die) {
					next = next->next;
					kill_Chlam(elem);
					elem = next;
				}
				if (elem != NULL) {
					elem = hunger_Chlamydomonas(elem);
					if (elem != NULL) {
						check_Change_Dir(elem);
						move(elem);
					}
				}
				return aggregation(elem);
			}
		}
		temp = temp->next;
	}
	if (rand() % prob_max < prob_self_aggregating) {
		add_Aggreg(spawn_Aggreg(elem, elem));
		elem = next;
		while (elem != NULL && rand() % prob_max < prob_die) {
			next = next->next;
			kill_Chlam(elem);
			elem = next;
		}
		if (elem != NULL) {
			elem = hunger_Chlamydomonas(elem);
			if (elem != NULL) {
				check_Change_Dir(elem);
				move(elem);
			}
		}
		return aggregation(elem);
	}
	return elem;
}//Returns the first guy in the list that did NOT aggregate

void mitosis(Chlamydomonas *elem)
{
	if (elem == NULL)
		return;
	elem->food /= 2;
	add_Chlam(create_Chlam(elem->x, elem->y, elem->z, elem->food));
}

void mitosis_In_Aggreg(Aggregate *elem)
{
	if (elem == NULL)
		return;
	Chlamydomonas *temp = elem->head;
	int new_prob = prob_init_clonage - elem->number * dimin_prob_clonage;
	char test = 1;
	while (temp != NULL && test) {
		if (temp->food > 3 && rand() % prob_max < new_prob) {
			temp->food /= 2;
			add_Chlam_To_Agg(elem, create_Chlam(temp->x,temp->y,temp->z, temp->food));
			new_prob -= dimin_prob_clonage;
			if (new_prob <= 0)
				test = 0;
		}
		temp = temp->next;
	}
}

Aggregate *hunger_Aggregate(Aggregate *elem)
{
	if (elem == NULL)
		return NULL;
	Chlamydomonas *temp = elem->head;
	if (temp == NULL) {
		if (head_aggregate == elem) {
			head_aggregate = elem->next;
			if (head_aggregate != NULL)
				head_aggregate->prev = NULL;
			free(elem);
			while (rand() % prob_max < prob_disaggregation)
				head_aggregate = disaggregation(head_aggregate);
			return hunger_Aggregate(head_aggregate);
		}
		elem->prev->next = elem->next;
		if (elem->next != NULL) 
			elem->next->prev = elem->prev;
		Aggregate *next = elem->next;
		free(elem);
		while (rand() % prob_max < prob_disaggregation)
			next = disaggregation(next);
		return hunger_Aggregate(next);
	}
	if (rand() % prob_max < prob_eat)
		temp->food += food_increase;
	else 
		temp->food -= food_decrease;
	if (temp->food <= 0) 
		return hunger_Aggregate(Take_Chlam_From_Agg(temp, elem));

	temp = temp->next;
	while (temp != NULL) {
		if (rand() % prob_max < prob_eat)
			temp->food += food_increase;
		else
			temp->food -= food_decrease;
		if (temp->food <= 0) {
			Chlamydomonas *temp2 = temp->next;
			Take_Chlam_From_Agg(temp,elem);
			temp = temp2;
		}
		else if (temp != NULL)
			temp = temp->next;
	}
	return elem;
}//Returns the last guy whose components experienced hunger

void patch()
{
	if (head_aggregate != NULL) {
		Aggregate *temp_aggreg = head_aggregate;
		while (temp_aggreg != NULL) {
			if (rand() % prob_max < prob_disaggregation)
				temp_aggreg = disaggregation(temp_aggreg);
			else {
				temp_aggreg = hunger_Aggregate(temp_aggreg);
				if (temp_aggreg != NULL)
					mitosis_In_Aggreg(temp_aggreg);
				if (temp_aggreg != NULL)
					temp_aggreg = temp_aggreg->next;
			}
		}
	}

	Chlamydomonas *temp_chlam = head_chlam;
	while (temp_chlam != NULL) {
		if (rand() % prob_max < prob_die) {
			Chlamydomonas *tempo = temp_chlam;
			temp_chlam = temp_chlam->next;
			kill_Chlam(tempo);
		}
		if (temp_chlam != NULL) {
			temp_chlam = hunger_Chlamydomonas(temp_chlam);
			if (temp_chlam != NULL) {
				check_Change_Dir(temp_chlam);
				move(temp_chlam);
				temp_chlam = aggregation(temp_chlam);
				if (temp_chlam != NULL) {
					if (temp_chlam->food > 3 && rand() % prob_max < prob_init_clonage)
						mitosis(temp_chlam);
				}
			}
		}
		if (temp_chlam != NULL) 
			temp_chlam = temp_chlam->next;
	}
}

void destroy_Chlam(Chlamydomonas *head)
{
	if (head == NULL)
		return;
	Chlamydomonas *temp = head->next;
	free(head);
	return destroy_Chlam(temp);
}

void destroy_Aggreg(Aggregate *list)
{
	if (list == NULL)
		return;
	destroy_Chlam(list->head);
	Aggregate *temp = list->next;
	free(list);
	return destroy_Aggreg(temp);
}

void delete_World()
{
	destroy_Chlam(head_chlam);
	destroy_Aggreg(head_aggregate);
	head_chlam = NULL;
	head_aggregate = NULL;
	is_initiated = 0;
}

void init_World()
{
	head_chlam = NULL;
	head_aggregate = NULL;

	srand(time(NULL));

	for (int i = 0; i < NB_INIT; i++) {
		add_Chlam(create_Chlam((rand() % (XMAX - XMIN + 1) + XMIN), (rand() % (YMAX - YMIN + 1) + YMIN), (rand() % (ZMAX - ZMIN + 1) + ZMIN), FOOD_INIT));
	}
	is_initiated = 1;
}

//Si on passe par un des process, temp = le return de ce process