#include "parser.cpp"

using namespace std;

int main(int argc, char* argv[]) {
    
    /*Scanner* scanner = new Scanner(argv[1]);
    
    Token *t;
    printf("\n");
    do{
        t = scanner->nextToken();

        cout << t->name << " ";
    }while(t->name != END_OF_FILE);
    cout << "\nLinha " << ": " << scanner->getLine()<< endl;
    delete scanner;*/

    Parser *parser = new Parser(argv[1]);
    printf("\n");
    parser->run();

    return 0;
}