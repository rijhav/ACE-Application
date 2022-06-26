#include "card.h"
#include "deck.h"
#include "player.h"
#include <iostream>
#include <iomanip>
#include <ctime>


using namespace std;

#define CARD 0
#define DECK 1
#define PLAYER 2
#define TEST_NUM PLAYER

/*
int main ()
{
	player COM1;
	cout << "PLAYER w/ one card " << endl;
	COM1.hand_add_to_player(card());
	COM1.print();
	cout << "PLAYER w/ more cards " << endl;

	card a;
	a.number = 1;
	a.color = wild;
	card b;
	b.number = 3;
	b.color  = yellow;
	card c;
	c.number = 2;
	c.color  = red;

	COM1.hand_add_to_player(a);
	COM1.hand_add_to_player(b);
	COM1.hand_add_to_player(c);

	COM1.print();


	// testing copy cctor
	cout << "copy cctor test player COM3(COM1);" << endl;
	player COM3(COM1);
	COM3.print();

	// testing operator equal
	cout << "operator equal COM4 = COM3" << endl;
	player COM4;
	COM4 = COM3;
	COM4.print();


	//testing removing cards from player's hand
	cout << "removing cards from player " << endl;

	player COM2;
	COM2.hand_add_to_player(card());
	COM2.hand_add_to_player(a);
	COM2.hand_add_to_player(b);
	COM2.hand_add_to_player(c);
	COM2.print();
	cout << endl;

	for (int i = 3 ; i >= 0 ; i--)
	{
		COM2.hand_remove_from_player(i);
		COM2.print();
		cout << endl;

	}


	for (int i = 0 ; i < 10 ; i ++)
	{
		COM2.hand_add_to_player(card());
	}
	COM2.print();
	cout << endl;
	for (int i = 0 ; i < 10 ; i ++)
	{
		COM2.hand_remove_from_player(0);
	}
	COM2.print();
	cout << endl;




	return 0;


}*/


