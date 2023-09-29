#include "CamadaFisica.hpp"

using namespace std;

vector<int> CamadaFisicaTransmissoraCodificacaoBinaria(vector<int> quadro){
    cout << "Quadro codificado: ";
    for(int i = 0; i < quadro.size(); i++){
        cout << quadro.at(i);
    }
    return quadro;
}

vector<int> CamadaFisicaTransmissoraCodificacaoManchester(vector<int> quadro){
    vector<int> bits;
    for(int i = 0; i < quadro.size(); i++){
    // Faz o xor com cada bit do quadro
        bits.push_back(quadro.at(i) ^ 0);
        bits.push_back(quadro.at(i) ^ 1);
    }

    cout << "Bits codificados: ";
    for(int i = 0; i < bits.size(); i++){
        cout << bits.at(i);
    }

    return bits;
}

vector<int> CamadaFisicaTransmissoraCodificacaoBipolar(vector<int> quadro){
    int bitNaoNuloAnterior = -1;
    for(int i = 0; i < quadro.size(); i++){
    // Alterna o simbolo 1 entre 1 e -1
        if(quadro.at(i) == 1){
            if(bitNaoNuloAnterior == -1){
            	quadro.at(i) = 1;
            	bitNaoNuloAnterior = 1;
			} else {
				quadro.at(i) = -1;
				bitNaoNuloAnterior = -1;
			}
        }
    }

    cout << "Quadro codificado: ";
    for(int i = 0; i < quadro.size(); i++){
        cout << quadro.at(i);
    }
    return quadro;
}

void CamadaFisicaTransmissora(vector<int> quadro){
    // Seleciona o tipo de codificacao
    vector<int> fluxoBrutoDeBits;
    int tipoDeCodificacao;

    cout << endl << "Selecione um modo de codificacao: "<< endl
                 << "0: Binaria"    << endl
                 << "1: Manchester" << endl
                 << "2: Bipolar"    << endl;

    cin >> tipoDeCodificacao;

    switch(tipoDeCodificacao){
        case 0:
            fluxoBrutoDeBits = CamadaFisicaTransmissoraCodificacaoBinaria(quadro);
            break;
        case 1:
            fluxoBrutoDeBits = CamadaFisicaTransmissoraCodificacaoManchester(quadro);
            break;
        case 2:
            fluxoBrutoDeBits = CamadaFisicaTransmissoraCodificacaoBipolar(quadro);
            break;
    }

    MeioDeComunicacao(fluxoBrutoDeBits, tipoDeCodificacao);
}

void MeioDeComunicacao(vector<int> fluxoBrutoDeBits, int tipoDeCodificacao){
    // Transfere o fluxo de bits do Ponto A para B
    // Transfere para a receptora
    vector<int> fluxoBrutoDeBitsPontoA, fluxoBrutoDeBitsPontoB;

    fluxoBrutoDeBitsPontoA = fluxoBrutoDeBits;

    for(int i = 0;i < fluxoBrutoDeBitsPontoA.size(); i++){
        if((rand()%100 == 42) || (rand()%100 == 7) || (rand()%100 == 10) || (rand()%100 == 11) || (rand()%100 == 84)){
            (fluxoBrutoDeBitsPontoA.at(i) == 0) ? fluxoBrutoDeBitsPontoB.push_back(1) : fluxoBrutoDeBitsPontoB.push_back(0);
        }else{
            fluxoBrutoDeBitsPontoB.push_back(fluxoBrutoDeBitsPontoA.at(i));
        }
    }

    CamadaFisicaReceptora(fluxoBrutoDeBitsPontoB, tipoDeCodificacao);
}

void CamadaFisicaReceptora(vector<int> quadro, int tipoDeCodificacao){
    // Transfere o quadro para a camada receptora
    vector<int> fluxoBrutoDeBits;

    switch(tipoDeCodificacao){
        case 0:
            fluxoBrutoDeBits = CamadaFisicaReceptoraCodificacaoBinaria(quadro);
            break;
        case 1:
            fluxoBrutoDeBits = CamadaFisicaReceptoraCodificacaoManchester(quadro);
            break;
        case 2:
            fluxoBrutoDeBits = CamadaFisicaReceptoraCodificacaoBipolar(quadro);
            break;
    }

    CamadaEnlaceDadosReceptora(fluxoBrutoDeBits);
}

vector<int> CamadaFisicaReceptoraCodificacaoBinaria(vector<int> quadro){
    return quadro;
}

vector<int> CamadaFisicaReceptoraCodificacaoManchester(vector<int> quadro){
    // Extrai o sinal verdadeiro
    vector<int> quadroDecodificado;
    for(int i = 0; i < quadro.size(); i++){
        if((i % 2) == 0){
            quadroDecodificado.push_back(quadro.at(i));
        }
    }
    return quadroDecodificado;
}

vector<int> CamadaFisicaReceptoraCodificacaoBipolar(vector<int> quadro){
    // Torna os -1 do sinal e transforma em 1
    for(int i = 0; i < quadro.size(); i++){
        if(quadro.at(i) == -1){
            quadro.at(i) = 1;
        }
    }

    return quadro;
}
