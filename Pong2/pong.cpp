#include <iostream>
#include<time.h>
#include<conio.h>

using namespace std;

enum enumDirection{STOP=0,LEFT=1,UPLEFT=2,DOWNLEFT=3,RIGHT=4,UPRIGHT=5,DOWNRIGHT=6};
class cBall{
    private:
      int x,y;
      int originalX,originalY;
     enumDirection Direction;
    public:
      cBall(int posX,int posY){
        originalX=posX;
        originalY=posY;
        x=posX;
        y=posY;
        Direction=STOP;
      }
      void Reset(){
        x=originalX;
        y=originalY;
        Direction=STOP;
      }
      void chnageDirection(enumDirection d){
        Direction=d;
      }
      void randomDirection(){
        Direction=(enumDirection)((rand()%6)+1);

      }
      inline int getX(){return x; }
      inline int getY(){return y;}
      inline enumDirection getDirection(){return Direction;}
      
      void Move(){
        switch(Direction){
            case STOP:
            break;
            case LEFT:
            x--;
            case RIGHT:
            x++;
            case UPLEFT:
            x--;y--;
            break;
            case DOWNLEFT:
            x--;y++;
            break;
            case UPRIGHT:
            x++;y--;
            break;
            case DOWNRIGHT:
            x++;y++;
            break;
            default:
            break;

        }
      }
      friend ostream & operator<<(ostream &o,cBall c){
        o<<"Ball ["<<c.x<<","<<c.y<<"]["<<c.Direction<<"]"<<endl;
        return o;
      }

};
class cPaddle{
    private:
    int x,y;
    int originalX,originalY;
    public:
    cPaddle(){
        x=y=0;
    }
    cPaddle(int posX,int posY): cPaddle(){
        originalX=posX;
        originalY=posY;
        x=posX;
        y=posY;
    }
      inline void Reset(){
      x=originalX;
      y=originalY;
      }
      inline int getX(){return x; }
      inline int getY(){return y;}
      inline void moveUp(){y--;}
      inline void moveDown(){y++;}

    friend ostream & operator<<(ostream &o,cPaddle c){
        o<<"Paddle ["<<c.x<<","<<c.y<<"]";
        return o;
      }
};
class cGameManager
{
    private:
      int width,height;
      int score1,score2;
      char up1,down1,up2,down2;
      bool quit;
      cBall*ball;
      cPaddle*player1;
      cPaddle*player2;
    public:
       cGameManager(int w,int h){
        srand(time(NULL));
        quit=false;
        up1='w';
        up2='i';
        down1='s';
        down2='k';
        score1=score2=0;
        width=w; 
        height=h;
        ball=new cBall(w/2,h/2);
        player1=new cPaddle(1,h/2-3);
        player2=new cPaddle(w-2,h/2-3);
       }
       ~cGameManager(){
        delete ball,player1,player2;
       }
       void ScoreUp(cPaddle*player){
        if(player==player1)
        score1++;
        else if(player==player2)
        score2++;

        ball->Reset();
        player1->Reset();
        player2->Reset();
       }
       void Draw(){
        system("cls");
        for(int i=0;i<width+2;i++)
        cout<<"\xB2"<<endl;
        for(int i=0;1<height;i++)
        {
            for(int j=0;j<width;j++){
                int ballx=ball->getX();
                int bally=ball->getY();
                int player1x=player1->getX();
                int player2x=player2->getX();
                int player1y=player1->getY();
                int player2y=player2->getY();

                if(j==0){
                cout<<"\xB2";
                }
                if(ballx==j&&bally==i){
                 cout<<"O";
                }
                else if(player1x==j &&player1y==i){
                 cout<<"\xDB";
                }
                else if(player2x==j &&player2y==i){
                 cout<<"\xDB";
                }
                else if(player1x==j &&player1y+1==i){
                 cout<<"\xDB";
                }
                else if(player1x==j &&player1y+2==i){
                 cout<<"\xDB";
                }
                else if(player1x==j &&player1y+3==i){
                 cout<<"\xDB";
                }
                else if(player2x==j &&player2y+1==i){
                 cout<<"\xDB";
                }
                else if(player2x==j &&player2y+2==i){
                 cout<<"\xDB";
                }
                else if(player2x==j &&player2y+3==i){
                 cout<<"\xDB";
                }
                
                else{
                    cout<<" ";
                }

//++++++++++++++++++++++++++++++++++++++++++++++
                if(j==width-1){
                    cout<<"\xB2";
                }
                cout<<endl;
            }
        }
        for(int i=0;i<width+2;i++)
        cout<<"\xB2"<<endl;

        cout<<"Player 1 Score "<<score1<<endl;
        cout<<"Player 2 Score "<<score2<<endl;
       }

       void Input(){
        ball->Move();
        
         int ballx=ball->getX();
         int bally=ball->getY();
         int player1x=player1->getX();
         int player2x=player2->getX();
         int player1y=player1->getY();
         int player2y=player2->getY();

        if(_kbhit()){
            char current=_getch();
            if(current==up1){
            if(player1y>0){
                player1->moveUp();
            }
            }
            if(current==up2){
            if(player2y>0){
                player2->moveUp();
            }
            }
            if(current==down1){
            if(player1y+4<height){
                player1->moveDown();
            }
            }
            if(current==down2){
            if(player2y+4<height){
                player2->moveDown();
            }
            }
            if(ball->getDirection()==STOP){
              ball->randomDirection();
            }
            if(current=='q'){
              quit=true;
            }
        }

       }
       void logic(){
        int ballx=ball->getX();
         int bally=ball->getY();
         int player1x=player1->getX();
         int player2x=player2->getX();
         int player1y=player1->getY();
         int player2y=player2->getY();

        //Left Paddle
         for(int i=0;i<4;i++){
          if(ballx==player1x+1){
            if(bally==player1y+i){
               ball->chnageDirection((enumDirection)((rand()%3)+4));

            }
          }
         }
         //right paddle
          for(int i=0;i<4;i++){
          if(ballx==player2x-1){
            if(bally==player2y+i){
               ball->chnageDirection((enumDirection)((rand()%3)+4));

            }
          }
         }
         //Bottom Wall
         if(bally==height-1){
          ball->chnageDirection(ball->getDirection()==DOWNRIGHT?UPRIGHT:UPLEFT);
         }
          //Top Wall
         if(bally==0){
          ball->chnageDirection(ball->getDirection()==UPRIGHT?DOWNRIGHT:DOWNLEFT);
         }
         //Right Wall
         if(ballx==width-1){
          ScoreUp(player1);
         }
         //LEft Wall
         if(ballx==0){
          ScoreUp(player2);
         }
       }
       void Run(){
          while(!quit){
            Draw();
            Input();
            logic();
          }
         }
};

int main(){
    cGameManager c(40,20);
    c.Run();
    return 0;
    // cBall c(0,0);
    // cout<<c<<endl;
    // c.randomDirection();
    // cout<<c<<endl;
    // c.Move();
    // cout<<c<<endl;
    // c.randomDirection();
    // c.Move();
    // cout<<c<<endl;
    // c.randomDirection();
    // c.Move();
    // cout<<c<<endl;
    // cPaddle p1(0,0);
    // cPaddle p2(10,0);
    // cout<<p1<<endl;
    // cout<<p2<<endl;
    // p1.moveUP();
    // p2.moveDown();
    // cout<<p1<<endl;
    // cout<<p2<<endl;
    
    return 0;
}