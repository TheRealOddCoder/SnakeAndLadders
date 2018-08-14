

int de=700;  //delay time in ms
int grid=3,pl1=10,pl2=6,pl3=14,value=15,dev=2,cnpl=6;  //color values
char sym[]={-61,-60,-59,-77,-76,-37,-37,-80,-70,-64,-39,-63};



#include<iostream.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<time.h>  //for srand function
#include<dos.h>  //for delay function



//it gives the random number between min & max
int random_no(int min,int max)
{
   int random_number;
   do{
      random_number=random(max);  //get the random number using rand function
   }while(random_number<min);
   return random_number;
}


static int sub_board[100];  //to determine the embty box


//it checks the box is empty or not
int is_not_empty(int random_number )
{
   if( sub_board[random_number]==0)
   {
      //if the box is empty,one is stored in the box
      return 0;
   }
   else
      return 1;
}


//it gives the different box numbers
int randomp(int min,int max)
{
   int random_number;
   do{
      random_number=random_no(min,max);
   }while(is_not_empty(random_number));  //while we get the different box
   return random_number ;
}


static int no_of_tail_in_row [13];
static int no_of_tail_in_column [13];

//it tells if tails is in same row & column
int check_tail(int init_tail)
{
   init_tail--;
   int tail_in_column;
   if((int(init_tail/10)%2)==0)
      tail_in_column=init_tail%10;
   else
      tail_in_column=9-init_tail%10;

   if(no_of_tail_in_column[tail_in_column]<1)
   {
      no_of_tail_in_column[tail_in_column]++;
      return 0;
   }
   else
      return 1;
}


static int no_of_head_in_column[13];

//it tell if heads is in same column
int check_head(int init_head)
{
   int i;
   init_head--;
   if((int(init_head/10)%2)==0)
      i=init_head%10;
   else
      i=9-init_head%10;

   if(no_of_head_in_column[i]<1)
   {
      no_of_head_in_column[i]++;
      return 0;
   }
   else
      return 1;
}

//it gives head & tail position of a snake
void position_of_snake(int &head,int &tail,int i,int gap_of_head)
{
   int min_head;
   int max_head;
   int over=0;

   //it takes particular series in the board
   min_head=i*gap_of_head+20;
   max_head=i*gap_of_head+20+gap_of_head;

   //it gives the position of snake's head
   do{
      do{
	 head=randomp(min_head,max_head);
      }while(head>99);
      over++;
      if(over>50)
	 break;
   }while(check_head(head));

   //it gives the difference bettween head & tail
   int max_tail;
   sub_board[head]++;
   over=0;
   if(head<50)
      max_tail=(head-(head%10))-10;
   else
      max_tail=(head-(head%10))-25;

   //it gives the tail of a snake
   if(head<87)
   {
      do{
	 tail=randomp(1,max_tail);
	 over++;
	 if(over>50)
	    break;
      }while(check_tail(tail));
   }
   //it gives tail of the longest snake
   else
      tail=randomp(1,25);
   sub_board[tail]++;
}


static int no_of_up_in_row[13];
static int no_of_up_in_column [13];

//it checks if the up of the ladder is in same row & column
int check_up(int init_up)
{
   int up_in_column;
   init_up--;
   if((int(init_up/10)%2)==0)
      up_in_column=init_up%10;
   else
      up_in_column=9-init_up%10;

   if(no_of_up_in_column[up_in_column]<1)
   {
      no_of_up_in_column [up_in_column]++;
      return 0;
   }
   else
      return 1;
}


static int no_of_down_in_column[13];
int gap_of_down[]={0,0,0,0,0,16,13,11,10,9,8};

//it checks if the down of the ladder is in samecolumn
int check_down(int init_down)
{
   int i;
   init_down--;
   if((int(init_down/10)%2)==0)
      i=init_down%10;
   else
      i=9-init_down%10;

   if(no_of_down_in_column[i]<1)
   {
      no_of_down_in_column[i]++;
      return 0;
   }
   else
      return 1;
}


//it gives the up & down positions of a ladder
void position_of_ladder(int &down,int &up,int i,int gap_of_down)
{
   int min_down;
   int max_down ;
   int over=0;
   int init_down;
   //it takes particular series
   min_down=i*gap_of_down;
   max_down=i*gap_of_down+gap_of_down ;
   if(i==0)
      min_down=2;

   //it gives position of down of the ladder
   do{
      do{
	 init_down=randomp(min_down,max_down);
      }while(init_down>79);
      over++;
      if(over>50)
	 break;
   }while(check_down(init_down));

   //it gives the difference between up & down of the ladder

   down=init_down;
   sub_board[down]++;
   int min_up;
   int init_up;
   over=0;
   min_up=(down-(down%10))+20;

   //it gives the position of top of the ladder
   if(min_up<80)
   {
      do{
	 init_up=randomp(min_up,min_up+20);
	 over++;
	if(over>50)
	    break;
      }while(check_up(init_up));
   }
   else
      init_up=randomp(min_up,98);

   up=init_up;
   sub_board[up]++;
}


static int play_board2[105];

//it prints the number in a sequance
void empty(int x)
{
   if(x<10)
      cout<<"  "<<x<<"  "<<sym[3];
   else if(x<100)
      cout<<" "<<x<<"  "<<sym[3];
   else
      cout<<" "<<x<<" "<<sym[3];
}


static int play_board[105];

//it prints the position of snakes and ladders
void not_empty(int n)
{
   int x;
   x=play_board[n];
   if(x<(-9))
      cout<<sym[6]<<x<<sym[6]<<sym[3];
   else if(x<0)
      cout<<sym[6]<<sym[6]<<x<<sym[6]<<sym[6]<<sym[3];
   else if(x<10)
      cout<<sym[6]<<"+"<<x<<sym[6]<<sym[6]<<sym[3];
   else
      cout<<sym[6]<<"+"<<x<<sym[6]<<sym[3];
}


//it prints the position of players
void posi(int x)
{
   textcolor(x);
   cprintf(" %c%c%c ",sym[6],sym[6],sym[6]);
   textcolor(grid);
   cout<<sym[3];
}


int llg;
int gap_of_head[]={0,0,0,0,0,16,13,11,10,9,8};
static int player[3];
char player_name[3][20];

void main()
{
   textcolor(grid);  //it gives the color to the entire text in the program
   randomize();
   clrscr();
   cout<<"W     ->  UP\nS     ->  DOWN\nSPACE ->  SELECT\n\n\n";
   system("pause");
   int nplayer=1;
   int control=1;
   char cnt;
   int snake[25];
   int ladder[25];
   int no_of_snakes;
   int no_of_ladders;
   int n,rr,ff,i,j;
   int exit;
   int di=1,ll=0;
   char option,p[5],ch;
   int pl=0;
   do{
      BACK:
      do{
	 p[1]=' ';
	 p[2]=' ';
	 p[3]=' ';
	 p[control]=16;
	 clrscr();
	 cout<<"\n\n\n\n\n\n\n";
	 cout<<"\t\t\t\t"<<p[1]<<"START\n";
	 cout<<"\t\t\t\t"<<p[2]<<"DEVELOPERS\n\t\t\t\t"<<p[3]<<"EXIT\n";
	 ch=getche();
	 if(ch=='w')
	 {
	    if(control==1)
	       control=3;
	    else
	       control--;
	 }
	 if(ch=='s')
	 {
	    if(control==3)
	       control=1;
	    else
	       control++;
	 }
	 if(ch==32)
	    break;

      }while(1);
      if(control==2)
      {
	 for(i=20;i>0;i--)
	 {
	 clrscr();
	 for(j=i;j>0;j--)
	   cout<<endl;
	 textcolor(dev);
	 cout<<"VIGNESHWARAN\n";
	 }
	 system("pause");
	 textcolor(grid);
      }
      if(control==3)
	 break;
      if(control==1)
      {

	 //it get the number of players from the user
	 do{
	    p[1]=' ';
	    p[2]=' ';
	    p[3]=' ';
	    p[4]=' ';
	    p[nplayer]=16;
	    clrscr();
	    for(i=0;i<1;i++)
	    cout<<"\n\n\n\n\n\n\n\n\t\t\t\t";
	    cout<<p[1]<<"1 PLAYER\n\t\t\t\t";
	    cout<<p[2]<<"2 PLAYER\n\t\t\t\t";
	    cout<<p[3]<<"3 PLAYER\n\t\t\t\t";
	    cout<<p[4]<<"BACK\n";
	    ch=getche();
	    if(ch=='w')
	    {
	       if(nplayer==1)
		  nplayer=4;
	       else
		  nplayer--;
	    }
	    if(ch=='s')
	    {
	       if(nplayer==4)
		  nplayer=1;
	       else
		  nplayer++;
	    }
	    if(ch==32)
	       break;
	 }while(1);
	 if(nplayer==4)
	   goto BACK;
	 clrscr();

	 //it gets the name of the players
	 for(i=0;i<nplayer;i++)
	 {
	    cout<<"ENTER NAME OF PLAYER"<<i+1<<":";
	    cin>>player_name[i];
	    if(nplayer==1)
	       strcpy(player_name[1],"COMPUTER");
	 }
	 clrscr();
	 cout<<"T->ROLL THE DICE\nM->GOTO MENU\n";
	 delay(1400);

	 //it gives the number of snakes & ladders randomly
	 no_of_snakes=random_no(6,11);
	 no_of_ladders=random_no(6,11);

	 //it gives the snake positions
	 for(i=0;i<no_of_snakes;i++)
	    position_of_snake(snake[i],snake[i+no_of_snakes],i,gap_of_head[no_of_snakes]);

	 //it gives the ladder positions
	 for(i=0;i<no_of_ladders;i++)
	    position_of_ladder(ladder[i],ladder[i+no_of_ladders],i,gap_of_down[no_of_ladders]);

	 //initialize the the value between 0-100
	 for(i=0;i<101;i++)
	    play_board2[i]=i;

	 //get the head &tail position
	 for(i=0;i<no_of_snakes;i++)
	    play_board[snake[i]]=snake[i+no_of_snakes]-snake[i];

	 //get the down & top position
	 for(i=0;i<no_of_ladders;i++)
	    play_board[ladder[i]]=ladder[i+no_of_ladders]-ladder[i];



	 //prints the table
	 do{

	    //prints the exact position of the player in the table
	    do{
	       if(ll>0)
		  ++player[pl];
	       clrscr();

	       for(i=9;i>=0;i--)
	       {
		  cout<<"    "<<sym[0];

		  //creates the line
		  for(rr=0;rr<10;rr++)
		  {
		     for(ff=0;ff<5;ff++)
			cout<<sym[1];
		     if(rr==9)
			cout<<sym[4];
		     else
			cout<<sym[2];
		  }
		  cout<<endl<<"    "<<sym[3];

		  //prints the player,snakes,ladder positions & box number
		  if((i%2)==0)
		  {
		     for(int j=1;j<11;j++)
		     {
			n=i*10+j;
			if(player[0]==n)
			   posi(pl1);
			else if(player[1]==n)
			   posi(pl2);
			else if(player[2]==n)
			   posi(pl3);
			else if(play_board[n]==0)
			   empty(n);
			else
			   not_empty(n);
		     }
		     cout<<endl;
		  }
		  else
		  {
		     for(int j=10;j>0;j--)
		     {
			n=i*10+j;
			if(player[0]==n)
			   posi(pl1);
			else if(player[1]==n)
			   posi(pl2);
			else if(player[2]==n)
			   posi(pl3);
			else if(play_board[n]==0)
			   empty(n);
			else
			   not_empty(n);
		     }
		     cout<<endl;
		  }
	       }
	       cout<<"    "<<sym[9];
	       for(rr=0;rr<10;rr++)
	       {
		  for(ff=0;ff<5;ff++)
		     cout<<sym[1];
		  if(rr==9)
		     cout<<sym[10];
		  else
		     cout<<sym[11];
	       }
	       cout<<"\n    ";

	       //prints the players information
	       textcolor(pl1);
	       cprintf("%s: ",player_name[0]);
	       textcolor(value);
	       cprintf("%d",player[0]);
	       textcolor(pl2);
	       cout<<"\t";
	       cprintf("%s: ",player_name[1]);
	       textcolor(value);
	       cprintf("%d",player[1]);
	       if(nplayer==3)
	       {
		  textcolor(pl3);
		  cout<<"\t";
		  cprintf("%s: ",player_name[2]);
		  textcolor(value);
		  cprintf("%d",player[2]);
	       }
	       textcolor(grid);

	       if(ll!=0)
	       {
		  ll--;
		  delay(de);
	       }
	    }while(ll!=0);

	    //get the playern instruction
	    if(di!=0)
	    {
	       cout<<endl<<player_name[pl]<<" ";
	       cout<<"\tPRESS 'T' ";
	       do{
		  if((nplayer!=1)||(pl!=1))
		     option=getche();
		  else
		  {
		     option='t';
		     cout<<endl;
		  }

		  //get the dice value
		  if(option=='t'||option=='T')
		  {
		     delay(de);
		     di=random_no(1,7);
		     cout<<"\t\t\t"<<di<<endl;
		     delay(de);
		     break;
		  }
		  else if(option=='m'||option=='M')
		     break;
	       }while(option!='t'||option!='T');
	       if(option=='m'||option=='M')
		  break;
         
	       llg=di;
	       if(player[pl]!=0||di==1)
	       {
		  ll=di;
		  di=0;
		  continue;
	       }
	    }

	    //checking for the snake or ladders at the player position
	    di=llg;
	    if(play_board[player[pl]]!=0)
	    {
	       clrscr();
	       if(play_board[player[pl]]<0)
		  cout<<"\n\n\n\n\n\n\n\n\n\n\t\t\tSNAKE BIT YOU";
	       else
		  cout<<"\n\n\n\n\n\n\n\n\n\n\t\t\tYOU FIND A LADDER";
	       delay(de);
		  player[pl]=player[pl]+play_board[player[pl]];
	    }

	    //looking for the next player
	    if(di<5&&di>1)
	    {
	       if((nplayer==1)&&(pl==1))
		  pl=0;
	       else if(nplayer==1)
		  pl++;
	       else if(pl==(nplayer-1))
		  pl=0;
	       else
		  pl++;
	    }
	 }while(player[1]<100&&player[2]<100&&player[0]<100);
      }
      clrscr();
      if(player[0]>99)
	 cout<<"\n\n\n\n\n\n\n\n\n\n\t\t\t"<<player_name[0]<<" WINS THE MATCH";
      if(player[1]>99)
	 cout<<"\n\n\n\n\n\n\n\n\n\n\t\t\t"<<player_name[1]<<" WINS THE MATCH";
      if(player[2]>99)
	 cout<<"\n\n\n\n\n\n\n\n\n\n\t\t\t"<<player_name[2]<<" WINS THE MATCH";
   }while(1);
   getch();
}