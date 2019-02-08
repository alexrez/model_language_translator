#include <iostream>
#include <cstring>

using namespace std;

enum type_of_lex {
    LEX_NULL, 								// 0
    LEX_PROGRAM, LEX_INT, LEX_STRING, 		// 1 2 3
    LEX_IF, LEX_ELSE, LEX_WHILE, 			// 4 5 6
    LEX_READ, LEX_WRITE, LEX_NOT, 			// 7 8 9
    LEX_AND, LEX_OR, LEX_BREAK, 			// 10 11 12
    LEX_CASE, LEX_OF, LEX_END, LEX_DO,		// 13 14 15 16

    LEX_LBRACE, LEX_RBRACE, LEX_SEMICOLON, 	// { } ;
    LEX_COMMA, LEX_ASSIGN, LEX_PLUS,		// , = +
    LEX_MINUS, LEX_QUOTE, LEX_TIMES, 		// - " *
    LEX_SLASH, LEX_LSS, LEX_GTR,			// / < >
    LEX_LEQ, LEX_GEQ, LEX_EQ,				// <= >= ==
    LEX_NEQ, LEX_LPAREN, LEX_RPAREN,		// != (  )
    LEX_COLON, LEX_PERCENT,					// : %
    LEX_NUM,
    LEX_ID,
    LEX_EOF,
    LEX_PHRASE,
    POLIZ_LABEL, 
    POLIZ_ADDRESS,
    POLIZ_GO,
    POLIZ_FGO
};

string str_lex [100] = {
    "LEX_NULL", 								// 0
    "LEX_PROGRAM", "LEX_INT", "LEX_STRING", 	// 1 2 3
    "LEX_IF", "LEX_ELSE", "LEX_WHILE", 			// 4 5 6
    "LEX_READ", "LEX_WRITE", "LEX_NOT", 		// 7 8 9
    "LEX_AND", "LEX_OR", "LEX_BREAK", 			// 10 11 12
    "LEX_CASE", "LEX_OF", "LEX_END", "LEX_DO",	// 13 14 15 16

    "LEX_LBRACE", "LEX_RBRACE", "LEX_SEMICOLON",// { } ;
    "LEX_COMMA", "LEX_ASSIGN", "LEX_PLUS",		// , = +
    "LEX_MINUS", "LEX_QUOTE", "LEX_TIMES", 		// - " *
    "LEX_SLASH", "LEX_LSS", "LEX_GTR",			// / < >
    "LEX_LEQ", "LEX_GEQ", "LEX_EQ",				// <= >= ==
    "LEX_NEQ", "LEX_LPAREN", "LEX_RPAREN",		// != (  )
    "LEX_COLON", "LEX_PERCENT",					// : %
    "LEX_NUM",
    "LEX_ID",
    "LEX_EOF",
    "LEX_PHRASE",
    "POLIZ_LABEL", 
    "POLIZ_ADDRESS",
    "POLIZ_GO",
    "POLIZ_FGO"
};	

/////////////////////////  Класс Lex  //////////////////////////

class Lex {
    type_of_lex	t_lex;
    int 		v_lex;

public:
    Lex (type_of_lex t = LEX_NULL, int v = 0){
        t_lex = t;
        v_lex = v;
    }
    type_of_lex get_type(){ return t_lex; }
    int get_value() { return v_lex; }
    friend ostream& operator<< (ostream &s, Lex l){
        s << '(' << l.t_lex << " , " << l.v_lex << "); ";
        return s;
    }
};

/////////////////////  Класс Ident  ////////////////////////////

class Ident {
    char *name;
    bool declare;
    type_of_lex type;
    bool assign;
    int value;
    // string strval;

public:
    Ident() {
        declare = false;
        assign = false;
    }

    char *get_name() { return name; }
    void put_name(const char *n){
        name = new char [strlen(n)+1];
        strcpy(name, n);
    }
    bool get_declare() { return declare; }
    void put_declare() { declare = true; }
    type_of_lex get_type() { return type; }
    void put_type(type_of_lex t) { type = t; }
    bool get_assign() { return assign; }
    void put_assign() { assign = true; }
    int get_value() { return value; }
    void put_value(int v) { value = v; }
    // string get_strval() { return strval; } 		//???????????
    // void put_strval(string s) { strval = s; } 	//???????????
};

//////////////////////  Класс Tabl_ident  ///////////////////////

class Tabl_ident{
    Ident *p;
    int size;
    int top;

public:
    Tabl_ident(int maxsize){
        p = new Ident[size = maxsize];
        top = 1;
    }
    ~Tabl_ident () { delete []p; }
    Ident& operator[] (int k) { return p[k]; }
    int put (char *name);
    int get_size(){return size;}
};

int Tabl_ident::put(char *buf){
    for(int j=1; j<top; j++)
        if ( !strcmp(p[j].get_name(), buf) )
            return j;
    p[top].put_name(buf);
    top++;
    return top-1;
}

//////////////////////  Класс Tabl_phrase  ///////////////////////

class Tabl_phrase{
    string *p;
    // int size;
    int top;

public:
    Tabl_phrase(int maxsize){
        p = new string[maxsize];
        top = 1;
    }
    ~Tabl_phrase () { delete []p; }
    string& operator[] (int k) { return p[k]; }
    int put (string);
    int get_top(){return top;}
};

int Tabl_phrase::put(string buf){
    // for(int j=1; j<top; j++)
    //     if ( !strcmp(p[j].get_name(), buf) )
    //         return j;
    p[top] = buf;
    top++;
    return top-1;
}

////////////////////////////////////////////////////////////////////

Tabl_ident TID(100);
Tabl_phrase TPHR(100);

///////////////////////////////////////////////////////////////////

template < class T, int max_size >
class Stack
{
         T            s [max_size];
         int          top;
public:
                      Stack () { top = 0; }
         void         reset () { top = 0; }
         void         push ( T i );
         T            pop ();
         bool         is_empty () { return top == 0; }
         bool         is_full  () { return top == max_size; }
};
 
template < class T, int max_size >
void Stack < T, max_size > :: push (T i)
{
  if ( !is_full() )
    s [top++] = i;
  else
    throw "Stack_is_full";
}
 
template <class T, int max_size >
T Stack < T, max_size > :: pop ()
{
  if ( !is_empty() )
    return s[--top];
  else
    throw "stack_is_empty";
}

/////////////////////  Класс Poliz    //////////////////////////////

class Poliz {
    Lex* p;
    int size;
    int free;
public:
    Poliz(int max_size) {
        p = new Lex[size = max_size];
        free = 0;
    }
    ~Poliz() {delete []p;}
    void put_lex(Lex l){
        p[free] = l;
        free++;
    }
    void put_lex(Lex l, int place){
        if (0 < place && place <= size)
            p[place] = l;
    }
    Lex& operator[](int k){
        if ( k > size )
            throw "POLIZ:out of array";
        else if ( k > free )
            throw "POLIZ:indefinite element of array";
        else
            return p[k];
    }
    void blank(){ free++; }
    int get_free(){ return free; }
    void print(){
        for (int i=0; i<free; i++){
            // cout << p[i];
            cout << str_lex[p[i].get_type()] << endl;
        }
    }
};

/////////////////////  Класс Scanner  //////////////////////////////

class Scanner {
// public:
    enum state { H, IDENT, NUMB, STRN, ALE, NEQ, COMDEL, COM, ZVZ, DELIM};
    static char* TW[];
    static type_of_lex words[];
    static char* TD[];
    static type_of_lex dlms[];
    state CS;
    FILE *fp;
    char c;
    char buf[80];
    int buf_top;
    void clear(){
        buf_top = 0;
        for(int i=0; i<80; i++)
            buf[i] = '\0';
    }
    void add(){
        buf[buf_top++] = c;
    }

    int look(const char *buf, char **list){
        int i = 0;
        while (list[i]){
            if ( !strcmp(buf, list[i]) )
                return i;
            i++;
        }
        return 0;
    }
    void gc(){ c = fgetc(fp); }
public:
    Scanner (const char *program){
        fp = fopen(program, "r");
        CS = H;
        clear();
        gc();
    }
    Lex get_lex();
};

char *
        Scanner::TW[] = {"", "program",  "int", "string", "if", "else", "while", "read", "write", "not", "and", "or", "break", "case", "of", "end", "do", NULL};

type_of_lex
        Scanner::words[] = {
        LEX_NULL, 								// 0
        LEX_PROGRAM, LEX_INT, LEX_STRING, 		// 1 2 3
        LEX_IF, LEX_ELSE, LEX_WHILE, 			// 4 5 6
        LEX_READ, LEX_WRITE, LEX_NOT, 			// 7 8 9
        LEX_AND, LEX_OR, LEX_BREAK, 			// 10 11 12
        LEX_CASE, LEX_OF, LEX_END, LEX_DO,		// 13 14 15
};

char *
        Scanner::TD[] = { "", "{", "}", ";", ",", "=", "+", "-", "\"", "*", "/", "<", ">", "<=", ">=", "==", "!=", "(", ")", ":", "%", NULL};
type_of_lex
        Scanner::dlms[] = {
        LEX_NULL,
        LEX_LBRACE, LEX_RBRACE, LEX_SEMICOLON, 	// { } ;
        LEX_COMMA, LEX_ASSIGN, LEX_PLUS,		// , = +
        LEX_MINUS, LEX_QUOTE, LEX_TIMES, 		// - " *
        LEX_SLASH, LEX_LSS, LEX_GTR,			// / < >
        LEX_LEQ, LEX_GEQ, LEX_EQ,				// <= >= ==
        LEX_NEQ, LEX_LPAREN, LEX_RPAREN,			// != (  )
        LEX_COLON, LEX_PERCENT					// : %
};

Lex
Scanner::get_lex() {
    int d,j;

    CS = H;
    do {
        switch(CS){
            case H:
                if (c == ' ' || c == '\n' || c == '\t' || c == '\r')
                    gc();
                else if (isalpha(c)){
                    clear();
                    add();
                    gc();
                    CS = IDENT;
                }
                else if (isdigit(c)){
                    d = c - '0';
                    gc();
                    CS = NUMB;
                }
                else if (c == '"'){
                    clear();
                    gc();
                    CS = STRN;
                }
                else if (c == '<' || c == '>' || c == '='){
                    clear();
                    add();
                    gc();
                    CS = ALE;
                }
                else if (c == '!'){
                    clear();
                    add();
                    gc();
                    CS = NEQ;
                }
                else if (c == '/'){
                    clear();
                    add();
                    gc();
                    CS = COMDEL;
                }
                else if (c == EOF){
                    return Lex(LEX_EOF, LEX_EOF); ///////////////////////////////////
                    break;
                }
                else {
                    CS = DELIM;}
                break;

            case IDENT:
                if (isalpha(c) || isdigit(c)){
                    add();
                    gc();
                }
                else if (j = look(buf, TW)){
                    return Lex(words[j], j);
                    CS = H;
                }
                else {
                    j = TID.put(buf);
                    return Lex(LEX_ID, j);
                    CS = H;
                }
                break;

            case NUMB:
                if (isdigit(c)){
                    d = d*10 + c-'0';
                    gc();
                }
                else{
                    return Lex(LEX_NUM, d);
                	CS = H;
                }
                break;

            case STRN:
            	if (isprint(c) && c!= '"'){
            		add();
            		gc();
            	}
            	else if  (c == '"'){
            		gc();
            		j = TPHR.put(string(buf));
            		return Lex(LEX_PHRASE, j);
            	}
            	else {
            		gc();
            	}
                break;

            case ALE:
                if (c == '='){
                    add();
                    gc();
                    j = look(buf, TD);
                    return Lex(dlms[j], j);
                    CS = H;
                }
                else {
                    j = look(buf, TD);
                    return Lex(dlms[j], j);
                    CS = H;
                }
                break;

            case NEQ:
                if (c == '='){
                    add();
                    gc();
                    j = look(buf, TD);
                    return Lex(dlms[j], j);
                    CS = H;
                }
                else {
                    throw "error";
                }
                break;

            case COMDEL:
                if (c == '*'){
                    gc();
                    CS = COM;
                }
                else {
                    j = look(buf, TD);
                    return Lex(dlms[j], j);
                    CS = H;
                }
                break;

            case COM:
                if (c == '*'){
                    gc();
                    CS = ZVZ;
                }
                else if (c == EOF){
                    throw "unexpected EOF (in comment)";
                }
                else
                    gc();
                break;
            case ZVZ:
                if (c == '/'){
                    gc();
                    CS = H;
                }
                else if (c == EOF){
                    throw "unexpected EOF (in comment)";
                }
                else {
                    gc();
                    CS = COM;
                }
                break;
            case DELIM:
                if (c == '*' || c == '+' || c == '-' || c == '/' || c == ',' ||
                    c == ';' || c == '(' || c == ')' || c == '{' || c == '}'){
                    clear();
                    add();
                    gc();
                    j = look(buf, TD);
                    return Lex(dlms[j], j);
                    CS = H;
                }
                else{
                    throw("error");
                }
                break;
        }
    }//end switch
    while(true);

}

class Parser{
    int ind, sign = 1;
	Lex curr_lex;
	type_of_lex c_type;
	int c_val;
    Stack < type_of_lex, 100 >  st_lex;
	// string str_val; //// ??
	Scanner scan;

	void Programma();
	void Opisaniya();
	// void Opisanie();
	// void Tip();
	void Peremennaya(Lex);
	void Konstanta(Lex);
	void Celochislennaya();
	// void Znak();
	void Strokovaya();
	void Operatori();
	void Operator();
	void SostavnoyOperator();
	void OperatorViragenie();
	void Viragenie();

	void E1();
	void T();
	void F();

    void check_id ();
    void check_op ();
    void check_not ();
    void eq_type ();
    void eq_int();
    void check_id_in_read();

	void gl(){
		curr_lex = scan.get_lex();
		c_type = curr_lex.get_type();
		c_val = curr_lex.get_value();
	};

public:
    Poliz prog;
	Parser(const char *program): scan(program), prog(1000){}
	void analyze();
};



void Parser::analyze(){
	gl();
	Programma();
	// cout << endl << "Success!!!" << endl;
}

void Parser::Programma(){
	if (c_type == LEX_PROGRAM)
		gl();
	else
		throw curr_lex;
	if (c_type == LEX_LBRACE)
		gl();
	else
		throw curr_lex;
	Opisaniya();
	Operatori();
	if (c_type == LEX_RBRACE)
		gl();
	else
		throw curr_lex;
	if (c_type != LEX_EOF)
		throw curr_lex;
}

void Parser::Opisaniya(){
	while (c_type == LEX_INT || c_type == LEX_STRING){
        Lex param_lex = curr_lex;
		gl();
		Peremennaya(param_lex);
		while (c_type == LEX_COMMA){
			gl();
			Peremennaya(param_lex);
		}
		if (c_type == LEX_SEMICOLON)
			gl();
		else 
			throw curr_lex;
	}
}

// void Parser::Opisanie(){}
// void Parser::Tip(){}
void Parser::Peremennaya(Lex param_lex){
	if (c_type == LEX_ID){
		ind=curr_lex.get_value();
        if (TID[ind].get_declare())
            throw string("Error: Variable ")+ string(TID[ind].get_name()) + string(" declared twice!");
        else { 
            TID[ind].put_declare();
            TID[ind].put_type(param_lex.get_type());
            gl();
        }
    }
	else
		throw curr_lex;
	if (c_type == LEX_ASSIGN){
		gl();
		Konstanta(param_lex);
	}
}
void Parser::Konstanta(Lex param_lex){
	if (c_type == LEX_PLUS || c_type == LEX_MINUS){
        (c_type == LEX_MINUS)?sign=-1:sign=1;
		gl();
        if (param_lex.get_type() == LEX_INT)
		  Celochislennaya();
        else
            throw string("Error: Incorrect initialization of variable with type ") + string(str_lex[param_lex.get_type()]);
	}
	else if (c_type == LEX_NUM){
		if (param_lex.get_type() == LEX_INT)
          Celochislennaya();
        else
            throw string("Error: Incorrect initialization of variable with type ") + string(str_lex[param_lex.get_type()]);
	}
	// else if (c_type == LEX_QUOTE){
	// }
	else if (c_type == LEX_PHRASE){
		if (param_lex.get_type() == LEX_STRING)
          Strokovaya();
        else
            throw string("Error: Incorrect initialization of variable with type ") + string(str_lex[param_lex.get_type()]);
	}
	else
		throw curr_lex;
}

void Parser::Celochislennaya(){
	if (c_type == LEX_NUM){
        TID[ind].put_value(sign*curr_lex.get_value());
        TID[ind].put_assign();
        gl();
    }
	else 
		throw curr_lex;
}

// void Parser::Znak(){}
void Parser::Strokovaya(){
	if (c_type == LEX_PHRASE){
        TID[ind].put_value(curr_lex.get_value());
        TID[ind].put_assign();
		gl();
    }
	else 
		throw curr_lex;
}
void Parser::Operatori(){
	while (c_type == LEX_IF || 
		c_type == LEX_WHILE || 
		c_type == LEX_READ || 
		c_type == LEX_WRITE || 
		c_type == LEX_LBRACE ||
		c_type == LEX_ID){
			Operator();
	}
}

void Parser::Operator(){
    int pl0, pl1, pl2, pl3;

	if (c_type == LEX_IF){
		gl();
		if (c_type == LEX_LPAREN)
			gl();
		else
			throw curr_lex;
		Viragenie();
        eq_int(); // проверка типов в операторах
        pl2 = prog.get_free(); // внутр предст
        prog.blank(); // внутр предст
        prog.put_lex(Lex(POLIZ_FGO)); // внутр предст
		if (c_type == LEX_RPAREN)
			gl();
		else
			throw curr_lex;
		Operator();
        pl3 = prog.get_free(); prog.blank(); // внутр предст
        prog.put_lex(Lex(POLIZ_GO)); // внутр предст
        prog.put_lex(Lex(POLIZ_LABEL, prog.get_free()),pl2); // внутр предст
		if (c_type == LEX_ELSE){
			gl();
            Operator();
            prog.put_lex(Lex(POLIZ_LABEL, prog.get_free()),pl3); // внутр предст
		}
        else
			throw curr_lex;
	}
	else if (c_type == LEX_WHILE){
        pl0=prog.get_free(); // внутр предст
		gl();
		if (c_type == LEX_LPAREN)
			gl();
		else
			throw curr_lex;
		Viragenie();
        eq_int(); // проверка типов в операторах
        pl1=prog.get_free(); prog.blank(); // внутр предст
        prog.put_lex(Lex(POLIZ_FGO)); // внутр предст
		if (c_type == LEX_RPAREN){
			gl();
            Operator();
            prog.put_lex(Lex(POLIZ_LABEL, pl0)); // внутр предст
            prog.put_lex(Lex(POLIZ_GO)); // внутр предст
            prog.put_lex(Lex(POLIZ_LABEL, prog.get_free()), pl1); // внутр предст
        }
		else
			throw curr_lex;

	}
	else if (c_type == LEX_READ){
		gl();
		if (c_type == LEX_LPAREN)
			gl();
		else
			throw curr_lex;
		if (c_type == LEX_ID){
            check_id_in_read(); // проверка типов в операторах
            prog.put_lex(Lex(POLIZ_ADDRESS, c_val)); // внутр предст
			gl();
        }
		else
			throw curr_lex;
		if (c_type == LEX_RPAREN){
			gl();
            prog.put_lex(Lex(LEX_READ)); // внутр предст
        }
		else
			throw curr_lex;
		if (c_type == LEX_SEMICOLON)
			gl();
		else
			throw curr_lex;
	}
	else if (c_type == LEX_WRITE){
		gl();
		if (c_type == LEX_LPAREN)
			gl();
		else
			throw curr_lex;
		Viragenie();
        prog.put_lex(Lex(LEX_WRITE)); // внутр предст
		while (c_type == LEX_COMMA){
			gl();
			Viragenie();
            prog.put_lex(Lex(LEX_WRITE)); // внутр предст
		}
		if (c_type == LEX_RPAREN){
			gl();
        }
		else
			throw curr_lex;
		if (c_type == LEX_SEMICOLON)
			gl();
		else
			throw curr_lex;
	}
	else if (c_type == LEX_LBRACE){   // SostavnoyOperator()
		gl();
		Operatori();
		if (c_type == LEX_RBRACE)
			gl();
		else
			throw curr_lex;
	}
	else if (c_type == LEX_ID){
        check_id (); // проверка типов в операторах
        prog.put_lex(Lex(POLIZ_ADDRESS, c_val)); // внутр предст
		gl();
		if (c_type == LEX_ASSIGN){
			gl();
			OperatorViragenie();
            eq_type(); // проверка типов в операторах
            prog.put_lex(Lex(LEX_ASSIGN)); // внутр предст
		}
		else
			throw curr_lex;
	}
	else
		OperatorViragenie();
}

// void Parser::SostavnoyOperator(){}
void Parser::OperatorViragenie(){
	Viragenie();
	if (c_type == LEX_SEMICOLON)
		gl();
	else
		throw curr_lex;
}

void Parser::Viragenie(){
	E1();
	if (c_type == LEX_EQ || c_type == LEX_LSS || c_type == LEX_GTR ||
		c_type == LEX_LEQ || c_type == LEX_GEQ || c_type == LEX_NEQ ){
            st_lex.push(c_type); // проверка типов в выражении
			gl();
			E1();
            check_op(); // проверка типов в выражении
	}
}

void Parser::E1 ()
{
  T();
  while ( c_type == LEX_PLUS || c_type == LEX_MINUS || c_type == LEX_OR){
    st_lex.push(c_type); // проверка типов в выражении
    gl();
    T();
    check_op(); // проверка типов в выражении
  }
}
 
void Parser::T ()
{
  F();
  while ( c_type == LEX_TIMES || c_type == LEX_SLASH || c_type == LEX_AND) {
    st_lex.push(c_type); // проверка типов в выражении
    gl();
    F();
    check_op(); // проверка типов в выражении
  }
}
 
void Parser::F () 
{
  if ( c_type == LEX_ID ){
    check_id(); // проверка типов в выражении
    prog.put_lex(curr_lex); // внутр предст
    gl();
  }
  else if ( c_type == LEX_NUM ){
    st_lex.push(LEX_INT); // проверка типов в выражении
    prog.put_lex(curr_lex); // внутр предст
    gl();
  }
  else if (c_type == LEX_NOT){
    gl(); 
    F(); 
    check_not(); // проверка типов в выражении
  }
  else if (c_type == LEX_PHRASE){
    st_lex.push(LEX_STRING); // проверка типов в выражении
    prog.put_lex(curr_lex); // внутр предст
    gl();
  }
  else if ( c_type == LEX_LPAREN ) 
  {
    gl(); 
	Viragenie();
    if ( c_type == LEX_RPAREN)
      gl();
    else 
      throw curr_lex;
  }
  else 
    throw curr_lex;
}

////////////////проверка типов в выражении////////////////////////

void Parser::check_id () 
{
  if ( TID[c_val].get_declare() )
    st_lex.push ( TID[c_val].get_type() );
  else 
    throw  string("Error: Variable ") + string(TID[c_val].get_name()) + string(" is not declared!");
}

void Parser::check_op () 
{
  type_of_lex t1, t2, op;
 
  t2 = st_lex.pop();
  op = st_lex.pop();
  t1 = st_lex.pop();
  if (t1 == t2){
    if (op == LEX_PLUS && t1 == LEX_STRING)
        st_lex.push(LEX_STRING);
    else if (t1 == LEX_STRING && (op == LEX_MINUS || op == LEX_TIMES|| op == LEX_SLASH || op == LEX_PERCENT ||
             op == LEX_LEQ || op == LEX_GEQ || op == LEX_AND || op == LEX_OR))
        throw "Error: Incorrect operation for string type!";
    else
        st_lex.push(LEX_INT);
    // st_lex.push(r);
  }
  else
    throw "Error: Unequal types in expression!";
  prog.put_lex(Lex(op)); // внутр предст
}

void Parser::check_not () 
{
  if (st_lex.pop() != LEX_INT)
    throw "wrong type is in not";
  else 
  {
    st_lex.push (LEX_INT);
    prog.put_lex(Lex(LEX_NOT)); // внутр предст
  }
}

////////////////проверка типов в операторах////////////////////

void Parser::eq_type (){
    if (st_lex.pop() != st_lex.pop())
        throw "Error: Wrong types in assign operator!";
} 

void Parser::eq_int (){
    if (st_lex.pop() != LEX_INT)
        throw "Error: Type of conditional expression must be integer!";
}

void Parser::check_id_in_read (){
    if (!TID[c_val].get_declare())
       throw string("Error: Variable ") + string(TID[c_val].get_name()) + string(" is not declared in read operator!");
}

////////////////////////////////////////////////////////////////

class ExecStack
{
         Lex            s [1000];
         int          top;
public:
                      ExecStack () { top = 0; }
         void         reset () { top = 0; }
         void         push ( int i );
         void         push_str ( int i );
         int          pop ();
         type_of_lex  get_type();  
         bool         is_empty () { return top == 0; }
         bool         is_full  () { return top == 1000; }
};
 

void ExecStack:: push (int i)
{
  if ( !is_full() )
    s [top++] = Lex(LEX_INT, i);
  else
    throw "Stack_is_full";
}

void ExecStack:: push_str (int i)
{
  if ( !is_full() )
    s [top++] = Lex(LEX_STRING, i);
  else
    throw "Stack_is_full";
}
 

int ExecStack:: pop ()
{
  if ( !is_empty() )
    return s[--top].get_value();
  else
    throw "stack_is_empty";
}

type_of_lex ExecStack:: get_type ()
{
  if ( !is_empty() )
    return s[top-1].get_type();
  else
    throw "stack_is_empty";
}

////////////////////////////////////////////////////////////////
 
class Executer
{
         Lex          pc_el;
public:
         void         execute ( Poliz & prog );
};
 
void Executer::execute ( Poliz & prog )
{
  ExecStack args;
  int i, j, index = 0, size = prog.get_free();
  while ( index < size )
  {
    pc_el = prog [ index ];
    switch ( pc_el.get_type () )
    {
      case LEX_NUM: case POLIZ_LABEL: // +
            args.push ( pc_el.get_value () );
            break;
      case POLIZ_ADDRESS:
            if (TID[pc_el.get_value()].get_type() == LEX_STRING){
                args.push_str( pc_el.get_value () );
                break;
            }
            else if (TID[pc_el.get_value()].get_type() == LEX_INT){
                args.push( pc_el.get_value () );
                break;
            }

      case LEX_PHRASE: // +
            args.push_str( pc_el.get_value () );
            break;
      case LEX_ID: // +
            i = pc_el.get_value ();
            if (TID[i].get_assign()){
                if (TID[i].get_type() == LEX_INT){
                    args.push ( TID[i].get_value () );
                    break;
                }
                else if (TID[i].get_type() == LEX_STRING){
                    args.push_str ( TID[i].get_value () );
                    break;
                }
            }
            else
              throw "(Poliz) Error: indefinite identifier!";
      case LEX_NOT: // +
            args.push( !args.pop() );
            break;
      case LEX_OR: // +
        i = args.pop();
        args.push ( args.pop() || i );
        break;
      case LEX_AND: // +
        i = args.pop();
        args.push ( args.pop() && i );
        break;
      case POLIZ_GO:
        index = args.pop() - 1;
        break;
      case POLIZ_FGO:
        i = args.pop();
        if ( !args.pop() ) index = i-1;
        break;
      case LEX_WRITE: // +
            if (args.get_type() == LEX_INT){
                cout << args.pop() << endl;
                break;}
            else if (args.get_type() == LEX_STRING){
                cout << TPHR[args.pop()] << endl;
                break;
            }
      case LEX_READ:
            if (args.get_type() == LEX_INT){
                i = args.pop ();
                int k;
                cout << "Input int value for " << TID[i].get_name () << endl;
                cin >> k;
                TID[i].put_value (k);
                TID[i].put_assign ();
                break;}
            else if (args.get_type() == LEX_STRING){
                i = args.pop();
                int k;
                string input_str;
                cout << "Input string value for " << TID[i].get_name () << endl;
                cin >> input_str;
                TPHR[TID[i].get_value()] = input_str;
                // TID[i].put_value (k);
                // TID[i].put_assign ();
                break;
            }
        {
          int k;
          i = args.pop ();
          if ( TID[i].get_type () == LEX_INT )
          {
            cout << "Input int value for" << TID[i].get_name () << endl;
            cin >> k;
          }
          else
          {
            char j[20];
            rep:
            cout << "Input boolean value (true or false) for" << TID[i].get_name() << endl;
            cin >> j;
            if (!strcmp(j, "true"))
              k = 1;
            else
              if (!strcmp(j, "false"))
                k = 0;
              else
              {
                cout << "Error in input:true/false" << endl;
                goto rep;
              }
          }
          TID[i].put_value (k);
          TID[i].put_assign ();
          break;
        }
      case LEX_PLUS: // +
            if (args.get_type() == LEX_INT){
                args.push ( args.pop() + args.pop() );
                break;}
            else if (args.get_type() == LEX_STRING){ 
                args.push_str(TPHR.put( TPHR[args.pop()] +TPHR[args.pop()] ));
                break;
            }
      case LEX_TIMES: // +
        args.push ( args.pop() * args.pop() );
        break;
      case LEX_MINUS: // +
        i = args.pop();
        args.push ( args.pop() - i );
        break;
      case LEX_SLASH: // +
        i = args.pop();
        if (i)
        {
          args.push(args.pop() / i);
          break;
        }
        else
          throw "(Poliz) Error: divizion by zero!";
      case LEX_EQ: // +
            if (args.get_type() == LEX_INT){
                args.push ( args.pop() == args.pop() );
                break;}
            else if (args.get_type() == LEX_STRING){  
                args.push(TPHR[args.pop()]  == TPHR[args.pop()]);
                break;
            }
      case LEX_LSS: // +
            if (args.get_type() == LEX_INT){
                i = args.pop();
                args.push ( args.pop() < i);
                break;}
            else if (args.get_type() == LEX_STRING){  
                string ts = TPHR[args.pop()];
                args.push(TPHR[args.pop()]  < ts);
                break;
            }
      case LEX_GTR: // +
            if (args.get_type() == LEX_INT){
                i = args.pop();
                args.push ( args.pop() > i);
                break;}
            else if (args.get_type() == LEX_STRING){  
                string ts = TPHR[args.pop()];
                args.push(TPHR[args.pop()]  > ts);
                break;
            }
      case LEX_LEQ: // +
        i = args.pop();
        args.push ( args.pop() <= i );
        break;
      case LEX_GEQ: // +
        i = args.pop();
        args.push ( args.pop() >= i );
        break;
      case LEX_NEQ: // +
        if (args.get_type() == LEX_INT){
                i = args.pop();
                args.push ( args.pop() != i);
                break;}
            else if (args.get_type() == LEX_STRING){  
                string ts = TPHR[args.pop()];
                args.push(TPHR[args.pop()]  != ts);
                break;
            }
      case LEX_ASSIGN: // +
            i = args.pop();
            j = args.pop();
            TID[j].put_value(i);
            TID[j].put_assign(); break;
      default:
        throw "POLIZ: unexpected elem";
    }//end of switch
    ++index;
  };//end of while
  cout << "Finish of executing!!!" << endl;
}
 
class Interpretator
{
  Parser   pars;
  Executer E;
public:
           Interpretator  (const char* program): pars (program) {}
  void     interpretation ();
};
 
void Interpretator::interpretation ()
{
  pars.analyze ();
  cout << endl;
  pars.prog.print();
  cout << endl;
  E.execute ( pars.prog );
}

int main() {
	// Scanner scan1("input.txt");
 //    try {
	//     Lex lex1;
	//     int i = 1;
	//     lex1 = scan1.get_lex();
	//     while (lex1.get_type() != LEX_EOF){
	//     	cout << lex1 << " <=> " << str_lex[lex1.get_type()] << endl;
	//     	lex1 = scan1.get_lex();
	//     	i++;
	//     }
 //    }
 //    catch (char const* str){
 //    	cout << str << endl;
	// }

 // // Проверка работы лексич+семантич анализа и генерации полиза
	// Parser pars1("input.txt");
	// try {
	// 	pars1.analyze();
 //        pars1.prog.print();
	// }
  try
  {
    Interpretator I ("input.txt");
    I.interpretation ();
  }

  catch (char c){
    cout << "unexpected symbol " << c << endl;
    return 1;
  }
	catch (char const* str){
    	cout << str << endl;
        return 1;
    }
    catch (Lex l)
  {
    cout << "unexpected lexeme";
    cout << l << " <=> " << str_lex[l.get_type()] << endl;
    return 1;
  }
    catch (string s){
        cout << s << endl;
        return 1;
    }


// // Вывод всех идентификаторов из таблицы TID, с типом и флагом описания
// int i=1;
//  while (TID[i].get_name()){
//     cout << TID[i].get_name() << "  " << str_lex[TID[i].get_type()]<< " -> "<< TID[i].get_declare()<< "  " << TID[i].get_value() << endl;
//     i++;
// }

// // Вывод всех фраз из таблицы TPHR
// int j=1;
//  while (j < TPHR.get_top()){
//     cout << j<<"-\""<< TPHR[j] << "\""<< endl;
//     j++;
// }

}
