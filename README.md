# C & C++ Based Operating System

<h6>This study was conducted as part of the module "BS1" at Brandenburgerische Technische Universität in Cottbus</h6>

This repository is part of an operating systems study project, written in C, C++, and Assembly. It provides a foundational template for learning about OS design, commonly used in European university courses.

## Features
### Display & Screen Management
- **CGA Screen Based:** The system uses a CGA (Color Graphics Adapter) for display management, providing basic output functionality.
- **CGAchannel.cc:** Manages screen output channels.
- **CgaScreen.cc:** Handles low-level CGA screen operations.
### Thread & Activity Management
- **Thread Management:** The OS supports basic threading mechanisms to allow concurrent execution.
- **Activity Management:** Manages and schedules different activities (threads) using a Queue.
- **Coroutines:** Implemented in Coroutine.cc, allowing cooperative multitasking within the OS.
### Synchronization & Semaphores
- **Semaphores:** Used for controlling access to shared resources, enabling safe and synchronized execution of concurrent tasks.
### Interrupt Handling
- **Gate-based Interrupts:** The system uses gates to manage hardware interrupts:
- **Interruptguardian.cc:** Safeguards interrupt handling.
- **Panicgate.cc:** Handles critical interrupts and system panics.
- **Spuriousgate.cc:** Manages spurious interrupts (unwanted interrupts).
- **PIC (Programmable Interrupt Controller):** Handled in PIC.cc to manage hardware interrupt requests.
- **PIT (Programmable Interval Timer):** PIT.cc controls time-based events and interrupts.
- **Clock.cc:** The system's clock module is used for time management and clock interrupts.
- **Keyboard.cc:** Manages keyboard inputs and associated interrupts.
### Parsing & Interpreting
- **Calc.cc, Interp.cc, Scanner.cc:** Modules that provide basic mathematical interpretation and expression parsing.
### PrintStream
- Provides a PrintStream interface for outputting formatted text to the screen.

### Custom WSL2 Configuration File
- A custom run file for WSL2 systems.

### Run
This operating system is meant to be ran on a bare-bones Linux system. It is required for to have C and C++ compilers installed and bochs emulator.

Run either by running `run.sh` inside of `/system_core`, or execute the following command
```bash
cd ./system_core/bin
make clean bootdisk
bochs -q
```
