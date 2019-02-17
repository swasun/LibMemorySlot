# Description

LibMemorySlot provides an API to save/load slot from/to executable. A slot is a chunck of data identified by an integer ID, saved directly in the executable. The creation of the slot have to be when the executable isn't running ; however, the update and the load can be at the running time of the process.

# API

Example of use of API without error handling for sake of simplicity.

In `save_slot_example.exe`, load a slot from a file, and save it to the executable we want.
```c
ms_slot *slot = ms_slot_create_from_file("data.txt");
ms_slot_save_to_file(slot, SLOT_ID, "load_slot_example.exe");
ms_slot_destroy(slot);
```

In `load_slot_example.exe`, load a slot from the same integer id used in saving.
```c
ms_slot *slot = ms_slot_load(SLOT_ID);
printf("%s\n", (char *)slot->data);
ms_slot_destroy(slot);
```

# Output

Saving the slot onto an exe.
```bash
>save_slot_example.exe
[INFO] Loading slot from file 'data.txt'...
[INFO] Slot loaded.
[INFO] Saving slot...
[INFO] Slot saved to file 'load_slot_example.exe'.
```

Loading the saved slot.
```bash
>load_slot_example.exe
[INFO] Loading slot id 100
[DEBUG] size: 13
[INFO] Slot loaded.
[INFO] Content of the slot: Hello world ! of size 13
```

# Dependencies

* [LibErrorInterceptor](https://github.com/swasun/LibErrorInterceptor) a lightweight and cross-plateform library to handle stacktrace and logging in C99.
* [LibUnknownEchoUtilsModule](https://github.com/swasun/LibUnknownEchoUtilsModule) Utils module of [LibUnknownEcho](https://github.com/swasun/LibUnknownEcho). Last version.

# Installation

Clone the repository:
```bash
git clone http://github.com/swasun/LibMemorySlot
```

Build in release mode:
```bash
mkdir -p build/release
cmake -Bbuild/release -H. -DCMAKE_BUILD_TYPE=Release
cd build/release
cmake --build . --config Release
```

Or build in debug mode:
```bash
mkdir -p build/debug
cmake -Bbuild/debug -H. -DCMAKE_BUILD_TYPE=Debug
cd build/debug
cmake --build . --config Debug
```

* By default, dependencies are built and install in the `build` directoy.
To specify an other path, add `-DLIBEI_INSTALL=/usr` flag (LIBUEUM_INSTALL for LIBUEUM) in `cmake` command.

* To build with LIBEI already installed in the system, add `-DLIBEI_SYSTEM=TRUE` flag (LIBUEUM_SYSTEM for LIBUEUM) in `cmake` command.

* Alternatively, you can build using `build_release.<sh|bat>` and `build_debug.<sh|bat>` scripts.

Finally, to install in the system:
```bash
cd build/release
<sudo> cmake --build . --config Release --target install
```

# Implementation

The Windows implementation manipulate the Resource API. No Linux implementation for now.

# Cross-plateform

Tested on:
* Windows x86
* Windows 64
