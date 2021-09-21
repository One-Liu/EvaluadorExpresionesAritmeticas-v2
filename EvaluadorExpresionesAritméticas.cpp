#include<iostream>
using namespace std;
#include "Pila.h"
#include <cmath>

void EvaluarExpresionesAritmeticas(char[],char[],int,int,int,int,bool);
int SacarOperadores(char[],int);
void RevisarPila(char[],int);
void MostrarPostfija(char[],int);
void MostrarInfija(char[],int);
void ReiniciarExpresiones(char[],int);
bool RevisarPostfija(char[],int);
int ResultadoExpresionPostfija(char[],int,int,Pila,int,int);
int HacerOperacion(char[],int,int,int);

Pila p;
Pila pOperadores;

int main() {
	int opc;
	int tamanio = 20;
	char expresionInfija[tamanio];
	char expresionPostfija[tamanio];
	//char caracter;
	Pila pAyuda;
	do{
		cout<<"Ingrese una opcion:"<<endl;
		cout<<"[1] Ingresar cualquier expresion infija con numeros"<<endl;
		cout<<"[2] Pueda consultar la expresion infija ingresada"<<endl;
		cout<<"[3] Convertir la expresion ingresada a postfija"<<endl;
		cout<<"[4] Mostrar operador en la cima de la pila"<<endl;
		cout<<"[5] Mostrar operadores en la pila"<<endl;
		cout<<"[6] Vaciar pila y reiniciar expresiones"<<endl;
		cout<<"[7] Resultado final de la expresion infija"<<endl;
		cout<<"[8] Salir"<<endl;
		cout<<">";
		cin>>opc;
		switch(opc) {
			case 1:
				p.Inicializar();
				pAyuda.Inicializar();
				cout<<"Ingrese una expresion infija: ";
				cin>>expresionInfija;
				break;
			case 2:
				if(expresionInfija[0] == NULL) {
					cout<<"No hay ninguna expresion infija ingresada."<<endl;
				}else {
					cout<<"La expresion infija es: ";
					MostrarInfija(expresionInfija,0);
					cout<<endl;
				}
				break;
			case 3:
				if(expresionInfija[0] == NULL) {
					cout<<"No hay ninguna expresion infija ingresada."<<endl;
				}else {
					cout<<"Se convirtio la expresion ";
					MostrarInfija(expresionInfija,0);
					cout<<" a la expresion postfija ";
					EvaluarExpresionesAritmeticas(expresionInfija,expresionPostfija,0,0,0,0,false);
				}
				break;
			case 4:
				if(pOperadores.Cima() != -1) {
					cout<<"El operador que se encuentra en la cima de la pila es: "<<pOperadores.CimaChar()<<endl;
				}else {
					cout<<"La pila esta vacia!"<<endl;
				}
				break;
			case 5:
				if(pOperadores.Cima() != -1) {
					cout<<"Los datos de la pila son: ";
					pOperadores.MostrarDatos(0);
					cout<<endl;
				}else {
					cout<<"La pila esta vacia!"<<endl;
				}
				break;
			case 6:
				p.LimpiarPila();
				pOperadores.LimpiarPila();
				cout<<"La pila se ha limpiado."<<endl;
				ReiniciarExpresiones(expresionInfija,0);
				ReiniciarExpresiones(expresionPostfija,0);
				cout<<"Se han reiniciado las expresiones."<<endl;
				break;
			case 7:
				if(expresionPostfija[0] == NULL) {
					cout<<"Convierta a expresion postfija para poder mostrar un resultado!"<<endl;
				}else {
					if(!RevisarPostfija(expresionPostfija,0)) {
						cout<<"Ingrese valores validos!"<<endl;
					}else {
						pAyuda.LimpiarPila();
						cout<<"El resultado de la operacion es: "<<ResultadoExpresionPostfija(expresionPostfija,0,0,pAyuda,0,0)<<endl;
					}
				}
				break;
			case 8:
				cout<<"Saliendo del programa..."<<endl;
				break;
			default:
				cout<<"Ingrese una opcion valida!"<<endl;
				break;
		}
		system("pause");
		system("cls");
	}while(opc != 8);
	return 0;
}

void EvaluarExpresionesAritmeticas(char expresionInfija[],char expresionPostfija[],int posInfija,int prioridadInfija,int prioridadPila,int posPostfija,bool valorCambiado) {
	if(expresionInfija[posInfija]==NULL) {
		if(p.Cima() != -1) {
			pOperadores = p;
		}
		RevisarPila(expresionPostfija,posPostfija);
		return;
	}else {
		if(valorCambiado == false) {
			switch(expresionInfija[posInfija]) {
				case '^':
					prioridadInfija = 4;
					valorCambiado = true;
					break;
				case '*':
				case '/':
					prioridadInfija = 2;
					valorCambiado = true;
					break;
				case '-':
				case '+':
					prioridadInfija = 1;
					valorCambiado = true;
					break;
				case '(':
					prioridadInfija = 5;
					valorCambiado = true;
					break;
				case ')':
					if(expresionInfija[posInfija+1] == NULL) {
						pOperadores = p;
					}
					posPostfija = SacarOperadores(expresionPostfija,posPostfija);
					//Para que no caiga en un bucle si la última posición es un ')'
					++posInfija;
					break;
				default:
					expresionPostfija[posPostfija] = expresionInfija[posInfija];
					++posInfija;
					++posPostfija;
					break;
			}
		}
		
		if(valorCambiado == true) {
			if(p.PilaVacia() == false) {
				if(prioridadInfija > prioridadPila) {
					p.Push(expresionInfija[posInfija]);
					++posInfija;
					valorCambiado = false;
				}
				if(prioridadInfija <= prioridadPila) {
					expresionPostfija[posPostfija] = p.CimaChar();
					p.Pop();
					++posPostfija;
				}
			}else {
				p.Push(expresionInfija[posInfija]);
				++posInfija;
				valorCambiado = false;
			}	
			switch(p.CimaChar()) {
				case '^':
					prioridadPila = 3;
					break;
				case '*':
				case '/':
					prioridadPila = 2;
					break;
				case '+':
				case '-':
					prioridadPila = 1;
					break;
				case '(':
					prioridadPila = 0;
					break;
			}
		}
		EvaluarExpresionesAritmeticas(expresionInfija,expresionPostfija,posInfija,prioridadInfija,prioridadPila,posPostfija,valorCambiado);
	}
}

int SacarOperadores(char expresionPostfija[], int pos) {
	if(p.CimaChar() == '(') {
		p.Pop();
		return pos;
	}else {
		if(p.CimaChar() != '(' && p.CimaChar() != ')') {
			expresionPostfija[pos] = p.CimaChar();
			++pos;
		}
		p.Pop();
		SacarOperadores(expresionPostfija,pos);
	}
}

void RevisarPila(char expresionPostfija[], int pos) {
	if(p.PilaVacia()) {
		MostrarPostfija(expresionPostfija,0);
		cout<<endl;
		return;
	}else {
		if(p.CimaChar() != '(' && p.CimaChar() != ')') {
			expresionPostfija[pos] = p.CimaChar();
			pos++;
		}
		p.Pop();
		RevisarPila(expresionPostfija,pos);
	}
}

void MostrarPostfija(char expresionPostfija[], int cont) {
	if(expresionPostfija[cont] == NULL) {
		return;
	}else {
		cout<<expresionPostfija[cont];
		MostrarPostfija(expresionPostfija,++cont);
	}
}

void MostrarInfija(char expresionInfija[], int pos) {
	if(expresionInfija[pos] == NULL) {
		return;
	}else {
		cout<<expresionInfija[pos];
		MostrarInfija(expresionInfija,++pos);
	}
}

void ReiniciarExpresiones(char expresion[], int pos) {
	if(expresion[pos] == NULL) {
		return;
	}else {
		expresion[pos] = NULL;
		ReiniciarExpresiones(expresion,++pos);
	}
}

bool RevisarPostfija(char expresionPostfija[], int pos) {
	if(expresionPostfija[pos] == NULL) {
		return true;
	}else {
		if(expresionPostfija[pos] < 48 || expresionPostfija[pos] > 57) {
			switch(expresionPostfija[pos]) {
				case '^':
				case '*':
				case '/':
				case '+':
				case '-':
					break;
				default:
					//Si la expresion postfija tiene algun elemento distinto de un operador o un int, regresa false
					return false;
					break;
			}
		}
		RevisarPostfija(expresionPostfija,++pos);
	}
}

//Se hace uso de una pila de apoyo en la cual se ingresan 2 operandos, se hace la operacion, se eliminan de la pila y el resultado
//de la operacion se almacena en la pila. Posteriormente se repite el ciclo.
int ResultadoExpresionPostfija(char expresionPostfija[], int pos, int resultado, Pila pAyuda, int operando1, int operando2) {
	if(expresionPostfija[pos] == NULL) {
		return operando2;
	}else {
		switch(expresionPostfija[pos]) {
			case '^':
			case '*':
			case '/':
			case '+':
			case '-':
				//Elimina los numeros con los que se operó y guarda su resultado en la pila
				operando1 = pAyuda.CimaChar();
				pAyuda.Pop();
				operando2 = pAyuda.CimaChar();
				pAyuda.Pop();
				operando2 = HacerOperacion(expresionPostfija,pos,operando2,operando1);
				pAyuda.Push(operando2);
				break;
			default:
				//Se pone el -'0' ya que así toma el valor del int de acuerdo al código ASCII
				pAyuda.Push(expresionPostfija[pos]-'0');
				break;
		}
		ResultadoExpresionPostfija(expresionPostfija,++pos,resultado,pAyuda,operando1,operando2);
	}
}

int HacerOperacion(char expresionPostfija[], int posOperador, int operando1, int operando2) {
	switch(expresionPostfija[posOperador]) {
		case '^':
			operando1 = pow(operando1,operando2);
			break;
		case '*':
			operando1 = operando1 * operando2;
			break;
		case '/':
			operando1 = operando1 / operando2;
			break;
		case '+':
			operando1 = operando1 + operando2;
			break;
		case '-':
			operando1 = operando1 - operando2;
			break;
	}
	return operando1;	
}
