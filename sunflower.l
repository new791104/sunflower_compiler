%{
/*
*   sunflower 詞彙分析
*/
#include <stdio.h>
#include "sunflower.tab.h"
#include <string.h>
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
// char *doNEG(char*);

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
    putReg(rt);
    return text;
}

char *makeBranchInstr(char *text, char *op, char *rs, char *rt, char *label) {
    char result[20];
    snprintf(result, sizeof(result), "\n%s %s, %s, %s", op, rs, rt, label);
    text = combineStr(text, result);
    putReg(rs);
    putReg(rt);
    return text;
}

char *makeIdentifierInstr(char *text, char *reg, char *label) {
    char result[40];
    snprintf(result, sizeof(result), "\nla %s, %s", reg, label);
    snprintf(result, sizeof(result), "%s\nlw %s, 0(%s)", result, reg, reg);
    text = combineStr(text, result);
    return text;
}

char *newLabel() {
    char *result = malloc(integer_length(LABEL_COUNTER) + 1);
    snprintf(result, sizeof(result), "L%d", LABEL_COUNTER);
    LABEL_COUNTER++;
    return result;
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

char *makebooleanTermInstr(char *text, branch_type branch) { 
    char result[20], *label = newLabel(), label_format[10];
    snprintf(result, sizeof(result), "\n%s %s, $zero, %s", branch.op, branch.reg, label);
    text = combineStr(text, result);
    putReg(branch.reg);
    snprintf(label_format, sizeof(label_format), "\n%s:", label);
    return combineStr(branch.label_array, label_format);
}

// char *doNEG(char *op) {
//     printf("#### doNEG ####\ninput: %s\n", op);
//     printf("size: %d\n", strlen(op));
//     if (*op == "beq") {
//         return "bne";
//     }
//     else if (*op == "bne") {
//         return "beq";
//     }
//     else if (*op == "bgt") {
//         return "ble";
//     }
//     else if (*op == "bge") {
//         return "blt";
//     }
//     else if (*op == "blt") {
//         return "bge";
//     }
//     else if (*op == "ble") {
//         return "bgt";
//     }
//     else {
//         return combineStr("input: ", op);
//     }
// }