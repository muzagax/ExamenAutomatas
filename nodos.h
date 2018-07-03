#include <iostream>
#include "ListaSimbolos.cpp"
#include <vector>
#include <string>


using namespace std;

/** Macros para los operadores  **/
#define SUMA 1 
#define RESTA 2
#define MULTI 3
#define DIV 4
#define MOD 5
#define AND 6
#define OR 7
#define NEG 8
#define MENOR 9
#define MENOR_IGUAL 10
#define MAYOR 11
#define MAYOR_IGUAL 12
#define DIFERENTE 13
#define IGUAL 14
#define SI 15
#define PERO_SI 16
#define SINO 17
#define PARA 18
#define MIENTRAS 19



class NodoInstruccion;
class NodoDeclaracion;


typedef vector<NodoDeclaracion*> listaDeclaraciones;
typedef	vector<NodoInstruccion*> dimensionesMatriz;
typedef	vector< vector<NodoInstruccion*> > matrizValores;
typedef vector<NodoInstruccion*> bloqueInstrucciones;
typedef vector<NodoDeclaracion*> parametrosFuncion;
typedef vector<NodoInstruccion*> listaVar;
typedef vector<NodoInstruccion*> listaLlamadoFun;

typedef vector<string> ListaHil;



class Nodo {
public:
    virtual ~Nodo() {}
    virtual void printValores(ListaHil* niveles, int nivel,int numHijo,string padre)
        {

        }
    virtual bool cargarTablaSimbolos(map<string, ListaSimbolos*> *tablaSimbolos){
        return true;
    }
    virtual bool cargarTablaSimbolos(string nombreFuncion, map<string, ListaSimbolos*> *tablaSimbolos){
        return true;
    }
    virtual bool cargarTablaSimbolos(string nombreFuncion, map<string, ListaSimbolos*> *tablaSimbolos, string token){
        return true;
    }
    virtual bool cargarTablaSimbolos(map<string, ListaSimbolos*> *tablaSimbolos, string tipoVar){
        return true;
    }
};


class NodoInstruccion: public Nodo
{
    public:
    void printValores(ListaHil* niveles, int nivel,int numHijo,string padre){}
    bool cargarTablaSimbolos(map<string, ListaSimbolos*> *tablaSimbolos){
        return true;
    }
    bool cargarTablaSimbolos(string nombreFuncion, map<string, ListaSimbolos*> *tablaSimbolos){
        return true;
    }
    bool cargarTablaSimbolos(string nombreFuncion, map<string, ListaSimbolos*> *tablaSimbolos, string token){
        return true;
    }
    bool cargarTablaSimbolos(map<string, ListaSimbolos*> *tablaSimbolos, string tipoVar){
        return true;
    }
};

class NodoDeclaracion: public Nodo
{
    public:
    void printValores(ListaHil* niveles, int nivel,int numHijo,string padre){}
    bool cargarTablaSimbolos(map<string, ListaSimbolos*> *tablaSimbolos){
        return true;
    }
    bool cargarTablaSimbolos(string nombreFuncion, map<string, ListaSimbolos*> *tablaSimbolos){
        return true;
    }
    bool cargarTablaSimbolos(string nombreFuncion, map<string, ListaSimbolos*> *tablaSimbolos, string token){
        return true;
    }
    bool cargarTablaSimbolos(map<string, ListaSimbolos*> *tablaSimbolos, string tipoVar){
        return true;
    }
};



/** ---- Variables --- **/
class NodoVariable: public NodoInstruccion
{
};


class NodoEntero : public NodoVariable
{
public:
    int valor;
    NodoEntero(int valor) : valor(valor) { }
    void printValores(ListaHil* niveles, int nivel,int numHijo,string padre)
        {
            string info ="[N]" + padre + "|" + to_string(numHijo) + ":" + to_string(valor) + "   ";
            niveles->at(nivel)+=info;
        }

};

class NodoDecimal : public NodoVariable
{
public:
    float valor;
    NodoDecimal(float valor) : valor(valor) { }
    void printValores(ListaHil* niveles, int nivel,int numHijo,string padre)
        {
            string info ="[N]"+padre+"|"+to_string(numHijo)+":"+to_string(valor)+"   ";
            niveles->at(nivel)+=info;
        }

};

class NodoHilera : public NodoVariable
{
public:
	string valor;
	NodoHilera(string valor) : valor(valor){}
    void printValores(ListaHil* niveles, int nivel,int numHijo,string padre)
        {	      
            string info ="[N]"+padre+"|"+to_string(numHijo)+":"+valor+"   ";
            niveles->at(nivel)+=info;
        }
};

class NodoIdentificador : public NodoVariable
{
public:
	string valor;
	NodoIdentificador(string valor) : valor(valor){}

    bool cargarTablaSimbolos(map<string, ListaSimbolos*> *tablaSimbolos){
        map<string, ListaSimbolos*>::iterator itContextoG = tablaSimbolos->find(valor); //itContextoG iterador contexto global
        if(itContextoG == tablaSimbolos->end()){
            ListaSimbolos *listaContexto = new ListaSimbolos();
            tablaSimbolos->insert(pair<string, ListaSimbolos*>(valor, listaContexto));
        }
         return true;
    }

    bool cargarTablaSimbolos(string nombreFuncion, map<string, ListaSimbolos*> *tablaSimbolos){
        map<string, ListaSimbolos*>::iterator itContextoG = tablaSimbolos->find(valor); //itContextoG iterador contexto global
        if(itContextoG == tablaSimbolos->end()){
            itContextoG = tablaSimbolos->find(nombreFuncion);
            ListaSimbolos *listaContexto = itContextoG->second;
            if(listaContexto->buscar(valor) == listaContexto->getFinLista()){
                cout << "Error: Este identificador no ha sido declarado: " << valor << endl;
            }
        }
        return true;
    }

     bool cargarTablaSimbolos(string nombreFuncion, map<string, ListaSimbolos*> *tablaSimbolos, string token){
        map<string, ListaSimbolos*>::iterator itContextoG = tablaSimbolos->find(valor); //itContextoG iterador contexto global
        if(itContextoG == tablaSimbolos->end()){
            itContextoG = tablaSimbolos->find(nombreFuncion);
            ListaSimbolos *listaContexto = itContextoG->second;
            if(listaContexto->buscar(valor) == listaContexto->getFinLista()){
                listaContexto->insertarNuevo(valor, token, "");
            } else {
                cout << "Error: Ya existe en este contexto una variable con este nombre " << valor << endl;
            }
        } else {
            cout << "Error: Ya existe en este contexto una variable con este nombre " << valor << endl;
        }

         return true;
    }

    bool cargarTablaSimbolos(map<string, ListaSimbolos*> *tablaSimbolos, string token){
        map<string, ListaSimbolos*>::iterator itContextoG = tablaSimbolos->find(valor); //itContextoG iterador contexto global
        if(itContextoG == tablaSimbolos->end()){
            ListaSimbolos *listaContexto = new ListaSimbolos();
            tablaSimbolos->insert(pair<string, ListaSimbolos*>(valor, listaContexto));
        }
        return true;
    }


    void printValores(ListaHil* niveles, int nivel,int numHijo,string padre)
        {
            string info ="[N]"+padre+"|"+to_string(numHijo)+":"+valor+"   ";
            niveles->at(nivel)+=info;
        }
};


class NodoBooleano : public NodoVariable
{
public:
	bool valor;
	NodoBooleano(bool valor) : valor(valor){}
    void printValores(ListaHil* niveles, int nivel,int numHijo,string padre)
        {
            string info ="[N]"+padre+"|"+to_string(numHijo)+":"+to_string(valor)+"   ";
            niveles->at(nivel)+=info;
        }
};


class NodoArray: public NodoVariable
{
	public:

	string id;
	dimensionesMatriz dimensiones;
	matrizValores valores;

	NodoArray(string id,dimensionesMatriz dimensiones,matrizValores valores):
	    id(id),dimensiones(dimensiones),valores(valores){}

    NodoArray(string id,dimensionesMatriz dimensiones):
	    id(id),dimensiones(dimensiones){}

    NodoArray(string id):
	    id(id){}
};




/** ---- Instrucciones ---- **/


class NodoEstructuraControl: public NodoInstruccion
{
	public:
    	int tipo;
	NodoInstruccion* comparacion;
	NodoEstructuraControl* siguienteSi;
	bloqueInstrucciones* bloque;
	NodoDeclaracion* declaracion;
	NodoEstructuraControl(int tipo, NodoInstruccion* comparacion, bloqueInstrucciones* bloque):
    		tipo(tipo), comparacion(comparacion), bloque(bloque) {}

	// Método para inserta en la ultima posicion de la lista de SiguienteSi.
	// Esto es en caso de tener muchos pero si: ; pero si: ; (...) y por ultimo un sino ya que
	//debido a cómo esta hecha la gramatica pueden o no hacer varios "pero si" o ninguno
	void InsertarUltimo(NodoEstructuraControl* nodo)
	{
	   if(siguienteSi != 0)
	   {
	     siguienteSi->InsertarUltimo(nodo);
	   }
	   else
	   {
	     siguienteSi= nodo;
	   }
	}

    bool cargarTablaSimbolos(string nombreFuncion, map<string, ListaSimbolos*> *tablaSimbolos){
        /** Llamado para cargarTablaSimbolos de los siguientes nodos Si **/
        if(siguienteSi != 0)
        {
           siguienteSi->cargarTablaSimbolos(nombreFuncion, tablaSimbolos);
        }
        /** Llamado para cargarTablaSimbolos de comparacion
        nota: En caso que sea tipo SINO entonces no hay comparación
        **/
        if(comparacion != 0)
        {
           comparacion->cargarTablaSimbolos(nombreFuncion, tablaSimbolos);
        }
        /** Procedo a llamar cargarTablaSimbolos de los "nodos hijos" en bloque **/
        for(int hijo = 0; hijo < bloque->size(); hijo++)
           {
                bloque->at(hijo)->cargarTablaSimbolos(nombreFuncion, tablaSimbolos);

           }
        return true;
    }

   	 void printValores(ListaHil* niveles, int nivel,int numHijo,string padre)
    	{

        string info ="[N]"+padre+"|"+to_string(numHijo)+":NEC-"+to_string(tipo)+"   ";
        niveles->at(nivel)+=info;

        /** Para sacar el nombre actual de este nodo **/
        string actual = padre+","+to_string(numHijo);
	
	cout<<"Antes de SiguenteSi "<<siguienteSi<<"\n";
	/** Llamado para printValores de los siguientes nodos Si **/
	if(siguienteSi != 0)
	{
	   siguienteSi->printValores(niveles,nivel,-2,actual);
	}

	cout<<"Antes de comparacion "<<comparacion<<"\n";	
        /** Llamado para printValor de comparacion
	    nota: En caso que sea tipo SINO entonces no hay comparación
	 **/
	if(comparacion != 0)
	{
	   comparacion->printValores(niveles, nivel+1 , -1 ,actual);
	}
	
	cout<<"Antes de bloque "<<"\n";
        /** Procedo a llamar el printValores de los "nodos hijos" en bloque **/
        for(int hijo =0; hijo< bloque->size();hijo++)
           {
                bloque->at(hijo)->printValores(niveles, nivel+1 , hijo ,actual);

           }
    	}
};


class NodoLlamadoFuncion: public NodoInstruccion
{
	public:

	string nombreFuncion;
	listaLlamadoFun* parametros;
	NodoLlamadoFuncion(string nombreFuncion, listaLlamadoFun* parametros ):
	    nombreFuncion(nombreFuncion), parametros(parametros) {}

    NodoLlamadoFuncion(string nombreFuncion ):
	    nombreFuncion(nombreFuncion){}

    bool cargarTablaSimbolos(string funcionContexto, map<string, ListaSimbolos*> *tablaSimbolos){
        map<string, ListaSimbolos*>::iterator itContextoG = tablaSimbolos->find(nombreFuncion); //itContextoG iterador contexto global
        if(itContextoG == tablaSimbolos->end()) { //Si el Nodo(lista de símbolos) Contexto no está en la tabla se agrega, y se le solicita a los hijos del nodo auto-agregarse
            cout << "Error: La función \"" << nombreFuncion << "\" no ha sido declarada" << endl;
        }
        return true;
    }

    bool cargarTablaSimbolos(map<string, ListaSimbolos*> *tablaSimbolos) {
        map<string, ListaSimbolos*>::iterator itContextoG = tablaSimbolos->find(nombreFuncion); //itContextoG iterador contexto global
        if(itContextoG != tablaSimbolos->end()) { //Si el Nodo(lista de símbolos) Contexto no está en la tabla se agrega, y se le solicita a los hijos del nodo auto-agregarse
            /** Procedo a llamar cargarTablaSimbolos de los "nodos hijos" en parametros **/
            for(int hijo =0; hijo < parametros->size(); hijo++) {
                parametros->at(hijo)->cargarTablaSimbolos(nombreFuncion, tablaSimbolos);
            }
        } else { //Si no, si está se indica el error, los nombres de funciones deben ser únicos
            cout << "Error: La función " << nombreFuncion << " no ha sido declarada" << endl;
        }
        return true;
    }

    void printValores(ListaHil* niveles, int nivel,int numHijo,string padre)
        {
            string info ="[N]"+padre+"|"+to_string(numHijo)+":NLLF-"+nombreFuncion+"   ";
            niveles->at(nivel)+=info;

            string actual = padre+","+to_string(numHijo);

            /** Procedo a llamar el printValores de los "nodos hijos" en parametros **/
            for(int hijo =0; hijo< parametros->size();hijo++)
            {
                parametros->at(hijo)->printValores(niveles, nivel+1 , hijo ,actual);

            }
        }

};


class NodoAsignacion: public NodoInstruccion
{
	public:

	NodoInstruccion* idNAsignacion; //Siempre es un NodoIdentificador
	NodoInstruccion* expresion;
	NodoAsignacion(NodoInstruccion* idNAsignacion , NodoInstruccion* expresion):
	idNAsignacion(idNAsignacion), expresion(expresion){}


    bool cargarTablaSimbolos(map<string, ListaSimbolos*> *tablaSimbolos, string tipoVar){
        idNAsignacion->cargarTablaSimbolos(tablaSimbolos, tipoVar);
         return true;
    }

    bool cargarTablaSimbolos(string nombreFuncion, map<string, ListaSimbolos*> *tablaSimbolos){
        idNAsignacion->cargarTablaSimbolos(nombreFuncion, tablaSimbolos);
        expresion->cargarTablaSimbolos(nombreFuncion, tablaSimbolos);
        return true;
    }

    bool cargarTablaSimbolos(string nombreFuncion, map<string, ListaSimbolos*> *tablaSimbolos, string token){
        idNAsignacion->cargarTablaSimbolos(nombreFuncion, tablaSimbolos, token);
        expresion->cargarTablaSimbolos(nombreFuncion, tablaSimbolos);
        return true;
    }

    void printValores(ListaHil* niveles, int nivel,int numHijo,string padre)
        {
            string info ="[N]"+padre+"|"+to_string(numHijo)+":NA   ";
            niveles->at(nivel)+=info;

            string actual = padre+","+to_string(numHijo);

            idNAsignacion->printValores(niveles, nivel+1 , 0 ,actual);
            expresion->printValores(niveles, nivel+1 , 1 ,actual);


        }
};


class NodoVarLocal: public NodoInstruccion
{
	public:

	NodoDeclaracion* variableLocal;
	NodoVarLocal(NodoDeclaracion* variableLocal): variableLocal(variableLocal) {}

    bool cargarTablaSimbolos(string nombreFuncion, map<string, ListaSimbolos*> *tablaSimbolos){
        variableLocal->cargarTablaSimbolos(nombreFuncion, tablaSimbolos);
        return true;
    }

	void printValores(ListaHil* niveles, int nivel,int numHijo,string padre)
        {
            string info ="[N]"+padre+"|"+to_string(numHijo)+":NVL    ";
            niveles->at(nivel)+=info;

            string actual = padre+","+to_string(numHijo);

            variableLocal->printValores(niveles, nivel+1 , 0 ,actual);
        }
};

class NodoExpresion: public NodoInstruccion
{
	public:
    	int operador;
	NodoInstruccion* expIz;
	NodoInstruccion* expDe;
	NodoExpresion(NodoInstruccion* expIz,NodoInstruccion* expDe, int operador):
	    expIz(expIz),expDe(expDe),operador(operador){}

    bool cargarTablaSimbolos(string nombreFuncion, map<string, ListaSimbolos*> *tablaSimbolos){
        expIz->cargarTablaSimbolos(nombreFuncion, tablaSimbolos);
        if(expDe!= 0)
        {
            expDe->cargarTablaSimbolos(nombreFuncion, tablaSimbolos);
        }
    }

    bool cargarTablaSimbolos(map<string, ListaSimbolos*> *tablaSimbolos){
        expIz->cargarTablaSimbolos(tablaSimbolos);
        if(expDe!= 0)
        {
            expDe->cargarTablaSimbolos(tablaSimbolos);
        }
        return true;
    }

    void printValores(ListaHil* niveles, int nivel,int numHijo,string padre)
    {

        string info ="[N]"+padre+"|"+to_string(numHijo)+":NExp"+to_string(operador)+"   ";
        niveles->at(nivel)+=info;

        string actual = padre+","+to_string(numHijo);
	
	    expIz->printValores(niveles, nivel+1 , 0 ,actual);

	    if(expDe!= 0)
	    {
               expDe->printValores(niveles, nivel+1 , 1 ,actual);
	    }


        }
};






/** --- Declaraciones --- **/


class NodoDeclaracionFunc: public NodoDeclaracion
{

	public:

	string tipoRetorno;
	string nombreFuncion;
	parametrosFuncion* parametros;
	bloqueInstrucciones* codigo;

	NodoDeclaracionFunc(string tipoRetorno,string nombreFuncion,
                     parametrosFuncion* parametros,bloqueInstrucciones* codigo):
        tipoRetorno(tipoRetorno),nombreFuncion(nombreFuncion),parametros(parametros),codigo(codigo){}

	NodoDeclaracionFunc(string tipoRetorno,string nombreFuncion,bloqueInstrucciones* codigo):
        tipoRetorno(tipoRetorno),nombreFuncion(nombreFuncion),codigo(codigo){}

    bool cargarTablaSimbolos(map<string, ListaSimbolos*> *tablaSimbolos) {
        if(tablaSimbolos->find(nombreFuncion) == tablaSimbolos->end()){ //Si el Nodo(lista de símbolos) Contexto no está en la tabla se agrega, y se le solicita a los hijos del nodo auto-agregarse
            ListaSimbolos *listaContexto = new ListaSimbolos();
            tablaSimbolos->insert(pair<string, ListaSimbolos*>(nombreFuncion, listaContexto));

            /** Procedo a llamar cargarTablaSimbolos de los "nodos hijos" en parametros **/
            for(int hijo =0; hijo< parametros->size(); hijo++) {
                parametros->at(hijo)->cargarTablaSimbolos(nombreFuncion, tablaSimbolos);

            }

            /** Procedo a llamar cargarTablaSimbolos de los "nodos hijos" en codigo **/
             for(int hijo2 = 0; hijo2 < codigo->size(); hijo2++) {
                 codigo->at(hijo2)->cargarTablaSimbolos(nombreFuncion, tablaSimbolos);
            }
        } else { //Si no, si está se indica el error, los nombres de funciones deben ser únicos
            cout << "Error: Ya existe una función en el contexto global con el nombre  \"" << nombreFuncion << "\"" << endl;
        }
        return true;
    }

    void printValores(ListaHil* niveles, int nivel,int numHijo,string padre)
        {
            string info ="[N]"+padre+"|"+to_string(numHijo)+":NDF-"+tipoRetorno+"+"+nombreFuncion+"   ";
            niveles->at(nivel)+=info;

            string actual = padre+","+to_string(numHijo);

            /** Procedo a llamar el printValores de los "nodos hijos" en parametros **/
            for(int hijo =0; hijo< parametros->size();hijo++)
            {
                parametros->at(hijo)->printValores(niveles, nivel+1 , (hijo+1)*-1 ,actual);

            }

            /** Procedo a llamar el printValores de los "nodos hijos" en codigo **/
            for(int hijo2 =0; hijo2< codigo->size();hijo2++)
            {
                codigo->at(hijo2)->printValores(niveles, nivel+1 , hijo2 ,actual);

            }
        }
};

class NodoDeclaracionVar: public NodoDeclaracion
{
	public:

	string tipoVar;
	listaVar* variables; //Pueden haber nodos NodoIdentificador y nodos NodoAsignacion
	NodoDeclaracionVar(string tipoVar,listaVar* variables):
	    tipoVar(tipoVar), variables(variables){}

    bool cargarTablaSimbolos(map<string, ListaSimbolos*> *tablaSimbolos) {
        /** Procedo a llamar cargarTablaSimbolos de los "nodos hijos" en variables **/
        for(int hijo = 0; hijo < variables->size(); hijo++) {
            variables->at(hijo)->cargarTablaSimbolos(tablaSimbolos, tipoVar);
        }
        return true;
    }

    bool cargarTablaSimbolos(string nombreFuncion, map<string, ListaSimbolos*> *tablaSimbolos){
        /** Procedo a llamar cargarTablaSimbolos de los "nodos hijos" en variables **/
        for(int hijo = 0; hijo < variables->size(); hijo++) {
            variables->at(hijo)->cargarTablaSimbolos(nombreFuncion, tablaSimbolos, tipoVar);
        }
        return true;
    }

    void printValores(ListaHil* niveles, int nivel,int numHijo,string padre)
        {
            string info ="[N]"+padre+"|"+to_string(numHijo)+":NDV-"+tipoVar+"   ";
            niveles->at(nivel)+=info;

            string actual = padre+","+to_string(numHijo);

            /** Procedo a llamar el printValores de los "nodos hijos" en variables **/
            for(int hijo =0; hijo< variables->size();hijo++)
            {
                variables->at(hijo)->printValores(niveles, nivel+1 , hijo ,actual);

            }
        }

};



/**  --- Controlador/Raiz --- **/
class NodoControlador: public Nodo
{
	public:

	NodoInstruccion* iniciarNombreFuncion;
    listaDeclaraciones declaraciones;


    bool cargarTablaSimbolos(map<string, ListaSimbolos*> *tablaSimbolos){
        for(int hijo =0; hijo < declaraciones.size(); hijo++) {
            declaraciones.at(hijo)->cargarTablaSimbolos(tablaSimbolos);
        }
        iniciarNombreFuncion->cargarTablaSimbolos(tablaSimbolos);
        return true;
    }

   	void printValores(ListaHil* niveles, int nivel,int numHijo,string padre)
        {
		
            string info ="[N]"+padre+"|"+to_string(numHijo)+":NControlador"+"   ";
            niveles->at(nivel)+=info;
		
            string actual = padre;
		
            //iniciarNombreFuncion->printValores(niveles, nivel+1 , -1 ,actual);
		

            /** Procedo a llamar el printValores de los "nodos hijos" en declaraciones **/
            for(int hijo =0; hijo< declaraciones.size();hijo++)
            {
                declaraciones.at(hijo)->printValores(niveles, nivel+1 , hijo ,actual);

            }
        }
};
