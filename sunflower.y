%{
/*
*   sunflower 語法分析
*/
#include <stdio.h>
#include <string.h>
#include "sunflower.tab.h"

extern int yylex();
extern FILE *yyin;
extern FILE *yyout;
extern char *exception_array;
extern char *combineStr(char*, char*);
extern char *getReg();
extern void putReg(char*);
extern char *makeAluInstr(char*, char*, char*, char*, char*);
extern char *makeIdentifierInstr(char*, char*, char*);
extern char *makeBranchInstr(char*, char*, char*, char*, char*);
extern char *newLabel();
extern char *makebooleanTermInstr(char *text, branch_type branch);
extern char *deleteLine(char *text);
extern char *formatLabel(char *label);
extern char *doNEG(char*);
extern int countLines(char *text);
extern char *substr(char *dest, char *src, int start, int cnt);
extern char *insertInstr(char *text, char *mid, int addr, int isAnd);

char *data = "    .data";
char *text = "\n    .text\nmain:";
%}

%token IDENTIFIER INTCONST INITIAL SPACE OTHERS
%token ADD SUB MUL DIV MOD GIVE EQUAL NEQUAL GREATER GEQUAL SMALLER SEQUAL LEFTBRACKET RIGHTBRACKET 
%token AND BEGIN_ DO ELSE END ENDIF ENDWHILE EXIT IF SET NOT OR PROGRAM READ THEN VAR WHILE WRITE
%start program

%type <str> program declarations statements statement INTCONST IDENTIFIER
%type <str> arithmeticExpression arithmeticTerm arithmeticFactor primaryExpression
%type <branch> booleanExpression booleanTerm booleanFactor relationExpression
%%

program: 
    PROGRAM IDENTIFIER BEGIN_ declarations statements END { 
        char *finish = "\nli $v0, 10\nsyscall";
        printf("program -> Program Identifier Begin declarations statements End\n");
        printf("\nLexical errors: \n%s", exception_array);    
        fwrite(data, 1, strlen(data), yyout);
        fwrite(text, 1, strlen(text), yyout);
        fwrite(finish, 1, strlen(finish), yyout);
    };

declarations: 
    declarations VAR IDENTIFIER { 
        printf("declarations -> declarations Var Identifier\n");
        char *result = "\n";
        result = combineStr(result, $3);
        result = combineStr(result, ":\n\t.word 0");
        data = combineStr(data, result);
    }
    | /* empty */ { printf("declarations -> empty\n"); }
    ;
statements: 
    statements statement { printf("statements -> statements statement\n"); }
    | /* empty */  { printf("statements -> empty\n"); }
    ;
statement: 
    SET IDENTIFIER GIVE arithmeticExpression { 
        printf("statement -> Set Identifier = arithmeticExpression\n");
        char result[40], *rd = $4, *rs = getReg(), *var_label = $2;
        snprintf(result, sizeof(result), "\nla %s, %s", rs, var_label);
        snprintf(result, sizeof(result), "%s\nsw %s, 0(%s)", result, rd, rs);
        text = combineStr(text, result);
        putReg(rs);
        putReg(rd);
    }
    | IF booleanExpression THEN statements ENDIF { 
        printf("statement -> If booleanExpression Then statements EndIf\n");
        // char result[20];
        // snprintf(result, sizeof(result), "%s", $2.label_else);
        if ($2.isAnd) {
            // And
        }
        else {
            // Or
            int last_addr = $2.last_addr, org_length = strlen(text);
            char *front = malloc(last_addr + 1), *mid = $2.label_stmt, *behind = malloc(org_length - last_addr + 1);
            text = insertInstr(text, mid, last_addr, 0);
            // text = combineStr(text, behind);
            // printf("######\n\nfront: %s\n\nmid: %s\n\nbehind: %s\n######\n", front, mid, behind);
        }
        text = combineStr(text, $2.label_else);
    }
    | IF booleanExpression THEN statements ELSE statements ENDIF { 
        printf("statement -> If booleanExpression Then statements Else statements EndIf\n"); 
    }
    | WHILE booleanExpression DO statements ENDWHILE { printf("statement -> While booleanExpression Do statements EndWhile\n"); }
    | READ IDENTIFIER { printf("statement -> Read Identifier\n"); }
    | WRITE arithmeticExpression { printf("statement -> Write arithmeticExpression\n"); }
    | EXIT { printf("statement -> Exit\n"); }
    ;
booleanExpression: 
    booleanExpression OR booleanTerm { 
        printf("booleanExpression -> booleanExpression Or booleanTerm\n");
        text = combineStr(text, $3.label_else);
        $$.last_addr = strlen(text);
        $$.label_else = $3.label_else;
        $$.label_stmt = combineStr($1.label_stmt, $3.label_stmt);
    }
    | booleanTerm { 
        printf("booleanExpression -> booleanTerm\n");
        if ($1.isAnd) {
            // insert
            
            char *mid = formatLabel($1.label_stmt);
            int last_addr = $1.last_addr;
            text = insertInstr(text, mid, last_addr, 1);
            $$.last_addr = strlen(text);
        }
        else {
            text = combineStr(text, $1.label_else);
            // text = combineStr(text, "\n### booleanTerm");
        }
    }
    ;
booleanTerm: 
    booleanTerm AND booleanFactor {
        printf("booleanTerm -> booleanTerm And booleanFactor\n");
        char result[20], *mid = $1.label_stmt;
        int last_addr = $1.last_addr;
        // insert
        text = insertInstr(text, mid, last_addr, 1);
        snprintf(result, sizeof(result), "\nb %s", $3.label_else);
        text = combineStr(text, result);
        
        $$.last_addr = strlen(text);
        $$.label_else = combineStr($1.label_else, formatLabel($3.label_else));
        $$.label_stmt = $3.label_stmt;
        $$.isAnd = 1;
    }
    | booleanFactor { // 第一個條件
        printf("booleanTerm -> booleanFactor\n");
        char result[20], *label_else = $1.label_else, *label_stmt = $1.label_stmt;
        snprintf(result, sizeof(result), "\nb %s", label_else);
        text = combineStr(text, result);
        $$.last_addr = strlen(text);
        $$.label_else = formatLabel(label_else);
        $$.label_stmt = formatLabel(label_stmt);
        $$.isAnd = 0;
    }
    ;
booleanFactor: 
    NOT booleanFactor { 
        printf("booleanFactor -> Not booleanFactor\n");
        $$.label_else = $2.label_stmt;
        $$.label_stmt = $2.label_else;
    }
    | relationExpression { 
        printf("booleanFactor -> relationExpression\n");
        $$.label_else = $1.label_else;
        $$.label_stmt = $1.label_stmt;
    }
    ;
relationExpression: 
    arithmeticExpression EQUAL arithmeticExpression { 
        printf("relationExpression -> arithmeticExpression == arithmeticExpression\n");
        char result[20], *rs = $1, *rt = $3, *label_else = newLabel(), *label_stmt = newLabel();
        text = makeBranchInstr(text, "beq", rs, rt, label_stmt);
        putReg(rt);
        putReg(rs);
        $$.label_else = label_else;
        $$.label_stmt = label_stmt;
    }
    | arithmeticExpression NEQUAL arithmeticExpression { 
        printf("relationExpression -> arithmeticExpression <> arithmeticExpression\n"); 
        char result[20], *rs = $1, *rt = $3, *label_else = newLabel(), *label_stmt = newLabel();
        text = makeBranchInstr(text, "bne", rs, rt, label_stmt);
        putReg(rt);
        putReg(rs);
        $$.label_else = label_else;
        $$.label_stmt = label_stmt;
    }
    | arithmeticExpression GREATER arithmeticExpression { 
        printf("relationExpression -> arithmeticExpression > arithmeticExpression\n");
        char result[20], *rs = $1, *rt = $3, *label_else = newLabel(), *label_stmt = newLabel();
        text = makeBranchInstr(text, "bgt", rs, rt, label_stmt);
        putReg(rt);
        putReg(rs);
        $$.label_else = label_else;
        $$.label_stmt = label_stmt;
    }
    | arithmeticExpression GEQUAL arithmeticExpression { 
        printf("relationExpression -> arithmeticExpression >= arithmeticExpression\n"); 
        char result[20], *rs = $1, *rt = $3, *label_else = newLabel(), *label_stmt = newLabel();
        text = makeBranchInstr(text, "bge", rs, rt, label_stmt);
        putReg(rt);
        putReg(rs);
        $$.label_else = label_else;
        $$.label_stmt = label_stmt;
    }
    | arithmeticExpression SMALLER arithmeticExpression { 
        printf("relationExpression -> arithmeticExpression < arithmeticExpression\n");
        char result[20], *rs = $1, *rt = $3, *label_else = newLabel(), *label_stmt = newLabel();
        text = makeBranchInstr(text, "blt", rs, rt, label_stmt);
        putReg(rt);
        putReg(rs);
        $$.label_else = label_else;
        $$.label_stmt = label_stmt;
    }
    | arithmeticExpression SEQUAL arithmeticExpression { 
        printf("relationExpression -> arithmeticExpression <= arithmeticExpression\n");
        char result[20], *rs = $1, *rt = $3, *label_else = newLabel(), *label_stmt = newLabel();
        text = makeBranchInstr(text, "ble", rs, rt, label_stmt);
        putReg(rt);
        putReg(rs);
        $$.label_else = label_else;
        $$.label_stmt = label_stmt;
    }
    ;
arithmeticExpression: 
    arithmeticExpression ADD arithmeticTerm { 
        printf("arithmeticExpression -> arithmeticExpression + arithmeticTerm\n"); 
        text = makeAluInstr(text, "add", $1, $3, $1);
        putReg($3);
        $$ = $1;
    }
    | arithmeticExpression SUB arithmeticTerm { 
        printf("arithmeticExpression -> arithmeticExpression - arithmeticTerm\n");
        text = makeAluInstr(text, "sub", $1, $3, $1);
        putReg($3);
        $$ = $1;
    }
    | arithmeticTerm { 
        printf("arithmeticExpression -> arithmeticTerm\n");
        $$ = $1;
    }
    ;
arithmeticTerm: 
    arithmeticTerm MUL arithmeticFactor { 
        printf("arithmeticTerm -> arithmeticTerm * arithmeticFactor\n");
        text = makeAluInstr(text, "mul", $1, $3, $1);
        putReg($3);
        $$ = $1;
    }
    | arithmeticTerm DIV arithmeticFactor { 
        printf("arithmeticTerm -> arithmeticTerm / arithmeticFactor\n"); 
        text = makeAluInstr(text, "div", $1, $3, $1);
        putReg($3);
        $$ = $1;
    }
    | arithmeticTerm MOD arithmeticFactor { 
        printf("arithmeticTerm -> arithmeticTerm % arithmeticFactor\n"); 
        text = makeAluInstr(text, "rem", $1, $3, $1);
        putReg($3);
        $$ = $1;
    }
    | arithmeticFactor { 
        printf("arithmeticTerm -> arithmeticFactor\n");
        $$ = $1;
    }
    ;
arithmeticFactor: 
    SUB arithmeticFactor { 
        printf("arithmeticFactor -> arithmeticFactor\n");
        char result[20], *rd = $2, *rs = $2;
        snprintf(result, sizeof(result), "\nneg %s, %s", rd, rs);
        text = combineStr(text, result);
        $$ = $2;
    }
    | primaryExpression { 
        printf("arithmeticFactor -> primaryExpression\n");
        $$ = $1;
    }
    ;
primaryExpression: 
    INTCONST { 
        printf("primaryExpression -> IntConst\n");
        char result[20], *reg = getReg(), *intconst = $1;
        snprintf(result, sizeof(result), "\nli %s, %s", reg, intconst);
        text = combineStr(text, result);
        $$ = reg;
    }
    | IDENTIFIER { 
        printf("primaryExpression -> Identifier\n");
        char *reg = getReg();
        text = makeIdentifierInstr(text, reg, $1);
        $$ = reg;
    }
    | LEFTBRACKET arithmeticExpression RIGHTBRACKET { 
        printf("primaryExpression -> arithmeticExpression\n");
        $$ = $2;
    }
    ;
%%

