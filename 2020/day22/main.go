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
	"log"
)

var DEBUG = false

const (
	PLAYER_1 = 1
	PLAYER_2 = 2
)

// calculate the score of the winning hand of cards
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

// part 1
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

// copy as many as numOfCards into a new deck
// for using when calling recursionCards()
func copyDeck(deck *queue, numOfCards int) *queue {
	if deck.head == nil {
		return nil
	}

	tmp := deck.head
	deckCopy := queueInit()

	for tmp != nil && numOfCards > 0 {
		deckCopy.addCard(tmp.card)
		tmp = tmp.next
		numOfCards--
	}
	return deckCopy
}

// check savedDecks array to see if both of these decks
// have been seen before in game
func compareDecks(deck string, savedDecks []string) bool {
	// we only have one deck as a parameter rather than both
	// this is because the same final answer is recieved whether
	// one or both of the decks are compared. This probably shouldn't
	// be the case from the language of the directions, but it
	// saves some resources here to deal with only one deck

	// convert the deck to a string
	//s1 = deck.toString()

	// check if that string in the savedDecks array
	for _, d := range savedDecks {
		if deck == d {
			return true
		}
	}
	return false
}

func recursionCards(deck1, deck2 *queue) int {
	var winner int
	var savedDecks []string

	for deck1.len() > 0 && deck2.len() > 0 {
		
		deckStr := deck1.toString()
		if compareDecks(deckStr, savedDecks) {
			return PLAYER_1
		}
		savedDecks = append(savedDecks, deckStr)

		deck1Card := deck1.drawCard()
		deck2Card := deck2.drawCard()

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

	// part 1
	n := playCards(player1, player2)
	if n == PLAYER_1 {
		n = calculateScore(player1)
		fmt.Println("part 1:", n)
	} else {
		n = calculateScore(player2)
		fmt.Println("part 1:", n)
	}

	// part 2
	n = recursionCards(p1cpy, p2cpy)
	if n == PLAYER_1 {
		n = calculateScore(p1cpy)
		fmt.Println("part 1:", n)
	} else {
		n = calculateScore(p2cpy)
		fmt.Println("part 1:", n)
	}
}


// QUEUE STRUCTURE

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

// convert each card in a deck into a single string
// this is used for comparing the decks
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

// create a copy of a deck of cards
func (q *queue) deckcpy() *queue {
	if q.head == nil {
		return nil
	}
	d := queueInit()
	tmp := q.head
	for tmp.next != nil {
		d.addCard(tmp.card)
		tmp = tmp.next
	}
	d.addCard(tmp.card)
	return d
}
