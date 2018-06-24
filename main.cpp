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

class card
{
public:
	int value;
	card *link;
};

class handOfCards
{
private:
	card *head;
	card *end;
	bool isDealer;

	card *newCard()
	{
		card *temp;
		temp = new card();
		temp->link = NULL;
		srand(time(NULL));
		temp->value = (rand() % 13) + 1;
	}

public:
	handOfCards(bool isDealer)
	{
		head = NULL;
		end = NULL;
		isDealer = isDealer;
	}

	//deals a new card on the hand
	void deal()
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
	int handValue()
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
	void printHand(bool isDealer)
	{
		card *cur = head;
		int cardNum = 1;

		while (cur)
		{
			if (cardNum == 1 && isDealer)
				cout << "*\t";
			else
				cout << cur->value << '\t';

			cur = cur->link;
			cardNum++;
		}

		cout << endl;
	}
};

int main()
{
    return 0;
}

