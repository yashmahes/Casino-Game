
//yash is the great
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define m 13 /*these variables are for the 2D array, rows and columns*/
#define n 4

void display_menu();
int error_check(int option);
void shuffle(int arr[]);
int draw_card(int arr[]);
int lucky_seven(int cardValue);
int high_card(int userCard, int dealerCard);
double calculate_winnings(int gamePlayed, int outcome, double amountBet);
int match_card(int userCard, int dealerCard);
int checkBet(int bet, int balance);
void shuffleFullDeck(int arr[m][n]);
int drawFullDeckCard(int arr[m][n]);

int main()
{

    const int SIZE = 13; //We use const because we'll be using this variable throughout the program
    int ans =0, usrOption, bet, validBet, drawnCard, computerDraw, remainder, seven, prize, result, drawResult, decide;
    int balance = 100;
    int deck[SIZE];
    int fulldeck[13][4]; // For 4 decks

    printf("Welcome to the Casino!\n"); //welcome user
    while(ans != 3)  // Continue, as long as the user doesn't want to quit
    {
        display_menu();
        scanf("%d", &ans);
        usrOption = error_check(ans);

        while(usrOption == 0)  //This is to check if the option entered is valid
        {
            printf("Invalid choice; Try again.\n");
            display_menu();
            scanf("%d", &ans);
            usrOption = error_check(ans);
        }
        if(ans == 1)  //play Lucky Seven game
        {
            printf("How much do you want to bet? $");
            scanf("%d", &bet);
            validBet = checkBet(bet, balance);//check that the bet is valid as defined in checkBet function
            while(validBet==0)
            {
                printf("Invalid bet; Try again.\n");
                printf("How much do you want to bet? $\n");
                scanf("%d", &bet);
                validBet = checkBet(bet, balance);
            }
            printf("Lucky Seven\n");
            shuffle(deck);
            drawnCard = draw_card(deck);
            printf("You drew %d.\n", drawnCard);
            seven = lucky_seven(drawnCard);
            if(seven != 1)  //This is if the user loses
            {
                printf("You lost $ %d. Too bad.\n", bet);
                printf("Lucky Seven\n");
                remainder = balance - bet;
                balance = remainder;
                printf("Your total money is $ %d.\n\n", balance);
                if(balance == 0)
                {
                    printf("You have been thrown out of the casino.\n");
                    printf("Be more careful with your money next time.\n");
                    break;
                }
            }
            else   //If the user wins
            {
                prize = calculate_winnings(ans, seven, bet);
                printf("You won $ %d!\n", prize);
                balance += prize;
                printf("Your total money is $ %d.\n\n", balance);
            }
        }
        if(ans == 2)  //play High Card game
        {
            printf("How much do you want to bet? $");
            scanf("%d", &bet);
            validBet = checkBet(bet, balance);
            while(validBet==0)
            {
                printf("Invalid bet; Try again.\n");
                printf("How much do you want to bet? $\n");
                scanf("%d", &bet);
                validBet = checkBet(bet, balance);
            }
            printf("High Card\n");
            shuffle(deck);
            computerDraw = draw_card(deck);
            drawnCard = draw_card(deck);
            printf("You drew %d. The dealer drew %d.\n", drawnCard, computerDraw);
            result = high_card(drawnCard, computerDraw);
            if(result != 1)
            {
                printf("You lost $ %d. Too bad.\n", bet);
                remainder = balance - bet;
                balance = remainder;
                printf("Your total money is $ %d.\n\n", balance);
                if(balance == 0)
                {
                    printf("You have been thrown out of the casino.\n");
                    printf("Be more careful with your money next time.\n");
                    break;
                }
            }
            else
            {
                prize = calculate_winnings(ans, result, bet);
                printf("You won $ %d!\n", prize);
                balance += prize;
                printf("Your total money is $ %d.\n\n", balance);
            }
        }
        if(ans == 3)  //if user chooses to exit
        {
            printf("Wait! Before you go, do you want a chance to double your money???\n");
            printf("1) Yes\n");
            printf("2) No\n");
            scanf("%d", &decide);
            if(decide == 1)
            {
                printf("Match Card\n"); //if user chooses to play match card game
                shuffleFullDeck(fulldeck);
                drawnCard = draw_card(deck);
                computerDraw = drawFullDeckCard(fulldeck);
                drawResult = match_card(drawnCard, computerDraw);
                if(drawResult != 1)
                {
                    printf("You drew %d. The dealer drew %d.\n", drawnCard, computerDraw);
                    printf("You lost everything!!!\n");
                    balance = 0.00;
                    printf("Your total is now %d.\n", balance);
                    printf("Thanks for playing!\n");
                    break;
                }
                else
                {
                    printf("You drew %d. The dealer drew %d.\n", drawnCard, computerDraw);
                    printf("You doubled your money!\n");
                    balance *= 2;
                    printf("Your total is now $ %d.\n", balance);
                    break;
                }

            }
            else
            {
                printf("Bye!\n");
            }
        }

    }

    return 0;
}

void display_menu()
{

    printf("Which game do you want to play?\n");
    printf("1) Lucky Seven\n");
    printf("2) High Card\n");
    printf("3) Exit\n");
}

int error_check(int option)
{

    if(option == 1 || option == 2 || option == 3)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void shuffle(int arr[])
{
    int index, temp, max=13;
    int i;
    for( i=0; i<max; i++)
    {
        arr[i]=i+1;
    }
    srand(time(0));
    for( i=0; i<max; i++)
    {

        index = rand() % 13;

        temp = arr[index];
        arr[index] = arr[0];
        arr[0] = temp;

    }

}

int draw_card(int arr[])
{
    int chosen;
    int len = 13;
    int i;
    for( i=0; i<len; i++)
    {
        if(arr[i] != -1)
        {
            chosen = arr[i];

            arr[i] = -1;

            return chosen;
        }

    }
}

int lucky_seven(int cardValue)
{

    if(cardValue == 7)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int high_card(int userCard, int dealerCard)
{

    if(userCard > dealerCard)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

double calculate_winnings(int gamePlayed, int outcome, double amountBet)
{
    int winning=0;

    if(gamePlayed == 1 && outcome == 1)
    {
        winning = amountBet * 7;

    }
    else if(gamePlayed == 2 && outcome == 1)
    {
        winning = amountBet;

    }
    return winning;
}

int match_card(int userCard, int dealerCard)
{

    if(userCard == dealerCard)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/*validate user bet*/
int checkBet(int bet, int balance)
{
    if(bet > 0 && bet <= balance)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void shuffleFullDeck(int arr[m][n])  /*shuffle 2D array*/
{
    int index, temp, temp2, temp3, temp4;
    int i,j;
    for( i=0; i<m; i++)
    {

        for( j=0; j<n; j++)
        {
            arr[i][j]=i+1,j;
        }
    }
    for( i=0; i<m; i++)
    {

        for(j=0; j<n; j++)
        {
            srand(time(NULL));
            index = rand() % 13;

            temp = arr[index][0];
            arr[index][0] = arr[0][0];
            arr[0][0] = temp;

            temp2 = arr[index][1];
            arr[index][1] = arr[0][1];
            arr[0][1] = temp2;

            temp3 = arr[index][2];
            arr[index][2] = arr[0][2];
            arr[0][2] = temp3;

            temp4 = arr[index][3];
            arr[index][3] = arr[0][3];
            arr[0][3] = temp4;

        }
    }

}

int drawFullDeckCard(int arr[m][n])
{
    int pickedcard;
    int i,j;
    for( i=1; i<m; i++)
    {
        for( j=1; j<n; j++)
        {
            if(arr[i][j] != -1)
            {
                pickedcard = arr[i][j];
                arr[i][j] = -1;
                return pickedcard;
            }
        }
    }
}
