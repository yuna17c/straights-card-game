## 1 Objectives
Straights is a four-player game. The objective is to get the fewest number of points among the players. The game ends when
one player accumulates 80 points or more, and the player with the lowest score is declared the winner. If the lowest score is a tie, then all players with that score win.

## 2 The Deck
Straights uses a standard 52-card deck, without the jokers. Each player is dealt 13 cards at the beginning of each round. In this game, the Ace is considered to be the lowest card in each suit (rank of 1), while the King is the highest (rank of 13).

## 3 Gameplay
3.1 Legal Plays
Immediately following the deal, the player with the 7 of spades goes first. This player must play the 7 of spades in the centre of the table. After the 7 of spades, the players take turns to play cards on the table. At this point, the players must play cards that constitute legal plays. The following cards are legal:
• A 7 of any suit. This card starts a new pile on the table.
• A card with the same suit and adjacent rank2
as another card that has already been played. It must be played on the pile
of the appropriate suit. (Note that the “pile” is spread across the table, so that play can proceed at either end.)

For example, if the 7 of spades is the only card on the table, then the legal plays are: the 7 of diamonds, the 7 of hearts, the 7 of clubs, the 8 of spades, and the 6 of spades. Once the 8 of spades is played, the next legal plays are: the 9 of spades, the 6 of spades, the 7 of diamonds, the 7 of hearts, and the 7 of clubs. In this way, you can add cards to either end of the suit “pile” so long as there are no gaps.

3.2 Discards
When a player has no legal plays, they must then choose a card in their hand, and place it face down in front of them. This is a discard. Note that if a player has at least one legal play in their hand, then they must make a legal play; they may not discard in this case.

## 4 Scoring
The round ends when all the cards have either been played or discarded. For each player, their score for the round is the sum of all the ranks of the player’s discards. Jacks, Queens, and Kings count as 11, 12, and 13 points, respectively. For example, if a player discarded an Ace, a Six, and a King, the number of points would be 1 + 6 + 13 = 20.
Each player’s game score is of the sum of their scores in each round. If no player has accumulated 80 or more points at
the end of a round, then the deck is reshuffled and another round begins. Note that the game does not end early since points are only scored at the end of the round, thus the game won’t know if someone has reached 80 or more points until the round ends.

## 5 Cards
A card is represented in the program output as <rank><suit> (e.g. 7S). For the ranks, T=10, J=Jack, Q=Queen, K=King.
The suits are: C=Clubs, D=Diamonds, H=Hearts. S=Spades.
Initially, the cards in the deck must be in the following order:
AC 2C 3C ... TC JC QC KC AD 2D ... QD KD AH 2H ... QH KH AS 2S ... QS KS

## 6 Commands
- play <card>
- discard <card>
- deck
- quit
- ragequit: computer player takes over the human player

