#ifdef _WIN32
	#include <windows.h>
	#define MKDIR(path) _mkdir(path)
#else
	#include <sys/stat.h>
	#include <sys/types.h>
	#define MKDIR(path) mkdir(path, 0755)
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "config.h"

char *type = "s";

void createDir(const char *dirname) {
	if(MKDIR(dirname) != 0) {
		printf("ERROR %s - directory creation failed\n", dirname);
		exit(EXIT_FAILURE);
	} else {
		printf("%s - directory created\n", dirname);
	}
}

void createFile(const char *filename, const char *content) {
	FILE *file = fopen(filename, "w");
	if(!file) {
		printf("ERROR %s - file creation failed\n", filename);
		exit(EXIT_FAILURE);
	}
	if(fputs(content, file) == EOF) {
		printf("ERROR %s - writing failed\n", filename);
		exit(EXIT_FAILURE);
	}
	fclose(file);
	printf("%s - file created\n", filename);
}

void createCmain(const char *src_dir) {
	char path[256];
	snprintf(path, sizeof(path), "%s/main.c", src_dir);
	createFile(path, main_c_content);
}
void createMakefile(char *type,char *cc, char *flags, const char *name, char *include, char *obj, char *lib, char *src) {
	char content [2048];
	if(!strcmp(type,"-l")) {
	snprintf(content, sizeof(content), makefile_content_large,
		cc, flags, include, lib,
		src, obj, name);
	}
	else if(!strcmp(type,"-s")) {
	snprintf(content, sizeof(content), makefile_content_simple,
		cc,flags,"main.c",name);
	}
	createFile("makefile", content);
}

void cd(const char *dir) {
	if(chdir(dir) != 0) {
	printf("ERROR can't cd into %s", dir);
	exit(EXIT_FAILURE);
	}
}

void createLargeProject(const char *name) {
	createDir(name);
	cd(name);
	createDir("build");
	createDir("build/include");
	createDir("build/lib");
	createDir("build/obj");
	createDir("build/src");
	createCmain("build/src");
	createMakefile(type,"gcc","-O3",name,"build/include","build/obj","build/lib","build/src");
	cd("..");
	printf("Project '%s' structure created successfully!\n", name);
}

void createSimpleProject(const char *name) {
	createDir(name);
	createCmain(name);
	cd(name);
	createMakefile(type,"gcc","-O3",name,"build/include","build/obj","build/lib","build/src");
	cd("..");
}
int main(int argc, char *argv[]) {
	if(argc < 2) {
		printf(help);
		return -1;
	}
	const char *name = argv[1];
	if(argc == 3) {
		type = argv[2];
		if(!strcmp(type,"-s")) createSimpleProject(name);
		else if (!strcmp(type,"-l")) createLargeProject(name);
		else printf(help);
	}
	else if(argc < 3) createSimpleProject(name);
	else printf(help);
	return 0;
}
