#include <iostream>
#include "IFund.h"

Fund::Fund() {
	m_bIsGoodFund = false;
	// calc withdrawal rate
	m_nfNetVal = nullptr;
	m_nfMaxNetVal = 0;
	m_bIsHighWithdrawalRate = false;
	// calc temperature
	m_Temperature = new Temperature;
	// check "4433"
	m_nTotal = 0;
	m_nRank[4] = {0};
	m_bIsNot4433 = false;
	// calc return rate
	m_bHasBuyed = false;
	m_bHasEarnedEnough = false;
	m_nfBuyNetVal = 0;
	m_nfCurNetVal = 0;
	m_nBuyDay[3] = {0};//y.m.d
	m_nCurDay[3] = {0};//y.m.d
	m_nfTotRate = 0;
	m_nfAnnualRate = 0;
	// global index
	m_nInterestRateof10y = nullptr;
	m_nfMarketValue = 0;
	m_nfGDP = 0;
	m_nfSecuritizationRate = 0;
	m_bIsMarketHot = false;
}

Fund::~Fund() {
	if (m_nfNetVal) {
		delete[] m_nfNetVal;
		m_nfNetVal = nullptr;
	}
	if (m_Temperature) {
		delete m_Temperature;
		m_Temperature = nullptr;
	}
	if (m_nInterestRateof10y) {
		delete[] m_nInterestRateof10y;
		m_nInterestRateof10y = nullptr;
	}
}

bool Fund::Process() {
	CalcWithdrawalRate();
	Check4433();
	m_Temperature->process();
	CalcReturnRate();
	CheckMarketHotness();
	if (!m_bIsHighWithdrawalRate
		&& !m_Temperature->m_bIsHighTemperature
		&& !m_bIsMarketHot
		&& !m_bHasEarnedEnough
		&& !m_bIsNot4433) {
		m_bIsGoodFund = true;
	}
	return m_bIsGoodFund;
}

void Fund::CalcWithdrawalRate() {
	int CurNetVal, WithDrawRate;
	if (nullptr == m_nfNetVal) {
		std::cout << "ERROR! Fund::CalcWithdrawalRate() No input data!\n";
		return;
	}
	for (int i = 0; i < m_nNetValNum; i++) {
		CurNetVal = *(m_nfNetVal + i);
		m_nfMaxNetVal = CurNetVal > m_nfMaxNetVal ? CurNetVal : m_nfMaxNetVal;
		WithDrawRate = 1 - CurNetVal / m_nfMaxNetVal;
	}
	if (WithDrawRate > WITHDRAWALRATETHRES) {
		m_bIsHighWithdrawalRate = true;
	}
}

void Fund::Check4433() {
	int tmp[4];
	if (0 == m_nTotal) {
		std::cout << "ERROR! Check4433() No input data!\n";
		return;
	}
	for (int i = 1; i < 4; i++) {
		tmp[i] = m_nRank[i] / m_nTotal;
	}
	if (tmp[0] > 1 / 4
		|| tmp[1] > 1 / 4
		|| tmp[2] > 1 / 3
		|| tmp[3] > 1 / 3) {
		m_bIsNot4433 = true;
	}
}

void Fund::CalcReturnRate() {
	if (true == m_bHasBuyed) {
		m_nfTotRate = (1 - (m_nfCurNetVal / m_nfBuyNetVal)) * 100;
		int delta = (m_nCurDay[0] - m_nBuyDay[0]) * 365
			+ (m_nCurDay[1] - m_nBuyDay[1]) * 30
			+ (m_nCurDay[2] - m_nBuyDay[2]) * 1;
		m_nfAnnualRate = m_nfTotRate / delta * 365;
		std::cout << "Fund " << m_cSymbol << "Has earned: " << m_nfTotRate
			<< ", expect annual rate is:" << m_nfAnnualRate << "\n";
		if (RETURNRATETHRES < m_nfTotRate) {
			m_bHasEarnedEnough = true;
			std::cout << "WARNING! Fund::CalcReturnRate() Earned enough! Don't be greedy!\n";
		}
	}
}

void Fund::CheckMarketHotness() {
	if (0 == m_nfGDP || 0 == m_nfMarketValue) {
		std::cout << "ERROR! Fund::CheckMarketHotness() No input data!\n";
		return;
	}
	m_nfSecuritizationRate = m_nfMarketValue / m_nfGDP * 100;
	if (SECURITIZATIONRATETHRES < m_nfSecuritizationRate) {
		std::cout << "WARNING! Fund::CheckMarketHotness() Securitization rate is "<< m_unSecuritizationRate
			<<"Don't be zealous!";
	}
}