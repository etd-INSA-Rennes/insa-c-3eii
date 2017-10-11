

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "memoryList.h"

static List l = {NULL, NULL, NULL};

/*!
 * \brief Redefines the malloc function behavior
 * In addition of the memory allocation, this function adds an element in the list of the allocated blocks
 * \param[in] size the size of the block to be allocated
 * \param[in] file the file name where the memory allocation is required
 * \param[in] func the function name where the memory allocation is required
 * \param[in] line the line number where the memory allocation is required
 * \return void * the address of the allocated block
*/
void * myMalloc(unsigned int size, const char * file,  const char * func, int line) {
	void * allocated_block = NULL;

	if ((allocated_block = malloc(size)) != NULL) {
			insertSort(&l, file, func, line, allocated_block);
      printf("In file %s,\n\t function %s,\n\t\t line %d :\n\t\t\t allocated block at memory address: %p\n", file, func, line, allocated_block);
	}

	printList(&l);

	return allocated_block;
}


/*!
 * \brief Redefines the free function behavior
 * In addition of the memory deallocation, this function  deletes an element in the list of the allocated blocks.
 * \param[in] block the address of the block to be deallocated
 * \param[in] file the file name where the memory deallocation is required
 * \param[in] func the function name where the memory deallocation is required
 * \param[in] line the line number where the memory deallocation is required
*/
void myFree(void * block, const char * file,  const char * func, int line) {
    if (block) {
        deleteValue(&l, block);
				free(block);
        printf("In file %s,\n\t function %s,\n\t\t line %d :\n\t\t\t freed block at memory address: %p\n", file, func, line, block);
    }
}

/*!
 * \fn  int myCheck()
 * \brief Check if every allocated block has been freed
 * It relies on the counter of allocated blocks
 * \return int the number of allocated blocks
*/
int myCheck() {
		return countElement(&l);
}

/*!
 * Free every memory block registered in the list.
*/
void myGarbageCollector() {
		printf("===\nGarbage collector\n===\n");
		freeList(&l);
}
