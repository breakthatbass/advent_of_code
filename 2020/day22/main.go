/**
 * day 22 2020
 * https://adventofcode.com/2020/day/22
 *
 * compile:			go build main.go
 * run:				./main < input
 * compile & run:	go run main.go < input
 **/
package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

var DEBUG = false

const (
	PLAYER_1 = 1
	PLAYER_2 = 2
)

func calculateScore(deck *queue) int {
	total := 0
	numCards := deck.len()
	tmp := deck.head

	for numCards > 0 {
		total += (tmp.card * numCards)
		numCards--
		tmp = tmp.next
	}
	return total
}

func playCards(deck1, deck2 *queue) int {

	for deck1.len() > 0 && deck2.len() > 0 {
		deck1Card := deck1.drawCard()
		deck2Card := deck2.drawCard()

		if deck1Card > deck2Card {
			deck1.addCard(deck1Card)
			deck1.addCard(deck2Card)
		} else {
			deck2.addCard(deck2Card)
			deck2.addCard(deck1Card)
		}
	}

	// if we're here then one player has no cards
	if deck1.len() == 0 {
		return PLAYER_2
	}
	return PLAYER_1
}

// copy numOfCards nodes from deck into another queue
func copyDeck(deck *queue, numOfCards int) *queue {
	tmp := deck.head
	if tmp == nil {
		return nil
	}

	deckCopy := queueInit()

	for tmp != nil && numOfCards > 0 {
		deckCopy.addCard(tmp.card)
		tmp = tmp.next
		numOfCards--
	}
	return deckCopy
}


var s1 string
// check savedDecks array to see if both of these decks
// have been seen before in game
func compareDecks(deck *queue, savedDecks []string) bool {
	s1 = deck.toString()

	for _, d := range savedDecks {
		if s1 == d {
			return true
		}
	}
	return false
}

var recursionWinner int
var gameNumber int
var i int

func recursionCards(deck1, deck2 *queue) int {
	var winner int
	round := 1
	gameNumber++

	var savedDecks []string

	for deck1.len() > 0 && deck2.len() > 0 {

		if compareDecks(deck1, savedDecks) {
			return PLAYER_1
		}

		savedDecks = append(savedDecks, s1)

		deck1Card := deck1.drawCard()
		deck2Card := deck2.drawCard()

		// recurse
		if deck1.len() >= deck1Card && deck2.len() >= deck2Card {
			// winner determined by recursive combat
			winner = recursionCards(copyDeck(deck1, deck1Card), copyDeck(deck2, deck2Card))
		} else {
			if deck1Card > deck2Card {
				winner = PLAYER_1
			} else {
				winner = PLAYER_2
			}
		}
		switch winner {
		case PLAYER_1:
			deck1.addCard(deck1Card)
			deck1.addCard(deck2Card)
		case PLAYER_2:
			deck2.addCard(deck2Card)
			deck2.addCard(deck1Card)
		}
		round++
	}

	if deck1.len() == 0 {
		return PLAYER_2
	}
	return PLAYER_1
}

func main() {

	player1 := queueInit()
	player2 := queueInit()

	// start with saving the values in the file into player 1's deck
	playerState := PLAYER_1

	scan := bufio.NewScanner(os.Stdin)
	for scan.Scan() {

		line := scan.Text()

		if line == "Player 1:" || line == "" {
			continue
		} else if line == "Player 2:" {
			// save values into player 2's deck
			playerState = PLAYER_2
			continue
		}

		card, _ := strconv.Atoi(line)

		switch playerState {
		case PLAYER_1:
			player1.addCard(card)
		case PLAYER_2:
			player2.addCard(card)
		}
	}
	// 2 copies of the decks for part 1 and part 2
	p1cpy := player1.deckcpy()
	p2cpy := player2.deckcpy()

	n := playCards(player1, player2)
	if n == PLAYER_1 {
		fmt.Println("part 1:", calculateScore(player1))
	} else {
		fmt.Println("part 1:", calculateScore(player2))
	}

	n = recursionCards(p1cpy, p2cpy)

	fmt.Println("player 1 score", calculateScore(player1))

}

///////////////////////////////////////
//									 //
//	QUEUE STRUCTURE					 //
///////////////////////////////////////

// a single card in a deck
type node struct {
	card int
	next *node
}

// the deck of cards
type queue struct {
	head   *node
	tail   *node
	length int
}

func queueInit() *queue {
	return &queue{
		head:   nil,
		tail:   nil,
		length: 0,
	}
}

func newNode(v int) *node {
	return &node{
		card: v,
	}
}

func (q *queue) toString() string {
	var v []string
	tmp := q.head

	for tmp.next != nil {
		v = append(v, fmt.Sprintf("%d", tmp.card))
		tmp = tmp.next
	}

	v = append(v, fmt.Sprintf("%d", tmp.card))
	res := strings.Join(v, "")
	return res
}

// peek at the top card
func (q *queue) peek() int {
	return q.head.card
}

// pull a card from the top of the card deck
func (q *queue) drawCard() int {
	tmp := q.head
	if tmp == nil {
		return -1
	}
	q.head = tmp.next
	q.length--
	return tmp.card
}

// add a card to the bottom of the card deck
func (q *queue) addCard(c int) {
	n := newNode(c)
	//fmt.Println(poo)
	//poo++
	if q.head == nil {
		// empty list
		q.head = n
		q.tail = n
	} else {
		tmp := q.tail
		tmp.next = n
		q.tail = n
	}
	q.length++
}

// get the number of cards in a deck
func (q *queue) len() int {
	return q.length
}

// print all the cards in a deck
func (q *queue) printList() {
	tmp := q.head
	if tmp == nil {
		return
	}

	for tmp.next != nil {
		fmt.Printf("%d ", tmp.card)
		tmp = tmp.next
	}
	fmt.Printf("%d\n", tmp.card)
}

func (q *queue) deckcpy() *queue {
	d := queueInit()
	tmp := q.head
	for tmp.next != nil {
		d.addCard(tmp.card)
		tmp = tmp.next
	}
	d.addCard(tmp.card)
	return d
}