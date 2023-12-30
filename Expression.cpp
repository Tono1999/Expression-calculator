/********************************************************************
Una calculadora de expresiones 

By
Angel Antonio Mendez Hernandez
********************************************************************/

#include <iostream>
#include <string>
#include <cctype>
#include <stack>
using namespace std;

float operacion(float a, float b, char operador){
    switch(operador){
        case '*':
            return a*b;
        case '/':
            return a/b;
        case '+':
            return a+b;
        case '-':
            return a-b;
        default:
            return 0;
    }
}

int jerarquia(char operador) {
    if(operador=='+'||operador=='-')
        return 1;
    else if(operador=='*'||operador=='/')
        return 2;
    return 0;
}

float evaluar(const string& expresion) {
    stack<float> valores;
    stack<char> operadores;
    size_t lim=expresion.length();
    for(size_t i=0; i<lim; ++i) {
        if(isdigit(expresion[i])||expresion[i]=='.'){
            string valor_str;
            //leemos la cadena mientras sean numeros o punto
            while(i<lim && (isdigit(expresion[i])||expresion[i]=='.')){
                valor_str+=expresion[i];
                ++i;
            }
            //convertimos la cadena a un flotante
            float valor=stof(valor_str);
            valores.push(valor);
            --i;
        }
        //para indicar una multiplicacion si hay un parentesis
        //junto a un numero
        else if(expresion[i]=='('){
            if(i > 0){
                if(isdigit(expresion[i-1]))
                    operadores.push('*');
            }
            operadores.push(expresion[i]);
        }
        //si encontramos un cierre de parentesis
        else if(expresion[i] == ')') {
            //verificamos que el stack de operadores no este vacio y
            //que si haya algo entre los parentesis
            while(!operadores.empty() && operadores.top()!='('){
                //identificamos la operacion que se hace en el parentesis
                //y la retiramos del stack
                char operador = operadores.top();
                operadores.pop();
                //identificamos los valores que se van a operar, y los
                //quitamos del stack correspondiente
                float b = valores.top();
                valores.pop();
                float a = valores.top();
                valores.pop();
                //guardamos en el stack el valor operado
                valores.push(operacion(a, b, operador));
            }
            //quitamos el parentesis que abre
            operadores.pop();
        }
        //si encontramos un operador
        else if(expresion[i]=='+'||expresion[i]=='*'||expresion[i]=='-'||expresion[i]=='/'){
            //verificamos que haya operadores y que se cumpla el orden de la jerarquia de operaciones
            while(!operadores.empty() && jerarquia(operadores.top())>=jerarquia(expresion[i])){
                //misma idea que en caso anterior
                char operador = operadores.top();
                operadores.pop();
                float b = valores.top();
                valores.pop();
                float a = valores.top();
                valores.pop();
                valores.push(operacion(a, b, operador));
            }
            operadores.push(expresion[i]);
        }
    }
    //verificamos si quedan operadores en el stack
    while(!operadores.empty()){
        //misma idea
        char operador = operadores.top();
        operadores.pop();
        float b = valores.top();
        valores.pop();
        float a = valores.top();
        valores.pop();
        valores.push(operacion(a, b, operador));
    }
    //el resultado de la expresion queda aqui
    return valores.top();
}

int main() {
    string expresion;
    cout<<"Ingrese una expresion aritmetica: ";
    getline(cin, expresion);
    float resultado = evaluar(expresion);
    cout<<"El resultado es: "<<resultado<<endl;

    return 0;
}
