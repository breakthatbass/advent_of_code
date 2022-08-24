package main

import (
	"fmt"
	"bufio"
	"os"
	"strconv"
)

const (
	PLAYER_1 = iota
	PLAYER_2
)



func _calculateScore(deck *queue) int {
	total := 0
	numCards := deck.getLen()
	tmp := deck.head
	
	for numCards > 0 {
		total += (tmp.card * numCards)
		numCards--
		tmp = tmp.next
	}
	return total
}


func playCards(deck1, deck2 *queue) int {

	for deck1.getLen() > 0 && deck2.getLen() > 0 {

		deck1Card := *deck1.drawCard()
		deck2Card := *deck2.drawCard()

		if deck1Card > deck2Card {
			deck1.addCard(deck1Card)
			deck1.addCard(deck2Card)
		} else {
			deck2.addCard(deck2Card)
			deck2.addCard(deck1Card)
		}
	}

	// if we're here then one player has no cards
	if deck1.getLen() == 0 {
		return _calculateScore(deck2)
	}
	return _calculateScore(deck1)
}

func main() {
	
	player1 := queueInit()
	player2 := queueInit()

	playerState := PLAYER_1
	
	scan := bufio.NewScanner(os.Stdin)
	for scan.Scan() {
		
		line := scan.Text()

		if line == "Player 1:" {
			continue
		} else if line == "Player 2:" {
			playerState = PLAYER_2
			continue
		} else if line == "" {
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
	fmt.Println("part 1:", playCards(player1, player2))
}


///////////////////////////////////////
//									 //
//	QUEUE STRUCTURE					 //
///////////////////////////////////////

// a single card in a deck
type node struct {
	card  int
	next *node
}

// the deck of cards
type queue struct {
	head   *node
	length int
}

func queueInit() *queue {
	return &queue{
		head:   nil,
		length: 0,
	}
}

func newNode(v int) *node {
	return &node{
		card: v,
	}
}

// pull a card from the top of the card deck
func (q *queue) drawCard() *int {
	tmp := q.head
	if tmp == nil {
		return nil
	}
	q.head = tmp.next
	q.length--
	return &tmp.card
}

// add a card to the bottom of the card deck
func (q *queue) addCard(c int) {
	n := newNode(c)
	if q.head == nil {
		q.head = n
	} else {
		tmp := q.head
		for tmp.next != nil {
			tmp = tmp.next
		}
		tmp.next = n
	}
	q.length++
}

// get the number of cards in a deck
func (q *queue) getLen() int {
	return q.length
}

// print all the cards in a deck
func (q *queue) printList() {
	tmp := q.head
	if tmp == nil {
		fmt.Println("list is empty")
		return
	}

	//fmt.Println(tmp.card)
	for tmp.next != nil {
		//fmt.Printf("%+v\n", *cur)
		//fmt.Println(tmp.card)
		fmt.Printf("%d ", tmp.card)
		tmp = tmp.next
	}
	fmt.Printf("%d ", tmp.card)
	fmt.Println()
}

