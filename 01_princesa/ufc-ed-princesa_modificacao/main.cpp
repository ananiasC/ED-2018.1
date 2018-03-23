#include <QCoreApplication>
#include <iostream>

// MODIFICAÇÃO DA PASSAGEM DA ARMA

using namespace std;

void preencherArray(int array[],int quantPessoa){
    //PREENCHE O ARRAY COM NUMEROS 1 A quantPessoa
    int i;

    for(i=0; i < quantPessoa;i++){
        array[i] = i+1;
    }
}
int passarArma(int array[], int quantPessoa,int pessoaComArma){
    //PASSAGEM DA ARMA PARA O PROXIMO MEMBRO
    int i,j;
    int k = pessoaComArma;

    for (j = 0; j < k; j++) { // EXECUTA O VALOR DE QUEM TA COM A ARMA VEZES

        for(i=0; i <= quantPessoa;i++){
            if(array[i] == pessoaComArma && array[i] != array[quantPessoa-1]){
                pessoaComArma = array[i+1];
                break;
            }else if(array[i] == pessoaComArma && array[i] == array[quantPessoa-1]){
                pessoaComArma = array[0];
                break;
            }
        }
    }
    return pessoaComArma;
}
void matarPessoa(int array[],int quantPessoa, int pessoaComArma){
    //ELIMINA OS MEMBROS ATÉ RESTA UM SÓ, O VENCEDOR;
    int i;

    while(true){

        //ENCERRA O LAÇO QUANDO TIVER APENAS 1 MEMBRO
        if(quantPessoa ==1){
            break;
        }

        //RESPONSAVEL PELA RETIRADA DO MEMBRO A SER MORTO, REORGANIZA O ARRAY

        if(pessoaComArma == array[quantPessoa-1]){
            for(i=0; i < quantPessoa-1; i++){
                array[i] = array[i+1];
            }
            quantPessoa--;
        }else{
            for(i=0; i < quantPessoa-1; i++){
                if(array[i] > pessoaComArma){
                    array[i] = array[i+1];
                }
            }
            quantPessoa--;
        }

        pessoaComArma = passarArma(array,quantPessoa,pessoaComArma);

    }
}

int main()
{
    int quantPessoa, pessoaComArma;

    cout << "Digite a quantidade de pessoas: ";
    cin >> quantPessoa;
    do{
        cout << "Digite a pessoa inicial: ";
        cin >> pessoaComArma;

        if(pessoaComArma > quantPessoa){
            cout << endl;
            cout << "A pessoa inicial deve está no intervalo dos participantes!" << endl;
        }else
            break;

    }while(true);


    int array[quantPessoa];

    preencherArray(array,quantPessoa);

    matarPessoa(array,quantPessoa,pessoaComArma);

    cout << endl;
    cout << "Vencedor: " << array[0] << endl;

    return 0;
}

