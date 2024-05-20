#ifndef Coroutine_h
#define Coroutine_h

/**
 * Coroutine:
 * This class serves as the base for all types of processes in Co-Stubs,
 * using an object-oriented coroutine model. It is abstract, requiring derived
 * classes to implement the 'body' method, which acts as the main function
 * for the coroutine.
 */

/**
 * Declaration for the assembly procedure "switchContext", which is expected to be implemented.
 * This procedure performs the control transfer between coroutines by switching their stacks.
 */
extern "C" {
	void switchContext(void*& from, void*& to);
}

class Coroutine {
public:
    /**
     * Constructor for initializing a new coroutine.
     * Sets up the initial stack context if provided.
     * @param tos Pointer to the top of the stack space for this coroutine, can be NULL.
     */
	explicit Coroutine(void* tos = 0) { setup(tos); }

    /**
     * Transfers control from this coroutine to another specified coroutine 'next'.
     * The actual context switching is handled by the assembly function "switchContext".
     * @param next Pointer to the next coroutine to resume.
     */
	void resume(Coroutine* next) { switchContext(this->sp, next->sp); }

    /**
     * Pure virtual function defining the body of the coroutine.
     * Must be implemented by derived classes to specify the coroutine's behavior.
     */
	virtual void body() = 0;

    /**
     * Pure virtual function that is called when the body of the coroutine has completed.
     * Must be implemented by derived classes to handle cleanup or termination actions.
     */
	virtual void exit() = 0;

private:
    /**
     * Static function to invoke the body of a given coroutine and call its exit method upon completion.
     * Serves as a bridge between non-object-oriented and object-oriented parts of the system.
     * Note: Since "startup" is static, it does not receive an implicit "this" pointer.
     * @param obj Pointer to the coroutine instance.
     */
	static void startup(Coroutine* obj);

    /**
     * Sets up a new coroutine using the provided stack top pointer.
     * @param tos Initial stack pointer value for the new coroutine. Can be NULL, implying no stack is set.
     */
	void setup(void* tos);

    void* sp;   // Saved stack pointer for this coroutine.

    /**
     * Struct to represent the stack frame for a coroutine.
     * Stores registers and the coroutine's parameter, necessary for state saving and restoration during switches.
     */
	struct Stack {
		unsigned int edi;   // Extended Destination Index Register
		unsigned int esi;   // Extended Source Index Register
		unsigned int ebx;   // Extended Base Register
		void* ebp;          // Stack Base Pointer, for local base

        /**
         * Pointer to the coroutine function to start execution.
         */
		void (*coroutine)(Coroutine*);

        /**
         * Simulated return address, does not lead anywhere.
         */
		void* ret;

        /**
         * Parameter for the coroutine function, determined at runtime.
         */
		Coroutine* arg;
	};

};

#endif
