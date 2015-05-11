#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

#define HAND_LEN 5
enum SUIT {heart=0,diamond,spade,club};
enum VALUE {ace=1,two,three,four,five,six,seven,eight,nine,ten,jack=11,queen,king};

struct card{
  VALUE value;
  SUIT suit;
  bool operator() (card i,card j) { return (i.value<j.value);}
} myCard;

void bestHand(int);
void incHand();
card incCard(card);
int scoreFlush(card []);
int pairScore(vector<card>);
int straightScore(vector<card>);
int fifteenScore(card []);
vector<card> convToSortedVect(card []);
bool nonEqual(int i,int j,int k ,int l){
    
  if(i==j || i == k || i == l) return false;
  if (j == k || j ==l) return false;
  if( k == l) return false;
  return true;
  
}


int scoreHand(card hand[]){
 
  int score=0;
  vector<card> fullHand = convToSortedVect(hand);
  
  score+=scoreFlush(hand);
  score+=pairScore(fullHand);
  score+=straightScore(fullHand);
  score+=fifteenScore(hand);
  
  for(int i=0;i<HAND_LEN-1;i++){
    if(hand[i].value==jack){
      if(hand[i].suit==hand[HAND_LEN-1].suit)
	score+=1;
    }
  }
  
  return score;
}


card HAND[HAND_LEN];
int main(void){
  
  bestHand(100000000);

//   HAND[0].value = king; HAND[0].suit = club;
//   HAND[1].value = king; HAND[1].suit = club;
//   HAND[2].value = king; HAND[2].suit = club;
//   HAND[3].value = king; HAND[3].suit = club;
//   HAND[4].value = king; HAND[4].suit = club;
//   incHand();
//   for(int i = 0; i < HAND_LEN; i++){
//     cout<<"Value:: "<<HAND[i].value<<" Suit::"<<HAND[i].suit<<endl;
//   }
//   cout<<scoreHand(HAND)<<endl;
//    cout<<"\nFlush Score::"<<scoreFlush(HAND)<<" Pair Score:: "<<pairScore(convToSortedVect(HAND))<<
//   " Straight score:: "<<straightScore(convToSortedVect(HAND))<<" fifteenScore:: "<<fifteenScore(HAND)<<endl;
  return 0;  
}


void bestHand(int runs){
  
  int score=0, bestScore=0;
  int currRun=0;
  card best[HAND_LEN];
  
  //init hand
  HAND[0].value = ace; HAND[0].suit = heart;
  HAND[1].value = ace; HAND[1].suit = diamond;
  HAND[2].value = ace; HAND[2].suit = spade;
  HAND[3].value = ace; HAND[3].suit = club;
  HAND[4].value = two; HAND[4].suit = heart;
  
  while(currRun<runs){
    score = scoreHand(HAND);
    if(score>bestScore){
      bestScore=score;
      memcpy(best,HAND,sizeof(HAND));
    }
    
    incHand();
    
    currRun++;
  }
  
  cout<<"Max hand attained::"<<endl;
  for(int i = 0; i < HAND_LEN; i++){
    cout<<"Value:: "<<HAND[i].value<<" Suit::"<<HAND[i].suit<<endl;
  }
  cout<<scoreHand(HAND)<<"\nFlush Score::"<<scoreFlush(HAND)<<" Pair Score:: "<<pairScore(convToSortedVect(HAND))<<
  " Straight score:: "<<straightScore(convToSortedVect(HAND))<<" fifteenScore:: "<<fifteenScore(HAND)<<endl;
  
  memcpy(HAND,best, sizeof(best));

  for(int i = 0; i < HAND_LEN; i++){
    cout<<"Value:: "<<best[i].value<<" Suit::"<<best[i].suit<<endl;
  }
  cout<<bestScore<<"\nFlush Score::"<<scoreFlush(best)<<" Pair Score:: "<<pairScore(convToSortedVect(best))<<
  " Straight score:: "<<straightScore(convToSortedVect(best))<<" fifteenScore:: "<<fifteenScore(best)<<endl;
}


void incHand(){
  
  bool rollOver;
  int incPos=HAND_LEN-1;
  do{
    HAND[incPos] = incCard(HAND[incPos]);
    
    if(HAND[incPos].suit == heart && HAND[incPos].value == ace){
      rollOver = true;
      incPos--;
    }
    else
      rollOver = false;
    
  }while(rollOver);
  
  for(int i=0; i<HAND_LEN;i++){
    for(int j=i+1;j<HAND_LEN;j++){
      if(HAND[i].value==HAND[j].value && HAND[i].suit==HAND[j].suit)
	incHand();
    }  
  }  
}


card incCard(card c){
  if(c.suit!=club)
    c.suit=SUIT(c.suit+1);
  else{
    
    c.suit = heart;
    
    if(c.value==king){
      c.value=ace;
      return c;
    }
    c.value = VALUE(c.value+1);
  }  
  
  return c;
}  
  
  
int scoreFlush(card hand[]){

  SUIT flushSuit = hand[0].suit;
  for(int i = 1; i <  HAND_LEN-1; i++){
    
    if(hand[i].suit != flushSuit)
      return 0;
  }
  return 4;
}


int pairScore(vector<card> fullHand){
  
  int consec = 0, score = 0;
  int mod=0;
  
  for(vector<card>::iterator iter = fullHand.begin()+1; iter!=fullHand.end();iter++){
//     cout<<mod<<" "<<score<< " "<<(iter->value == (iter-1)->value)<<" "
//     <<(iter->value)<<endl;
    if(iter->value == (iter-1)->value){
      mod+=2;
      score+=mod;
    }
    else
      mod=0;
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

//brute force count; couldn't find a better method
int fifteenScore(card hand[]){
  int score=0,sum=0; 
  card tempHand[HAND_LEN];
  
  for(int i=0;i<HAND_LEN;i++){
      if(hand[i].value>ten)
	tempHand[i].value=ten;
      else
	tempHand[i].value = hand[i].value;
  }
  
  //two cards
  for(int i = 0; i < HAND_LEN;i++){
    for(int j = i+1; j < HAND_LEN; j++){
      sum = tempHand[i].value + tempHand[j].value;
      if(sum==15 && nonEqual(i,j,-2,-1)) score+=2;
    }
  }

  //three cards
  for(int i = 0; i < HAND_LEN;i++){
    for(int j = i+1; j < HAND_LEN; j++){
      for(int k = j+1; k < HAND_LEN; k++){
	sum = tempHand[i].value + tempHand[j].value + tempHand[k].value;
	if(sum==15 && nonEqual(i,j,k,-1)) score+=2;
      }
    }
  }

  //four cards
  for(int i = 0; i < HAND_LEN;i++){
    for(int j = i+1; j < HAND_LEN; j++){
      for(int k = j+1; k < HAND_LEN; k++){
	for(int l = k+1; l < HAND_LEN; l++){
	  sum = tempHand[i].value + tempHand[j].value + tempHand[k].value + tempHand[l].value;
	  if(sum==15 && nonEqual(i,j,k,l)) score+=2;
      
	}  
      }
    }
  }

  sum=0;
  for(int i=0; i<HAND_LEN; i++){
    sum+=tempHand[i].value;
  }
  if(sum==15)score+=2;
  
  return score;
}


vector<card> convToSortedVect(card hand[]){
   
  vector<card> fullHand(hand,hand+HAND_LEN);
  sort(fullHand.begin(), fullHand.end(), myCard);
  
//   for(vector<card>::iterator iter = fullHand.begin(); iter!=fullHand.end();iter++){
//     cout<<iter->value<<" ";
//   }
  return fullHand;
}  