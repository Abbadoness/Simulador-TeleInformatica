#include <cmath>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include "CamadaEnlace.hpp"

using std::vector;

void CamadaFisicaTransmissora(vector<int> quadro);
void MeioDeComunicacao(vector<int> fluxoBrutoDeBits, int tipoDeCodificacao);
void CamadaFisicaReceptora(vector<int> quadro, int tipoDeCodificacao);
vector<int> CamadaFisicaReceptoraCodificacaoBinaria(vector<int> quadro);
vector<int> CamadaFisicaReceptoraCodificacaoManchester(vector<int> quadro);
vector<int> CamadaFisicaReceptoraCodificacaoBipolar(vector<int> quadro);
void CamadaDeAplicacaoReceptora(vector<int> quadro);
