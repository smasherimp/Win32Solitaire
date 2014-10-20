#pragma once

class CCards
{
public:
	CCards(void);
	~CCards(void);
	void SetValue(int);
	int GetValue();
	void SetSuit(int);
	int GetSuit();
	void RevealCard();

private:
	int m_iCardValue;
	enum m_eCardSuits
	{
		hearts,
		diamonds,
		clubs,
		spades
	};
	bool m_bFaceUp;
};

