#ifndef PLAYER_H
#define PLAYER_H
#include "card.h"

class player  {
	public:
		player();
		player(const player & other);
		~player();

		const player & operator= (const player & other);

		void hand_add_to_player(card temp);
		void ace();
		void print() const;

		int get_size() const;

		card peek(int pos) const;
		card peek() const;
		card hand_remove_from_player(int pos);

	private:
		class card_elem  {

		  public:

			card_elem()  {
				next = NULL;
			}

			card data;
			card_elem * next;
		};

        card_elem * head;
		int size;
		void copy(const player & other);
		void clear();
};
#endif
