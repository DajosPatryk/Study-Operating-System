typedef void (*finit_ptr)();

extern "C" finit_ptr start_ctors;
extern "C" finit_ptr end_ctors;
extern "C" void call_ctors();
extern "C" void call_dtors();

/**
 * Calls all constructor functions.
 *
 * This function iterates over an array of function pointers, defined between
 * `start_ctors` and `end_ctors`. Each function pointer represents a constructor
 * function that is meant to be called to perform initializations before the main
 * application starts. The constructors are called in the order they appear.
 */
void call_ctors() {
	for (finit_ptr* ctor = &start_ctors; ctor != &end_ctors; ++ctor) {
		(*ctor)();
	}
}

extern "C" finit_ptr start_dtors;
extern "C" finit_ptr end_dtors;

/**
 * Calls all destructor functions.
 *
 * Similar to `call_ctors`, this function iterates over an array of function pointers,
 * defined between `start_dtors` and `end_dtors`. Each function pointer represents a
 * destructor function that is meant to be called to perform clean-up tasks after
 * the application or a certain scope ends. The destructors are called in the order
 * they appear, typically in reverse order of their corresponding constructors.
 */
void call_dtors() {
	for (finit_ptr* dtor = &start_dtors; dtor != &end_dtors; ++dtor) {
		(*dtor)();
	}
}

