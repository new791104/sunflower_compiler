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
    // initOutput(yyout);

    if (strcmp(argv[1], "-p") == 0) {
        debug_mode = 1;    
    }

    if (argc == 1 && debug_mode) {
        printf("#### You can use \" parse -p < file\" to parse the file. ####\n");
        yyparse();
    }
    else if (argc == 2 && debug_mode) {
        yyin = fopen(argv[1], "r");
        yyparse();
    }
    else if (argc == 3 && debug_mode) {
        yyout = fopen(argv[2],"w+");
        yyin = fopen(argv[1], "r");
        yyparse();
    }
    fclose(yyin);
    fclose(yyout);

	return 0;
}

// void initOutput(FILE *file) {
//     char initString[] = "    .data\n    .text";
//     fwrite(initString, 1, strlen(initString), file);
// }