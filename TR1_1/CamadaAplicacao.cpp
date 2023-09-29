using namespace std;

#include <string>
#include <sstream>
#include <iostream>
#include <bitset>
#include <vector>
#include "CamadaAplicacao.hpp"

using namespace std;

void AplicacaoTransmissora(void){
    // Pega a mensagem do usuario
    // Passa a mensagem para a Transmissora
    string mensagem;
    cout << "Digite a mensagem:" << endl;
    getline(cin, mensagem);

    CamadaDeAplicacaoTransmissora(mensagem);
}

void CamadaDeAplicacaoTransmissora(string mensagem){
    // Passa a mensagem para ser transformada em ASCII
    // Salva mensagem em ASCII para o quadro
    vector<int> quadro = StringParaASCII(mensagem);

    CamadaEnlaceDadosTransmissora(quadro);
}

vector<int> StringParaASCII(string mensagem){
    vector<int> quadro;
    const int n = 8;
    cout << "ASCII:" << endl;

    for (int i = 0; i < mensagem.length(); i++){
		char x = mensagem.at(i);
        int y = int(x);
        std::string binary = std::bitset<n>(y).to_string();
        for (int j = 0; j < binary.length(); j++){
        	if (binary[j] == '0'){
        		quadro.push_back(0);
        		cout << 0;
			}
			else{
				if (binary[j] == '1'){
					quadro.push_back(1);
					cout << 1;
				}
			}
		}
    }
    cout << endl;
    return quadro;
}

void CamadaDeAplicacaoReceptora(vector<int> quadro){
    string mensagem = ASCIIParaString(quadro);
    cout << endl << "Quadro recebido: ";
    for(int i = 0; i < quadro.size(); i++){
        cout << quadro.at(i);
    }
    cout << endl;
    AplicacaoReceptora(mensagem);
}

string ASCIIParaString(vector<int> quadro){
    string mensagem = "";

    for(int i = 0; i < quadro.size(); i += 8){
    	int charInteiro;

    	charInteiro  = quadro[i + 0] * 128;
    	charInteiro += quadro[i + 1] * 64;
    	charInteiro += quadro[i + 2] * 32;
    	charInteiro += quadro[i + 3] * 16;
    	charInteiro += quadro[i + 4] * 8;
    	charInteiro += quadro[i + 5] * 4;
    	charInteiro += quadro[i + 6] * 2;
    	charInteiro += quadro[i + 7] * 1;

    	mensagem.push_back(int(charInteiro));
	}

    return mensagem;
}

void AplicacaoReceptora(string mensagem){
    cout << endl << "A mensagem recebida foi:" << mensagem << endl;
}
