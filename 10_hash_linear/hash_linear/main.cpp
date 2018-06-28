#include <iostream>
#include <vector>
#include <tuple>
using namespace std;

enum Marcador {VAZIO = 0, CHEIO = 1, DELETADO = 2};

struct Elem {
    int key;
    string value;

    Elem(int key = 0, string value = ""){
        this->key = key;
        this->value = value;
    }

    bool operator ==(Elem other){
        return key == other.key;
    }

    friend ostream& operator << (ostream& os, Elem e){
        os << e.key;
        return os;
    }
};

struct HashLinear{ //linear probing

    pair<Elem, Marcador> * vet;
    int capacity;
    int size;

    HashLinear(int capacity){
        vet = new pair<Elem, Marcador>[capacity];
        this->capacity = capacity;
        this->size = 0;
        for(int i = 0; i < capacity; i++){
            vet[i].first = Elem();
            vet[i].second = VAZIO;
        }
    }

    int search(int key){
        int return_search = key % this->capacity;

        int i = 0;

        int pos = return_search;

        while(vet[pos].first == NULL || vet[pos].second != VAZIO){
            pos = (return_search+i*i) % capacity;
            ++i;
        }
        if(vet[pos].second == VAZIO)
            return -1;

        return pos;
    }

    bool insert(Elem elem){
        int it = search(elem.key);

        if(it == -1)
            return false;

        //pos = calcula a posicao base;
        int pos = elem.key % this->size;

        //enquanto pos != vazio ou deletado
        while(vet[pos].second !=VAZIO || vet[pos].second != DELETADO)
            pos = (pos + 1) % capacity;

        this->vet[pos].first = Elem;
        this->vet[pos].second = CHEIO;

        size ++;
    }

    bool remove(int key){
        int return_search = search(key);
        if(return_search != -1){
            this->vet[return_search].second = DELETADO;
            this->size--;
            return true;
        }
        return false;
    }
};

int main(){

    return 0;
}
