/**********************************************************
 * deck.h
 *
 * Deck class
 *
 *   Author: Com L.
 *   Date: Summer 2015
 */




/*
deck will contain class cards

public members will include
shuffle of cards
drawing of cards (+1, +2, +4)
- will use queue to pop out
- check if deck has run out
- if ran out ( reshuffle entire deck)

private members :
 the deck of cards
 a queue

*/

/* Game UNO - wikipedia
deck consists of 108 cards
	25 of each color ( red, green, blue, and yellow)
	each color having two of each rank except zero
	zero to nine
	"Skip"
	"Draw Two"
	"Reverse "
	"Wild "
	"Wild Draw Four"

*/


/*
zero - 4 cards (RGBY)
one till nine - 4 cards (RGBY) & 4 cards (RGBY)
"Skip" -  4 cards (RGBY) & 4 cards (RGBY)
"Draw Two" -  4 cards (RGBY) & 4 cards (RGBY)
"Reverse " -  4 cards (RGBY) & 4 cards (RGBY)
"Wild " -  4 cards (RGBY)
"Wild Draw Four" -  4 cards (RGBY)

*/


#ifndef DECK_H
#define DECK_H
#include "card.h"
class deck : public card {
	public:
		deck();//empty constructor
		deck(const deck & other);//initialise deck
		~deck(); //destructor

		const deck & operator= (const deck & other);

		void shuffle_deck();
		void create_deck();
		void quick_shuffle_deck();
		void print_deck();

		int get_size();
		int add_card_to_deck(card temp_card);

        card draw();
	private:
		card * ptr_deck;

		int size;

		void clear();
		void copy(const deck & other);
};

/**
 * Stream operator that allows a deck to be written to standard streams
 * (like cout).
 *
 * @param out Stream to write to.
 * @param temp_deck to write to the stream.
 */
std::ostream & operator<<(std::ostream & out, deck const & temp_deck);

#endif


