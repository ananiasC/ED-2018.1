#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;

const int nc = 60;
const int nl = 20;

struct Par{
    int l,c;

    //Construtor
    Par(int l = 0, int c= 0){
        this->l = l;
        this->c = c;
    }
};

vector<Par> getNeib(Par p){
    vector<Par> v;

    v.push_back(Par(p.l, p.c + 1));
    v.push_back(Par(p.l, p.c - 1));
    v.push_back(Par(p.l + 1, p.c));
    v.push_back(Par(p.l - 1, p.c));

    return v;
}

vector<Par> embaralhar(vector<Par> vet){
    for(int i = 0; i < (int) vet.size(); i++){
        int aleat = rand() % vet.size();

        swap(vet[i],vet[aleat]);

    }

    return vet;
}

void mostrar(vector<string>& mat){
    int i,j;
    cout << string(50, '\n');

    for (i = 0; i < nl; i++) {
        for (j = 0; j < nc; ++j) {
            cout << mat[i][j];
        }
        cout << endl;
    }

    getchar();

}

int queimar(vector<string> &mat, int l, int c, int nivel){
    if(l < 0 || l >= nl)
        return 0;
    if(c < 0 || c >= nc)
        return 0;
    if(mat[l][c] != '!')
        return 0;


    if(nivel == 9 + 1)
        nivel = 0;


    mat[l][c] = '0' + nivel;

    mostrar(mat);

    int total=0;
    total++;

    vector<Par> v = embaralhar(getNeib(Par(l,c)));

    for(int i = 0; i < (int)v.size();i++){
        Par p = v[i];
        total+= queimar(mat, p.l, p.c, nivel + 1);
    }

    nivel--;
    if(nivel == 0 -1)
        nivel = 9;

    mat[l][c]='o';
    mostrar(mat);


    return total;
}


int main()
{
    srand(time(NULL));
    vector<string> mat(nl, string(nc, ' '));
    int narvores = nl * nc * 1.0;
    for(int i = 0; i < narvores; i++){
        mat[rand() % nl][rand() % nc] = '!';
    }
    mostrar(mat);
    int total = queimar(mat, 0, 0, 0);

    cout << total << " arvores queimaram\n";

    return 0;
}
