# cmpb - C mini project builder

C mini project builder - is a tool to build small projects in C. It's automatically generates directories, Makefile, main.c file with "Hello world!" program. 
The goal of the project is to create a simple tool for creating small projects in C, without manually creating folders and fighting with make and/or cmake.

# Installation

To install this program on Linux use following commands
```
git clone https://github.com/azaz08967565/cmpb
```
```
cd cmpb
```
```
make
```
```
sudo make install
```
To uninstall:
```
sudo make uninstall
```
It is possible to run this programm on Windows, but support and release filles will be added later

# Usage

To use this just run the programm with the name of your future project as a second argument (names with spaces unsupported at the time).

```bash
cmpb <project_name>
```
It will create project with this structure:

```
<project_name>
        ├── build
        │   ├── include
        │   ├── lib
        │   ├── obj
        │   └── src
        │       └── main.c
        └── makefile
```
Different/Custom structures support will be added later
