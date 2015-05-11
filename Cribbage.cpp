#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define HAND_LEN 4
enum SUIT {heart=0,diamond,spade,club};
enum VALUE {ace=1,two,three,four,five,six,seven,eight,nine,ten,jack,queen,king};

struct card{
  VALUE value;
  SUIT suit;
  bool operator() (card i,card j) { return (i.value<j.value);}
} myCard;

int scoreFlush(card []);
int pairScore(vector<card>);
int straightScore(vector<card>);
int fifteenScore(card []);
vector<card> convToSortedVect(card [], card);

int main(void){
  
  card hand[HAND_LEN];
  card extra;
  int score=0;
  
  //init the hand for now
  hand[0].value = ace; hand[0].suit = heart;
  hand[1].value = five; hand[1].suit = heart;
  hand[2].value = two; hand[2].suit = heart;
  hand[3].value = three; hand[3].suit = heart;
  extra.value = four; extra.suit = diamond; 
  
  vector<card>fullHand = convToSortedVect(hand,extra);
  score = straightScore(fullHand);
  cout<<score;
  return 0;  
}

int scoreFlush(card hand[]){

  SUIT flushSuit = hand[0].suit;
  for(int i = 1; i <  HAND_LEN; i++){
    
    if(hand[i].suit != flushSuit)
      return 0;
  }
  return 4;
}


int pairScore(vector<card> fullHand){
  
  int consec = 0, score = 0;
  int scores[] = {2,6,12};
  
  for(vector<card>::iterator iter = fullHand.begin()+1; iter!=fullHand.end();iter++){
    if(iter->value == (iter-1)->value){
      score+=scores[consec];
      consec++;
    }
    else
      consec = 0;
  }
  return score;
}
  
  
int straightScore(vector<card> fullHand){
  
  int score=0, consec=1,lastScore=0;
  int runMod=1;
  
  
  for(vector<card>::iterator iter = fullHand.begin()+1; iter!=fullHand.end();iter++){
   
    if(iter->value - 1 == (iter-1)->value){
     consec++;
    }
    else if(iter->value == (iter-1)->value){
      runMod*=2;
    }  
    else{
      
      if(consec>=3){
	score+=runMod*consec;
      }
      consec = 1;
      runMod=1;
    }
  }
  
  if(consec>=3){
    score+=runMod*consec;
  }
  
  return score;
}


vector<card> convToSortedVect(card hand[], card extra){
   
  vector<card> fullHand(hand,hand+HAND_LEN);
  fullHand.push_back(extra);
  
  sort(fullHand.begin(), fullHand.end(), myCard);
  
  for(vector<card>::iterator iter = fullHand.begin(); iter!=fullHand.end();iter++){
    cout<<iter->value<<endl;
  }
  
  return fullHand;
}  