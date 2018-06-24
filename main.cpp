//Blackjack - C++
#include <iostream>
#include <ctime>

using namespace std;

//enum for face cards
enum FaceCards
{
	ACE = 1,
	JACK = 11,
	QUEEN = 12,
	KING = 13
};

ostream &operator<<(ostream &outs, FaceCards card)
{
	switch (card)
	{
	case ACE:
		outs << "Ace";
		break;
	case JACK:
		outs << "Jack";
		break;
	case QUEEN:
		outs << "Queen";
		break;
	case KING:
		outs << "King";
		break;
	default:
		outs << static_cast<int>(card);
		break;
	}

	return outs;
}

class card
{
public:
	int type;
	int value;
	card *link;
};

class handOfCards
{
private:
	card *head;
	card *end;

	card *newCard()
	{
		card *temp;
		temp = new card();
		temp->link = NULL;
		temp->type = (rand() % 13) + 1;
		temp->value = assignValue(temp);
		return temp;
	}

	//assigns the values to cards base on the card type
	int assignValue(card *temp)
	{
		int val;
		FaceCards tempType;
		tempType = static_cast<FaceCards>(temp->type);

		//assign value of 10 to jack, queen, king
		//everyone else just gets their card type (1-10)
		if (tempType == JACK || tempType == QUEEN || tempType == KING)
			val = 10;
		else
			val = temp->type;

		return val;
	}

public:
	handOfCards()
	{
		head = NULL;
		end = NULL;
		srand(time(NULL));
	}

	//deals a new card on the hand
	void draw()
	{
		card *temp;
		temp = newCard();

		if (head == NULL)
		{
			head = temp;
			end = temp;
		}
		else
		{
			end->link = temp;
			end = temp;
		}
	}

	//adds up the hand
	int value()
	{
		int value = 0;
		int aceCount = 0;
		card *cur = head;

		while (cur)
		{
			if (cur->type == 1)
			{
				value += 11;
				aceCount++;
			}
			else
				value += cur->value;
			
			cur = cur->link;
		}

		//if we have aces, and counting them all as 11 has us bust,
		//try setting to 1
		while (aceCount > 0 && value > 21)
		{
			value -= 10; //swap an ace from 11 to 1
			aceCount--;
		}

		return value;
	}

	//print function with flag on whether or not to print dealer first card
	void print(bool hideDealerCard)
	{
		card *cur = head;
		int cardNum = 1;
		while (cur)
		{
			if (cardNum == 1 && hideDealerCard)
				cout << "*\t";
			else
				cout << static_cast<FaceCards>(cur->type) << '\t';

			cur = cur->link;
			cardNum++;
		}

		cout << endl;
	}

	//determines if a hand has been dealt blackjack (only run with two cards dealt)
	bool isBlackjack()
	{
		bool blackjack = false;
		int handValue = head->value + end->value;
		
		//if the hand is a face card or ten and an ace, the value will be 11
		if (handValue == 11)
			blackjack = true;

		return blackjack;
	}

	//determines if a hand has aces in it
	bool hasAces()
	{
		bool aces = false;
		card *cur = head;

		while (cur)
		{
			if (cur->type == 1)
				aces = true;

			cur = cur->link;
		}

		return aces;
	}

	//plays the dealers hand
	void dealerPlay()
	{
		int handValue = value();
		bool aces = hasAces();
		
		if (handValue < 17 && !aces)
			this->draw();
		else if (handValue == 17 && aces)
			this->draw();
	}
};

int main()
{
	handOfCards *player = new handOfCards();
	handOfCards *dealer = new handOfCards();
	bool gameOver = false;
	char hitOrStay;

	//deal first two cards to player and dealer
	for (int i = 0; i < 2; i++)
	{
		player->draw();
		dealer->draw();
	}

	//check for blackjack
	if (player->isBlackjack())
	{
		gameOver = true;
		cout << "You got blackjack! You won!" << endl;
	}
	else if (dealer->isBlackjack())
	{
		gameOver = true;
		cout << "Dealer got blackjack. You lost." << endl;
	}

	while (!gameOver)
	{
		dealer->print(true);
		player->print(false);

		do
		{
			cout << "Do you want to hit or stay? [H / S]:";
			cin >> hitOrStay;
			if (tolower(hitOrStay) != 'h' && tolower(hitOrStay) != 's')
				cout << "Please enter H or S." << endl;
		} while (tolower(hitOrStay) != 'h' && tolower(hitOrStay) != 's');

		if (tolower(hitOrStay) == 'h')
		{
			player->draw();
			dealer->dealerPlay();
		}
		else
		{
			dealer->dealerPlay();
			gameOver = true;
		}
	}

	cout << "Final results:" << endl; 
	cout << "Dealer: " << dealer->value() << endl;
	cout << "Player: " << player->value();

	system("pause");

    return 0;
}

