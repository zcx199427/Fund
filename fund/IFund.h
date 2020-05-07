// Created by Carl Zhang on 2020/05/06
#include "temperature.h"
#ifndef  _H_IFund_H_
#define  _H_IFund_H_

#define WITHDRAWALRATETHRES 0.05 // 5%
#define RETURNRATETHRES     80   // 80%
#define SECURITIZATIONRATETHRES 80 // 80%
enum FundType {
	UNKNOWN = -1,
	CURRENCY,
	BOND,
	HYBRID,
	STOCK
};
class Fund {
private:
	char m_cSymbol[7] = {0}; // 6 + '\0'
	FundType m_Type;
	bool m_bIsGoodFund;
	// calc withdrawal rate
	unsigned int m_nNetValNum;
	float *m_nfNetVal;
	float m_nfMaxNetVal;
	bool m_bIsHighWithdrawalRate;
	// calc temperature
	Temperature *m_Temperature;
	// check "4433"
	int m_nTotal;
	int m_nRank[4];
	bool m_bIsNot4433;
	// calc return rate
	bool m_bHasBuyed;
	bool m_bHasEarnedEnough;
	float m_nfBuyNetVal;
	float m_nfCurNetVal;
	int m_nBuyDay[3];//y.m.d
	int m_nCurDay[3];//y.m.d
	float m_nfTotRate;
	float m_nfAnnualRate;
	// global index
	float *m_nInterestRateof10y;
	float m_nfMarketValue;
	float m_nfGDP;
	float m_nfSecuritizationRate;
	bool m_bIsMarketHot;

	void CalcWithdrawalRate();
	void Check4433();
	void CalcReturnRate();
	void CheckMarketHotness();
public:
	Fund();
	~Fund();
	bool Process();
};
#endif // ! _H_IFund_H_
