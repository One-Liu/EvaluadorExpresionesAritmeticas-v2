#include<iostream>
using namespace std;
#include <cstddef>

class Pila {
	private:
		int cima;
		int fondo = -1;
		int tope;
		char array[20];
		
		bool PilaLlena() {
			if(cima <= tope) {
				return false;
			}else {
				return true; //Si la pila esta llena regresa true, si no, regresa false
			}
		}
		
	public:
		//El m�todo PilaVac�a se hizo p�blico para poder ser capaces de saber si la Pila est� vac�a directamente
		bool PilaVacia() {
			if(cima-1 == fondo) {
				return true; //Si la pila esta vac�a regresa true, si no, regresa false
			}else {
				return false;
			}
		}
		
		void Inicializar() { //Sirve para inicializar los contadores y topes
			cima = 0;
			tope = (SizePila()) - 1;
			return;
		}
		
		int Push(char dato) {
			if(!PilaLlena()) {
				array[cima] = dato; 
				++cima;
				return 0; //Se insert� el elemento
			}else {
				return -1; //Indica que la pila est� llena
			}
		}
		
		int Pop() {
			if(!PilaVacia()) {
				array[cima-1] = NULL;
				--cima;
				return 0; //Elemento eliminado correctamente
			}else {
				return -1; //Indica que la pila est� vac�a
			}
		}
		
		//Se modific� el tipo del m�todo a char para que regresara el caracter que se encuentra en la cima del array
		//Se usa el m�todo PilaVac�a antes de llamar a este m�todo
		char CimaChar() {
			return array[cima-1]; //Valor almacenado en la cima
		}
		
		int Cima() {
			if(!PilaVacia()) {
				return cima; //Valor de la cima
			}else {
				return -1; //Pila vac�a
			}
		}
		
		void LimpiarPila() {
			if(PilaVacia()) {
				Inicializar();
				return;
			}else {
				Pop();
				LimpiarPila();
			}
			//Eliminar todos los elementos de la pila
		}
		
		int SizePila() {
			return sizeof(array)/sizeof(*array); //Devolver� el tama�o de la pila declarada
		}
		
		void MostrarDatos(int i) {
			//Recorre todos los elementos de la pila por medio de i (recursividad)
			if(i == cima) {
				return;
			}else {
				cout<<array[i];
				MostrarDatos(++i);
			}
		}
};
