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
// extern char *doNEG(char*);

char *data = "    .data";
char *text = "\n    .text\nmain:";
%}

%token IDENTIFIER INTCONST INITIAL SPACE OTHERS
%token ADD SUB MUL DIV MOD GIVE EQUAL NEQUAL GREATER GEQUAL SMALLER SEQUAL LEFTBRACKET RIGHTBRACKET 
%token AND BEGIN_ DO ELSE END ENDIF ENDWHILE EXIT IF SET NOT OR PROGRAM READ THEN VAR WHILE WRITE
%start program

%type <str> IDENTIFIER program declarations statements statement
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
        result = combineStr(result, yylval.str);
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
        char result[20];
        snprintf(result, sizeof(result), "%s", $2.label_array);
        text = combineStr(text, result);
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
    }
    | booleanTerm { 
        printf("booleanExpression -> booleanTerm\n"); 
        // char result[20], *label = newLabel(), label_format[10];
        // snprintf(result, sizeof(result), "\n%s %s, $zero, %s", $1.op, $1.reg, label);
        // text = combineStr(text, result);
        // putReg($1.reg);
        // snprintf(label_format, sizeof(label_format), "\n%s:", label);
        // $$.label_array = combineStr($1.label_array, label_format);
    }
    ;
booleanTerm: 
    booleanTerm AND booleanFactor { 
        printf("booleanTerm -> booleanTerm And booleanFactor\n");
        char result[20], *label = newLabel(), label_format[10];
        snprintf(result, sizeof(result), "\n%s %s, $zero, %s", $3.op, $3.reg, label);
        text = combineStr(text, result);
        putReg($1.reg);
        snprintf(label_format, sizeof(label_format), "\n%s:", label);
        $$.label_array = combineStr($1.label_array, label_format);
    }
    | booleanFactor { // 第一個條件
        printf("booleanTerm -> booleanFactor\n"); 
        // $$.op = $1.op;
        // $$.reg = $1.reg;
        // $$.label_array = "";

        char result[20], *label = newLabel(), label_format[10];
        snprintf(result, sizeof(result), "\n%s %s, $zero, %s", $1.op, $1.reg, label);
        text = combineStr(text, result);
        putReg($1.reg);
        snprintf(label_format, sizeof(label_format), "\n%s:", label);
        $$.label_array = combineStr($1.label_array, label_format);
    }
    ;
booleanFactor: 
    NOT booleanFactor { 
        printf("booleanFactor -> Not booleanFactor\n");
        // $$.op = doNEG($2.op);
        if ($2.op == "beq") {
            $$.op =  "bne";
        }
        else if ($2.op == "bne") {
            $$.op = "beq";
        }
        else if ($2.op == "bgt") {
            $$.op = "ble";
        }
        else if ($2.op == "bge") {
            $$.op = "blt";
        }
        else if ($2.op == "blt") {
            $$.op = "bge";
        }
        else if ($2.op == "ble") {
            $$.op = "bgt";
        }
        else {
            $$.op = combineStr("input: ", $2.op);
        }
        $$.reg = $2.reg;
        $$.label_array = "";
    }
    | relationExpression { 
        printf("booleanFactor -> relationExpression\n");
        $$.op = $1.op;
        $$.reg = $1.reg;
        $$.label_array = "";
    }
    ;
relationExpression: 
    arithmeticExpression EQUAL arithmeticExpression { 
        printf("relationExpression -> arithmeticExpression == arithmeticExpression\n");
        char result[20], *rs = $1, *rt = $3;
        snprintf(result, sizeof(result), "\nsub %s, %s, %s", rs, rs, rt);
        text = combineStr(text, result);
        putReg(rt);
        $$.op = "bne";
        $$.reg = rs;
    }
    | arithmeticExpression NEQUAL arithmeticExpression { 
        printf("relationExpression -> arithmeticExpression <> arithmeticExpression\n"); 
        char result[20], *rs = $1, *rt = $3;
        snprintf(result, sizeof(result), "\nsub %s, %s, %s", rs, rs, rt);
        text = combineStr(text, result);
        putReg(rt);
        $$.op = "beq";
        $$.reg = rs;
    }
    | arithmeticExpression GREATER arithmeticExpression { 
        printf("relationExpression -> arithmeticExpression > arithmeticExpression\n");
        char result[20], *rs = $1, *rt = $3;
        snprintf(result, sizeof(result), "\nsub %s, %s, %s", rs, rs, rt);
        text = combineStr(text, result);
        putReg(rt);
        $$.op = "ble";
        $$.reg = rs;
    }
    | arithmeticExpression GEQUAL arithmeticExpression { 
        printf("relationExpression -> arithmeticExpression >= arithmeticExpression\n"); 
        char result[20], *rs = $1, *rt = $3;
        snprintf(result, sizeof(result), "\nsub %s, %s, %s", rs, rs, rt);
        text = combineStr(text, result);
        putReg(rt);
        $$.op = "blt";
        $$.reg = rs;
    }
    | arithmeticExpression SMALLER arithmeticExpression { 
        printf("relationExpression -> arithmeticExpression < arithmeticExpression\n");
        char result[20], *rs = $1, *rt = $3;
        snprintf(result, sizeof(result), "\nsub %s, %s, %s", rs, rs, rt);
        text = combineStr(text, result);
        putReg(rt);
        $$.op = "bge";
        $$.reg = rs;
    }
    | arithmeticExpression SEQUAL arithmeticExpression { 
        printf("relationExpression -> arithmeticExpression <= arithmeticExpression\n");
        char result[20], *rs = $1, *rt = $3;
        snprintf(result, sizeof(result), "\nsub %s, %s, %s", rs, rs, rt);
        text = combineStr(text, result);
        putReg(rt);
        $$.op = "bgt";
        $$.reg = rs;
    }
    ;
arithmeticExpression: 
    arithmeticExpression ADD arithmeticTerm { 
        printf("arithmeticExpression -> arithmeticExpression + arithmeticTerm\n"); 
        text = makeAluInstr(text, "add", $1, $3, $1);
        $$ = $1;
    }
    | arithmeticExpression SUB arithmeticTerm { 
        printf("arithmeticExpression -> arithmeticExpression - arithmeticTerm\n");
        text = makeAluInstr(text, "sub", $1, $3, $1);
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
        $$ = $1;
    }
    | arithmeticTerm DIV arithmeticFactor { 
        printf("arithmeticTerm -> arithmeticTerm / arithmeticFactor\n"); 
        text = makeAluInstr(text, "div", $1, $3, $1);
        $$ = $1;
    }
    | arithmeticTerm MOD arithmeticFactor { 
        printf("arithmeticTerm -> arithmeticTerm % arithmeticFactor\n"); 
        text = makeAluInstr(text, "rem", $1, $3, $1);
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
        char result[20], *reg = getReg(), *intconst = yylval.str;
        snprintf(result, sizeof(result), "\nli %s, %s", reg, intconst);
        text = combineStr(text, result);
        $$ = reg;
    }
    | IDENTIFIER { 
        printf("primaryExpression -> Identifier\n");
        char *reg = getReg();
        text = makeIdentifierInstr(text, reg, yylval.str);
        $$ = reg;
    }
    | LEFTBRACKET arithmeticExpression RIGHTBRACKET { 
        printf("primaryExpression -> arithmeticExpression\n");
        $$ = $2;
    }
    ;
%%

