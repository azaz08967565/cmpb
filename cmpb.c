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
	const char *main_c_content = 
	"#include <stdio.h>\n\n"
	"int main(int argc, char *argv[]) {\n"
	"\tprintf(\"Hello World!\\n\");\n"
	"\treturn 0;\n"
	"}\n";
	createFile(path, main_c_content);
}
void createMakefile(char *cc, char *flags, const char *name, char *include, char *obj, char *lib, char *src) {
	char *makefile_content = 
	"CC = %s\n"
	"CFLAGS = %s\n"
	"INCLUDES = -I%s\n"
	"LIBS = -L%s\n"
	"SRC_DIR = %s\n"
	"OBJ_DIR = %s\n"
	"EXE = %s\n"
	"MKDIR = mkdir -p\n"
	"RM = rm -f\n"
	"RMDIR = rm -rf\n"
	"SRCS = \\\n"
	"\t$(SRC_DIR)/main.c\n"
	"OBJS = $(patsubst $(SRC_DIR)/%%.c, $(OBJ_DIR)/%%.o, $(SRCS))\n"
	"all: $(EXE)\n"
	"$(EXE): $(OBJS)\n"
	"\t$(CC) -o $@ $^ $(LIBS)\n"
	"$(OBJ_DIR)/%%.o: $(SRC_DIR)/%%.c | $(OBJ_DIR)\n"
	"\t$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@\n"
	"$(OBJ_DIR):\n"
	"\t$(MKDIR) $(OBJ_DIR)\n"
	"clean:\n"
	"\t$(RM) $(EXE)\n"
	"\t$(RMDIR) $(OBJ_DIR)\n"
	".PHONY: all clean\n";
	char content [2048];
	snprintf(content, sizeof(content), makefile_content,
		cc, flags, include, lib,
		src, obj, name);
	createFile("makefile", content);
}

void cd(const char *dir) {
	if(chdir(dir) != 0) {
	printf("ERROR can't cd into %s", dir);
	exit(EXIT_FAILURE);
	}
}

int main(int argc, char *argv[]) {
	if(argc < 2) {
		printf("Usage: %s <project_name>\n", argv[0]);
		return -1;
	}
	const char *name = argv[1];
	createDir(name);
	cd(name);
	createDir("build");
	createDir("build/include");
	createDir("build/lib");
	createDir("build/obj");
	createDir("build/src");
	createCmain("build/src");
	createMakefile("gcc","-O3",name,"build/include","build/obj","build/lib","build/src");
	printf("Project '%s' structure created successfully!\n", name);
	return 0;
}
