typedef struct chlamydomonas {
	int x;
	int y;
	int z;
	int direction;
    int food;
	struct chlamydomonas *next;
    struct chlamydomonas *prev;
    float distance_in_aggregate;
}Chlamydomonas;

typedef struct aggregate {
    int number;
    Chlamydomonas *center;
    Chlamydomonas *head;
    float radius;
    struct aggregate *next;
    struct aggregate *prev;
}Aggregate;