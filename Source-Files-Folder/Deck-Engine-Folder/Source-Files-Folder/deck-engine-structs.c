
#include "../Header-Files-Folder/engine-include-file.h"

const unsigned int RANK_NONE  = 0b0000;
const unsigned int RANK_ACE   = 0b0001;
const unsigned int RANK_TWO   = 0b0010;
const unsigned int RANK_THREE = 0b0011;
const unsigned int RANK_FOUR  = 0b0100;
const unsigned int RANK_FIVE  = 0b0101;
const unsigned int RANK_SIX   = 0b0110;
const unsigned int RANK_SEVEN = 0b0111;
const unsigned int RANK_EIGHT = 0b1000;
const unsigned int RANK_NINE  = 0b1001;
const unsigned int RANK_TEN   = 0b1010;
const unsigned int RANK_JACK  = 0b1011;
const unsigned int RANK_QUEEN = 0b1100;
const unsigned int RANK_KING  = 0b1101;

const unsigned int SUIT_NONE   = 0b000;
const unsigned int SUIT_SPADES = 0b001;
const unsigned int SUIT_HEARTS = 0b010;
const unsigned int SUIT_CLUBS  = 0b011;
const unsigned int SUIT_DIMNDS = 0b100;
const unsigned int SUIT_JOKER  = 0b101;

const Card CARD_SUIT_MASK = 0b1110000;
const Card CARD_RANK_MASK = 0b0001111;

const unsigned int CARD_SUIT_SHIFT = 4;
const unsigned int CARD_RANK_SHIFT = 0;