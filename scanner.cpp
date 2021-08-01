#include "scanner.h" 
#include <fstream>   
#include <string.h>

 //rever

/* 
Palavras reservadas x++:
class, extends, int, string, break, print, read, return, 
super, if, else, for, new, constructor

*/ 
//Construtor
/*
Scanner::Scanner(string input)

{

    pos = 0;

    ifstream inputFile(input, ios::in);
    Token *tok = NULL;

    string line;

    if (inputFile.is_open())

    {

        while (getline(inputFile,line) )

        {

            this->input.append(line + '\n');
            cout << "entrada: " << this->input;
            tok = this->nextToken();
            cout << tok->name << " ";
            cout << endl;

        }

        inputFile.close();

    }

    else 

        cout << "Unable to open file\n"; 

    cout << this->input;

}

    Construtor*/
Scanner::Scanner(string input){
        pos = 0;
        line = 1;

        ifstream inputFile(input, ios::in);
        string line;

        if(inputFile.is_open()){
            
            while(getline(inputFile, line)){
                this->input.append(line + '\n');
            }

            //elimina ultimo \n antes do fim da string
            this->input.pop_back();
            inputFile.close();
        }
        else
            cout << "Arquivo não encontrado!\n";

        /*Caso queira imprimir o conteudo do arquivo lido
        descomente essa parte
        cout << this->input;*/
        
}

Token* Scanner::nextToken(){
    Token* tok ;
   
    if(input[pos] == '\n'){
        line++;
        pos++;

        while(input[pos] == '\n'){
            line++;
            pos++;
        }
   
    }
    //comentário em bloco
    if(input[pos] == '/' && input[pos+1] == '*'){
   
        pos+=2;
       
        while(input[pos+1] != '*' && input[pos+2] != '/'){
            /*printf("(%c) ", input[pos]);*/
            
            if(input[pos] == '\n'){
            /*    printf("linha\n");*/
                line++;
            }

            pos++;
        }
        pos+=3;

        while(input[pos] == '\n'){
            /*printf("linha\n");*/
            line++;
            pos++;
        }
    }
    //comentário em linha
    if(input[pos] == '/' && input[pos+1] == '/'){
        
        
        pos+=2;
       
        while(input[pos] != '\n' && input[pos] != '\0'){
            pos+=1;
        }

        while(input[pos] == '\n'){
            line++;
            pos++;
        }
        
        
    }
    if(isspace(input[pos]) || input[pos] == '\n'){
        
        if(input[pos] == '\n'){
            line++; 
        }
        
        pos++;
        while(isspace(input[pos]) || input[pos] == '\n'){
            if(input[pos] == '\n'){
                line++; 
            }
            pos++;
        }
    }



    //string
    if(input[pos] == '"'){
        pos++;

        /*printf("string\n");*/
        
        while(input[pos] != '"'){

            //caso a string não tenha sido fechada
            if(input[pos] == '\0'){
                ErroLexico("Token nao pertence a linguagem\n");
            }
            pos++;
        }

        pos++;
        /*printf("morri aqui?\n");*/
        tok = new Token(STRING_LITERAL);
        /*printf("morri aqui2?\n");*/


    }
    else if(isalpha(input[pos]) || input[pos] == '_'){
        /*printf("é ID\n");*/
        /* 
        Palavras reservadas x++:
        class, extends, int, string, break, print, read, return, 
        super, if, else, for, new, constructor
        São reconhecidas como ID, mas inseridas como tokens, com o 
        nome e atributo pertencente ao seu próprio tipo
        */ 
        
        if(input.compare(pos, 5, "class") == 0){
            /*printf("É class \n");*/
            pos+=5;
            tok = new Token(CLASS, CLASS);
        }
        else if(input.compare(pos, 7, "extends") == 0){
            /*printf("É extends \n");*/
            pos+=7;
            tok = new Token(EXTENDS, EXTENDS);
        }
        else if(input.compare(pos, 3, "int") == 0){
            /*printf("É int \n");*/
            pos+=3;
            tok = new Token(INT, INT);
        }
        else if(input.compare(pos, 6, "string") == 0){
            /*printf("É string \n");*/
            pos+=6;
            tok = new Token(STRING, STRING);
        }
        else if(input.compare(pos, 5, "break") == 0){
            /*printf("É BREAK \n");*/
            pos+=5;
            tok = new Token(BREAK, BREAK);
        }
        else if(input.compare(pos, 5, "print") == 0){
            /*printf("É print \n");*/
            pos+=5;
            tok = new Token(PRINT, PRINT);
        }
        else if(input.compare(pos, 4, "read") == 0){
            /*printf("É read \n");*/
            pos+=4;
            tok = new Token(READ, READ);
        }
        else if(input.compare(pos, 6, "return") == 0){
            /*printf("É return \n");*/
            pos+=6;
            tok = new Token(RETURN, RETURN);
        }
        else if(input.compare(pos, 5, "super") == 0){
            /*printf("É super \n");*/
            pos+=5;
            tok = new Token(SUPER, SUPER);
        }
        else if(input.compare(pos, 3, "for") == 0){
            /*printf("É for \n");*/
            pos+=3;
            tok = new Token(FOR, FOR);
        }
        else if(input.compare(pos, 2, "if") == 0){
            /*printf("É if \n");*/
            pos+=2;
            tok = new Token(IF, IF);
        }
        else if(input.compare(pos, 4, "else") == 0){
            /*printf("É else \n");*/
            pos+=4;
            tok = new Token(ELSE, ELSE);
        }
        else if(input.compare(pos, 3, "new") == 0){
            /*printf("É NEW \n");*/
            pos+=3;
            tok = new Token(NEW, NEW);
        }
        else if(input.compare(pos, 11, "constructor") == 0){
            /*printf("É constructor \n");*/
            pos+=11;
            tok = new Token(CONSTRUCTOR, CONSTRUCTOR);
        }
        else{

            /*printf("Depois incremento %c\n", input[pos]);*/
            while(isalnum(input[pos]) || input[pos] == '_')
                pos++;
            tok = new Token(ID);
        }
    }
    else if(input[pos] == '\0'){
        tok = new Token(END_OF_FILE);
    }
    else if(input[pos] == '<'){
        pos++;
        if(input[pos] == '='){
            pos++;

            tok = new Token(OP, LE);
        }
        else
            tok = new Token(OP, LT);
    }
    else if(input[pos] == '>'){
        pos++;
        if(input[pos] == '='){
            pos++;

            tok = new Token(OP, GE);
        }
        else
            tok = new Token(OP, GT);
    }

    else if(input[pos] == '='){
        
        pos++;

        if(input[pos] == '='){
            pos++;

            tok = new Token(OP, ATT);
        }
        else
            tok = new Token(OP, EQ);
    }
    else if(input[pos] == '!'){
        pos++;
        if(input[pos] == '='){
            pos++;

            tok = new Token(OP, NE);
        }
        else{
            ErroLexico("Esperava-se '!='");
        }
    }
    else if(input[pos] == '+'){
        pos++;
        tok = new Token(OP, ADD);
    }

    else if(input[pos] == '-'){
        pos++;
        tok = new Token(OP, SUB);
    }

    else if(input[pos] == '*'){
        pos++;
        tok = new Token(OP, MUL);
    }

    else if(input[pos] == '/'){
        pos++;
        tok = new Token(OP, DIV);
    }

    else if(input[pos] == '%'){
        pos++;
        tok = new Token(OP, MOD);
    }
    else if(input[pos] == '('){
        pos++;
        tok = new Token(SEP, LP);
    }

    else if(input[pos] == ')'){
        pos++;
        tok = new Token(SEP, RP);
    }

    else if(input[pos] == '['){
        pos++;
        tok = new Token(SEP, SBL);
    }

    else if(input[pos] == ']'){
        pos++;
        tok = new Token(SEP, SBR);
    }

    else if(input[pos] == '{'){
        pos++;
        tok = new Token(SEP, LK);
    }

    else if(input[pos] == '}'){
        pos++;
        tok = new Token(SEP, RK);
    }

    else if(input[pos] == ';'){
        pos++;
        tok = new Token(SEP, SC);
    }

    else if(input[pos] == '.'){
        pos++;
        tok = new Token(SEP, DOT);
    }

    else if(input[pos] == ','){
        pos++;
        tok = new Token(SEP, COM);
    }
    else if(isdigit(input[pos])){
        pos++;
        while(isdigit(input[pos]))
            pos++;
        tok = new Token(INTEGER_LITERAL);
    }
    else{
        /*printf("pos=%d\n", pos);*/
        ErroLexico("Token nao pertence a linguagem\n");
    }

   

    return tok;
}

void Scanner::ErroLexico(string msg_erro){
   cout << "\nErro Lexico na linha "<< this->getLine()
    << ": "<< msg_erro << endl;
    exit(EXIT_FAILURE);
}


int Scanner::getLine(){
    return this->line;
}
