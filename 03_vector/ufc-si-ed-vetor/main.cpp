#include <iostream>

using namespace std;

struct Vetor{
    int * _data;//bloco de dados
    int _capacidade;//tamanho maximo do vetor
    int _size; //quantos elementos estao inseridos

    Vetor(int capacidade){
        this->_capacidade = capacidade;
        this->_size = 0;
//        this->data = (int*) malloc(capacidade * 4);//retorno lixo
        this->_data = new int[capacidade];//retorno zerado
    }
    void push_back(int value){
        if(this->_size == this->_capacidade)
            this->reserve(this->_capacidade*2);
            //this->reserve(2 * _capacitade);
        this->_data[this->_size] = value;
        this->_size += 1;
    }
    void pop_back(){
        if(this->_size == 0)
            return;
        this->_data[_size] = 0;
        this->_size -= 1;
    }

    //retornar a refencia à variavel dessa posicao
    int& at(int indice){
        return this->_data[indice];
    }
    int& front(){
        return this->_data[0];
    }
    int& back(){
        return this->_data[this->_size - 1];
    }
    int * begin(){
        return &this->_data[0];
    }
    int * end(){
        return &this->_data[this->_size];
    }
    int size(){
        return this->_size;
    }

    int capacity(){
        return this->_capacidade;
    }

    void reserve(int capacity){
        Vetor aux(capacity);

        if(this->_size <= capacity)
            for (int i = 0; i < this->_size; i++)
                aux.push_back(this->_data[i]);
        else
            for (int i = 0; i < capacity; i++)
                aux.push_back(this->_data[i]);

        this->_data = new int[capacity];
        this->_size = 0;

        for (int i = 0; i < aux.size(); ++i) {
            this->push_back(aux.at(i));
        }


    }


};

#include <vector>
int main()
{
    vector<int> v;
    v.push_back(1);//1 elemento, 1 de capacidade
    v.push_back(3);//2 elementos,2 de cap
    v.push_back(5);//3 elementos,4 cap

    v.reserve(100);
    v.size();// 3
    v.capacity();//100

    //lvalue
    v.front();//1
    v.back();//5
    v.front() = 6;

    //posicoes - iteradores
    //não são ponteiro, mas se comportam como se fosse
    v.begin();//iterador pro primeiro
    v.end();//iterador pro abismo

//    list<int> list = {3, 2, 5, 4, 3, 6, 8, 6};
//    for(int x : list)
//        cout << x << " ";
//    for(auto it = list.begin(); it != list.end(); it++)
//        cout << *it << " ";

    Vetor pivet(5);
    pivet.push_back(4);
    pivet.push_back(2);
    pivet.push_back(7);
    pivet.push_back(9);
    pivet.push_back(11);
    pivet.push_back(6);
    pivet.push_back(80);
    pivet.push_back(1);
    for (int i = 0; i < pivet.size(); i++) {
        cout << pivet.at(i) << endl;
    }


    return 0;
}





