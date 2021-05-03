#Insert Header Here
.data
	
	DECKSIZE: .word 52 #const int DECK_SIZE = 52;
	#int hands[4][13] = {{0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,0,0,0}};
	deckTop: .word  0 #int deckTop = 0;
	deck: .space 208 #int deck[DECK_SIZE]; 52* 4 bytes
	pairLimit: .word 52	#int pairLimit = 2;
	score: .word 0, 0, 0, 0 #int scores[4] = {0,0,0,0};
	numberOfPlayers: .space 4 #int numberOfPlayers = 0; 
	hands: .word 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
	four: .word 4
	thirteen: .word 13
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
		la $s0, deck #loading in deck $s0 = deck
          	la $s1, DECKSIZE #loading deck SIZE
          	lw $s2, deckTop #loading deckTop
          	la $s3, numberOfPlayers # loaind number of players
          	lw $t8, four
          	lw $t9, thirteen
        	move $a0, $s0
        	move $a1, $s1
        
       	 	jal createDeck
       	 	jal clearAllTemps
        	move $v0,$s0 # moving deck to back to $s0
        
        	la $a0, seedAsk # to move to startGame - Ask for seed number
        	li $v0, 4
        	syscall
        
        	move $a3, $s0 #move deck to arugement3
        
        	jal shuffleDeck
        	jal clearAllTemps
        	
        	move $a0, $v0
        
        	la $a0, playerAsk # to move to startGame - Ask for player number (2-4)
        	li $v0, 4
        	syscall
        	
        	li $v0, 5 # user input playerSize
		syscall
		
        	move $s3,$v0 # update playerSize
        	
        	move $a3, $s0 # move deck to Arguemnt 3 for next function
        	move $a0,$s3 # move player size to arument 0 
        	
        	jal dealCards
        	jal clearAllTemps
        	
		

		
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

	#Boris Marin
	printStr:
		li $v0, 4
		syscall
	jr $ra

	#Boris Marin
	printInt:
		li $v0, 1
		syscall
	jr $ra

	#Boris Marin
	inputInt:
		li $v0, 5
		syscall
	jr $ra

	#Boris Marin
	swap:
		move $v0, $a1
		move $v1, $a0
	jr $ra

	#Boris Marin
	getHandsCardValue:
		addi $sp, $sp -4
		sw $ra, 0($sp)
		jal clearAllTemps
		
		move $t0, $a0 #playerIndex
		move $t1, $a1 #cardIndex
		
		mult $t0, $t9
		mflo $t0
		
		add $t2, $t0, $t1
		
		mult $t2, $t8
		mflo $t2
		
		lw $t0, hands($t2)
		move $v0, $t0
		lw $ra, 0($sp)
		addi $sp, $sp, 4
	jr $ra
	
	#Boris Marin
	setHandsCardValue:
		addi $sp, $sp -4
		sw $ra, 0($sp)
		jal clearAllTemps
		
		move $t0, $a0 #playerIndex
		move $t1, $a1 #cardIndex
		move $t4, $a2 #cardValue
		
		mult $t0, $t9
		mflo $t0
		
		add $t2, $t0, $t1
		
		mult $t2, $t8
		mflo $t2
		
		sw $t4, hands($t2)
		
		lw $ra, 0($sp)
		addi $sp, $sp, 4
	jr $ra

	#int goFish (int player, int expCard) {
    	#	if (isEmpty()) {
        #		printf("All fish is DEAD(deck is empty).\n");
        #		return 0;
    	#	} else {
        #		printf("You are fishing(email) now. (Bad hacker stuff)\n");
        #		int card = draw(deck, deckTop);
        #		hands[player][card]++;
        #		printf("You got: %d\n", card);
        #		return expCard == card;
    	#	}
	#}
	goFish: #playerIndex #expCard
		addi $sp, $sp -4
		sw $ra, 0($sp)
		jal clearAllTemps
		
		move $t0, $a0
		move $t1, $a1
		
		jal isEmpty
		bne $v0, 1, else
		if:
			la $a0, deckEmpty
			jal printStr
			li $v0, 0
			j endIf
		else:
			la $a0, goFishText
			jal printStr
			
			jal draw
			move $t2, $v0
			
			move $a0, $t0
			move $a1, $t2
			jal getHandsCardValue
			move $a0, $t0
			move $a1, $t2
			addi $a2, $v0, 1
			jal setHandsCardValue
			
			la $a0, youHave
			jal printStr
			move $a1, $t2
			jal printInt
			
			seq $t3, $t1, $t2
			move $v0, $t3
			j endIf
		endIf:
		lw $ra, 0($sp)
		addi $sp, $sp, 4
	jr $ra
	
	#void moveCards(int srcPlayer, int targetPlayer, int card){
    	#	printf("You got the card you asked for, in your nasty hands!\n");
    	#	while(cardInHand(srcPlayer, card)) {
        #		hands[srcPlayer][card]--;
        #		hands[targetPlayer][card]++;
    	#	}		
	#}
	#Boris Marin
	moveCards: #srcPlayer, targetPlayer, card
		addi $sp, $sp -4
		sw $ra, 0($sp)
		jal clearAllTemps
		
		move $t0, $a0 #srcPlayer
		move $t1, $a1 #targetPlayer
		move $t2, $a2 #cardIndex
		
		la $a0, successFish
		jal printStr
		
		while:
			move $a0, $t0
			move $a1, $t2
			jal cardInHand
			bne $v0, 1, endWhile
			
			move $a0, $t0
			move $a1, $t2
			jal getHandsCardValue
			move $a0, $t0
			move $a1, $t2
			subi $a2, $v0, 1
			jal setHandsCardValue
			
			
			move $a0, $t1
			move $a1, $t2
			jal getHandsCardValue
			move $a0, $t1
			move $a1, $t2
			addi $a2, $v0, 1
			jal setHandsCardValue
			
			j while
		endWhile:		
		
		lw $ra, 0($sp)
		addi $sp, $sp, 4
	jr $ra
	
	#Keyoni McNair
	createDeck: #void createDeck() { $a0 = deck
		li $t1, 52 #deck size
    		li $t2, 13 # 13
    		li $t4, 0 # counter for j int j = 0
    		whileDeck: 
    			div $t4, $t2 #j % 13;
    			mfhi $t5	
    			#   while (j < 52)  {	
    			sw $t5, 0($a0)  #  deck[j] = j % 13;
    		
    			addi $a0, $a0, 4 # moves deck index
   			addi $t4,$t4,1  #j++
   		
    			blt $t4,$t1, whileDeck # while (j < 52)
     	endWhile:	
     	jr $ra
     	#Keyoni McNair
     	shuffleDeck: #void shuffleDeck() { $a3 = deck
     		addi $sp, $sp -4 # saving addresson the stack
		sw $ra, 0($sp)
		
		move $t7, $a3 # start pointer of deck is at $t7
		addi $t6, $zero, 4
		
     		li $v0, 5 # user input seed number
		syscall
     	
     		move $t0, $v0 #shuffle number = $t0
     		
     		mult $t1, $zero # clear $t1
     		mflo $t1 # $t1 = 0
     		
     		addi $t1, $t1, 51 # $t1 = int  i = DECK_SIZE-1;
     		
     		
     		
     		shuffleLoop:  # for (int i = DECK_SIZE-1; i > 0; i--){
     		
     			move $t2, $zero # clear $t2
     			move $t4, $zero # clear $t4
     			move $t5, $zero # clear $t5
     			
     			add $t5, $t5, $t1 # $t5 = 51
     			
     			mult $t5, $t6 # $t5 = i *4 for memory
     			mflo $t5
     			 
     			
  			addi $t2, $t1, 1  #    int j = shuffleNumber % (i+1);  # $t2 = (i+1)
     			div $t0, $t2
     			mfhi $t2 # $t2 = j
     			
     			mult $t2, $t6 # $t2 = j * 4 for memory
     			mflo $t2
     			
     			lw $t4, deck($t5) #deck[i]
 
     			#move $a0, $a3 # moving deck[i] to $a0
     			move $a0, $t4
     			
     			lw $t4, deck($t2)
   
     			move $a1, $t4
   			
   			jal swap #    swap(&deck[i], &deck[j]); swap ($a0, $a1) => $v0 = $a1 $v1= $a0 
   			
     			sw $v1, deck($t2) # putting what was in deck[i] in deck[j]
     
     			sw $v0, deck($t5) # putting what was in deck[j] in deck[i]
   			
   			subi $t1, $t1, 1 # i--
   			bgtz $t1, shuffleLoop  # i > 0
   			
   		shuffleLoopEnd:
   			
 		 #  for(int i = 0; i < DECK_SIZE; i++) {
 		 #      printf("*(deck + [%d]) : %d\n", i, *(deck + i) );
    		
    	shuffleDeckEnd:
    		move $v0, $a3
    		lw $ra, 0($sp)
		addi $sp, $sp, 4
	jr $ra

	#Keyoni McNair
	draw: #int draw () {
		mult $s2, $t8 #decktop * 4
    		mflo $t7
    		
		lw $t7, deck($t7)     #int card = deck[deckTop]; $t7 = deck[deckTop[
    		addi $s2, $s2, 1  # deckTop = deckTop + 1;
    		
  		move $v0,$t7  # return card;
  		
  	jr $ra
  	
  	#Keyoni McNair
  	dealCards: #void dealCards (int cardPerHand) { card per Hand = 5 arguments $a0 = numberOfPlayers $a3 = deck 
   		addi $sp, $sp -4 # saving addresson the stack
		sw $ra, 0($sp)
		
   		addi $t1, $t1, 0 #i = 0
   		addi $t2, $t2, 5 # $t2 = cardPerHand = 5
   		
   		dealCardsLoopI: #for(int i = 0; i < cardPerHand; i++){
   		move $t3, $zero #j = 0
   		
    			dealCardsLoopJ: #    for(int j = 0; j < numberOfPlayers; j++){
    				jal draw #        int card = draw(deck, deckTop); $v0 = card
    				move $t4, $v0 #move cardnumber to $t4
    				
    				
    				mult $t3, $t9  #       hands[j][card]++; player * 13
    				mflo $t5
    				add $t5, $t5, $t4 # (player*13) + card
    				
    				mult $t8, $t5  # (player*13) + card * 4 for address
    				
 				mflo $t5 # [j][card]
 				
 				lw $t6, hands($t5) # get current count at card
    				
    				addi $t6, $t6, 1 # current count ++  

    				sw $t6, hands($t5) # updare current count at card   		
    				
    				addi $t3, $t3, 1 #j++
    				blt $t3, $a0, dealCardsLoopJ # j < numberOfPlayers
    				
    			addi $t1, $t1, 1 #i++
    			blt $t1, $t2, dealCardsLoopI		#i < cardPerHand
   	dealCardsEnd:
   		move $v0, $a3
    	lw $ra, 0($sp)
    	jr $ra

	#Anthony Herrera
  	isEmpty: #Checks to see if the deckTop == DECKSIZE. If so, the deck is empty
		lw $t0, deckTop
		lw $t1, DECKSIZE
		
		seq $t2, $t0, $t1
		
		move $v0, $t2
	jr $ra
	
	#Anthony Herrera
	cardInHand: #Determines whether or not a card is in the hand. $a0 = playerIndex, $a1 = cardIndex
		addi $sp, $sp -4
		sw $ra, 0($sp)
		
		jal getHandsCardValue
		
		#if(hands[targetPlayer][card] > 0); if $v0 > 0 return 1, else 0.
    		seq $v0, $zero, $v0
    		
		lw $ra, 0($sp)
		addi $sp, $sp, 4
	jr $ra

	clearAllTemps:
		move $t0, $zero
		move $t1, $zero
		move $t2, $zero
		move $t3, $zero
		move $t4, $zero
		move $t5, $zero
		move $t6, $zero
		move $t7, $zero
	jr $ra
    		

	#End of Program
	exit:
		li $v0, 10
		syscall
