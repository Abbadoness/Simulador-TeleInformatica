#include <string>
#include <stdlib.h>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <algorithm>
#include <bitset>
#include "CamadaEnlace.hpp"
#include "CamadaFisica.hpp"

using namespace std;

void CamadaEnlaceDadosTransmissora(vector<int> quadro){

    cout << endl << "Camada Enlace Dados Transmissora" << endl;

    // Encaminha o quadro para ser enquadrado.

    CamadaEnlaceDadosTransmissoraEnquadramento(quadro);

}

void CamadaEnlaceDadosTransmissoraEnquadramento(vector<int>quadro){

    // Permite ao usuario selecionar o tipo de enquadramento.
    // Depois encaminha o quadro enquadrado para o controle de erro.

    int tipoDeEnquadramento = 0;
	vector<int> quadroEnquadrado;

    cout << "Selecione o tipo de Enquadramento:" << endl;
    cout << "0: Contagem De Caracteres." << endl;
    cout << "1: Insercao De Bytes."      << endl;

    cin >> tipoDeEnquadramento;

	switch(tipoDeEnquadramento){
		case 0:
			quadroEnquadrado = CamadaEnlaceDadosTransmissoraEnquadramentoContagemDeCaracteres(quadro);
			break;
		case 1:
			quadroEnquadrado = CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoDeBytes(quadro);
			break;
	}

	cout << "Quadro Enquadrado: " << endl;

	for(int i = 0; i < quadroEnquadrado.size(); i++){
        cout << quadroEnquadrado.at(i);
	}

	cout << endl;

	CamadaEnlaceDadosTransmissoraControleDeErro(quadroEnquadrado);
}

void CamadaEnlaceDadosTransmissoraControleDeErro(vector<int> quadro){

    // Solicita ao usuario o tipo de controle de erro desejado.
    // Depois encaminha o quadro codificado para transmissao na camada fisica.

    vector<int> quadroAux;
    int tipoDeControleDeErro = 0;
    cout << "Selecione um tipo de controle de erro: " << endl;
    cout << "0 - Bit de Paridade Par." << endl;
    cout << "1 - CRC."                 << endl;
    cout << "2 - Hamming."             << endl;

    cin  >> tipoDeControleDeErro;

    switch(tipoDeControleDeErro){
        case 0:
            quadroAux = CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar(quadro);
            break;
        case 1:
            quadroAux = CamadaEnlaceDadosTransmissoraControleDeErroCRC(quadro);
            break;
        case 2:
            quadroAux = CamadaEnlaceDadosTransmissoraControleDeErroCodigoDeHamming(quadro);
            break;
    }

    CamadaFisicaTransmissora(quadroAux);
}

vector<int> CamadaEnlaceDadosTransmissoraEnquadramentoContagemDeCaracteres(vector<int>quadro){

    // Conta quantos bytes o quadro possui.
    // Depois acrecenta um byte para representar essa quantidade no comeco do quadro.

    int caracteresQuadro;
    vector<int> quadroAux;

    if(quadro.size() % 8 == 0){
        caracteresQuadro = quadro.size()/8;
    }else{
        caracteresQuadro = (quadro.size()/8) + 1;
    }

    std::string binary = std::bitset<8>(caracteresQuadro + 1).to_string();
    for (int i = 0; i < binary.length(); i++){
        if (binary[i] == '0'){
            quadroAux.push_back(0);
        }
        else{
            if (binary[i] == '1'){
                quadroAux.push_back(1);
            }
        }
    }

    for(int i = 0; i < quadro.size(); i++){
        quadroAux.push_back(quadro.at(i));
    }

    return quadroAux;
}

vector<int> ColocaFlagESC (int opcao, vector<int> Bits) {

    // Funcao usada para acrescentar flags no vetor passado.
    // Se a opcao for 0 acresenta-se a flag 00001111.
    // Se a opcao for 1 acresenta-se o ESC  00011011.
    // Depois retorna os o vetor com os bits acresentados.

    vector<int> flag {0, 0, 0, 0, 1, 1, 1, 1}, ESC {0, 0, 0, 1, 1, 0, 1, 1};

    for(int i = 0; i < 8; i++){
        if(opcao == 0){
           Bits.push_back(flag.at(i));
        }
        else if(opcao == 1){
            Bits.push_back(ESC.at(i));
        }
    }

    return Bits;
}

vector<int> CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoDeBytes(vector<int> quadro){

    // Coloca os bytes de Flag e retorna o resultado.

    vector<int> quadroAux;

    for(int i = 0; i < quadro.size(); i++){
        // Se for o inicio ou final acresenta-se flag.
        if((i == 0) || (i == (quadro.size() - 1))){
            quadroAux = ColocaFlagESC(0, quadroAux);
        }
        if((i%8 == 0) && (0 < i)){
            // Se o ultimo byte lido do campo de dados for uma flag coloca-se um ESC.
            // Se o ultimo byte lido do campo de dados for um ESC coloca-se um ESC.
            if((quadro.at(i - 8) == 0) && (quadro.at(i - 7) == 0) && (quadro.at(i - 6) == 0) && (quadro.at(i - 5) == 0) && (quadro.at(i - 4) == 1) && (quadro.at(i - 3) == 1) && (quadro.at(i - 2) == 1) && (quadro.at(i - 1) == 1)){
                quadroAux = ColocaFlagESC(1, quadroAux);
            }else if((quadro.at(i - 8) == 0) && (quadro.at(i - 7) == 0) && (quadro.at(i - 6) == 0) && (quadro.at(i - 5) == 1) && (quadro.at(i - 4) == 1) && (quadro.at(i - 3) == 0) && (quadro.at(i - 2) == 1) && (quadro.at(i - 1) == 1)){
                quadroAux = ColocaFlagESC(1, quadroAux);
            }
        }
    }

    return quadroAux;
}

vector<int> CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar(vector<int> quadro){

    // Se a quantidade de bits 1 for divisivel por 2 coloca-se um bit 0 no final do quadro.
    // Caso contrario coloca-se um bit 1.
    // Depois retorna o quadro com essas alteracoes.

    int contadorBitsUm = 0;

    for(int i = 0; i < quadro.size(); i++){
        if(quadro.at(i) == 1){
            contadorBitsUm++;
        }
    }
    if(contadorBitsUm%2 == 0){
        quadro.push_back(0);
    }else{
        quadro.push_back(1);
    }

    cout << endl << "Bit de paridade: " << quadro.at(quadro.size() - 1) << endl;

    return quadro;
}

vector<int> CamadaEnlaceDadosTransmissoraControleDeErroCodigoDeHamming(vector<int> quadro){

    // Coloca-se os bits redundantes nas posicoes que sao potencias de 2.
    // Nos demais coloca-se os bits de dados.

    vector<int> quadroAux,quadroAux2,quadroAux3;
    int m, r, p, j, k, x, minimo, maximo;
    m = quadro.size();
    r = 0;
    j = 0;
    k = 1;
    x = 0;
    minimo = 0;
    maximo = 0;

    quadroAux2.push_back(0);

    for(int i = 0; i < m; i++){
        quadroAux2.push_back(quadro.at(i));
    }

    while((pow(2,r)) < (m + r + 1)){
        r++;
    }

    for(int i = 0; i <= (m + r); i++){
        quadroAux.push_back(0);
    }

    for(int i = 1; i <= (m + r); i++){
        if(i == pow(2, j)){
            quadroAux[i] = -1;
            j++;
        }
        else{
            quadroAux[i] = quadroAux2[k];
            k++;
        }
    }

    k = 0;

    for (int i = 1; i <= (m + r); i = pow(2, k)){
      k++;
      p = 0;
      j = i;
      x = i;
      minimo = 1;
      maximo = i;

      while(j <= (m + r)){
          for(x = j; (minimo <= maximo) && (x <= m + r); minimo++, x++){
              if(quadroAux[x] == 1){
                p = p + 1;
              }
          }
          j = x + i;
          minimo = 1;
      }

      if((p % 2) == 0){
        quadroAux[i] = 0;
      }
      else{
        quadroAux[i] = 1;
      }
    }
    cout << endl << "Codigo Hamming na Transmissora: ";

    for(int i = 1; i <= (m + r); i++){
        cout << quadroAux.at(i);
        quadroAux3.push_back(quadroAux.at(i));
    }
    cout << endl;

    return quadroAux3;
}

vector<int> CamadaEnlaceDadosTransmissoraControleDeErroCRC(vector<int> quadro){

    // Nao consegui implementar a tempo por isso apaguei o que tinha feito.
    // Sinto muito mesmo.

    return quadro;
}

void CamadaEnlaceDadosReceptora(vector<int> quadro){

    // Encaminha o quadro para o controle de erro.

    cout << endl << "Camada Enlace Dados Receptora." << endl;

    CamadaEnlaceDadosReceptoraControleDeErro(quadro);
}

void CamadaEnlaceDadosReceptoraControleDeErro(vector<int> quadro){

    // Seleciona o tipo de controle de erro dado na transmissora.

    vector<int> quadroAux;
    int tipoDeControleDeErro = 0;

    cout << "Selecione o mesmo tipo de controle de erro escolhido anteriormente: " << endl;
    cout << "0 - Bit de Paridade Par." << endl;
    cout << "1 - CRC."                 << endl;
    cout << "2 - Hamming."             << endl;

    cin  >> tipoDeControleDeErro;

    switch(tipoDeControleDeErro){
        case 0:
            quadroAux = CamadaEnlaceDadosReceptoraControleDeErroBitDeParidadePar(quadro);
            break;
        case 1:
            quadroAux = CamadaEnlaceDadosReceptoraControleDeErroCRC(quadro);
            break;
        case 2:
            quadroAux = CamadaEnlaceDadosReceptoraControleDeErroCodigoDeHamming(quadro);
            break;
    }

    CamadaEnlaceDadosReceptoraEnquadramento(quadroAux);
}

vector<int> CamadaEnlaceDadosReceptoraEnquadramentoContagemDeCaracteres(vector<int> quadro){

    // Usando o primeiro byte do quadro calcula-se o numero de bytes que ele deveria possuir.
    // Se o quadro possuir um numero diferente o programa é encerrado.

    vector<int> quadroAux, quadroAux2;
    int contador = 0;
    int quantidadeDeBytes;

    for(int i = 0; i < 8; i++){
        quadroAux.push_back(quadro.at(i));
    }

    for(int i = 0; i < quadroAux.size(); i++){
        contador  += quadroAux.at(i) * pow(2, (quadroAux.size() - 1 - i));
    }

    for(int i = 8; i < quadro.size(); i++){
        quadroAux2.push_back(quadro.at(i));
    }

    quantidadeDeBytes = ceil(quadroAux2.size()/8);

    if((contador - 1) != quantidadeDeBytes){
        cout << "Erro detectado no quadro." << endl;
        cout << "Encerrando programa."      << endl;
        exit(0);
    }else{
        cout << "Quadro recebido com sucesso." << endl;
        return quadroAux2;
    }
}

vector<int> CamadaEnlaceDadosReceptoraControleDeErroCodigoDeHamming(vector<int> quadro){

    // Deveria decodificar o quadro codificado com o metodo de Hamming
    // mas nao entendo o porque nao estar funcionando.
    // Se estivesse poderia detectar se houve algum erro e corrigi-lo.

    vector<int> quadroAux, quadroAux2, quadroAux3, bitsRedundantes;
    int m, r, j, k, x, minimo, maximo, contador;
    m = quadro.size();
    r = 0;
    j = 0;
    k = 1;
    x = 0;
    minimo = 0;
    maximo = 0;
    contador = 0;

    quadroAux.push_back(0);

    for(int i = 0; i < m; i++){
        quadroAux.push_back(quadro.at(i));
    }

    while((pow(2,r)) <= m){
        r++;
    }

    for(int i = 1; i <= m; i++){
        if(i == pow(2, j)){
            bitsRedundantes.push_back(quadroAux.at(i));
            j++;
        }else{
            quadroAux3.push_back(quadroAux.at(i));
            k++;
        }
    }

    k = 0;

    for(int i = 1; i <= m; i = pow(2, k)){
      k++;
      j = i;
      x = i;
      minimo = 1;
      maximo = i;

      while(j <= m){
          for(x = j; (minimo <= maximo) && (x <= m); minimo++, x++){
              if(quadroAux[x] == 1){
                 bitsRedundantes[k] = bitsRedundantes[k] + 1;
              }
          }
          j = x + i;
          minimo = 1;
      }
    }


    for(int i = 0; i < bitsRedundantes.size(); i++){
        contador += (bitsRedundantes.at(i) % 2) * (2 ^ i);
    }

    if(contador == 0){
        cout << "Mensagem recebida com sucesso." << endl;
        cout << "Quadro recebido: ";

        for(int i = 0; i < quadroAux3.size(); i++){
            cout << quadroAux3.at(i);
        }
        cout << endl;

        return quadroAux3;
    }else{
        j = 0;
        cout << "Ocorreu erro no bit " << contador << "." << endl;
        for(int i = 1; i <= m; i++){
            if(i == pow(2, j)){
                j++;
            }else{
                if(contador == i){
                    if(quadroAux.at(i) == 1){
                        quadroAux2.push_back(0);
                    }else{
                        quadroAux2.push_back(1);
                    }
                }else{
                    quadroAux2.push_back(quadroAux.at(i));
                }
            }
        }

        cout << "Erro corrigido." << endl;
        cout << "Quadro sem erro: ";

        for(int i = 0; i < quadroAux2.size(); i++){
            cout << quadroAux2.at(i);
        }

        cout << endl;

        return quadroAux2;
    }
}

void CamadaEnlaceDadosReceptoraEnquadramento(vector<int> quadro){

    // O Usuario deve selecionar o mesmo enquadramento da transmisora.
    // Para haver desenquadramento.

    int tipoDeEnquadramento;
    vector<int> quadroDesenquadrado;

    cout << "Camada de Enlace de Dados Receptora Enquadramento."          << endl;
    cout << "Selecione o tipo de enquadramento escolhido na transmissao." << endl;
    cout << "0: Contagem De Caracteres." << endl;
    cout << "1: Insercao De Bytes."      << endl;

    cin >> tipoDeEnquadramento;

	switch(tipoDeEnquadramento){
		case 0:
			quadroDesenquadrado = CamadaEnlaceDadosReceptoraEnquadramentoContagemDeCaracteres(quadro);
			break;
		case 1:
			quadroDesenquadrado = CamadaEnlaceDadosReceptoraEnquadramentoInsercaoDeBytes(quadro);
			break;
	}

    CamadaDeAplicacaoReceptora(quadroDesenquadrado);
}

vector<int> CamadaEnlaceDadosReceptoraControleDeErroBitDeParidadePar(vector<int> quadro){

    // Conta quantos bit 1 existe no quadro e se for impar retorna um erro.
    // Caso contrario retorna somente os bits de dados.

    int contador = 0;

    for(int i = 0; i < quadro.size(); i++){
        if(quadro.at(i) == 1){
            contador += 1;
        }
    }

    quadro.pop_back();

    if(contador % 2 != 0){
        cout << "Ocorreu um erro durante a transmissao da mensagem." << endl;
        cout << "Programa sera encerrado pois com o metodo escolhido apenas detecta se houve erro." << endl;
        exit(0);
    }else{
        cout << "Mensagem recebida com sucesso." << endl;
    }

    return quadro;
}

vector<int> CamadaEnlaceDadosReceptoraControleDeErroCRC(vector<int> quadro){
    return quadro;
}

vector<int> CamadaEnlaceDadosReceptoraEnquadramentoInsercaoDeBytes(vector<int> quadro){

    // Remove as flags inicial e final.
    // Varre o vetor e, se encontrar dois bytes ESC consecutivos ignora um.
    // Caso contrario escreve o byte no quadro desenquadrado.

    vector<int> quadroDesenquadrado, quadroAux;

    for(int i = 8; i < quadro.size() - 8; i++){
        quadroAux.push_back(quadro.at(i));
    }

    for(int i = 0; i <= quadroAux.size(); i++){
        if((i%8 == 0) && (0 < i)){
            if(i <= (quadroAux.size() - 9)){
                if(((quadroAux.at(i - 8) == 0) && (quadroAux.at(i - 7) == 0) && (quadroAux.at(i - 6) == 0) && (quadroAux.at(i - 5) == 1) && (quadroAux.at(i - 4) == 1) && (quadroAux.at(i - 3) == 0) && (quadroAux.at(i - 2) == 1) && (quadroAux.at(i - 1) == 1))
                && ((quadroAux.at(i + 0) == 0) && (quadroAux.at(i + 1) == 0) && (quadroAux.at(i + 2) == 0) && (quadroAux.at(i + 3) == 1) && (quadroAux.at(i + 4) == 1) && (quadroAux.at(i + 5) == 0) && (quadroAux.at(i + 6) == 1) && (quadroAux.at(i + 7) == 1))){

                    continue;
                }else{
                    quadroDesenquadrado.push_back(quadroAux.at(i - 8));
                    quadroDesenquadrado.push_back(quadroAux.at(i - 7));
                    quadroDesenquadrado.push_back(quadroAux.at(i - 6));
                    quadroDesenquadrado.push_back(quadroAux.at(i - 5));
                    quadroDesenquadrado.push_back(quadroAux.at(i - 4));
                    quadroDesenquadrado.push_back(quadroAux.at(i - 3));
                    quadroDesenquadrado.push_back(quadroAux.at(i - 2));
                    quadroDesenquadrado.push_back(quadroAux.at(i - 1));
                }
            }else{
                quadroDesenquadrado.push_back(quadroAux.at(i - 8));
                quadroDesenquadrado.push_back(quadroAux.at(i - 7));
                quadroDesenquadrado.push_back(quadroAux.at(i - 6));
                quadroDesenquadrado.push_back(quadroAux.at(i - 5));
                quadroDesenquadrado.push_back(quadroAux.at(i - 4));
                quadroDesenquadrado.push_back(quadroAux.at(i - 3));
                quadroDesenquadrado.push_back(quadroAux.at(i - 2));
                quadroDesenquadrado.push_back(quadroAux.at(i - 1));
            }
        }
    }

    cout << "Resultado desenquadramento: ";

    for(int i = 0; i < quadroDesenquadrado.size(); i++){
        cout << quadroDesenquadrado.at(i);
    }

    cout << endl;

    return quadroDesenquadrado;
}
