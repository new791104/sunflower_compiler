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
extern char *makeBranchInstr(char *text, char *op, char *rs, char *rt, char *label_stmt, char *label_else);
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
extern void debugMode(char* text, int flag);

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
        char *finish = "\n\tli $v0, 10\n\tsyscall";
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
        result = combineStr(result, $3.var_name);
        result = combineStr(result, ":\n\t.word 0");
        data = combineStr(data, result);
    }
    | /* empty */ { printf("declarations -> empty\n"); }
    ;
statements: 
    statements statement { 
        printf("statements -> statements statement\n"); 
        // text = combineStr(text, "\n# STMTS #");
        // debugMode(text, strlen(text));
        $$.last_addr = strlen(text);
    }
    | /* empty */  { 
        printf("statements -> empty\n");
    }
    ;
statement: 
    SET IDENTIFIER GIVE arithmeticExpression { 
        printf("statement -> Set Identifier = arithmeticExpression\n");
        char result[40], *rd = $4.reg, *rs = getReg(), *var_name = $2.var_name;
        snprintf(result, sizeof(result), "\n\tla %s, %s", rs, var_name);
        snprintf(result, sizeof(result), "%s\n\tsw %s, 0(%s)", result, rd, rs);
        text = combineStr(text, result);
        putReg(rs);
        putReg(rd);
    }
    | IF booleanExpression THEN statements ENDIF { 
        printf("statement -> If booleanExpression Then statements EndIf\n");
        if (!$2.isAnd) {
            // insert or_label_stmt
            char *mid = findLastLine($2.label_stmt);
            text = insertInstr(text, mid, $2.last_addr);
        }
        // add $2.label_else:
        text = combineStr(text, $2.label_else);
    }
    | IF booleanExpression THEN statements ELSE statements ENDIF { 
        printf("statement -> If booleanExpression Then statements Else statements EndIf\n"); 
        // 需要修正 Or insert 過後 statements 傳回的插斷點
        int insert_offset = 0;
        if (!$2.isAnd) {
            // insert or_label_stmt
            char *mid = findLastLine($2.label_stmt);
            text = insertInstr(text, mid, $2.last_addr);
            insert_offset = strlen(mid);
        }
        // insert "\nb Lnext\n$2.label_else"
        int stmt_addr = $4.last_addr;
        char result[20], *Lnext = newLabel(), *mid;
        // debugMode("stmt_addr", stmt_addr);
        snprintf(result, sizeof(result), "\n\tb %s%s", Lnext, $2.label_else);
        text = insertInstr(text, result, stmt_addr + insert_offset);
        // add Lnext:
        text = combineStr(text, formatLabel(Lnext));
    }
    | WHILE booleanExpression DO statements ENDWHILE { 
        printf("statement -> While booleanExpression Do statements EndWhile\n");
        if (!$2.isAnd) {
            // insert or_label_stmt
            char *mid = findLastLine($2.label_stmt);
            text = insertInstr(text, mid, $2.last_addr);
        }
        // insert Lbegin
        char *bLabel = newLabel();
        text = insertInstr(text, formatLabel(bLabel), $2.first_addr);
        // add b Lbegin
        char result[20];
        snprintf(result, sizeof(result), "\n\tb %s", bLabel);
        text = combineStr(text, result);
        // add $2.label_else:
        text = combineStr(text, $2.label_else); 
    }
    | READ IDENTIFIER { 
        printf("statement -> Read Identifier\n"); 
        char result[40], *reg = getReg();
        snprintf(result, sizeof(result), "\n\tli $v0, 5\n\tsyscall");
        text = combineStr(text, result);
        snprintf(result, sizeof(result), "\n\tla %s, %s", reg, $2.var_name);
        text = combineStr(text, result);
        snprintf(result, sizeof(result), "\n\tsw $v0, 0(%s)", reg);
        text = combineStr(text, result);
        putReg(reg);
    }
    | WRITE arithmeticExpression { 
        printf("statement -> Write arithmeticExpression\n"); 
        char result[40], *reg = $2.reg;
        snprintf(result, sizeof(result), "\n\tmove $a0, %s", reg);
        text = combineStr(text, result);
        snprintf(result, sizeof(result), "\n\tli $v0, 1\n\tsyscall", reg);
        text = combineStr(text, result);
    }
    | EXIT { 
        printf("statement -> Exit\n"); 
        char *finish = "\n\tli $v0, 10\n\tsyscall";
        text = combineStr(text, finish);
    }
    ;
booleanExpression: 
    booleanExpression OR booleanTerm { 
        printf("booleanExpression -> booleanExpression Or booleanTerm\n");
        $$.first_addr = $1.first_addr;
        // text = combineStr(text, "\n### booleanExpression -> booleanExpression Or booleanTerm");
        char *label_else_1 = $1.label_else;
        if ($1.isAnd) {
            char *text_tmp = text;
            int last_line_size = strlen(findLastLine(text_tmp));
            text = deleteLine(text_tmp, $1.last_addr);
            text = insertInstr(text, label_else_1, $1.last_addr - last_line_size + 2);  // const(2): size of "\n\t"
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
        $$.first_addr = $1.first_addr;
        // text = combineStr(text, "\n### booleanExpression -> booleanTerm");
        if ($1.isAnd == 1) {
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
        
        $$.last_addr = strlen(text);
        $$.label_else = combineStr($1.label_else, formatLabel($3.label_else));
        $$.label_stmt = formatLabel($3.label_stmt);
        $$.isAnd = 1;
        $$.first_addr = $1.first_addr;
    }
    | booleanFactor {
        printf("booleanTerm -> booleanFactor\n");
        $$.last_addr = strlen(text);
        $$.label_else = formatLabel($1.label_else);
        $$.label_stmt = formatLabel($1.label_stmt);
        $$.isAnd = -1;
    }
    ;
booleanFactor: 
    NOT booleanFactor { 
        printf("booleanFactor -> Not booleanFactor\n");
        // text = combineStr(text, "\n### booleanFactor -> Not booleanFactor");
        $$.label_else = $2.label_stmt;
        $$.label_stmt = $2.label_else;
        $$.first_addr = $2.first_addr;
    }
    | relationExpression { 
        printf("booleanFactor -> relationExpression\n");
        // text = combineStr(text, "\n### booleanFactor -> relationExpression");
        $$.label_else = $1.label_else;
        $$.label_stmt = $1.label_stmt;
        $$.first_addr = $1.first_addr;
    }
    ;
relationExpression: 
    arithmeticExpression EQUAL arithmeticExpression { 
        printf("relationExpression -> arithmeticExpression == arithmeticExpression\n");
        $$.first_addr = $1.first_addr;
        // text = combineStr(text, "\n### ==");        
        char result[20], *rs = $1.reg, *rt = $3.reg, *label_else = newLabel(), *label_stmt = newLabel();
        text = makeBranchInstr(text, "beq", rs, rt, label_stmt, label_else);
        putReg(rt);
        putReg(rs);
        $$.label_else = label_else;
        $$.label_stmt = label_stmt;
    }
    | arithmeticExpression NEQUAL arithmeticExpression { 
        printf("relationExpression -> arithmeticExpression <> arithmeticExpression\n");
        $$.first_addr = $1.first_addr;
        // text = combineStr(text, "\n### <>"); 
        char result[20], *rs = $1.reg, *rt = $3.reg, *label_else = newLabel(), *label_stmt = newLabel();
        text = makeBranchInstr(text, "bne", rs, rt, label_stmt, label_else);
        putReg(rt);
        putReg(rs);
        $$.label_else = label_else;
        $$.label_stmt = label_stmt;
    }
    | arithmeticExpression GREATER arithmeticExpression { 
        printf("relationExpression -> arithmeticExpression > arithmeticExpression\n");
        $$.first_addr = $1.first_addr;
        // text = combineStr(text, "\n### >"); 
        char result[20], *rs = $1.reg, *rt = $3.reg, *label_else = newLabel(), *label_stmt = newLabel();
        text = makeBranchInstr(text, "bgt", rs, rt, label_stmt, label_else);
        putReg(rt);
        putReg(rs);
        $$.label_else = label_else;
        $$.label_stmt = label_stmt;
    }
    | arithmeticExpression GEQUAL arithmeticExpression { 
        printf("relationExpression -> arithmeticExpression >= arithmeticExpression\n"); 
        $$.first_addr = $1.first_addr;
        // text = combineStr(text, "\n### >="); 
        char result[20], *rs = $1.reg, *rt = $3.reg, *label_else = newLabel(), *label_stmt = newLabel();
        text = makeBranchInstr(text, "bge", rs, rt, label_stmt, label_else);
        putReg(rt);
        putReg(rs);
        $$.label_else = label_else;
        $$.label_stmt = label_stmt;
    }
    | arithmeticExpression SMALLER arithmeticExpression { 
        printf("relationExpression -> arithmeticExpression < arithmeticExpression\n");
        $$.first_addr = $1.first_addr;
        // text = combineStr(text, "\n### <");
        char result[20], *rs = $1.reg, *rt = $3.reg, *label_else = newLabel(), *label_stmt = newLabel();
        text = makeBranchInstr(text, "blt", rs, rt, label_stmt, label_else);
        putReg(rt);
        putReg(rs);
        $$.label_else = label_else;
        $$.label_stmt = label_stmt;
    }
    | arithmeticExpression SEQUAL arithmeticExpression { 
        printf("relationExpression -> arithmeticExpression <= arithmeticExpression\n");
        $$.first_addr = $1.first_addr;
        // text = combineStr(text, "\n### <=");
        char result[20], *rs = $1.reg, *rt = $3.reg, *label_else = newLabel(), *label_stmt = newLabel();
        text = makeBranchInstr(text, "ble", rs, rt, label_stmt, label_else);
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
        $$.reg = $1.reg;
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
        snprintf(result, sizeof(result), "\n\tneg %s, %s", rd, rs);
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
        $$.first_addr = strlen(text);
        char result[20], *reg = getReg(), *intconst = $1.reg;
        snprintf(result, sizeof(result), "\n\tli %s, %s", reg, intconst);
        text = combineStr(text, result);
        $$.reg = reg;
    }
    | IDENTIFIER { 
        printf("primaryExpression -> Identifier\n");
        $$.first_addr = strlen(text);
        char *reg = getReg();
        text = makeIdentifierInstr(text, reg, $1.var_name);
        $$.reg = reg;
    }
    | LEFTBRACKET arithmeticExpression RIGHTBRACKET { 
        printf("primaryExpression -> arithmeticExpression\n");
        $$.first_addr = strlen(text);
        $$.reg = $2.reg;
    }
    ;
%%

