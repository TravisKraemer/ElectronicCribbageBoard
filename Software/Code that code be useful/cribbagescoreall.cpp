#include <algorithm>
#include <iostream>

const int NUM_CARDS = 5;
const char CARDS[52][2] = {{'A','D'},{'2','D'},{'3','D'},{'4','D'},{'5','D'},{'6','D'},{'7','D'},{'8','D'},{'9','D'},{'T','D'},{'J','D'},{'Q','D'},{'K','D'},{'A','S'},{'2','S'},{'3','S'},{'4','S'},{'5','S'},{'6','S'},{'7','S'},{'8','S'},{'9','S'},{'T','S'},{'J','S'},{'Q','S'},{'K','S'},{'A','H'},{'2','H'},{'3','H'},{'4','H'},{'5','H'},{'6','H'},{'7','H'},{'8','H'},{'9','H'},{'T','H'},{'J','H'},{'Q','H'},{'K','H'},{'A','C'},{'2','C'},{'3','C'},{'4','C'},{'5','C'},{'6','C'},{'7','C'},{'8','C'},{'9','C'},{'T','C'},{'J','C'},{'Q','C'},{'K','C'}};
int Score_hand(const char cards[5][2], bool crib);
bool TestCribbageScorer();

/**
Scores every possible cribbage hand
Can be compared with stats online to verify scoring algorithm correctness
*/
int main()
{
   TestCribbageScorer();
   char hand[5][2];
   int sum = 0;
   int count = 0;
   int count0 = 0;
   int count1 = 0;
   int count2 = 0;
   int count3 = 0;
   int count4 = 0;
   int count5 = 0;
   int count6 = 0;
   int count7 = 0;
   int count8 = 0;
   int count9 = 0;
   int count10 = 0;
   int count11 = 0;
   int count12 = 0;
   int count13 = 0;
   int count14 = 0;
   int count15 = 0;
   int count16 = 0;
   int count17 = 0;
   int count18 = 0;
   int count19 = 0;
   int count20 = 0;
   int count21 = 0;
   int count22 = 0;
   int count23 = 0;
   int count24 = 0;
   int count25 = 0;
   int count26 = 0;
   int count27 = 0;
   int count28 = 0;
   int count29 = 0;
   for (int i = 0; i < 52; i++)
   {
      hand[0][0] = CARDS[i][0];
      hand[0][1] = CARDS[i][1];
      for (int j = i + 1; j < 52; j++)
      {
         hand[1][0] = CARDS[j][0];
         hand[1][1] = CARDS[j][1];
         for (int k = j + 1; k < 52; k++)
         {
            hand[2][0] = CARDS[k][0];
            hand[2][1] = CARDS[k][1];
            for (int l = k + 1; l < 52; l++)
            {
               hand[3][0] = CARDS[l][0];
               hand[3][1] = CARDS[l][1];
               for (int m = 0; m < 52; m++)
               {
                  if ( m != l && m != k && m != j && m != i)
                  {
                     hand[4][0] = CARDS[m][0];
                     hand[4][1] = CARDS[m][1];
                     count++;
                     int score = Score_hand(hand, true);
                     sum += score;
                     if(score == 0)
                        count0++;
                     else if(score == 1)
                        count1++;
                     else if(score == 2)
                        count2++;
                     else if(score == 3)
                        count3++;
                     else if(score == 4)
                        count4++;
                     else if(score == 5)
                        count5++;
                     else if(score == 6)
                        count6++;
                     else if(score == 7)
                        count7++;
                     else if(score == 8)
                        count8++;
                     else if(score == 9)
                        count9++;
                     else if(score == 10)
                        count10++;
                     else if(score == 11)
                        count11++;
                     else if(score == 12)
                        count12++;
                     else if(score == 13)
                        count13++;
                     else if(score == 14)
                        count14++;
                     else if(score == 15)
                        count15++;
                     else if(score == 16)
                        count16++;
                     else if(score == 17)
                        count17++;
                     else if(score == 18)
                        count18++;
                     else if(score == 19)
                        count19++;
                     else if(score == 20)
                        count20++;
                     else if(score == 21)
                        count21++;
                     else if(score == 22)
                        count22++;
                     else if(score == 23)
                        count23++;
                     else if(score == 24)
                        count24++;
                     else if(score == 25)
                        count25++;
                     else if(score == 26)
                        count26++;
                     else if(score == 27)
                        count27++;
                     else if(score == 28)
                        count28++;
                     else if(score == 29)
                        count29++;
                  }
               }
            }
         }
      }
   }
   std::cout << sum << '\n' << count << '\n' << float(sum)/count << '\n';
   std::cout << count0 <<'\n';
   std::cout << count1 <<'\n';
   std::cout << count2 <<'\n';
   std::cout << count3 <<'\n';
   std::cout << count4 <<'\n';
   std::cout << count5 <<'\n';
   std::cout << count6 <<'\n';
   std::cout << count7 <<'\n';
   std::cout << count8 <<'\n';
   std::cout << count9 <<'\n';
   std::cout << count10 <<'\n';
   std::cout << count11 <<'\n';
   std::cout << count12 <<'\n';
   std::cout << count13 <<'\n';
   std::cout << count14 <<'\n';
   std::cout << count15 <<'\n';
   std::cout << count16 <<'\n';
   std::cout << count17 <<'\n';
   std::cout << count18 <<'\n';
   std::cout << count19 <<'\n';
   std::cout << count20 <<'\n';
   std::cout << count21 <<'\n';
   std::cout << count22 <<'\n';
   std::cout << count23 <<'\n';
   std::cout << count24 <<'\n';
   std::cout << count25 <<'\n';
   std::cout << count26 <<'\n';
   std::cout << count27 <<'\n';
   std::cout << count28 <<'\n';
   std::cout << count29 <<'\n';
   return 0;
}

/**
Scores a Cribbage hand
params (in, in)
cards - char array of cards (value suit pair), crib - boolean indicating whether the hand is a crib
Return int - number of points hand is worth
*/
int Score_hand( const char cards[5][2], bool crib) //enter in form card1, card2, card3, card4, flipped card, && crib
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
            subsum = sum - valcards[z++];
            if( subsum == 15)
                score += 2;
            else if( subsum > 15)
            {
                int y = z;
                while( y < 5)
                {
                    sub2sum = subsum - valcards[y++];
                    if( sub2sum == 15)
                        score += 2;
                    else if( subsum > 15)
                    {
                        for(int x = y; x < 5; x++)
                        {
                            sub3sum = sub2sum - valcards[x];
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
    int runcards[NUM_CARDS];//new array without duplicates to make it easier
    for( int i = 0; i < NUM_CARDS; i++)
      runcards[i] = 0;
    int n = 0;
    for( int i = 0; i < NUM_CARDS; i++)
    {
       int a = numcards[i];
       //Only add cards not already in array
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
    for( int i = 0; i < NUM_CARDS; i++)
      used[i] = 0;
    for( int i = 0; i < n; i++)
    {
        if( (runcards[i] + 1) == runcards[i + 1])
        {
            run ++;
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
        score += multi * run;
   }
   return score;
}

bool TestCribbageScorer()
{
    bool pass = true;
    //Pair Test
    const char testCards[5][2] = {{'A','H'},{'A','D'},{'2','S'},{'4','H'},{'6','D'}};
    if(Score_hand(testCards,false) != 2)
    {
        pass = false;
        std::cout << "Pair failed" << std::endl;
    }
    //Three of a kind Test
    const char testCards2[5][2] = {{'A','H'},{'A','D'},{'A','S'},{'4','H'},{'6','D'}};
    if(Score_hand(testCards2,false) != 6)
    {
        pass = false;
        std::cout << "Three of a kind failed" << std::endl;
    }
    //Four of a kind Test
    const char testCards3[5][2] = {{'A','H'},{'A','D'},{'A','S'},{'A','C'},{'6','D'}};
    if(Score_hand(testCards3,false) != 12)
    {
        pass = false;
        std::cout << "Four of a kind failed" << std::endl;
    }
    //15 using all cards plus pair already tested
    const char testCards4[5][2] = {{'A','H'},{'A','D'},{'2','S'},{'4','H'},{'7','D'}};
    if(Score_hand(testCards4,false) != 4)
    {
        pass = false;
        std::cout << "15 (5 Cards) failed" << std::endl;
    }
    //15 using four cards plus pair already tested
    const char testCards5[5][2] = {{'A','H'},{'A','D'},{'7','S'},{'4','H'},{'9','D'}};
    if(Score_hand(testCards5,false) != 4)
    {
        pass = false;
        std::cout << "15 (4 Cards) failed" << std::endl;
    }
    //15 using three cards plus pair already tested
    const char testCards6[5][2] = {{'A','H'},{'A','D'},{'7','S'},{'3','H'},{'5','D'}};
    if(Score_hand(testCards6,false) != 4)
    {
        pass = false;
        std::cout << "15 (3 Cards) failed" << std::endl;
    }
    //15 using two cards plus pair already tested
    const char testCards7[5][2] = {{'A','H'},{'A','D'},{'7','S'},{'3','H'},{'8','D'}};
    if(Score_hand(testCards7,false) != 4)
    {
        pass = false;
        std::cout << "15 (2 Cards) failed" << std::endl;
    }
    //15 with ten
    const char testCards8[5][2] = {{'T','H'},{'5','D'},{'2','S'},{'A','H'},{'6','D'}};
    if(Score_hand(testCards8,false) != 2)
    {
        pass = false;
        std::cout << "15 (2 Cards, Ten) failed" << std::endl;
    }
    //15 with Jack
    const char testCards9[5][2] = {{'J','H'},{'5','D'},{'2','S'},{'A','H'},{'6','D'}};
    if(Score_hand(testCards9,false) != 2)
    {
        pass = false;
        std::cout << "15 (2 Cards, Jack) failed" << std::endl;
    }
    //15 with queen
    const char testCards10[5][2] = {{'Q','H'},{'5','D'},{'2','S'},{'A','H'},{'6','D'}};
    if(Score_hand(testCards10,false) != 2)
    {
        pass = false;
        std::cout << "15 (2 Cards, Queen) failed" << std::endl;
    }
    //15 with king
    const char testCards11[5][2] = {{'K','H'},{'5','D'},{'2','S'},{'A','H'},{'6','D'}};
    if(Score_hand(testCards11,false) != 2)
    {
        pass = false;
        std::cout << "15 (2 Cards, King) failed" << std::endl;
    }
    //Run of 3
    const char testCards12[5][2] = {{'A','H'},{'2','D'},{'T','S'},{'J','H'},{'Q','D'}};
    if(Score_hand(testCards12,false) != 3)
    {
        pass = false;
        std::cout << "Run of 3 failed" << std::endl;
    }
     //Run of 4
    const char testCards13[5][2] = {{'A','H'},{'9','D'},{'T','S'},{'J','H'},{'Q','D'}};
    if(Score_hand(testCards13,false) != 4)
    {
        pass = false;
        std::cout << "Run of 4 failed" << std::endl;
    }
    //Run of 5
    const char testCards14[5][2] = {{'8','H'},{'9','D'},{'T','S'},{'J','H'},{'Q','D'}};
    if(Score_hand(testCards14,false) != 5)
    {
        pass = false;
        std::cout << "Run of 5 failed" << std::endl;
    }
    //Run of 4, Double (plus pair)
    const char testCards15[5][2] = {{'9','H'},{'9','D'},{'T','S'},{'J','H'},{'Q','D'}};
    if(Score_hand(testCards15,false) != 10)
    {
        pass = false;
        std::cout << "Double run of 4 failed" << std::endl;
    }
    //Quadruple run of 3 (plus 2 pairs)
    const char testCards16[5][2] = {{'9','H'},{'9','D'},{'T','S'},{'J','H'},{'J','D'}};
    if(Score_hand(testCards16,false) != 16)
    {
        pass = false;
        std::cout << "Quadruple run of 3 failed" << std::endl;
    }
    //Triple run of 3 (plus three of kind)
    const char testCards17[5][2] = {{'9','H'},{'9','D'},{'T','S'},{'J','H'},{'9','C'}};
    if(Score_hand(testCards17,false) != 15)
    {
        pass = false;
        std::cout << "Triple run of 3 failed" << std::endl;
    }
    //0 point hand
    const char testCards18[5][2] = {{'A','H'},{'9','D'},{'T','S'},{'Q','H'},{'K','D'}};
    if(Score_hand(testCards18,false) != 0)
    {
        pass = false;
        std::cout << "0 point hand failed" << std::endl;
    }
    //Knobs test
    const char testCards19[5][2] = {{'A','H'},{'J','D'},{'9','S'},{'8','H'},{'K','D'}};
    if(Score_hand(testCards19,false) != 1)
    {
        pass = false;
        std::cout << "Knobs failed" << std::endl;
    }
    //Flush test (non crib) 4 cards
    const char testCards20[5][2] = {{'A','H'},{'9','H'},{'T','H'},{'Q','H'},{'K','D'}};
    if(Score_hand(testCards20,false) != 4)
    {
        pass = false;
        std::cout << "Non crib four card flush failed" << std::endl;
    }
    //Near Flush test (non crib) 4 cards
    const char testCards21[5][2] = {{'A','H'},{'9','H'},{'T','H'},{'Q','D'},{'K','C'}};
    if(Score_hand(testCards21,false) != 0)
    {
        pass = false;
        std::cout << "Non crib four card not flush failed" << std::endl;
    }
    //Flush test (crib) 4 cards
    const char testCards22[5][2] = {{'A','H'},{'9','H'},{'T','H'},{'Q','H'},{'K','D'}};
    if(Score_hand(testCards22,true) != 0)
    {
        pass = false;
        std::cout << "crib four card flush failed" << std::endl;
    }
    //Flush test (crib) 5 cards
    const char testCards23[5][2] = {{'A','H'},{'9','H'},{'T','H'},{'Q','H'},{'K','H'}};
    if(Score_hand(testCards23,true) != 5)
    {
        pass = false;
        std::cout << "crib five card flush failed" << std::endl;
    }
    //Flush test (non crib) 5 cards
    const char testCards24[5][2] = {{'A','H'},{'9','H'},{'T','H'},{'Q','H'},{'K','H'}};
    if(Score_hand(testCards24,false) != 5)
    {
        pass = false;
        std::cout << "non crib five card flush failed" << std::endl;
    }
    return pass;
}
