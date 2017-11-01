/**
	DS Assignment 3
	Implementation of a vector of integers in C
	vectors.h

	@author Shreyansh Murarka
	@version 1.0.0
*/

#ifndef VECTORS
#define VECTORS
#include <stdlib.h>
#include <limits.h>
#include <math.h>

typedef enum{FALSE=0,TRUE=1} BOOLEAN;

typedef struct{
	int *arr;
	int max_size;
	int size;
}VECTOR;
/**
	Initialises the vector pointer with an initial_size

	@param initial_size The initial size of the vector
	@return The initialized pointer of VECTOR
*/
VECTOR* init(int initial_size){
	VECTOR* vec=(VECTOR*) malloc(sizeof(VECTOR));
	vec->arr=(int*) malloc(initial_size*sizeof(int));
	vec->max_size=initial_size;
	vec->size=0;
	return vec;
}

/**
	Inserts an element in the vector at a specified position

	@param vec The pointer to the VECTOR to be used
	@param position The position at which the element needs to be inserted
	@param data The element that needs to be inserted
	@return Returns 1 if the element has been inserted, 0 otherwise
*/

BOOLEAN insert(VECTOR *vec,int position, int data){
	if(vec->size == vec->max_size){
		int *new_arr = realloc(vec->arr,vec->max_size*2);
		if(!new_arr)
			return FALSE;
		vec->max_size=vec->max_size*2;
		vec->arr=new_arr;
	}
	if(vec->size < position)
		return FALSE;
	if(position < 0)
		return FALSE;
	int i;
	for(i=vec->size;i>position;i--)
		vec->arr[i]=vec->arr[i-1];
	vec->arr[position]=data;
	vec->size++;
	return TRUE;
}

/**
	Inserts an element to the end of a vector
	
	@param vec The pointer to the VECTOR to be used
	@param data The element that needs to be inserted
	@return Returns 1 if the element has been inserted, 0 otherwise
*/

BOOLEAN push_back(VECTOR *vec,int data){
	return insert(vec,vec->size,data);
}

/**
	Inserts an element to the beginning of a vector
	
	@param vec The pointer to the VECTOR to be used
	@param data The element that needs to be inserted
	@return Returns 1 if the element has been inserted, 0 otherwise
*/

BOOLEAN push_front(VECTOR *vec,int data){
	return insert(vec,0,data);
}

/**
	Returns the element present at a specified position
	
	@param vec The pointer to the VECTOR to be used
	@param position The position whose element is needed
	@return Returns the element at position
*/

int get(VECTOR *vec,int position){
	if(position >= vec->size || position < 0)
		return INT_MIN;
	return vec->arr[position];
}

/**
	Returns the element present at the beginning of the VECTOR
	
	@param vec The pointer to the VECTOR to be used
	@return Returns the element at the first position
*/

int get_front(VECTOR *vec){
	return get(vec,0);
}

/**
	Returns the element present at the end of the VECTOR
	
	@param vec The pointer to the VECTOR to be used
	@return Returns the element at the last position
*/

int get_back(VECTOR *vec){
	return get(vec,vec->size-1);
}

/**
	Sets the value of the element at a specified position
	
	@param vec The pointer to the VECTOR to be used
	@param position The position where the element needs to be modified
	@param data The value that needs to be set
	@return Returns 1 if the element has been modified, 0 otherwise
*/

BOOLEAN set(VECTOR *vec,int position,int data){
	if(position >= vec->size || position<0)
		return FALSE;
	vec->arr[position]=data;
	return TRUE;
}

/**
	Removes the element at a specified position

	@param vec The pointer to the VECTOR to be used
	@param position The position from where element is to be removed
	@return The removed element
*/

int remove_elem(VECTOR *vec, int position){
	if(position >= vec->size || position<0)
		return INT_MIN;
	int i;
	int data=vec->arr[position];
	for(i=position;i<vec->size;i++)
		vec->arr[i]=vec->arr[i+1];
	vec->size--;
	return data;
}

/**
	Removes the last element from the vector

	@param vec The pointer to the VECTOR to be used
	@return The element that has been removed
*/

int pop_back(VECTOR *vec){
	return remove_elem(vec,vec->size-1);
}

/**
	Removes the first element from the vector

	@param vec The pointer to the VECTOR to be used
	@return The element that has been removed
*/

int pop_front(VECTOR *vec){
	return remove_elem(vec,0);
}

/**
	Inserts an array to the vec

	@param vec The pointer to the VECTOR to be used
	@param arr The integer array to be inserted
	@param n  The number of elements from the array to be inserted
	@return Returns 1 if the elements are inserted, 0 otherwise
*/

BOOLEAN insert_array(VECTOR *vec,int *arr,int n){
	int i;
	int initial_size = vec->size;
	for(i=0;i<n;i++){
		if(!push_back(vec,arr[i])){
			vec->size = initial_size;
			return FALSE;
		}
	}
	return TRUE;
}

/**
	Adds 2 vectors and returns the sum

	@param v1 The first vector to be added
	@param v2 The second vector to be added
	@return pointer to the vector containing the sum of the 2 vectors
*/

VECTOR* add_vectors(VECTOR v1,VECTOR v2){
	if(v1.size != v2.size)
		return NULL;
	VECTOR* sum=init(v1.size);
	int i;
	for(i=0;i<v1.size;i++)
		push_back(sum,v1.arr[i]+v2.arr[i]);
	return sum;
}


/**
	Calculates the dot product of 2 vectors

	@param v1 The first vector
	@param v2 The second vector
	@return The dot product of v1 and v2
*/
int dot_product(VECTOR v1,VECTOR v2){
	if(v1.size != v2.size)
		return INT_MIN;
	int sum,i;
	sum=0;
	for(i=0;i<v1.size;i++)
		sum+=v1.arr[i]*v2.arr[i];
	return sum;
}

/**
	Multiplies the given vector with a scalar

	@param vec The pointer to the vector that needs to be multiplied
	@param scalar The scalar value by which the vector is to be multiplied
*/

VECTOR* multiply_scalar(VECTOR *vec,int scalar){
	int i;
	VECTOR *new_vec = init(vec->size);
	for(i=0;i<vec->size;i++)
		push_back(new_vec,vec->arr[i]*scalar);
	return new_vec;
}

/**
	Calculates the norm of the given vector

	@param vec The vector whose norm is to be calculated
	@return The norm of the given vector
*/

double norm(VECTOR vec){
	double val;
	int i;
	val=0.0;
	for(i=0;i<vec.size;i++)
		val+=vec.arr[i]*vec.arr[i];
	val = sqrt(val);
	return val;
}

/**
	Displays the vector

	@param vec The vector to be displayed
*/
void show_vec(VECTOR vec){
	int i;
	for(i=0;i<vec.size;i++)
		printf("%d ", vec.arr[i]);
	printf("\n");
}

#endif