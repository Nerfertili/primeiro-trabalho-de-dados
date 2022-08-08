#include <iostream>
#include <string>
#include <stdio.h>
using namespace std;

template <class T>

class No {
    public:
        T valor;
        No *next;
 
        No(T v) {
            valor = v;
        }
};
template <class T>
class stack {
    public:
        No<T> *topo;
 
        stack() {
            topo = NULL;
        }
 
        void push(T valor){
            No<T> *aux = new No<T>(valor);
            if (topo == nullptr){
                topo = aux;
            } else {
                aux->next = topo;
                topo = aux;
            }
        }
 
        T pop(){
            if (topo != nullptr){
                T retorno = topo->valor;
                topo = topo->next;
                return  retorno;
            }else {
              T ora;
              return ora;
            }
        }
 
        T top(){
            if (topo == NULL){
              T ora;
              return ora;
            } else {
                return topo->valor;
            }
        }

      int size(){
        int size=0;
        No<T> *reserva = topo;
        while(topo != nullptr){
          topo = topo->next;
          size++;
        }
        topo = reserva;
        return size;
      }
 
};

int main() {
  
  string cont;
  cout << "coloque a conta que deseja fazer no formato RPN:\n";
  getline(cin, cont);
  
  stack<char> operators;
  
  for(int i=(cont.size()-1);i>=0;i--){
    char tmp = cont[i];    
    if( tmp == ')'){
      char op = cont[i-1];
      operators.push(op);
    }
  }

  stack<string> string_numbers;
  string sn1,sn2;
  int f1=0;
  int fi,mi,li;
  
  for(int w=(cont.size()-1);w>=0;w--){
    if (cont[w]=='(' && f1==0){
      fi=w;
      
      for(int j=fi;j<cont.size();j++){
        if(cont[j]==' '){
          mi=j;
        }
      }

      for(int l=mi;l<cont.size();l++){
        if(cont[l]==')'){
          li=l-1;
        }
      }
      f1=1;
    }
  }
  
  string temp_str;
  f1=0;
  for(int w=(cont.size()-1);w>=0;w--){
    if(cont[w]=='('&& f1==1){
      for(int k=w+1;k<cont.size();k++){
        if(cont[k]==' '){
          break;
        }
        temp_str+=cont[k];
      }
      string_numbers.push(temp_str);
      temp_str="";
    }
    if(cont[w]=='('&& f1==0) {
      f1=1;
    }
  }

  for(int i=fi+1;i<mi;i++){
    sn1+=cont[i];
  }

  for(int i=mi+1;i<li;i++){
    sn2+=cont[i];
  }

  double n1 = stod(sn1);
  double n2 = stod(sn2);

  stack<double> numbers;
  if(string_numbers.size()>0){
    int floop=string_numbers.size();
    for(int j=0;j<floop;j++){
      numbers.push(stod(string_numbers.top()));
      string_numbers.pop();
    }
  }
  

  double result;

  if(operators.top()=='*'){
    result = n1*n2;
  }else if(operators.top()=='/'){
    result = n1/n2;
  }else if(operators.top()=='+'){
    result = n1+n2;
  }else if(operators.top()=='-'){
    result = n1-n2;
  }
  operators.pop();

  int floop = operators.size();
  for(int i=0;i<floop;i++){
    if(operators.top()=='*'){
      result = result*numbers.top();
    }else if(operators.top()=='/'){
      result = result/numbers.top();
    }else if(operators.top()=='+'){
      result = result+numbers.top();
    }else if(operators.top()=='-'){
      result = result-numbers.top();
    }
    operators.pop();
    numbers.pop();
  }

  cout << "resultado final deve ser :" << result << "\n";
}
