/* Clase Símbolo, el cual compone cada uno de los elementos de la lista, la cual se utiliza para la lista de símbolos */
class Simbolo {
	private:
	public:
	    string identificador;
	    string token;
	    string valor;
	    list<Simbolo*> *listSH; //Puntero a una lista de Símbolos Hijos que tienen a este Simbolo como padre (ie: contexto)

	Simbolo() {

	}

	~Simbolo() {
		
	}
};