/* Lista de Símbolos */
#include <cstring>
#include <iostream>
#include <list>
#include <map>
#include <string>
using namespace std;

#include "Simbolo.cpp"

class ListaSimbolos {
    private:
        list<Simbolo*> *ls; //ls: lista de símbolos

    public:
        /* Constructor */
         ListaSimbolos(){
            ls = new list<Simbolo*>;
         }

         /* Destructor */
         ~ListaSimbolos(){
            for( list<Simbolo*>::iterator it = ls->begin(); it != ls->end(); it++ ){
                delete *it;
            }
            delete ls;
        }

        /* Inserta un símbolo en la lista, si este ya existe, lo actualiza */
        list<Simbolo*>::iterator insertar(Simbolo *s) {
            list<Simbolo*>::iterator it = buscar(s->identificador);
            if(it == getFinLista()){
                ls->push_back(s);
                it = buscar(s->identificador);
            } else {
                (*it)->identificador = s->identificador;
                (*it)->token = s->token;
                (*it)->valor = s->valor;
            }
            return it;
        }

        /* Inserta un símbolo en la lista, si este ya existe, lo actualiza */
        list<Simbolo*>::iterator insertarNuevo(string identificador, string token, string valor) {
            list<Simbolo*>::iterator it = buscar(identificador);
            if(it == getFinLista()){
                Simbolo *s = new Simbolo();
                s->identificador = identificador;
                s->token = token;
                s->valor = valor;
                ls->push_back (s);
                it = buscar(s->identificador);
            } else {
                it = insertar(*it);
            }
            return it;
        }

        /* Busca un símbolo en la lista y retorna su ubicación, si no existe el fin de la lista */
        list<Simbolo*>::iterator buscar(string identificador) {
            list<Simbolo*>::iterator it = ls->begin();
            bool encontrado = false;
            while(it != ls->end() && !encontrado) {
                if(0 == (*it)->identificador.compare(identificador)) {
                    encontrado = true;
                } else {
                    it++;
                }
            }
            return it;
        }

        /* Imprime los símbolos que están la lista */
        bool imprimir() {
            if(ls->empty()){
                cout << "La lista está vacía" << endl;
            } else {
                for(list<Simbolo*>::iterator it = ls->begin(); it != ls->end(); it++){
                    cout << "Símbolo de la posición -> " << *it << endl;
                    cout << "Identificador: " << (*it)->identificador << endl;
                    cout << "Token: " << (*it)->token << endl;
                    cout << "Valor: " << (*it)->valor << endl << endl;
                }
            }
            return true;
        }

        list<Simbolo*>::iterator getInicioLista(){
            return ls->begin();
        }

        list<Simbolo*>::iterator getFinLista(){
            return ls->end();
        }

        bool listaVacia(){
            return ls->empty();
        }
}; //Fin de la clase ListaSimbolos


//Actual, usa el map.
// int main() {
//     map<string, ListaSimbolos> *tablaSimbolos = new map<string, ListaSimbolos>();
//     delete tablaSimbolos;
//     return 0;
//}







//Original
//int main(){
//    ListaSimbolos *listaSimbolos = new ListaSimbolos();
    // simbolo *s = new simbolo;

    // char identificador[] = {"Hola"};
    // char token[] = {"T_HILERA"};
    // char valor[] = {"Variable con nombre de saludo"};
    // char idABuscar[] = {"Hola"};

    // s->identificador = identificador;
    // s->token = token;
    // s->valor = valor;

    // listaSimbolos->insertar(s);
    // //listaSimbolos->imprimir();
    // cout << *(listaSimbolos->buscar(idABuscar)) << endl;

//    cout << "Presione enter para salir...";

//    cin.get();
//    delete listaSimbolos;
//    return 0;
//}