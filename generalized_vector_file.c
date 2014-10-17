typedef struct _vector_t {
	void ** array;
	void * loc;
	void * end;
	size_t size;
	size_t vector_type;
	size_t elem_type;
} vector_t;

void vector_init(vector_t * vect, size_t vtype, size_t etype) {
	vect = malloc(sizeof(vector_t));
	vect->size = 10 * vect->vector_type;	// arbitrarily chose 10
	vect->array = malloc(vect->size);
	vect->loc = vect->array;
	vect->vector_type = vtype;
	vect->elem_type = etype;
	if(vtype == sizeof(int *)) {
		vect->end = (int *)vect->array[vect->size - 1];
	}
}

void vector_grow(vector_t * vect) {
	void ** newArray = malloc(2 * vect->size);
	size_t i = vect->size - 1;
	for(; i != 0; i--) {
		if(vect->array + i * vect->vector_type) {
			*(newArray + i * vect->vector_type) = 
				*(vect->array + i * vect->vector_type);
		}
		free(vect->array + i * vect->vector_type);
		*(vect->array + i * vect->vector_type) = NULL;
	}
	vect->loc = newArray + (vect->size - 1);
	vect->size *= 2;
	free(vect->array);
	vect->array = newArray;
}

void vector_push(vector_t * vect, void * elem) {
	if(vect == NULL) {
		vector_t * vect;
		vector_init(vect, sizeof(int *), sizeof(int));
	}
	if(vect->loc == (void *)(vect->array + sizeof(int *) * (vect->size - 1))) {
		vector_grow(vect);
	}
	vect->loc = malloc(vect->elem_type);
	if(vect->elem_type == sizeof(int)) {
		*((int *)vect->loc) = *((int *)elem);
	}
	// Can add cases for different kinds of types
	// (there shouldn't be many at all, in practice)
	else {
		printf("Error, type not defined in vector_push()!\n");
	}
	vect->loc += vect->vector_type;
}