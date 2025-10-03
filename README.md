# cmpb - C project builder

C mini builder - is a tool to build small projects in C. It's automatically generates directories, Makefile, main.c file with "Hello world!" program. 
The goal of the project is to create a simple tool for creating small projects in C, without manually creating folders and fighting with make and/or cmake.

# Installation

You can install cpb on Linux using following commands:
```
git clone https://github.com/azaz08967565/cmpb
```
```
cd cpb
```
```
make
```
```
sudo make install
```
to remove cpb you can use:
```
sudo make uninstall
```
It is possible to run this programm on Windows, macOS, and other linux distros, but support and release filles will be added later

# Usage

To use cpb, simply run the program, specifying the name of your future project as an argument (names with spaces are currently not supported).

```bash
cpb <project_name> <flag>
```
Empty name of the project, flag `-h`, or project name `-h` will print help information

With flag `-s`, or without any flags, program will create project with this structure:
```
<project_name>
        ├── build
        ├── <project_name>.c
        └── makefile
```
With flag `-l` program will create project with this structure:
```
<project_name>
        ├── build
        │   ├── include
        │   ├── lib
        │   ├── obj
        │   └── src
        │       └── <project_name>.c
        └── makefile
```
Custom structures support will be added later.
