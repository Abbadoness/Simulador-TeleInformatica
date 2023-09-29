#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>

using std::vector;

// Declaracao da funcoes usadas na camada de enlace.

void CamadaEnlaceDadosTransmissora(vector<int> quadro);

void CamadaEnlaceDadosTransmissoraEnquadramento(vector<int> quadro);

void CamadaEnlaceDadosTransmissoraControleDeErro(vector<int> quadro);

vector<int> CamadaEnlaceDadosTransmissoraEnquadramentoContagemDeCaracteres(vector<int> quadro);

vector<int> CamadaEnlaceDadosTransmissoraEnquadramentoInsercaoDeBytes(vector<int> quadro);

vector<int> CamadaEnlaceDadosTransmissoraControleDeErroBitParidadePar(vector<int> quadro);

vector<int> CamadaEnlaceDadosTransmissoraControleDeErroCRC(vector<int> quadro);

vector<int> CamadaEnlaceDadosTransmissoraControleDeErroCodigoDeHamming(vector<int> quadro);

void CamadaEnlaceDadosReceptora(vector<int> quadro);

void CamadaEnlaceDadosReceptoraEnquadramento(vector<int> quadro);

void CamadaEnlaceDadosReceptoraControleDeErro(vector<int> quadro);

vector<int> CamadaEnlaceDadosReceptoraEnquadramentoContagemDeCaracteres(vector<int> quadro);

vector<int> CamadaEnlaceDadosReceptoraEnquadramentoInsercaoDeBytes(vector<int> quadro);

vector<int> CamadaEnlaceDadosReceptoraControleDeErroBitDeParidadePar(vector<int> quadro);

vector<int> CamadaEnlaceDadosReceptoraControleDeErroCRC(vector<int> quadro);

vector<int> CamadaEnlaceDadosReceptoraControleDeErroCodigoDeHamming(vector<int> quadro);
