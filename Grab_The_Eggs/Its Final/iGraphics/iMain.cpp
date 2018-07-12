/*
	author: Anik Chowdhury and Faiza Omar
	Aust,Cse, 34th Batch
*/
# include "iGraphics.h"
#include <stdlib.h>


int jhuri_x = 0;
int jhuri_y = 0;
int type[]= {0,0,0,0,1,2,1,1,1,1,1};
int nDim_x[]={100,250,370,450,55,300,0,0,0,0,0};
int nDim_y[]={500,450,500,450,500,450,500,450,500,450,500};
int levelSpeed[]={0,5,10,15,20,25,30,35,40};
int tempSpeed[]={5,10,8,16,14,15,0,0,0,0,0};
int noOfNdim=6;
int t1;
int score=0;
int level=1;
int speed;
int isPause = 1;
int needHelp = 1; 
int lives=3;
int mode=1,hs=1;
int noOfBomb=1;
int animationTemp=0;
int hs_flag_for_gameover=0;
int hs_flag_for_scoreboard=0;
char hscore[12][200];
FILE *input, *output;
struct player{
	char name[20];
	int highscore;
	}s[11],temp;

//for text box
char str[100],str2[100];
int len=0;
int textMode=0;

void drawTextBox()
{
	iSetColor(150, 150, 150);
	iRectangle(150, 300, 450, 30);
}

//text box end


//user defined functions

void MainMenuHighScore(){
	
		input = fopen("Highscore.txt", "r");
	
		for(int j=0; j<10; j++)
		{
			fscanf(input,"%d %s", &s[j].highscore, s[j].name);
			sprintf(hscore[j], " %d------------%s",s[j].highscore,s[j].name);
		}
		fclose(input);
		hs_flag_for_scoreboard=1;
}
void bombcalculator(){
	if(level==3 && noOfBomb==1){
		noOfBomb++;
		noOfNdim++;
		nDim_x[noOfNdim]=rand()%568;
	}
	if(level==5 && noOfBomb==2){
		noOfBomb++;
		noOfNdim++;
		nDim_x[noOfNdim]=rand()%568;
	}
	if(level==7 && noOfBomb==3){
		noOfBomb++;
		noOfNdim++;
		nDim_x[noOfNdim]=rand()%568;
	}
	if(level==9 && noOfBomb==4){
		noOfBomb++;
		noOfNdim++;
		nDim_x[noOfNdim]=rand()%568;
	}

}
void move(){
	for(int i =0;i<noOfNdim;i++){
		if(nDim_y[i]>=0){
			speed= tempSpeed[i]+levelSpeed[level-1];
			nDim_y[i]-=speed;
		}
		
		else {
			nDim_x[i]=rand()%568;
			nDim_y[i]= 500;
		}
	}	
		
}

void points()
{
	for(int i=0;i<noOfNdim;i++){
        if(jhuri_x<=nDim_x[i] && jhuri_x+128>=nDim_x[i]+32 && nDim_y[i]<=jhuri_y+64){
			if(type[i]==0){
				nDim_x[i]=(rand()%568);    
				nDim_y[i]=600;
                score+=1;
			}
			if(type[i]==1){
				nDim_x[i]=(rand()%568);    
				nDim_y[i]=600;
				lives--;
				if(lives==0){
					mode=4;

				}
			}
			if(type[i]==2){
				nDim_x[i]=(rand()%568);    
				nDim_y[i]=600;
				score+=5;
			}
        }
	}
}
void isMissed()
{
	for(int i=0;i<noOfNdim;i++){
		if((nDim_x[i]+32<=jhuri_x || jhuri_x+128<=nDim_x[i]) && nDim_y[i]<=34){
			if(type[i]==0){
				iShowBMPWOBG(nDim_x[i],0,"fatadim.bmp");
				if(score>0)score--;
				nDim_y[i]=600;
			}
			if(type[i]==1)iShowBMPWOBG(nDim_x[i],0,"fataBomb.bmp");
			if(type[i]==2)iShowBMPWOBG(nDim_x[i],0,"fatadim.bmp");
		}
	}
}
void scoring()
{
        char strScore[100],strLevel[100],strHighScore[100];
        iSetColor(0,0,0 );
        sprintf( strScore, "Score: %d", score);
        iText( 660, 435, strScore, GLUT_BITMAP_TIMES_ROMAN_24);
		sprintf(strLevel, "Level: %d",level);
		iText(660,405,strLevel, GLUT_BITMAP_TIMES_ROMAN_24);
		if(hs_flag_for_scoreboard==0)MainMenuHighScore();
		if(s[0].highscore>score){
			sprintf(strHighScore, "HighScore: %d",s[0].highscore);
			iText(630,375,strHighScore, GLUT_BITMAP_TIMES_ROMAN_24);
		}
		else{
			sprintf(strHighScore, "HighScore: %d",score);
			iText(630,375,strHighScore, GLUT_BITMAP_TIMES_ROMAN_24);
		}
		
                
}
void gameOverScoring()
{
        char strScore[200];
        iSetColor( 0, 0, 0 );
        sprintf( strScore, "%s your Score is: %d",str2,score);
        iText(316,305, strScore, GLUT_BITMAP_TIMES_ROMAN_24);
                
}
void levelUp()
{
	if(score>30 && score<60)level=2;
	else if(score>60 && score<90) level=3;
	else if(score>90 && score<120) level=4;
	else if(score>120 && score<150) level=5;
	else if(score>150 && score<180) level=6;
	else if(score>180 && score<210) level=7;
	else if(score>210 && score<240) level=8;
	else if(score>240) level=9;
}
void showLiveStatus(){
	if(lives==3)iShowBMP(626,220,"threeLives.bmp");
	if(lives==2)iShowBMP(626,220,"twoLives.bmp");
	if(lives==1)iShowBMP(626,220,"oneLives.bmp");
}
void animation(){
	if(animationTemp==0) animationTemp=1;
	else animationTemp=0;
}

void retry(){
		jhuri_x = 0;
		jhuri_y = 0;
		noOfNdim=6;
		score=0;
		level=1;
		isPause = 1;
		needHelp = 1; 
		lives=3;
		noOfBomb=1;
		hs_flag_for_gameover=0;
		hs_flag_for_scoreboard=0;
}


void showMainMenuHighScore(){
		iText(300,550,"HighScores",GLUT_BITMAP_TIMES_ROMAN_24);
		iText(225,500,"Score                         Name",GLUT_BITMAP_TIMES_ROMAN_24);
		iText(225,475, hscore[0], GLUT_BITMAP_TIMES_ROMAN_24);
		iText(225,450, hscore[1], GLUT_BITMAP_TIMES_ROMAN_24);
		iText(225,425, hscore[2], GLUT_BITMAP_TIMES_ROMAN_24);
		iText(225,400, hscore[3], GLUT_BITMAP_TIMES_ROMAN_24);
		iText(225,375, hscore[4], GLUT_BITMAP_TIMES_ROMAN_24);
		iText(225,350, hscore[5], GLUT_BITMAP_TIMES_ROMAN_24);
		iText(225,325, hscore[6], GLUT_BITMAP_TIMES_ROMAN_24);
		iText(225,300, hscore[7], GLUT_BITMAP_TIMES_ROMAN_24);
		iText(225,275, hscore[8], GLUT_BITMAP_TIMES_ROMAN_24);
		iText(225,250, hscore[9], GLUT_BITMAP_TIMES_ROMAN_24);
}
void highScoreChange(){
		s[10].highscore = score;
	if(score>s[9].highscore){
		for (int c = 0 ; c < ( 11 - 1 ); c++)
		{
			for (int d = 0 ; d < 11 - c - 1; d++)
			{
			if (s[d].highscore < s[d+1].highscore)
				{
					temp   = s[d];
					s[d]   = s[d+1];
					s[d+1] = temp;
				}
			}
		}
		output = fopen("Highscore.txt", "w");
		for(int j=0; j<10; j++)
		{
			fprintf(output,"%d %s\n", s[j].highscore, s[j].name);
			sprintf(hscore[j], " %d------------%s",s[j].highscore,s[j].name);
		}
		fclose(output);
		hs_flag_for_gameover=1;
		hs_flag_for_scoreboard=0;
	}
}
void iDraw()
{
	//place your drawing codes here
	if(mode==1){
		iClear();
		iShowBMP(0,0,"Menu.bmp");
		if(needHelp%2==0)iShowBMP(0,0,"helpMenuForMainMenu.bmp");
	}
	if(mode==2){
		iClear();
		drawTextBox();
		iText(150,350,"Enter Your Name: ");
		if(textMode == 1)
		{
			iSetColor(255, 255, 255);
			iText(150, 312, str);
		}

		iText(10, 10, "Click to activate the box, enter to finish.");
		//mode=3;
	}
	if(mode==3){
		iClear();
		iShowBMP(0,0,"background.bmp");
		iShowBMP(601,0,"scoreBoard.bmp");
		for(int i=0;i<noOfNdim;i++){
			if(type[i]==0)iShowBMPWOBG(nDim_x[i],nDim_y[i],"nDim.bmp");
			if(type[i]==1)iShowBMPWOBG(nDim_x[i],nDim_y[i],"bomb.bmp");
			if(type[i]==2)iShowBMPWOBG(nDim_x[i],nDim_y[i],"dim.bmp");
		}
		iShowBMPWOBG(jhuri_x,jhuri_y,"jhuri.bmp");
		if(isPause%2==0)iShowBMP(0,0,"pauseMenuTemp.bmp");
		if(needHelp%2==0)iShowBMP(0,0,"hlpMenu.bmp");
		
		showLiveStatus();
		isMissed();
		points();
		scoring();
		levelUp();
		bombcalculator();
		
	}
	if(mode==4){
		iClear();
		if(hs_flag_for_gameover==0)highScoreChange();
		if(animationTemp==0) iShowBMP(0,0,"gameOver1.bmp");
		else iShowBMP(0,0,"gameOver2.bmp");
		animation();
		gameOverScoring();
		iShowBMP(100,100,"gameOverButtons.bmp");
	}
	if(mode==5){
		iShowBMP(0,0,"HighScoreBoard.bmp");
		if(hs_flag_for_scoreboard==0)MainMenuHighScore();
		iSetColor( 0, 0, 0 );
		showMainMenuHighScore();


	}
	if(mode==6){
		iShowBMP(0,0,"credits.bmp");
	}
	
}



void iMouseMove(int mx, int my)
{
}


void iMouse(int button, int state, int mx, int my)
{
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		if(mode==1){
			if(mx>=441 && mx<766 && my>=458 && my<=548){
				mode=2;
				printf("Start\n");
			}
			if(mx>=441 && mx<766 && my>=358 && my<=448){
				mode=5;
				printf("HighScore\n");
			}
			if(mx>=441 && mx<766 && my>=258 && my<=348){
				needHelp++;
				printf("HelpMenu\n");
			}
			if(mx>=441 && mx<766 && my>=158 && my<=248){
				mode=6;
				printf("About\n");
			}
			if(mx>=441 && mx<766 && my>=58 && my<=148){
				exit(0);
				printf("Exit\n");
			}
		}

		if(mode==2){
			if(mx >= 150 && mx <= 600 && my >= 300 && my <= 330 && textMode == 0)
			{
			textMode = 1;
			}
		}

		if(mode==4){
			if(mx>=126 && mx<=291 && my>=185 && my<=235){
				retry();
				mode=2;
				printf("retry\n");
			}
			if(mx>=316 && mx<=486 && my>=184 && my<=234){
				mode=1;
				retry();
				printf("Main Menu\n");
			}
			if(mx>=513 && mx<=675 && my>=185 && my<=235){
				exit(0);
				printf("Quit\n");
			}
		}

		if(mode==5){
			if(mx>=561 && mx<=771 && my>=39 && my<=89){
				mode=1;
			}
		}

		if(mode==6){
			if(mx>=511 && mx<=716 && my>=39 && my<=89){
				mode=1;
			}
		}
	}
	if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
	}
}

void iKeyboard(unsigned char key)
{	
	if(mode==2){
		int i;
		if(textMode == 1)
		{
			if(key == '\r')
			{
				//textMode = 0;
				strcpy(str2, str);
				strcpy(s[10].name, str);
				printf("%s\n", s[10].name);
				for(i = 0; i < len; i++)
				str[i] = 0;
				len = 0;
				mode=3;
				iResumeTimer(t1);
			}
			else
			{
				str[len] = key;
				len++;
			}
	}

		if(key == 'x')
		{
			//do something with 'x'
			exit(0);
		}
	}
	
	if(mode==3){
		if(key == 'p')
		{
			isPause++;
			if(isPause%2==0) iPauseTimer(t1);
			else iResumeTimer(t1);
		}
	}

	
	//place your codes for other keys here
}

/*
	function iSpecialKeyboard() is called whenver user hits special keys like-
	function keys, home, end, pg up, pg down, arraows etc. you have to use
	appropriate constants to detect them. A list is:
	GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
	GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
	GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
	GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
*/
void iSpecialKeyboard(unsigned char key)
{

	if(key == GLUT_KEY_RIGHT)
	{
		if(jhuri_x<470)jhuri_x+=20;
		if(jhuri_x==480)jhuri_x-=8;
	}
	if(key == GLUT_KEY_LEFT)
	{
		if(jhuri_x>0)jhuri_x-=20;
		if(jhuri_x==12)jhuri_x-=12;
	}
	
	
	if(key == GLUT_KEY_F1)
	{
		if(mode==1){
			needHelp++;
		}
		if(mode ==3){
			needHelp++;
			if(needHelp%2==0) iPauseTimer(t1);
			else iResumeTimer(t1);
		}
	}
	//place your codes for other keys here
}
int main()
{
	//place your own initialization codes here.
	t1 = iSetTimer(100,move);
	iPauseTimer(t1);
	//len = 0;
	//textMode = 0;
	str[0]= 0;
	PlaySound("Happy_Background_Music",NULL,SND_ASYNC);
	iInitialize(800,600, "GRAB THE EGGS");
	return 0;
}
