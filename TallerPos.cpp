#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define tamano 100
#include <math.h>

//Estructuras

struct Nodo{
    int dato;
    Nodo *siguiente;
};


//Prototipo de Funciones

void menu();
void ingresarExpresion(char [tamano]);
void mostrarExpresion(char [tamano]);
bool pilaVacia(Nodo *pila);
void hacerOperacionPostfijo(Nodo *&, char [tamano]);
void mostrarResultadosOperacionPostfijo(Nodo *&, char [tamano]);
float hacerOperacion(float, float, char);
bool esNumero(char);
bool esOperador(char);
bool esEspacio(char);
void insertarElementoPila(Nodo *&, float);
float eliminarElementoPila(Nodo *&);
void imprimirPila(Nodo *);
float convertirCadenaNumero(char [tamano]);

int main(){
    menu();
    return 0;
}

void menu(){
    Nodo *pila = NULL;
    char Arreglo[tamano];
    int opcion;
    do{
        printf("\n\t\t---MENU NOTACION POSTFIJA---\n\n");
        printf("\n1. Ingresar Expresion");
        printf("\n2. Mostrar Expresion Ingresada");
        printf("\n3. Hacer Operacion Postfija");
        printf("\n4. Mostrar Resultados Operacion Postfija");
        printf("\n0. Salir");
        printf("\nIngrese una opcion: ");
        scanf("%d", &opcion);
        switch(opcion){
            case 1: ingresarExpresion(Arreglo);
                break;
            case 2: mostrarExpresion(Arreglo);
                break;
            case 3: hacerOperacionPostfijo(pila, Arreglo);
                    printf("\nOperacion Realizada Correctamente\n\n");
                break;
            case 4: mostrarResultadosOperacionPostfijo(pila, Arreglo);
                    printf("\n\n");
                break;
            case 0: exit(0);
                break;
            default: printf("\nNo es una opcion valida, intentelo de nuevo\n");
                break;
        }
        system("pause");
        system("cls");
    }while(opcion != 0);
}

void ingresarExpresion(char Arreglo[tamano]){
    fflush(stdin);
    int longitud;
    printf("\n Ingrese la expresion en postfijo: ");
    fgets(Arreglo, tamano, stdin);
    longitud = strlen(Arreglo);
    printf("\n Estructura almacenada con exito \n");
    printf("\nExpresion ingresada: %s\n", Arreglo);
}
void mostrarExpresion(char Arreglo[tamano]){
    int longitud;
    longitud = strlen(Arreglo);
    printf("\nLongitud de la expresion: %d", longitud);
    printf("\nExpresion ingresada: %s\n", Arreglo);
}
bool pilaVacia(Nodo *pila){
    return (pila==NULL) ? true:false;
}
void hacerOperacionPostfijo(Nodo *&pila, char Arreglo[tamano]){
    int i, longitud, j = 0;
    float numero_insertar,a,b,c;
    char numero[tamano];
    longitud = strlen(Arreglo);
    for(i = 0; i < longitud; i++){
        if(esNumero(Arreglo[i])){
            numero[j] = Arreglo[i];
            j++;
        }
        if(esEspacio(Arreglo[i])){
            numero_insertar = convertirCadenaNumero(numero);
            insertarElementoPila(pila, numero_insertar);
            j=0;
        }
        if(esOperador(Arreglo[i])){
            a=eliminarElementoPila(pila);
            b=eliminarElementoPila(pila);
            c=hacerOperacion(a,b,Arreglo[i]);
            insertarElementoPila(pila,c);

            i++;
        }
    }
}
float hacerOperacion(float a, float b, char operador){
    int op =operador;
    float c;

     switch(op)
    {
    case 43:
        c=a+b;
    break;
    case 45:
        c=a-b;
    break;
    case 47:
        c=a/b;
    break;
    case 94:
        c=pow(a,b);
    break;
    case 42:
        c=a*b;
    break;
    }
    return c;
}
bool esNumero(char valor){
    int numero=valor;
    return (numero>47 && numero<58) ? true: false;
}
bool esOperador(char valor){
    int numero=valor;
    return (numero==43 || numero==45 || numero==42 || numero==47 || numero==94) ? true: false;
}
bool esEspacio(char valor){
    int numero=valor;
    return (numero==32) ? true: false;
}

void insertarElementoPila(Nodo *&pila, float n){
    Nodo *nuevo_nodo=(Nodo*)malloc(sizeof(Nodo));
    nuevo_nodo->dato=n;
    nuevo_nodo->siguiente=pila;
    pila=nuevo_nodo;
}
 float eliminarElementoPila(Nodo *&pila){
    float n;
    Nodo *aux=pila;
    n=aux->dato;
    pila=aux->siguiente;
    free(aux);
    return n;
}
void imprimirPila(Nodo *pila){
    while(pilaVacia(pila)!=true);
    {
        printf("%d",pila->dato);
        pila=pila->siguiente;
    }
}
void mostrarResultadosOperacionPostfijo(Nodo *&pila, char Arreglo[tamano]){
    printf("%s = %d",Arreglo, pila->dato);
}
float convertirCadenaNumero(char numero[tamano]){
    float num;
    num = atoi(numero);
    return num;
}
