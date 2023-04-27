#include "PokerGame.h"

PokerGame::PokerGame() {
	maxNumber = 0;
	PokerGame::type = HighCard;
	//TO_DO: initial constructor
}

void PokerGame::distribute(bool usedCards[52]) {
	for (int i = 0; i < 5; i++) {
		int tmp,input=0;
		while (input == 0) {
			tmp = rand() % 52;
			if (usedCards[tmp] == false) {
				usedCards[tmp] = true;
				PokerGame::playerCards.push_back(tmp);
				input = 1;
			}
		}
	}
	//TO_DO: Random generate five cards to player
	//Hint: Use usedCards to record which card have been distributed
}

void PokerGame::set(vector<int> cards) {
	for (int i = 0; i < 5; i++) {
		PokerGame::playerCards.push_back(cards[i]);
	}
	//TO_DO: Set the cards to player
}

void PokerGame::printCards() {
	cout << "Player cards:" << endl;
	for (int i = 0; i < 5; i++) {
		switch ((PokerGame::playerCards[i])/13) {
		case 0:
			cout << "C";
			break;
		case 1:
			cout << "D";
			break;
		case 2:
			cout << "H";
			break;
		case 3:
			cout << "S";
			break;
		}
		cout << (PokerGame::playerCards[i]) % 13+1 << " ";
		//TO_DO: Print the player's cards.
		// For example: "C1" "S2" "H3" ...
	}
	cout << endl;
}

void PokerGame::sortCards() {
	for (int i = 0; i < 5; i++) {
		for (int j = i + 1; j < 5; j++) {
			if (PokerGame::playerCards[i] % 13 > PokerGame::playerCards[j] % 13 || (PokerGame::playerCards[i] % 13 == PokerGame::playerCards[j] % 13 && PokerGame::playerCards[i] / 13 > PokerGame::playerCards[j] / 13))
				swap(PokerGame::playerCards[i], PokerGame::playerCards[j]);
		}
	}
	//TO_DO: Sort the cards accroding to thier number
}

void PokerGame::evaluate() {
	//cout << "evaluating" << endl;
	sortCards();
	if (this->isStraight() && this->isFlush()) {
		type = StraightFlush;
		//cout << "StraightFlush";
	}
	else if (this->isFourOfKind()) {
		type = FourOfKind;
		//cout << "FourOfKind";
	}
	else if (this->isFullHouse()) {
		type = FullHouse;
		//cout << "FullHouse";
	}
	else if (this->isFlush()) {
		type = Flush;
		//cout << "Flush";
	}
	else if (this->isStraight()) {
		type = Straight;
		//cout << "Straight";
	}
	else if (this->isThreeOfKind()) {
		type = ThreeOfKind;
		//cout << "ThreeOfKind";
	}
	else if (this->isTwoPairs()) {
		type = TwoPairs;
		//cout << "TwoPairs";
	}
	else if (this->isOnePair()) {
		type = OnePair;
		//cout << "OnePair";
	}
	else {
		type = HighCard;
		//cout << "HighCard";
		PokerGame::maxNumber = PokerGame::playerCards[4];
		//TO_DO: Set the maxNumber
	}
}

int PokerGame::getType() {
	return type;
}

int PokerGame::getMaxNumber() {
	return maxNumber;
}

void PokerGame::compare(int type_, int maxNumber_) {
	//TO_DO: Compare the type and output who is winner
	//Compare the type of card first. If types are the same, compare which is max the number of card.
	//If the max number is the same, compare the suit of card.
	//cout << PokerGame::maxNumber << "   " << maxNumber_ << endl;
	if (PokerGame::type > type_ || (PokerGame::type == type_ && (PokerGame::maxNumber % 13 > maxNumber_ % 13 || (PokerGame::maxNumber % 13 == maxNumber_ % 13 && PokerGame::maxNumber / 13 > maxNumber_ / 13))))
		cout << "Player1 win" << endl;
	else
		cout << "Player2 win" << endl;
}

bool PokerGame::isStraight() {
	for (int i = 1; i < 5; i++) {
		if ((PokerGame::playerCards[i] - 1) % 13 != PokerGame::playerCards[i - 1] % 13) {
			return false;
		}
	}
	PokerGame::maxNumber = PokerGame::playerCards[4];
	return true;
	//TO_DO: Check whether the hand of cards is Straight or not and set the maxNumber
}

bool PokerGame::isFlush() {
	for (int i = 1; i < 5; i++) {
		if (PokerGame::playerCards[i] / 13 != PokerGame::playerCards[i - 1] / 13)
			return false;
	}
	PokerGame::maxNumber = PokerGame::playerCards[4];
	return true;
	//TO_DO: Check whether the hand of cards is Flush or not and set the maxNumber
}

bool PokerGame::isFourOfKind() {
	//TO_DO: Check whether the hand of cards is FourOfaKind or not and set the maxNumber
	int cnt = 0, i = 0;
	for ( i = 0; i <= 1; i++) {
		int j = i + 1;
		for (j = i + 1; j <= i + 3; j++) {
			if (PokerGame::playerCards[j] % 13 != PokerGame::playerCards[i] % 13)
				break;
		}
		if (j == i + 4) 
			break;
	}
	if (i == 2)
		return false;
	PokerGame::maxNumber = PokerGame::playerCards[i+3];
	return true;
}

bool PokerGame::isFullHouse() {
	//TO_DO: Check whether the hand of cards is FullHouse or not and set the maxNumber
	int cnt = 0;
	if (PokerGame::playerCards[0] % 13 == PokerGame::playerCards[2] % 13 && playerCards[3] % 13 == PokerGame::playerCards[4] % 13) {
		cnt++;
		PokerGame::maxNumber = PokerGame::playerCards[2];
	}
	else if (PokerGame::playerCards[0] % 13 == PokerGame::playerCards[1] % 13 && playerCards[2] % 13 == PokerGame::playerCards[4] % 13) {
		cnt++;
		PokerGame::maxNumber = PokerGame::playerCards[4];
	}
	if (cnt==0)
		return false;
	return true;
}

bool PokerGame::isThreeOfKind() {
	//TO_DO: Check whether the hand of cards is ThreeOfaKind or not and set the maxNumber
	int cnt = 0, i = 0;
	for (i = 0; i <= 2; i++) {
		int j = i + 1;
		for (j = i + 1; j <= i + 2; j++) {
			if (PokerGame::playerCards[j] % 13 != PokerGame::playerCards[i] % 13)
				break;
		}
		if (j == i + 3)
			break;
	}
	if (i == 3)
		return false;
	PokerGame::maxNumber = PokerGame::playerCards[i+2];
	return true;
}

bool PokerGame::isTwoPairs() {
	//TO_DO: Check whether the hand of cards is TwoPairs or not and set the maxNumber
	int cnt = 0, i = 0,now;
	for (i = 0; i < 4; i++) {
		if (PokerGame::playerCards[i] % 13 == PokerGame::playerCards[i + 1] % 13) {
			cnt++;
			now=++i;
		}
	}
	if (cnt < 2)
		return false;
	PokerGame::maxNumber = PokerGame::playerCards[now];
	return true;
}

bool PokerGame::isOnePair() {
	//TO_DO: Check whether the hand of cards is OnePair or not and set the maxNumber
	int cnt = 0, i = 0;
	int now = 0;
	for (i = 0; i < 4; i++) {
		if (PokerGame::playerCards[i] % 13 == PokerGame::playerCards[i + 1] % 13) {
			cnt++;
			now=++i;
		}
	}
	if (cnt == 0)
		return false;
	PokerGame::maxNumber = PokerGame::playerCards[now];
	return true;
}
