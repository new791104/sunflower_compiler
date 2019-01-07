#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void initOutput(FILE*);
extern int yyparse();
extern int yylex();
extern FILE *yyin;
extern FILE *yyout;

int main(int argc, char* argv[]) {
    yyout = fopen("mips.txt", "w+");
    _Bool debug_mode = 0;
    int test = 0;

    if (argc == 2 && strcmp(argv[1], "-p") == 0) {
        yyparse();   
    }
    else {
        printf("#### You can use \"parse -p < filename\" to parse the file. ####\n");
        printf("#### Output will be \"mips.txt\" ####\n");
    }
    fclose(yyin);
    fclose(yyout);

	return 0;
}