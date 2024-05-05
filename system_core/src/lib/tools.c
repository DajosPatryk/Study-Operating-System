#include "lib/tools.h"

/**
 * Copies `n` bytes from memory area `src` to memory area `dest`.
 *
 * The copying is done byte by byte, starting from the beginning of `src` and
 * copied into `dest`. Both `src` and `dest` are treated as character pointers
 * to handle the byte-by-byte copy operation. This function does not handle
 * overlapping memory areas; if `src` and `dest` overlap, the behavior is
 * undefined.
 *
 * @param dest Pointer to the destination memory area where the content is to be copied.
 * @param src Pointer to the source memory area from which the content is to be copied.
 * @param n Number of bytes to copy.
 *
 * @return Returns a pointer to the destination memory area `dest`.
 */
void* memcpy(void* dest, const void* src, unsigned n){
	
	char* a= dest;
	const char* b= src;
	unsigned i= 0;

	for(i=0; i < n; i++){
		
		(*a) = (*b);
		a++;
		b++;
	}
	
	return dest;
}


