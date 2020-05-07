#include <iostream>
#include <math.h>
#include "temperature.h"
Temperature::Temperature(){
	m_unLen = 0;
	m_nfPE_TTM = nullptr;
	m_nfPB = nullptr;
	m_nfTemperature = 0;
	m_bIsHighTemperature = false;
}
Temperature::~Temperature() {
	if (m_nfPE_TTM) {
		delete[] m_nfPE_TTM;
		m_nfPE_TTM = nullptr;
	}
	if (m_nfPB) {
		delete[] m_nfPB;
		m_nfPB = nullptr;
	}
}
double normalCDF(double value)
{
	return 0.5 * erfc(-value * sqrt(0.5));
}
void Temperature::process() {
	float *PE_TTM, *PB;
	float CurPE_TTM = 0, CurPB = 0, AvePE_TTM = 0, StandardPE_TTM = 0, AvePB = 0, StandardPB = 0;
	float deltaPE_TTM = 0, deltaPB = 0, tempPE_TTM = 0, tempPB = 0;
	float TotShare = 0;
	int i,j;
	if (nullptr == m_nfPE_TTM
		|| nullptr == m_nfPB
		|| 0 == m_unLen) {
		std::cout << "ERROR! Temperature::process() No input data!\n";
		return;
	}
	PE_TTM = m_nfPE_TTM;
	PB = m_nfPB;
	CurPE_TTM = *(PE_TTM + m_unLen - 1);
	CurPB = *(PB + m_unLen - 1);
	// calc distribution para
	for (j = 0; j < m_unLen; j++) {
		AvePE_TTM += *(PE_TTM + j);
		AvePB += *(PB + j);
	}
	AvePE_TTM /= m_unLen;
	AvePB /= m_unLen;
	for (j = 0; j < m_unLen; j++) {
		StandardPE_TTM += (*(PE_TTM + j) - AvePE_TTM)*(*(PE_TTM + j) - AvePE_TTM);
		StandardPB += (*(PB + j) - AvePB)*(*(PB + j) - AvePB);
	}
	StandardPE_TTM = sqrtf(StandardPE_TTM);
	StandardPE_TTM /= (m_unLen - 1);
	StandardPB = sqrtf(StandardPB);
	StandardPB /= (m_unLen - 1);
	// turn to normal distribution
	deltaPE_TTM = (CurPE_TTM - AvePE_TTM) / StandardPE_TTM;
	deltaPB = (CurPB - AvePB) / StandardPB;
	// calc temperature
	tempPE_TTM = normalCDF(deltaPE_TTM);
	tempPB = normalCDF(deltaPB);
	m_nfTemperature = (tempPE_TTM + tempPB) / 2;
	if (TEMPERATURETHRES < m_nfTemperature) {
		m_bIsHighTemperature = true;
	}
}