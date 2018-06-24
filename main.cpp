//Blackjack - C++
#include <iostream>

using namespace std;

//enum for face cards
enum FaceCards
{
	ACE = 1,
	JOKER = 11,
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

public:
	handOfCards(bool isDealer)
	{
		head = NULL;
		end = NULL;
		isDealer = isDealer;
	}

	//use linked list for hand of cards
	// random number generator with new card
	//print function with flag on whether or not to print dealer first card
};

int main()
{
    return 0;
}

