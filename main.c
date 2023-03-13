#include <stdio.h> 			// must-have
#include <stdlib.h> 		// where srand() and rand() live
#include <time.h> 			// where time() lives

#define UPPER 100 			// max value that can be generated
#define LOWER 1 			// min value that can be generated


// user input error check
void errCheck(int scanout, int* guess, int* errs) { 	
	int i = 1;
		if (scanout != 1) { 									// checks if output of scanf is different to one (the amount of values we need written)
			++*errs; 											// counts the number of errors encountered this way
			printf("\nInput Error!! Maybe try using a number this time:\n> ");
			int c = getchar(); 									// pauses the function to get new input
			errCheck(scanf("%d", guess), guess, errs); 			// writes new value for guess and error checks itself!
	}
}

// function handling the endgame message
void endgame(int* guess, int* errs, int* tries, int* num){
// if you encountered 0 input errors
	if (*guess == *num && *errs == 0) {
		if (*tries > 1)
			printf("\n\aYou guessed it :D !\nIt took you %d tries!\nNice job!:3\n", *tries);
		else if  (*tries == 1)
			printf("\n\aWow! You got it first try!! \nNice job :D\n");
	}
// if there was only 1 input error
	else if (*guess == *num && *errs == 1) {
		if (*tries > 1)
			printf("\n\aYou guessed it :D !\nIt took you %d tries, and 1 error!\nNice job!:3\n", *tries);
		else if  (*tries == 1)
			printf("\n\aWow! You got it first try with 1 error!!\nNice job :D\n");
	}
// if there were multiple input errors
	else if (*guess == *num && *errs >= 1) {
		if (*tries > 1)
			printf("\n\aYou guessed it :D !\nIt took you %d tries, and %d errors!\nNice job!:3\n", *tries, *errs);
		else if  (*tries == 1)
			printf("\n\aWow! You got it first try with %d errors!!\nNice job :D\n", *errs);
	}
}

int main() {
	srand(time(NULL)); 									// seed the rand() function (more at the bottom)
	int num = (rand() % UPPER) + LOWER; 				// generate & store randomly generated number from 1 - 100 (more at the bottom)
	
	int guess, tries = 1, errs = 0; 					// guess = user input; tries = amount of tries (1, because first try doesn't increment the counter); errs = numbers of input errors
	printf("Guess what number I'm thinking of!\n> ");
	errCheck(scanf("%d", &guess), &guess, &errs); 		// run the output of scanf through error check, along w/ necessary values
	
	while (guess != num) {
		++tries; 										// count the amount of tries
		if (guess > num)
			printf("\nMy number is less than that!\n> ");
		else if (guess < num)
			printf("\nMy number is more that!\n> ");
		errCheck(scanf("%d", &guess), &guess, &errs); 	// get (and check) input again
	}
	
	endgame(&guess, &errs, &tries, &num); 				// run the endgame function
}


/* The rand() function, if not seeded, will produce the same "random" numbers every time the program is run. The first, second, thrid, etc, 
   number will be the same every single time the program is run. I don't know whether these numbers vary on different machines, but there's a high
   chance they do. That's where the srand() function comes in. Its argument is a seed for new numbers to be generated by rand(). Using a constant 
   number for srand() produces the same number every single time, so we use the function time() to give srand() a constantly changing seed. time()
   returns the amount of time (in seconds) that has elapsed since the UNIX Epoch: January 1st, 1970, 00:00:00 UTC. */

/* The rand() function generates a "random" number that ranges from 0 to a constant: RAND_MAX. On my implementation of C, RAND_MAX is set at
   2,147,483,647. That's kind of a big number. Guessing a number in that range would probably take days, so we need to reduce the range of outputs
   of rand() that we have in our program. To do that, we use the formula (rand() % (UPPER - LOWER + 1)) + LOWER, where UPPER and LOWER are the 
   maximum and minimum values you wish to receive from rand(). In this program, LOWER is 1, so the formula is simplified to (rand % UPPER) + LOWER.
   If you're wondering how the formula works, so am I. But it works, and that's good enough for now. */ 
