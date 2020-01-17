typedef struct chlamydomonas {
	int x;
	int y;
	int z;
	int direction;
    int food;
	struct chlamydomonas *next;
    float distance_in_aggregate;
}Chlamydomonas;

typedef struct numb_per_coord{
    int *numb_per_x;
    int *numb_per_y;
    int *numb_per_z;
}Numb_per_coord;

typedef struct aggregate {
    int number;
    Chlamydomonas *center;
    Chlamydomonas *head;
    float radius;
    struct aggregate *next;
}Aggregate;