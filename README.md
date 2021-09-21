# EvaluadorExpresionesAritmeticas-v2
Pilas, recursividad, arreglos, expresiones infijas, expresiones postfijas

[1] Ingresar cualquier expresión infija con números
[2] Pueda consultar la expresión infija ingresada
[3] Convertir la expresión ingresada a postfija
[4] Mostrar operador en la cima de la pila
[5] Mostrar operadores en la Pila
[6] Vaciar pila y reiniciar expresiones
[7] Resultado final de la expresión infija
[8] Salir

Limitaciones reconocidas del programa:
> Se trabaja con arreglos de char, por lo que operaciones con numeros que no sean enteros no se pueden realizar.
> No es recomendable ingresar valores que no sean enteros, si se ingresa algo como A+B o 1.5+3, si bien en el primer ejemplo si se podrá realizar una expresión postfija de la expresión ingresada, en ninguno de los casos se podrá hacer una operación.
> Los resultados que se muestren en pantalla siempre van a ser enteros, si se hace una operación que de como resultado un número no entero entonces este se va a redondear (puesto que se hizo uso de valores int y que el valor de retorno de la función que devuelve el resultado es un int).
> Hay un límite para el tamaño de las expresiones ingresadas (máximo 20 caracteres ingresados).

Errores encontrados al momento de ejecutar el programa:
> Si ingresas la expresión infija (2^3*4/5-6) te devuelve la expresión postfija 23^4*5/6-5G. Sinceramente no sé a qué se deba que aparezca ese 5G al final XD
> Considerando lo de arriba, no se van a poder realizar operaciones con esa expresión.
