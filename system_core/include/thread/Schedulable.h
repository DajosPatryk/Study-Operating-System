#ifndef Schedulable_h
#define Schedulable_h
#include "lib/Chain.h"

/**
 * Schedulable class:
 * Implements an element that can be used within the scheduler's ready list. This class is derived
 * from the Chain class, allowing instances to be linked together, facilitating easy management
 * in a linked list structure used by the scheduler.
 *
 * Notes:
 * - The class is designed to potentially store process-specific information such as runtime statistics
 *   and priorities which can be crucial for advanced scheduling decisions. However, as of now, these
 *   features are not implemented, and the class serves primarily as a chainable entity within the
 *   scheduler's ready list.
 * - The current implementation does not contain any member variables or methods, making it a placeholder
 *   for future enhancements where process-specific attributes may be required.
 */
class Schedulable: public Chain {
};

#endif
