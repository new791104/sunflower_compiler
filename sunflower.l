%{
/*
*   sunflower 詞彙分析
*/
#include <stdio.h>
#include <string.h>
#include "sunflower.tab.h"

char *exception_array = "\0";
void lexerror(char*);
char *combineStr(char*, char*);
char *getReg();
void putReg(char*);
char *makeAluInstr(char*, char*, char*, char*, char*);
char *makeIdentifierInstr(char*, char*, char*);
char* makeBranchInstr(char*, char*, char*, char*, char*);
char *newLabel();
char *makebooleanTermInstr(char *text, branch_type branch);
char *deleteLine(char *text);
char *formatLabel(char *label);
char *doNEG(char*);
int countLines(char *text);
char *substr(char *dest, char *src, int start, int cnt);
char *insertInstr(char *text, char *mid, int addr, int isAnd);

int integer_length(int integer);
int REG_TEMP[10] = {0};
int REG_TEMP_LENGTH = sizeof(REG_TEMP) / sizeof(int);
int LABEL_COUNTER = 0;
%}
letter [A-Za-z]
digit [0-9]
Identifier (_|{letter})({letter}|_|{digit})*
IntConst {digit}+
Space [ \t]+
%x COMMENT
%%
\n {yylineno++;}
And {return AND;}
Begin {return BEGIN_;}
Do {return DO;}
Else {return ELSE;}
End {return END;}
EndIf {return ENDIF;}
EndWhile {return ENDWHILE;}
Exit {return EXIT;}
If {return IF;}
Set {return SET;}
Not {return NOT;}
Or {return OR;}
Program {return PROGRAM;}
Read {return READ;}
Then {return THEN;}
Var {
    return VAR;
}
While {return WHILE;}
Write {return WRITE;}
"+" {return ADD;}
"-" {return SUB;}
"*" {return MUL;}
"/" {return DIV;}
"%" {return MOD;}
"=" {return GIVE;}
"==" {return EQUAL;}
"<>" {return NEQUAL;}
">" {return GREATER;}
">=" {return GEQUAL;}
"<" {return SMALLER;}
"<=" {return SEQUAL;}
"(" {return LEFTBRACKET;}
")" {return RIGHTBRACKET;}


{Identifier} {
    if (yyleng > 16) {
        char buffer[10];
        sprintf(buffer, "Lexical error: line %d identifier length too long\n", yylineno);
        exception_array = combineStr(exception_array, buffer);
    }
    yylval.str = combineStr(yytext, "\0");
    return IDENTIFIER;
}
{IntConst} {
    int integer = atoi(yytext);
    if (integer > 0x4FFF || integer < -0x4FFF) {
        char buffer[10];
        sprintf(buffer, "Lexical error: line %d illegal integer constant\n", yylineno);
        exception_array = combineStr(exception_array, buffer);
    }
    yylval.str = combineStr(yytext, "\0");
    return INTCONST;
}

"//" {
    BEGIN COMMENT;
}

<COMMENT>\n {
    yylineno++;
    BEGIN INITIAL;
}

<COMMENT>. {
}

{Space} {
    // do nothing
}

. {
    char buffer[1];
    sprintf(buffer, "Lexical error: line %d unknown character %s\n", yylineno, yytext);
    exception_array = combineStr(exception_array, buffer);
}

%%
int yywrap()
{
    return 1;
}

int yyerror(const char* msg){
    fprintf(stderr, "%s: line %d\n", msg, yylineno);
    return 1;
}

void lexerror(char* msg) {
    char buffer[10];
    sprintf(buffer, "Lexical error: line %d %s\n", yylineno, msg);
    exception_array = combineStr(exception_array, buffer);
}

char *combineStr(char* str1, char* str2) {
    char *result = malloc(strlen(str1) + strlen(str2) + 1);
    result[0] = '\0';
    sprintf(result, "%s%s", str1, str2);
    return result;
}

char *getReg() {
    for (int i = 0; i < REG_TEMP_LENGTH; i++) {
        if (REG_TEMP[i] == 0) {
            REG_TEMP[i] = 1;
            char index[1];
            sprintf(index, "%d", i);
            // printf("#### index: %s\n", index);
            return combineStr("$t", index);
        }
    }
    return "####### REG BUFFER OVERFLOW ########";
}

/*
* 假設只會用 t0 ~ t9 號暫存器
*/
void putReg(char *reg) {
    int token = reg[2] - '0';
    REG_TEMP[token] = 0;
}

char *makeAluInstr(char *text, char *op, char *rs, char *rt, char *rd) {
    char result[20];
    snprintf(result, sizeof(result), "\n%s %s, %s, %s", op, rd, rs, rt);
    text = combineStr(text, result);
    return text;
}

char *makeBranchInstr(char *text, char *op, char *rs, char *rt, char *label) {
    char result[20];
    snprintf(result, sizeof(result), "\n%s %s, %s, %s", op, rs, rt, label);
    text = combineStr(text, result);
    return text;
}

char *makeIdentifierInstr(char *text, char *reg, char *label) {
    char result[40] = {0};
    snprintf(result, sizeof(result), "\nla %s, %s", reg, label);
    snprintf(result, sizeof(result), "%s\nlw %s, 0(%s)", result, reg, reg);
    text = combineStr(text, result);
    return text;
}

char *newLabel() {
    char *result = malloc(integer_length(LABEL_COUNTER) + 1);
    snprintf(result, sizeof(result), "L%d\0", LABEL_COUNTER);
    LABEL_COUNTER++;
    return result;
}

char *formatLabel(char *label) {
    char *nexline = "\n", *colon = ":";
    char *label_format = malloc(strlen(label) + 2 + 1);
    label_format[strlen(label_format) - 1] = '\0';
    sprintf(label_format, "\n%s:", label);
    return label_format;
}

int integer_length(int integer) {
    int i;
    for (i = 0;; i++) {
        if (integer <= 0) {
            break;
        }
        integer /= 10;
    }
    return i;
}

// char *makebooleanTermInstr(char *text, branch_type branch) { 
//     char result[20], *label = newLabel(), label_format[10];
//     snprintf(result, sizeof(result), "\n%s %s, $zero, %s", branch.op, branch.reg, label);
//     text = combineStr(text, result);
//     putReg(branch.reg);
//     snprintf(label_format, sizeof(label_format), "\n%s:", label);
//     return combineStr(branch.label_array, label_format);
// }

char *deleteLine(char *text) {
    int i = 0;
    char *output;
    for (i = strlen(text); i >= 0; i--) {
        char tmp = *(text + i);
        if (tmp == '\n') {
            break;
        }
    }
    output = malloc(strlen(text));
    strncpy(output, text, i);
    // printf("text: %s\n", text);
    // printf("# output: %s\n", output);
    // printf("# size: %d", strlen(output));
    // printf("# text size: %d", strlen(text));
    return output;
}

char *doNEG(char *op) {
    if (!strcmp(op, "beq")) {
        return "bne";
    }
    else if (!strcmp(op, "bne")) {
        return "beq";
    }
    else if (!strcmp(op, "bgt")) {
        return "ble";
    }
    else if (!strcmp(op, "bge")) {
        return "blt";
    }
    else if (!strcmp(op, "blt")) {
        return "bge";
    }
    else if (!strcmp(op, "ble")) {
        return "bgt";
    }
    else {
        return combineStr("input: ", op);
    }
}

int countLines(char *text) {
    int i, lines = 0;
    for (i = 0; i < strlen(text); i++) {
        char tmp = *(text + i);
        if (tmp == '\n') {
            lines++;
        }
    }
    return lines;
}

char *substr(char *dest, char *src, int start, int cnt) {
    strncpy(dest, src + start, cnt);
    dest[cnt] = 0;
    return dest;
}

char *insertInstr(char *text, char *mid, int addr, int isAnd) {
    char *output = (char*)malloc(strlen(text) + strlen(mid));
    strncpy(output, text, addr);
    output[addr] = '\0';
    if (isAnd == 0)
        output = deleteLine(output);
    combineStr(output, "\0");
    strcat(output, mid);
    strcat(output, text + addr);
    return output;
}