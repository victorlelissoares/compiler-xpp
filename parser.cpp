#include "scanner.h"

class Parser{
	private:
		Scanner* scanner;
		Token* lToken;
		
		//vetor para auxiliar na impressão de erros
		string vetor[45] = {"UNDEF", "ID", "IF", "ELSE", "THEN", "OPERADOR",
		"=", "!=", ">", ">=", "<", "<=", "NUMBER", "INTEGER_LITERAL",
		"+", "-", "*", "/", "%", "==", "STRING_LITERAL", "SEPARADOR", "(",
	  	")", "{", "}", ";", ".", ",", "class", "int", "string", "break",
		"print", "read", "return", "super", "for", "new", "constructor", 
		"relop", "END_OF_FILE"};
  	
  	//verificar relop

  	/*Por algum motivo, em alguns pontos quando utilizo match(ID)
	tenho um erro de segmentação, mesmo a função match usando exit(),
	para "driblar" isso, usei uma verificação a mais e implementei
	uma função error*/
	
	/*
	Da produção Statements em diante, utilizei a gramática modificada
	para me auxiliar, a mesma está contida no diretório do trabalho com
	o nome "gramat_altered.txt".
	*/

	public:
	Parser(string input){
		scanner = new Scanner(input);
	}

		void advance(){
			lToken = scanner->nextToken();
		}


		int match(int t){
			
			if( (lToken->name) == t || (lToken->attribute) == t ){
				advance();
				return 1;
			}
			else{

				/*printf("valor de t->%d", t);*/
				cout << "Erro na Linha " << scanner->getLine() << ": espera-se '" <<
				this->vetor[t-2] << "'." <<endl;
				
				exit(EXIT_FAILURE);
				return 0;
			}
		}

		void run(){
			advance();
			Program();
			printf("Compilação Encerrada com Sucesso\n");
		}

		void error(string mensagem){
			cout << "Erro Sintático na linha "<< scanner->getLine()
			<< ": "<< mensagem << endl;
			exit(EXIT_FAILURE);
		}

		void Program(){
			
			if( !(lToken->name == END_OF_FILE) )
				ClassList();
			else
				;
		}


		void ClassList(){
			
			do{
				ClassDecl();
			}while(lToken->attribute == CLASS);

		}

		void ClassDecl(){
			match(CLASS);
			if(lToken->name == ID)
				match(ID);			
			else
				error("Espera-se 'ID'.");

			if(lToken->attribute == EXTENDS){
				advance();
				if(lToken->name == ID)
					match(ID);			
				else
					error("Espera-se 'ID'.");
			}

			ClassBody();
		}



		void ClassBody(){
			/*printf("ClassBody");*/
			match(LK);
			/*printf("LK\n");*/
			VarDeclListOpt();
			ConstructDeclListOpt();
			MethodDeclListOpt();
			//Statement();
			//VarDeclListOpt TOTALMENT FUNCIONAL
			//Statements();
			//Expression();
			match(RK);
		}

		void MethodDeclListOpt(){
			if(isType(lToken)){
				/*printf("Entrei\n");*/
				MethodDeclList();
			}
		}

		void MethodDeclList(){
			do{
				MethodDecl();  
				/*printf("\n, %d %d\n", lToken->name, lToken->attribute);*/
			}while(isType(lToken));
			//problema aqui
		}

		void MethodDecl(){
			
			Type();

			if(lToken->attribute == SBL){
				advance();
				match(SBR);
			}
			
			if(lToken->name == ID)
				match(ID);			
			else
				error("Espera-se 'ID'.");
		
			MethodBody();
			/*printf("\n, %d %d\n", lToken->name, lToken->attribute);*/
			

			/*printf("pasei ;\n");*/

		}


		void VarDeclListOpt(){
			if(isType(lToken)){
				/*printf("Entrei\n");*/
				VarDeclList();
			}
		}

		void VarDeclList(){
			do{
				VarDecl();  
				/*printf("\n, %d %d\n", lToken->name, lToken->attribute);*/
			}while(isType(lToken));
			//problema aqui
		}

		void VarDecl(){
			
			Type();

			if(lToken->attribute == SBL){
				advance();
				match(SBR);
			}
			
			if(lToken->name == ID)
				match(ID);			
			else
				error("Espera-se 'ID'.");
		
			VarDeclOpt();
			/*printf("\n, %d %d\n", lToken->name, lToken->attribute);*/
			match(SC);

			/*printf("pasei ;\n");*/

		}

		void VarDeclOpt(){
			
			while(lToken->attribute == COM){
				advance();		

				if(lToken->name == ID)
					match(ID);			
				else
					error("Espera-se 'ID'.");
				
				//após consumir um id, nesse caso
				//ou vem ;, ou , 
			}
			
		}

		void Type(){
			if(isType(lToken)){
				/*printf("aqui1");*/
				advance();
			}
			else{
				printf("Erro na linha %d: Não é um tipo válido\n", scanner->getLine());
				exit(EXIT_FAILURE);
			}
		}

		void ConstructDeclListOpt(){
			/*printf("construtor %d, %d\n", lToken->name, lToken->attribute);*/
			if(lToken->attribute == CONSTRUCTOR){
				/*printf("Entrei aqui");*/
				ConstructDeclList();
			}
		}

		void ConstructDeclList(){
			do{
				ConstructDecl();
			}while(lToken->attribute == CONSTRUCTOR);
		}

		void ConstructDecl(){
			match(CONSTRUCTOR);
			MethodBody();
		}

		void MethodBody(){
			
			match(LP);
			ParamListOpt();
			match(RP);
			match(LK);
			Statements();
			match(RK);
		}

		void Statements(){
			do{
				Statement();
			}while(StatementType(lToken));
		}

		void ParamListOpt(){
			if(isType(lToken))
				ParamList();
		}

		void ParamList(){
			do{
				Param();
			}while(isType(lToken));
		}

		void Param(){
			Type();


			if(lToken->attribute == SBL){
				advance();
				match(SBR);
			}
			if(lToken->name == ID)
					match(ID);			
				else
					error("Espera-se 'ID'.");
			ParamDeclOpt();
			/*printf("pasei ;\n");*/
		}

		void ParamDeclOpt(){
			if(lToken->attribute == COM){
				/*printf("virgula");*/
				advance();
				/*printf("\n, %d %d\n", lToken->name, lToken->attribute);*/
				Type();


				if(lToken->attribute == SBL){
					advance();
					match(SBR);
				}
				if(lToken->name == ID)
					match(ID);			
				else
					error("Espera-se 'ID'.");

			
			}
			/*printf("ParamDeclOpt\n");*/
		}

		int StatementType(Token *t){

			if((t->name == ID) || (isType(t)) || (t->name == PRINT || t->name == RETURN)
				|| (t->name == READ) || (t->name == SUPER) || (t->name == BREAK) || 
				(t->name == IF) || (t->attribute == SC)){
				return 1;
			}
			else{
				return 0;
			}

		}

		void Statement(){
			/*printf("\n, %d %d\n", lToken->name, lToken->attribute);*/
			if(lToken->name == ID){
				advance();
				/*printf("Statement\n");*/
				StatementLine();
				
				/*printf("SC\n");*/
			}
			else if(isType(lToken)){
				VarDeclList();
			}
			else if(lToken->name == PRINT || lToken->name == RETURN){
				advance();
				Expression();
				match(SC);
			}
			else if(lToken->name == READ){
				advance();
				LValue();
				match(SC);
			}
			else if(lToken->name == SUPER){
				advance();
				match(LP);
				ArgListOpt();
				match(RP);
				match(SC);
			}
			//falta if e for
			else if(lToken->name == BREAK){
				advance();
				match(SC);
			}
			else if(lToken->name == IF){
				match(IF);
				match(LP);//(
				Expression();
				match(RP);//)
				match(LK);//{
				Statements();
				match(RK);//}
				ifStatLine();//caso tenha else
			}
			else if(lToken->attribute == FOR){
				/*for ( AtribStatOpt ; ExpressionOpt ; AtribStatOpt )
				{ Statements }*/
				match(FOR);
				match(LP);
				AtribStatOpt();
				match(SC);
				ExpressionOpt();
				match(SC);
				AtribStatOpt();
				match(RP);
				match(LK);
				Statements();
				match(RK);

			}
			else if(lToken->attribute == SC){
				advance();
			}
			//falta for
			//pode ser vazio
			//parece funcional

		}

		void AtribStatOpt(){
			//AtribStatOpt -> ID LValue' = AtribStat' | vazio
			if(lToken->name == ID){
				if(lToken->name == ID)
					match(ID);			
				else
					error("Espera-se 'ID'.");
				LValueLine();
				match(EQ);
				AtribStatLine();
			}
			else
				;//vazio
		}

		void ExpressionOpt(){
			if(lToken->name == ADD || lToken->name == SUB)
				Expression();
		}

		void ifStatLine(){
			if(lToken->name == ELSE){
				match(ELSE);
				match(LK);
				Statements();
				match(RK);
			}
			else
				;//if sem else
		}

		void LValue(){
			if(lToken->name == ID)
				match(ID);			
			else
				error("Espera-se 'ID'.");
			LValueLine();
		}

		void LValueLine(){
			if(lToken->attribute == DOT){
				match(DOT);
				if(lToken->name == ID)
					match(ID);			
				else
					error("Espera-se 'ID'.");
				LValueCompLine();
			}
			else if(lToken->attribute == SBL){
				match(SBL);
				Expression();
				match(SBR);
				LValueComp();
			}
			else
				;//vazio
		}
		void ArgListOpt(){
			ArgList();
		}

		void ArgList(){
			Expression();

			while(lToken->attribute == COM){
				advance();
				Expression();
			}

		}

		void AllocExpression(){
			if(isType(lToken)){
				Type();
				match(SBL);
				Expression();
				match(SBR);
			}else if(lToken->attribute == NEW){
				advance();
				if(lToken->name == ID)
					match(ID);			
				else
					error("Espera-se 'ID'.");
				match(LP);
				ArgListOpt();
				match(RP);
			}
		}

		void StatementLine(){
			if(lToken->name == ID){
				/*printf("É ID");*/
				advance();
				VarDeclOpt();
				/*printf("Depois VarDecl");*/
				//printf("\n, %d %d\n", lToken->name, lToken->attribute);
				match(SC);
				
				if(isType(lToken))
					VarDeclList();
				
			}
			else if(lToken->attribute == SBL){
				advance();
				if(lToken->name == ADD || lToken->name == SUB){
					Expression();
					match(SBR);
					LValueComp();
					match(EQ);
					AtribStatLine();
					match(SC);
				}
				else{
					match(SBR);
					if(lToken->name == ID){
						match(ID);			
					}
					else{
						error("Espera-se 'ID'.");
					}
					VarDeclOpt();
					match(SC);

					if(isType(lToken))
						VarDeclList();
				}
			}
			else if(lToken->attribute == DOT){
				/*printf("(DOT)\n");*/
				advance();
				if(lToken->name == ID)
					match(ID);			
				else
					error("Espera-se 'ID'.");
				/*printf("ID\n");*/
				LValueCompLine();
				match(EQ);
				/*printf("Igualdade\n");*/
				AtribStatLine();
				match(SC);
			}
			else if(lToken->attribute == EQ){
				match(EQ);
				AtribStatLine();
				match(SC);
			}
		}

		void LValueComp(){
			if(lToken->attribute == DOT){
				match(DOT);
				if(lToken->name == ID)
					match(ID);			
				else
					error("Espera-se 'ID'.");
				LValueCompLine();
			}
			else{
				;
			}
		}

		
		void LValueCompLine(){
			if(lToken->attribute == DOT){
				match(DOT);
				if(lToken->name == ID)
					match(ID);			
				else
					error("Espera-se 'ID'.");
				LValueCompLine();
			}
			else if(lToken->attribute == SBL){
				match(SBL);//[
				Expression();
				match(SBR);//]
				LValueComp();
			}
			else
				;
		}

		void AtribStatLine(){
			if(lToken->attribute == ADD || lToken->attribute == SUB){
				advance();
				Factor();
				TermLine();
				NumExpressionLine();
				ExpressionLine();
			}
			else if(lToken->name == NEW || isType(lToken)){
				AllocExpression();
			}
			else{
				error("Espera-se um '+' ou '-' ou uma 'AllocExpression'");	
			}
		}

		void Factor(){
			if(lToken->name == STRING_LITERAL ||
				lToken->name == INTEGER_LITERAL){
				advance();
			}
			else if(lToken->name == ID){
				LValue();
				
			}
			else if(lToken->attribute == LP){
				match(LP);
				Expression();
				match(RP);
			}
			else{
				error("Espera-se um 'Fator'.");
			}
				
			
		}

		void TermLine(){
			if(lToken->attribute == MUL
				|| lToken->attribute == DIV
				|| lToken->attribute == MOD){
				advance();
				UnaryExpression();
			}
			else
				;//vazio
		}

		void NumExpressionLine(){
			if(lToken->attribute == ADD
				|| lToken->attribute == SUB){
				advance();
				Term();
			
			}
			else
				;
		}

		void UnaryExpression(){
			if(lToken->attribute == ADD
				|| lToken->attribute == SUB){
				advance();
				Factor();
			}
			else{
				error("Espera-se '+' ou '-'.");
			}
		}
		int isRelop(Token *t){
			if(t->attribute == NE || t->attribute == LE ||
				t->attribute == LT || t->attribute == GE ||
				t->attribute == GT || t->attribute == ATT){
				return 1;
			}
			else
				return 0;

		}
		void ExpressionLine(){
			if(isRelop(lToken)){
				advance();
				NumExpression();
			}
			else{
				;//vazio
			}
		}

		void Expression(){
			NumExpression();
			ExpressionLine();
		}

		void Term(){
			UnaryExpression();
			TermLine();
		}

		void NumExpression(){
			Term();
			NumExpressionLine();
		}

		int isType(Token *t){
			int result = 0;

				if((t->attribute == INT) || (t->attribute == STRING)  || (t->name == ID) ){
					
					result = 1;
				}
		
			/*if(!result)
				printf("ERrro istype\n");*/

			return result;
		}

};



