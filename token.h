#include <iostream>
#include <ctype.h>//Funções de caracteres
#include <cstring>
#include <string>

using namespace std;

enum Names{
    UNDEF,//0
    ID,//1
    IF,//2
    ELSE,//3
    THEN,//4
    OP,//5
    EQ,// = 6
    NE,//7
    GT,//8
    GE,//9
    LT,//10
    LE,//11
    NUMBER,//12
    INTEGER_LITERAL,//13
    ADD,//+ 14
    SUB,// - 15
    MUL,// * 16
    DIV,// / 17
    MOD,// % 18
    ATT,// == 19
    STRING_LITERAL,//20
    SEP,//21
    LP,//22 (
    RP,//23 )
    SBL,//24 [
    SBR,//25 ]
    LK,//26 {
    RK,//27 }
    SC,// ; 28
    DOT,// . 29
    COM,// , 30
    CLASS, // 31
    EXTENDS, // 32
    INT, // 33
    STRING, // 34
    BREAK, // 35
    PRINT, // 36
    READ, // 37
    RETURN, // 38
    SUPER,// 39
    FOR,// 40
    NEW, // 41
    CONSTRUCTOR,// 42
    RelOp,//43
    END_OF_FILE//44
};

class Token 
{
    public: 
        int name;
        int attribute;
        string* lexeme;
    
        Token(int name)
        {
            this->name = name;
            attribute = UNDEF;
        }
        
        Token(int name, int attr)
        {
            this->name = name;
            attribute = attr;
        }
};