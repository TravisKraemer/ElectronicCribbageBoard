#include <algorithm>
#include <iostream>

const int NUM_CARDS = 5;
int Score_hand( char cards[5][2], bool crib);

int main()
{
   char CAR[5][2] = {{'A','D'},{'6','D'},{'7','D'},{'8','D'},{'9','D'}};
   std::cout << Score_hand(CAR, false);
}

int Score_hand( char cards[5][2], bool crib) //enter in form card1, card2, card3, card4, flipped card, && crib
{//cards should be entered in the for(m of number then suit ex. JH or 3D
    int numcards[NUM_CARDS];
    char suits[NUM_CARDS];
    int score = 0;
    for( int i = 0; i < NUM_CARDS; i++)//prepare data for( processing
    {
        if( cards[i][0] == 'T')
            numcards[i] = 10;
        else if( cards[i][0] == 'J')
            numcards[i] = 11;
        else if( cards[i][0] == 'Q')
            numcards[i] = 12;
        else if( cards[i][0] == 'K')
            numcards[i] = 13;
        else if( cards[i][0] == 'A')
            numcards[i] = 1;
        else
            numcards[i] = cards[i][0] - '0';
        suits[i] = cards[i][1];//data ready
    }
    if( suits[0] == suits[1] && suits[1] == suits[2] && suits[2] == suits[3])//flush
    {
        if( suits[0] == suits[4])
            score += 5;
        else
            if( !crib )
                score += 4;
   }
    for(int n = 0; n < (NUM_CARDS - 1); n++) //pairs loop
    {
        for(int i = 1 + n; i < NUM_CARDS; i++)
            if( numcards[i] == numcards[n])
            {
                score += 2;
            }
    }
    int valcards[NUM_CARDS]; //int array containing card values used in scoring fifteens
    for( int i = 0; i < NUM_CARDS; i++)
    {
        if( numcards[i] > 10)
            valcards[i] = 10;
        else
            valcards[i] = numcards[i];
   }
    int sum = 0;
    int subsum;
    int sub2sum;
    int sub3sum;
    for( int i = 0; i < NUM_CARDS; i++)
        sum += valcards[i];
    if( sum == 15)
        score += 2;
    else if( sum > 15)
    {
        int z = 0;
        while( z < 5)
        {
            subsum = sum - valcards[z];
            z += 1;
            if( subsum == 15)
                score += 2;
            else if( subsum > 15)
            {
                int y = z;
                while( y < 5)
                {
                    sub2sum = subsum - valcards[y];
                    y += 1;
                    if( sub2sum == 15)
                        score += 2;
                    else if( subsum > 15)
                    {
                        int x = y;
                        while( x < 5)
                        {
                            sub3sum = sub2sum - valcards[x];
                            x += 1;
                            if( sub3sum == 15)
                                score += 2; //15 finish
                        }
                    }
                }
            }
         }
    }
    for(int i = 0; i < NUM_CARDS - 1; i++)
    {
      if(cards[i][0] == 'J' && cards[i][1] == cards[NUM_CARDS - 1][1])
         score++;
    }
    std::sort(numcards, numcards + NUM_CARDS);
    int runcards[NUM_CARDS];//new list without duplicates to make it easier
    for( int i = 0; i < NUM_CARDS; i++)
      runcards[i] = 0;
    int n = 0;
    for( int i = 0; i < NUM_CARDS; i++)
    {
       int a = numcards[i];
       if(a != runcards[0] && a != runcards[1] && a != runcards[2]
                           && a != runcards[3] && a != runcards[4])
          {
           runcards[n] = a;
           n++;
          }
    }
    int run = 1;
    int n2 = 0;
    int used[NUM_CARDS];
    for( int i = 0; i < NUM_CARDS; i++) //initialize
      used[i] = 0;
    for( int i = 0; i < n; i++)
    {
        if( (runcards[i] + 1) == runcards[i + 1])
        {
            run++;
            used[n2] = runcards[i];
            used[n2+1] = runcards[i+1];
            n2++;
        }
        else
            if( run < 3)
            {
               n2 = 0;
               run = 1;
            }
    }
    int n3;
    std::cout << run << '\n';
    if( run >= 3)
    {
        int multi = 1;
        for(int i = 0; i < n2 + 1; i++)
        {
            n3 = 0;
            for(int j = 0; j < NUM_CARDS; j++)
               if(used[i] == numcards[j])
                  n3++;
            multi *= n3;
        }
        std::cout << "run of:" << multi*run << std::endl;
        score += multi * run;
   }
   return score;
}
