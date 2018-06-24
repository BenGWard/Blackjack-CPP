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
		assignValue(temp);
		return temp;
	}

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
		card *cur = head;

		while (cur)
		{
			value += cur->value;
			cur = cur->link;
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

	//bool isBlackjack

	//bool hasAces
};

int main()
{
	bool playertype = false;
	handOfCards player = new handOfCards(playertype);

	for (int i = 0; i < 100; i++)
		player.draw();

	player.print(false);

	system("pause");

    return 0;
}

