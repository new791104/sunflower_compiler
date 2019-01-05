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
extern char *deleteLine(char *text, int addr);
extern char *formatLabel(char *label);
extern char *doNEG(char*);
extern int countLines(char *text);
extern char *substr(char *dest, char *src, int start, int cnt);
extern char *insertInstr(char *text, char *mid, int addr);
extern char *findLastLine(char *text);
extern int findLastLineAddr(char *text);

char *data = "\t.data";
char *text = "\n\t.text\nmain:";
%}

%token IDENTIFIER INTCONST INITIAL SPACE OTHERS
%token ADD SUB MUL DIV MOD GIVE EQUAL NEQUAL GREATER GEQUAL SMALLER SEQUAL LEFTBRACKET RIGHTBRACKET 
%token AND BEGIN_ DO ELSE END ENDIF ENDWHILE EXIT IF SET NOT OR PROGRAM READ THEN VAR WHILE WRITE
%start program

%type <stmt> program declarations statements statement INTCONST IDENTIFIER
%type <stmt> arithmeticExpression arithmeticTerm arithmeticFactor primaryExpression
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
        free(data);
        free(text);
        free(finish);
    };

declarations: 
    declarations VAR IDENTIFIER { 
        printf("declarations -> declarations Var Identifier\n");
        char *result = "\n";
        result = combineStr(result, $3.var_label);
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
        char result[40], *rd = $4.reg, *rs = getReg(), *var_label = $2.var_label;
        snprintf(result, sizeof(result), "\nla %s, %s", rs, var_label);
        snprintf(result, sizeof(result), "%s\nsw %s, 0(%s)", result, rd, rs);
        text = combineStr(text, result);
        putReg(rs);
        putReg(rd);
    }
    | IF booleanExpression THEN statements ENDIF { 
        printf("statement -> If booleanExpression Then statements EndIf\n");
        // text = combineStr(text, "\n### statement -> If booleanExpression Then statements EndIf");
        // char result[20];
        // snprintf(result, sizeof(result), "%s", $2.label_else);
        if (!$2.isAnd) {
            // Or
            int last_addr = $2.last_addr;
            char *label_stmt_2 = $2.label_stmt;
            char *mid = findLastLine(label_stmt_2);
            printf("##### mid: %s\n", mid);
            text = insertInstr(text, mid, last_addr);
        }
        // add $2.label_else:
        text = combineStr(text, $2.label_else);
    }
    | IF booleanExpression THEN statements ELSE statements ENDIF { 
        printf("statement -> If booleanExpression Then statements Else statements EndIf\n"); 
        if (!$2.isAnd) {
            // Or
            int last_addr = $2.last_addr;
            char *label_stmt_2 = $2.label_stmt;
            char *mid = findLastLine(label_stmt_2);
            printf("##### mid: %s\n", mid);
            text = insertInstr(text, mid, last_addr);
        }
        // insert "\nb Lnext\n$2.label_else"
        // add Lnext:
    }
    | WHILE booleanExpression DO statements ENDWHILE { printf("statement -> While booleanExpression Do statements EndWhile\n"); }
    | READ IDENTIFIER { printf("statement -> Read Identifier\n"); }
    | WRITE arithmeticExpression { printf("statement -> Write arithmeticExpression\n"); }
    | EXIT { printf("statement -> Exit\n"); }
    ;
booleanExpression: 
    booleanExpression OR booleanTerm { 
        printf("booleanExpression -> booleanExpression Or booleanTerm\n");
        // text = combineStr(text, "\n### booleanExpression -> booleanExpression Or booleanTerm");
        char *label_else_1 = $1.label_else;
        if ($1.isAnd) {
            char *text_tmp = text;
            int last_line_size = strlen(findLastLine(text_tmp));
            printf("######### last_line_size: %d\n", last_line_size);
            text = deleteLine(text_tmp, $1.last_addr);
            text = insertInstr(text, label_else_1, $1.last_addr - last_line_size + 1);
            label_else_1 = "\0";
        }
        text = combineStr(text, $1.label_stmt);

        $$.last_addr = strlen(text);
        $$.label_else = combineStr(formatLabel(label_else_1), formatLabel($3.label_else));
        $$.label_stmt = combineStr(formatLabel($1.label_stmt), formatLabel($3.label_stmt));
        $$.isAnd = 0;
    }
    | booleanTerm { 
        printf("booleanExpression -> booleanTerm\n");
        // text = combineStr(text, "\n### booleanExpression -> booleanTerm");
        if ($1.isAnd == 1) {
            printf("# $1.isAnd addr: %d\n", $1.last_addr);
            // insert
            char *mid = $1.label_stmt;
            // char *hint = combineStr(mid, "\nbooleanTerm insert HERE HAHA!!!");
            int last_addr = $1.last_addr;
            text = insertInstr(text, mid, last_addr);

            $$.last_addr = strlen(text);
        }
        else if ($1.isAnd == 0) {
            text = combineStr(text, $1.label_else);
            // $1.label_else = deleteLine($1.label_else, strlen($1.label_else));
            $$.label_else = "\0";
            $$.last_addr = strlen(text);
            // text = combineStr(text, "\n### booleanTerm");
        }
        else {
            text = combineStr(text, formatLabel($1.label_stmt));
            $$.label_stmt = formatLabel($1.label_stmt);
            $$.label_else = formatLabel($1.label_else);
            $$.last_addr = strlen(text);
        }
    }
    ;
booleanTerm: 
    booleanTerm AND booleanFactor {
        printf("booleanTerm -> booleanTerm And booleanFactor\n");
        // text = combineStr(text, "\n### booleanTerm -> booleanTerm And booleanFactor");
        char result[20], *mid = $1.label_stmt;
        int last_addr = $1.last_addr;
        // insert
        text = insertInstr(text, mid, last_addr);
        // snprintf(result, sizeof(result), "\nb %s%s", $3.label_else, formatLabel($3.label_stmt));
        snprintf(result, sizeof(result), "\nb %s", $3.label_else);
        text = combineStr(text, result);
        
        $$.last_addr = strlen(text);
        $$.label_else = combineStr($1.label_else, formatLabel($3.label_else));
        $$.label_stmt = formatLabel($3.label_stmt);
        $$.isAnd = 1;
    }
    | booleanFactor {
        printf("booleanTerm -> booleanFactor\n");
        // text = combineStr(text, "\n### booleanTerm -> booleanFactor");
        char result[20], *label_else = $1.label_else, *label_stmt = $1.label_stmt;
        snprintf(result, sizeof(result), "\nb %s", label_else);
        text = combineStr(text, result);
        $$.last_addr = strlen(text);
        printf("# $$.last_addr: %d\n", $$.last_addr);
        $$.label_else = formatLabel(label_else);
        $$.label_stmt = formatLabel(label_stmt);
        $$.isAnd = -1;
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
        // text = combineStr(text, "\n### booleanFactor -> relationExpression");
        $$.label_else = $1.label_else;
        $$.label_stmt = $1.label_stmt;
    }
    ;
relationExpression: 
    arithmeticExpression EQUAL arithmeticExpression { 
        printf("relationExpression -> arithmeticExpression == arithmeticExpression\n");
        // text = combineStr(text, "\n### ==");
        char result[20], *rs = $1.reg, *rt = $3.reg, *label_else = newLabel(), *label_stmt = newLabel();
        text = makeBranchInstr(text, "beq", rs, rt, label_stmt);
        putReg(rt);
        putReg(rs);
        $$.label_else = label_else;
        $$.label_stmt = label_stmt;
    }
    | arithmeticExpression NEQUAL arithmeticExpression { 
        printf("relationExpression -> arithmeticExpression <> arithmeticExpression\n");
        // text = combineStr(text, "\n### <>"); 
        char result[20], *rs = $1.reg, *rt = $3.reg, *label_else = newLabel(), *label_stmt = newLabel();
        text = makeBranchInstr(text, "bne", rs, rt, label_stmt);
        putReg(rt);
        putReg(rs);
        $$.label_else = label_else;
        $$.label_stmt = label_stmt;
    }
    | arithmeticExpression GREATER arithmeticExpression { 
        printf("relationExpression -> arithmeticExpression > arithmeticExpression\n");
        // text = combineStr(text, "\n### >"); 
        char result[20], *rs = $1.reg, *rt = $3.reg, *label_else = newLabel(), *label_stmt = newLabel();
        text = makeBranchInstr(text, "bgt", rs, rt, label_stmt);
        putReg(rt);
        putReg(rs);
        $$.label_else = label_else;
        $$.label_stmt = label_stmt;
    }
    | arithmeticExpression GEQUAL arithmeticExpression { 
        printf("relationExpression -> arithmeticExpression >= arithmeticExpression\n"); 
        // text = combineStr(text, "\n### >="); 
        char result[20], *rs = $1.reg, *rt = $3.reg, *label_else = newLabel(), *label_stmt = newLabel();
        text = makeBranchInstr(text, "bge", rs, rt, label_stmt);
        putReg(rt);
        putReg(rs);
        $$.label_else = label_else;
        $$.label_stmt = label_stmt;
    }
    | arithmeticExpression SMALLER arithmeticExpression { 
        printf("relationExpression -> arithmeticExpression < arithmeticExpression\n");
        // text = combineStr(text, "\n### <");
        char result[20], *rs = $1.reg, *rt = $3.reg, *label_else = newLabel(), *label_stmt = newLabel();
        text = makeBranchInstr(text, "blt", rs, rt, label_stmt);
        putReg(rt);
        putReg(rs);
        $$.label_else = label_else;
        $$.label_stmt = label_stmt;
    }
    | arithmeticExpression SEQUAL arithmeticExpression { 
        printf("relationExpression -> arithmeticExpression <= arithmeticExpression\n");
        // text = combineStr(text, "\n### <=");
        char result[20], *rs = $1.reg, *rt = $3.reg, *label_else = newLabel(), *label_stmt = newLabel();
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
        text = makeAluInstr(text, "add", $1.reg, $3.reg, $1.reg);
        putReg($3.reg);
        $$ = $1;
    }
    | arithmeticExpression SUB arithmeticTerm { 
        printf("arithmeticExpression -> arithmeticExpression - arithmeticTerm\n");
        text = makeAluInstr(text, "sub", $1.reg, $3.reg, $1.reg);
        putReg($3.reg);
        $$.reg = $1.reg;
    }
    | arithmeticTerm { 
        printf("arithmeticExpression -> arithmeticTerm\n");
        $$.reg = $1.reg;
    }
    ;
arithmeticTerm: 
    arithmeticTerm MUL arithmeticFactor { 
        printf("arithmeticTerm -> arithmeticTerm * arithmeticFactor\n");
        text = makeAluInstr(text, "mul", $1.reg, $3.reg, $1.reg);
        putReg($3.reg);
        $$.reg = $1.reg;
    }
    | arithmeticTerm DIV arithmeticFactor { 
        printf("arithmeticTerm -> arithmeticTerm / arithmeticFactor\n"); 
        text = makeAluInstr(text, "div", $1.reg, $3.reg, $1.reg);
        putReg($3.reg);
        $$.reg = $1.reg;
    }
    | arithmeticTerm MOD arithmeticFactor { 
        printf("arithmeticTerm -> arithmeticTerm % arithmeticFactor\n"); 
        text = makeAluInstr(text, "rem", $1.reg, $3.reg, $1.reg);
        putReg($3.reg);
        $$.reg = $1.reg;
    }
    | arithmeticFactor { 
        printf("arithmeticTerm -> arithmeticFactor\n");
        $$.reg = $1.reg;
    }
    ;
arithmeticFactor: 
    SUB arithmeticFactor { 
        printf("arithmeticFactor -> arithmeticFactor\n");
        char result[20], *rd = $2.reg, *rs = $2.reg;
        snprintf(result, sizeof(result), "\nneg %s, %s", rd, rs);
        text = combineStr(text, result);
        $$.reg = $2.reg;
    }
    | primaryExpression { 
        printf("arithmeticFactor -> primaryExpression\n");
        $$.reg = $1.reg;
    }
    ;
primaryExpression: 
    INTCONST { 
        printf("primaryExpression -> IntConst\n");
        char result[20], *reg = getReg(), *intconst = $1.reg;
        snprintf(result, sizeof(result), "\nli %s, %s", reg, intconst);
        text = combineStr(text, result);
        $$.reg = reg;
    }
    | IDENTIFIER { 
        printf("primaryExpression -> Identifier\n");
        char *reg = getReg();
        text = makeIdentifierInstr(text, reg, $1.var_label);
        $$.reg = reg;
    }
    | LEFTBRACKET arithmeticExpression RIGHTBRACKET { 
        printf("primaryExpression -> arithmeticExpression\n");
        $$.reg = $2.reg;
    }
    ;
%%

