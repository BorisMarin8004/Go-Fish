#Insert Header Here
.data
	
	DECKSIZE: .word 52 #const int DECK_SIZE = 52;
	#int hands[4][13] = {{0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0}};
	deckTop: .word  0 #int deckTop = 0;
	deck: .space 208 #int deck[DECK_SIZE]; 52* 4 bytes
	pairLimit: .word 52	#int pairLimit = 2;
	score: .word 0, 0, 0, 0 #int scores[4] = {0,0,0,0};
	numberOfPlayers: .space 4 #int numberOfPlayers = 0; 
	type: .word 0,1,2,3,4,5,6,7,8,9,10,11,12 #int type[13] = {0,1,2,3,4,5,6,7,8,9,10,11,12}; for createDeck()
	
	# TEXT PHRASES
	pairAsk: .asciiz "Enter how many pair you want to play(put either 2 or 4):  "
	seedAsk: .asciiz "Enter an integer between 50 - 1000(seed): "
	playerAsk: .asciiz "Enter number of players between 2-4: "
	playerTurn: .asciiz "\nPlayer %d's turn!\n"
	playerHand: .asciiz "\nPlayer %d's hand!\n"
	youHave: .asciiz "You have " #print number at index and index after this
	space: .asciiz " " # a space
	onlyFish: .asciiz "You can only fish, your hand is empty.\n"
	turnAsk: .asciiz "Which Player would you like to ask for which card in your hand? (Player Number, Card Number): \n" 
	deckEmpty: .asciiz "All fish is DEAD(deck is empty).\n"
	goFishText: .asciiz "You are fishing(email) now. (Bad hacker stuff)\n"
	successFish: .asciiz "You got the card you asked for, in your nasty hands!\n"
	cannotFishSelf: .asciiz "Sorry, cannot yourself ya'\n"
	playAgainText: .asciiz "Would you like to play again?(1 for yes, 0 for no): \n"
	playerScores: .asciiz "Here are the scores in order by player: " # Might just be better to print a list of the scores and be less fancy haha
	
.text
	main:
		la $s0, deck #loading in deck
		la $s1, DECKSIZE #loading deck SIZE
		move $a0, $s0
		move $a1, $s1
		
		#jal createDeck
		
		li $t0, 3
		li $t1, 4
		
		move $a0, $t0
		jal printInt
		move $a0, $t1
		jal printInt
		
		move $a0, $t0
		move $a1, $t1
		jal swap
		move $t0, $v0
		move $t1, $v1
		
		la $a0, space
		jal printStr
		
		move $a0, $t0
		jal printInt
		move $a0, $t1
		jal printInt

		li $s0, 0
		li $s1, 0
	
		whileOuter:
			beq $s0, 4, endWhileOuter
				whileInner:
					beq $s1, 13, endWhileInner
					move $a0, $s0
					move $a1, $s1
					jal getHandsCardValue
					move $a0, $v0
					jal printInt
					addi $s1, $s1, 1
					j whileInner
				endWhileInner:
			li $s1, 0
			addi $s0, $s0, 1
			j whileOuter
		endWhileOuter:
	
	j exit

	printStr:
		li $v0, 4
		syscall
	jr $ra

	printInt:
		li $v0, 1
		syscall
	jr $ra

	inputInt:
		li $v0, 5
		syscall
	jr $ra
	
	swap:
		move $v0, $a1
		move $v1, $a0
	jr $ra

	getHandsCardValue:
		move $t1, $zero
		move $t2, $zero
		move $t3, $zero
		
		move $t0, $a0 #playerIndex
		move $t1, $a1 #cardIndex
		
		li $t3, 13
		
		mult $t0, $t3
		mflo $t0
		
		add $t2, $t0, $t1
		
		li $t3, 4
		
		mult $t2, $t3
		mflo $t2
		
		lw $t0, ARRAY($t2)
		move $v0, $t0
	jr $ra


	#End of Program
	exit:
		li $v0, 10
		syscall
