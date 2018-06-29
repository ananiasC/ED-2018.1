#include <vector>
#include <list>
#include <algorithm>
#include <ctime>//funcao time
#include <cstdlib> //funcao srand
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

//Cada dia possui 6 horas de trabalho
//60 minutos x 6 horas = 360 minutos
//cada minuto eh um turno.
const int TURNOS_DIA = 360;

//A quantidade máxima de caixa.
const int MAX_CAIXAS = 10;

//Esse valor determina o quanto o banco por caixa por dia de trabalho
const int CUSTO_CAIXA_DIA = 100;

//numero de simulacoes de teste
const int N_EXEC_TESTE = 10;

struct Cliente
{
    int paciencia;
    int documentos;
    std::string nome;

    Cliente(int paciencia, int documentos)
    {
        gerarNomeAleatorio();
        this->paciencia = paciencia;
        this->documentos = documentos;
    }

    void gerarNomeAleatorio(){
        std::string consoantes = "bcdfghjklmnpqrstvxyz";
        std::string vogais = "aeiou";
        this->nome = std::string(1, consoantes[std::rand() % consoantes.size()]);
        this->nome += std::string(1, vogais[std::rand() % vogais.size()]);
    }
};



//gera um numero entre min e max, [min, max]
int rand_mm(int min, int max){
    static int init = 1;
    if(init){
        init = 0;
        srand(time(NULL));
    }
    return rand() % (max - min + 1) + min;
}

std::string to_string(const Cliente *cliente){
    std::stringstream str;
    str << "[" << cliente->nome << ":";
    str << "d" << setw(2) << cliente->documentos <<
           ":p" << setw(2) << cliente->paciencia << "]";
    return str.str();
}


void print_banco(list<Cliente *> fila, vector<Cliente *> caixas, int turno, int lucro){
    Cliente dummy(0, 0);
    int slot = to_string(&dummy).size();//quandos caracteres ocupa um cliente
    std::cout << string(1 + (slot - 1) * MAX_CAIXAS, '#') << std::endl;
    std::cout << "|";
    for(auto& x : caixas){
        if(x == nullptr)
            cout << std::string(slot - 2, ' ');
        else
            cout << to_string(x);
        cout << "|";
    }
    for(int x = 0; x < MAX_CAIXAS - (int) caixas.size(); x++)
        std::cout << std::string(slot - 2, '-') << "|";
    std::cout << endl;
    std::cout << "-" << std::string(slot - 2, ' ') << std::string((slot - 1) * MAX_CAIXAS, '-') << std::endl;

    std::cout << " ";
    int ind = 1;
    for(auto it = fila.begin(); it != fila.end(); it++, ind++){
        if(ind % MAX_CAIXAS == 0)
            cout << endl << " ";
        cout << to_string(*it) << " ";
    }
    std::cout << std::endl;
    std::cout << std::string(1 + (slot - 1) * MAX_CAIXAS, '#') << std::endl;
    std::cout << "Turno : " << turno << endl;
    std::cout << "Lucro : " << lucro << endl;
}

//============= SIMULAÇÃO =================
int simulacao(pair<int, int> pac, pair<int, int> doc, pair<int, int> cli, int numCaixas){
    std::vector<Cliente*> caixa(numCaixas);
    std::list<Cliente*> fila;

    int turno = 1;
    int lucro = 1;


    while(turno <= TURNOS_DIA || !fila.empty()){
        int qtd_clientes = rand_mm(cli.first, cli.second);

        //GERANDO CLIENTES E INSERINDO NA FILA
        for(int i = 0; i < qtd_clientes; i++)
            fila.push_back(new Cliente(rand_mm(pac.first, pac.second),
                                       rand_mm(doc.first, doc.second)));

        for(int i = 0;i < (int) numCaixas;i++){
            if(caixa[i] != nullptr){
                if(caixa[i]->documentos > 0){
                    caixa[i]->documentos--;
                    lucro++;
                }else{
                    auto aux = caixa[i];
                    caixa[i] = nullptr;
                    delete aux;
                }
            }else{
                if(fila.size() != 0){
                    caixa[i] = fila.front();
                    fila.pop_front();
                }
            }
        }

        for(auto it = fila.begin(); it != fila.end();){
            if((*it)->paciencia > 0){
                (*it)->paciencia--;
                it++;
            }else
                it = fila.erase(it);
        }
        turno++;
    }

    lucro -= (numCaixas * CUSTO_CAIXA_DIA);

    return lucro;
}


int main ()
{

    vector<float> lucro_N_Caixas(10);
    cout << "QUANT. CAIXAS"<<"\t|\t"<<"LUCRO MÉDIO"<<endl;
    int melhor_n_caixa = 0;

    for(int numCaixas = 1;numCaixas <= MAX_CAIXAS;numCaixas++){
        lucro_N_Caixas[numCaixas] = 0;
        for(int exec = 0; exec < N_EXEC_TESTE;exec++)
            lucro_N_Caixas[numCaixas] += simulacao({1, 5}, {1, 2}, {0, 4}, numCaixas);

        lucro_N_Caixas[numCaixas] /= N_EXEC_TESTE;
    }

    for(int i=1;i<=MAX_CAIXAS;i++){
        cout << i << "\t|\t" << lucro_N_Caixas[i]<<endl;
        if(i == 1 || lucro_N_Caixas[melhor_n_caixa] < lucro_N_Caixas[i])
            melhor_n_caixa = i;
    }

    cout << "Melhor numero de caixas: " << melhor_n_caixa << "\nCom lucro de: " << lucro_N_Caixas[melhor_n_caixa]<< "\n" << endl;

    return 0;
}
