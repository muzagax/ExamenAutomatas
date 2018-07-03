%name JarParser
%{
	#include <iostream>
	#include <ostream>
	#include <string>
	#include <cstring>
	#include <fstream> 
	#include <cstdlib>
	#include "nodos.h"
	using namespace std;

	extern "C" int yylex();
	extern "C" int yyparse();
		 
	void yyerror(const char *s);

	NodoControlador* programa;
	
	extern FILE *yyin;
   	extern int yylineno;
	
%}

%union{

    char* palabras;
    char* operandos;
    char* error;
    string* hilera;
    int valores;

    Nodo * nodo;
    NodoInstruccion * instr;
    NodoControlador * contrl;
    NodoDeclaracion * declaracion;

    NodoVariable * var;
    NodoDeclaracionVar * declVariables;

    NodoAsignacion * asign;
    
    NodoVarLocal * varLocal;

    NodoExpresion * expr;
    NodoIdentificador * ident;
    NodoEstructuraControl * EstrucCont;

    NodoDeclaracionFunc * declFunc;

    std::vector<NodoInstruccion*> * listaNI;
    std::vector<NodoDeclaracion*> * listaND;
	
}

/* %error-verbose */
%type <valores> t_num_pos t_num_neg t_num_pos_dec t_num_neg_dec expNumeros
%type <hilera> t_id t_hilera t_boolean t_vacio t_entero data_type
%type <hilera> t_retornar t_imprimir t_escanear t_iniciar
%type <hilera> t_si t_sino t_mientras t_para t_hasta
%type <errores> t_error_lexico
 
/** seccion para dar tipos a los no terminales de la gramatica **/

%type <instr> exp_matem  idNum
%type <instr> expBooleana expBool simpleExpBool t_parent_iz t_parent_de
%type <instr> exp_Hilera  
%type <contrl> program statements

%type <declaracion> tipo_param var_declaration func_declaration blocks
%type <declVariables> declaracion_for

%type <listaNI> declaration_body_ent declaration_body_str declaration_body_bll
%type <listaNI> statements_block lista_elem param_input

%type <listaND> param
%type <instr> iniciar_programa declaration_line_ent declaration_line_str declaration_line_bll  
%type <instr> id_init estruc_control
%type <instr> llamado_funcion expr_impr
%type <EstrucCont> tipo_if pero_si sino tipo_for tipo_while
%type <instr> exp_cambio limite_for 
 



%token t_id
%token t_parent_iz t_parent_de
%token t_mayor_que t_menor_que t_mayor_igual t_menor_igual t_diferente_a t_igual_a
%token t_and t_or t_negacion
%token t_hilera
%token t_boolean
%token t_entero
%token t_si
%token t_sino
%token t_pero
%token t_mientras
%token t_para
%token t_hasta
%token t_comentario
%token t_imprimir
%token t_escanear
%token t_retornar
%token t_iniciar
%token t_vacio
%token t_dos_puntos
%token t_punto_coma
%token t_coma
%token t_comillas
%token t_cuadrado_iz
%token t_cuadrado_de
%token t_num_pos t_num_neg t_num_pos_dec t_num_neg_dec
%token t_error_lexico

%left t_division t_multiplicacion t_modulo t_mas t_menos

%%
program: statements iniciar_programa{cout<<"root"<<endl;programa = $1; programa->iniciarNombreFuncion = $2;}
       ;

statements: blocks{$$ = new NodoControlador(); $$->declaraciones.push_back($1);}
	    |statements blocks{$1->declaraciones.push_back($2);}
	    ;

iniciar_programa: t_iniciar llamado_funcion{$$ = $2;}
		  ;

blocks: var_declaration{$$ = $1;}
      |func_declaration{$$ = $1;}
      ;

var_declaration: t_entero t_dos_puntos declaration_body_ent t_punto_coma{$$ = new NodoDeclaracionVar(*$1,$3);delete $1;}
		 |t_hilera t_dos_puntos declaration_body_str t_punto_coma{$$ = new NodoDeclaracionVar(*$1,$3);delete $1;}
		 |t_boolean t_dos_puntos declaration_body_bll t_punto_coma{$$ = new NodoDeclaracionVar(*$1,$3);delete $1;}
             	 ;  
      
//NodoDeclaracion
declaration_body_ent: declaration_line_ent{$$ = new listaVar; $$->push_back($1);}
		      |  declaration_body_ent t_coma declaration_line_ent{$1->push_back($3);}
		      ;
//NodoInstruccion-NodoAsignacion
declaration_line_ent: t_id t_igual_a exp_matem{$$ = new NodoAsignacion(new NodoIdentificador(*$1), $3);delete $1;}
		      |t_id{$$ = new NodoIdentificador(*$1); delete $1;}
		      ;

declaration_body_str: declaration_line_str{$$ = new listaVar; $$->push_back($1);}
		      | declaration_body_str t_coma declaration_line_str  {$1->push_back($3);}
		      ;
declaration_line_str: t_id t_igual_a exp_Hilera{$$ = new NodoAsignacion(new NodoIdentificador(*$1), $3);delete $1;}
		      |t_id {$$ = new NodoIdentificador(*$1);delete $1;}
		      ;

declaration_body_bll: declaration_line_bll{$$ = new listaVar; $$->push_back($1);}
		      |declaration_body_bll t_coma declaration_line_bll {$1->push_back($3);}
		      ;
declaration_line_bll: t_id t_igual_a expBooleana{$$ = new NodoAsignacion(new NodoIdentificador(*$1), $3);delete $1;}
		      |t_id{$$ = new NodoIdentificador(*$1);delete $1;}
		      ;


/*********************************		EXPRESIONES MATEMÁTICAS*/
exp_matem: idNum{$$ = $1;}
	   |exp_matem t_mas exp_matem{$$ = new NodoExpresion($1, $3,SUMA);}
	   |exp_matem t_menos exp_matem{$$ = new NodoExpresion($1, $3,RESTA);}
	   |exp_matem t_multiplicacion exp_matem{$$ = new NodoExpresion($1, $3,MULTI);}
	   |exp_matem t_division exp_matem{$$ = new NodoExpresion($1, $3,DIV);}
	   |exp_matem t_modulo exp_matem{$$ = new NodoExpresion($1, $3,MOD);}
	   ;

expNumeros: t_num_pos{$$ = $1;}
	    | t_num_neg {$$ = $1;}
	    | t_num_pos_dec {$$ = $1;}
	    | t_num_neg_dec{$$ = $1;}
	    ;

/*********************************		EXPRESIONES BOOLEANAS*/

expBooleana: t_parent_iz expBool t_parent_de{$$=$2;}
     | expBool{$$= $1;}
     ;

expBool: simpleExpBool t_and simpleExpBool{$$ = new NodoExpresion($1, $3,AND);}
     | simpleExpBool t_or simpleExpBool{$$ = new NodoExpresion($1, $3,OR);}
     | simpleExpBool{$$ = $1;}
     ;

simpleExpBool: idNum t_mayor_que idNum{$$ = new NodoExpresion($1, $3,MAYOR);}
     | idNum t_menor_que idNum{$$ = new NodoExpresion($1, $3,MENOR);}
     | idNum t_mayor_igual idNum{$$ = new NodoExpresion($1, $3,MAYOR_IGUAL);}
     | idNum t_menor_igual idNum{$$ = new NodoExpresion($1, $3,MENOR_IGUAL);}
     | idNum t_diferente_a idNum{$$ = new NodoExpresion($1, $3,DIFERENTE);}
     | idNum t_igual_a idNum{$$ = new NodoExpresion($1, $3,IGUAL);}
     | t_negacion expBooleana{$$ = new NodoExpresion($2, 0,NEG);}
     ;

idNum: expNumeros{$$ = new NodoEntero($1);}
	| t_id{$$ = new NodoIdentificador(*$1);delete $1;}
	;

data_type: t_entero {$$ = $1;}
           |t_boolean {$$ = $1;}
	   |t_hilera {$$ = $1;}
	   |t_vacio {$$ = $1;}
	   ;

//NodoIdentificador
exp_Hilera: t_comillas t_id t_comillas {$$=new NodoHilera(*$2);delete $2;}
	    |t_comillas t_comillas{$$=new NodoHilera("");}
	    ;




/*********************************		DECLARACION DE FUNCIONES*/

func_declaration: data_type t_id param t_dos_puntos statements_block t_punto_coma {$$= new NodoDeclaracionFunc(*$1,*$2,$3,$5);delete $1;delete $2;}
	   | data_type t_id t_dos_puntos statements_block t_punto_coma {$$= new NodoDeclaracionFunc(*$1,*$2,$4);delete $1;delete $2;}
	  ;

param: tipo_param {$$ = new parametrosFuncion; $$->push_back($1);}
       |param  t_punto_coma tipo_param{$$->push_back($3);}
       ;
tipo_param: t_entero lista_elem {$$ = new NodoDeclaracionVar(*$1,$2);delete $1;}
	     |t_hilera lista_elem{$$ = new NodoDeclaracionVar(*$1,$2);delete $1;}
	     |t_boolean lista_elem{$$ = new NodoDeclaracionVar(*$1,$2);delete $1;}
	     ;

lista_elem: t_id {$$ = new listaVar; $$->push_back(new NodoIdentificador(*$1) ); delete $1;}
	    |lista_elem t_coma t_id{$$->push_back( new NodoIdentificador(*$3) );delete $3;}
	    ;


/*********************************		ESTRUCTURA DE CONTROL*/			
estruc_control: tipo_if {$$=$1;}
	 	|tipo_while{$$=$1;}
		|tipo_for{$$=$1;}
		;



tipo_if: t_si t_parent_iz expBooleana t_parent_de t_dos_puntos statements_block t_punto_coma pero_si sino{$$= new NodoEstructuraControl(SI,$3,$6);if($8!= 0){$$->siguienteSi=$8;}if($9!= 0){$$->InsertarUltimo($9);}}
	   ;

pero_si : t_pero t_si t_parent_iz expBooleana t_parent_de t_dos_puntos statements_block t_punto_coma pero_si{$$= new NodoEstructuraControl(PERO_SI,$4,$7);if($9!= 0){$$->siguienteSi=$9;}} 
	   |{$$=0;}
	   ;
sino : t_sino t_dos_puntos statements_block t_punto_coma{$$= new NodoEstructuraControl(SINO,0,$3);}
	   |{$$=0;}
	   ;
tipo_while: t_mientras t_parent_iz expBooleana t_parent_de t_dos_puntos statements_block t_punto_coma {$$= new NodoEstructuraControl(MIENTRAS,$3,$6); }
	    ;

// como declaracion_for devuelve un NodoVarLocal y me intersa el id de esa declaracion entonces se saca desde $3
tipo_for: t_para t_parent_iz declaracion_for t_hasta limite_for t_coma exp_cambio t_parent_de t_dos_puntos statements_block t_punto_coma {NodoExpresion* comp = new NodoExpresion($3->variables->at(0),$2,DIFERENTE);$$= new NodoEstructuraControl(PARA,comp,$10);$$->declaracion= $3;$$->bloque->push_back($7);cout<<"fin tipo for\n";}
	  ;	  


declaracion_for: t_entero t_id t_igual_a exp_matem {listaVar* var= new listaVar;var->push_back(new NodoAsignacion(new NodoIdentificador(*$2),$4));$$=new NodoDeclaracionVar(*$1,var);delete $1;delete $2;}
	 	 |t_entero t_id t_igual_a t_id {listaVar* var= new listaVar;var->push_back(new NodoAsignacion(new NodoIdentificador(*$2),new NodoIdentificador(*$4) ) );$$=new NodoDeclaracionVar(*$1,var);delete $1;delete $2;delete $4;}
		 ;
// crea directamente los nodos para: variable=variable +1
exp_cambio: t_id t_mas t_mas {NodoIdentificador* id= new NodoIdentificador(*$1);$$= new NodoAsignacion(id, new NodoExpresion(id,new NodoEntero(1),SUMA) ); delete $1;}
	   |t_id t_menos t_menos{NodoIdentificador* id= new NodoIdentificador(*$1);$$= new NodoAsignacion(id, new NodoExpresion(id,new NodoEntero(1),RESTA) ); delete $1;}
	    ;

limite_for: t_id {new NodoIdentificador(*$1);delete $1;}
	    |exp_matem{$$=$1;}
	    ;

/*********************************		BLOQUE PARA CODIGO DENTRO DE FUNCIONES*/	

statements_block: statements_block var_declaration {$$->push_back(new NodoVarLocal($2));}
        	| statements_block id_init {$$->push_back($2);}
		| statements_block estruc_control{$$->push_back($2);}
		| statements_block llamado_funcion{$$->push_back($2);}
		| id_init {$$ = new listaVar; $$->push_back($1);}
		| estruc_control{$$ = new listaVar; $$->push_back($1);}
		| {$$ = new listaVar;}
		| llamado_funcion{$$ = new listaVar; $$->push_back($1);}
		| var_declaration {$$ = new listaVar; $$->push_back(new NodoVarLocal($1));}
	    	;

id_init: t_id t_igual_a t_id t_punto_coma {$$ = new NodoAsignacion(new NodoIdentificador(*$1), new NodoIdentificador(*$3));delete $1;delete $3;}
	 |t_id t_igual_a exp_matem t_punto_coma {$$ = new NodoAsignacion(new NodoIdentificador(*$1), $3);delete $1;} 
	 |t_id t_igual_a exp_Hilera t_punto_coma {$$ = new NodoAsignacion(new NodoIdentificador(*$1), $3);delete $1;}
	 |t_id t_igual_a expBooleana t_punto_coma {$$ = new NodoAsignacion(new NodoIdentificador(*$1), $3);delete $1;}
	 ;


/*********************************		LLAMADO DE FUNCIONES*/
llamado_funcion: t_imprimir expr_impr t_punto_coma{listaLlamadoFun *lf = new listaLlamadoFun;lf->push_back($2);$$ = new NodoLlamadoFuncion(*$1,lf);delete $1;}
		 |t_escanear t_id t_punto_coma{listaLlamadoFun *lf = new listaLlamadoFun;lf->push_back(new NodoIdentificador(*$2));$$ = new NodoLlamadoFuncion(*$1,lf); delete $1;delete $2;}
		 |t_id param_input t_punto_coma{$$ = new NodoLlamadoFuncion(*$1, $2); delete $1;}
		 ;

expr_impr: exp_Hilera{$$ = $1;}
	   |exp_matem{$$ = $1;}
	   |t_id {$$ = new NodoIdentificador(*$1); delete $1;}
	   ;

param_input: t_id {$$ = new listaLlamadoFun; $$->push_back(new NodoIdentificador(*$1)); delete $1;}
	     |param_input t_coma t_id{$$->push_back(new NodoIdentificador(*$3)); delete $3;}
	     ;


%%
int main(int argc, char **argv){
	++argv, --argc;
	if ( argc > 0 ) {
		yyin = fopen( argv[0], "r" );
	} else {
		yyin = stdin;
	}
	yyparse();

	map<string, ListaSimbolos*> *tablaSimbolos = new map<string, ListaSimbolos*>();
	programa->cargarTablaSimbolos(tablaSimbolos);

	/** Impresion del arbol **/	
	ListaHil* lista = new ListaHil;
    	lista->resize(15,"");

    	cout<<"INICIO   O,..,O"<<endl<<endl;


	programa->printValores(lista,0,0,"r");
	cout<<"INICIO   |     |"<<endl<<endl;

    	for(int i=0; i< lista->size();i++)
    	{
           cout<<lista->at(i)<<endl;
    	}

    	cout<<endl<<"Final   |,..,/"<<endl;

    	delete tablaSimbolos;
	
}

void yyerror(const char * s){

	cout<< "ERROR" <<endl;
	cout<< s <<endl;
	cout<<endl;
}
