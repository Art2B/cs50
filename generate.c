#include <stddef.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "bstrlib.h"
#include <regex.h>

int main(int argc, char** argv) {
  struct stat st = {0};
  regex_t path_reg;
  char *pattern = "[^A-Za-z0-9|-|_]";
  int compiled_reg = regcomp(&path_reg, pattern, REG_EXTENDED);

  if (compiled_reg != 0) {
    char reg_error_buffer[512];
    regerror(compiled_reg, &path_reg, reg_error_buffer, 512);
    printf("Regex Error: %s\n", reg_error_buffer);
    return 1;
  }

  if (argc <= 1) {
    printf("Must provide at least 1 argument.\nUsage: ./generate NAME1\n");
    return 1;
  }

  for(int i=1; i<argc; i++) {
    // Check if name contains only alphabetical, numbers, - or _
    size_t nmatch = 1;
    regmatch_t pmatch[1];
    int reg_match = regexec(&path_reg, argv[i], nmatch, pmatch, 0);

    if (reg_match != REG_NOMATCH) {
      printf("Name: %s is not supported. Only alphabetical characters, numbers, \"-\" and \"_\" are supported. Skipping", argv[i]);
      continue;
    }

    // Generate folder path
    char folderPath[512];
    snprintf(folderPath, sizeof(folderPath), "./%s", argv[i]);

    if (stat(folderPath, &st) >= 0) {
      printf("Project %s already exist. Skipping.\n", argv[i]);
    }

    // Generate folder
    mkdir(folderPath, 0700);

    FILE* makefile = fopen("./.boilerplate/Makefile", "r");
    if (makefile == NULL) {
      printf("Generator ERROR: cannot open .boilerplate/Makefile");
      return 2;
    }

    // Generate path for makefile
    char makefile_output_path[528]; 
    snprintf(makefile_output_path, sizeof(makefile_output_path), "%s/Makefile", folderPath);

    // Create file for makefile
    FILE* makefile_output = fopen(makefile_output_path, "a");
    bstring to_replace = bfromcstr("$NAME");
    bstring new_name = bfromcstr(argv[i]);

    char makefile_string[100];
    while(fgets(makefile_string, 100, makefile)) {
      bstring mfs = bfromcstr(makefile_string);
      int position = binstr(mfs, 0, to_replace);

      // Check if there is something to replace
      if (position >= 0) {
        int result = bfindreplace(mfs, to_replace, new_name, 0);
        if (result == BSTR_OK) {
          fprintf(makefile_output, "%s", bdata(mfs));
        }
      } else {
        fprintf(makefile_output, "%s", makefile_string);
      }
      bdestroy(mfs);
    }

    // Close/clear strings and files
    bdestroy(to_replace);
    bdestroy(new_name);
    fclose(makefile);
    fclose(makefile_output);

    // Copy boilerplate of main.c
    FILE* main_file = fopen("./.boilerplate/main.c", "r");
    if (main_file == NULL) {
      printf("Generator ERROR: cannot open boilerplate/main.c");
      return 2;
    }

    char mf_output_file[1027]; 
    snprintf(mf_output_file, sizeof(mf_output_file), "%s/%s.c", folderPath, argv[i]);

    FILE* mf_output = fopen(mf_output_file, "a");
    char mf_string[100];
    while(fgets(mf_string, 100, main_file)) {
      fprintf(mf_output, "%s", mf_string);
    }

    // Close main.c file
    fclose(main_file);
    fclose(mf_output);

    printf("Generated boilerplate for %s\n", argv[i]);
  }

  regfree(&path_reg);

  printf("Finished generating boilerplates !\n");
  return 0;
}
