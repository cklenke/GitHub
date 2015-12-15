//Created by Collin Klenke and Ryan Mackey

#include<stdio.h>
#include"gfx5.h"
#include "gfxe.h"
#include<time.h>
#include<math.h>
#include<string.h>
#define XSIZE 1200
#define YSIZE 750
#define RAD 100

typedef struct circle_s{
	int x;
	int y;
	int draw;
}circle;

void basicMenu(int *r1);
void advancedMenu(int *n);
void countdownMenu(int *t);
void marathonMenu(double output[2],int *r2);
int advanced(int num);
void structXY(circle *c);
void putCircles(circle circles[], int num);
int countdown(int timer);
void draw2(int timer, int cx, int cy);
void getXY(int* x, int* y);
void drawbutton(int x, int y, int w, int h, char str[]);
void marathon(double output[2], int radius2);
void getXYc(int* x, int* y, int radius);
void basic(int radius1);

int main(){
	int radius1 = RAD, *r1;
	int score2, number = 5, *n;
	int score3, timer = 8, *t;
	int radius2 = RAD, *r2;
	char c;
	int xbegin, xend, x2begin, x2end;
	double output[2] = {0}, average;
	char clicknumChar[8], clicktimeChar[8], marathonOut[80] = "You got "; //to print score in gfx
	char countdownnumChar[8], countdownOut[80] = "You got ";

	r1 = &radius1;
	n = &number;
	t = &timer;
	r2 = &radius2;

	srand(time(NULL));

	xbegin = 481;
	xend = 687;
	x2begin = 699;
	x2end = 750;

	gfx_open(XSIZE, YSIZE, "Lightning Loops");
	unsigned char * buff = readRAWImage("GameMenu.bmp", 54);
	printRAWImage(0, 0, XSIZE, YSIZE, buff);
	while(1){
		c = gfx_wait();
		gfx_wait();
		if(c == 1){
			if(gfx_xpos()>=xbegin && gfx_xpos() <=xend){
				if(gfx_ypos() >= 269 && gfx_ypos() <= 317){
					basic(radius1); // gamemode 1
					gfx_clear();
				}
				else if(gfx_ypos() >= 327 && gfx_ypos() <= 375){
					score2 = advanced(number); // gamemode 2
					gfx_clear();
					//printf("YOUR SCORE: %d\n", score2);
				}
				else if(gfx_ypos() >= 387 && gfx_ypos() <= 435){
					score3 = countdown(timer); // gamemode 3
					sprintf(countdownnumChar, "%d", score3);
					strcat(countdownOut, countdownnumChar);
					strcat(countdownOut, " loops. Nice!"); //concatenate score with string
					gfx_color(200,10,10);
					gfx_clear();
					gfx_text(XSIZE/2 - 100, YSIZE/2, countdownOut);
					gfx_flush();
					sleep(3);
					
					countdownnumChar[0] = '\0';
					countdownOut[0] = '\0';
					strcat(countdownOut, "You got "); //reset values
					
					gfx_clear();
				}
				else if(gfx_ypos()>= 447 && gfx_ypos() <= 495 ){
					marathon(output, radius2); // gamemode 4
					average = output[1]/output[0];
					
					sprintf(clicknumChar, "%.0f", output[0]);
					sprintf(clicktimeChar, "%.2f", average);
					strcat(marathonOut, clicknumChar);
					strcat(marathonOut, " circles with an average reaction of ");
					strcat(marathonOut, clicktimeChar);
					strcat(marathonOut, " seconds!"); //concatenate score with string
					
					gfx_color(200,10,10);
					gfx_clear();
					gfx_text(XSIZE/2 - 100, YSIZE/2, marathonOut);
					gfx_flush();
					sleep(3);
					
					clicknumChar[0] = '\0';
					clicktimeChar[0] = '\0';
					marathonOut[0] = '\0';
					strcat(marathonOut, "You got "); //these reset the values
					
					output[0] = 0;
					output[1] = 0;
					gfx_clear();
				}
				else if(gfx_ypos()>= 507 && gfx_ypos() <= 556 ){
					return 0;
				}
				printRAWImage(0, 0, XSIZE, YSIZE, buff); // reprint background
			}
			else if(gfx_xpos() >= x2begin && gfx_xpos() <= x2end){ //options
				if(gfx_ypos() >= 269 && gfx_ypos() <= 317){
				basicMenu(r1);
				}
				else if(gfx_ypos() >= 327 && gfx_ypos() <= 375){
				advancedMenu(n);
				}
				else if(gfx_ypos() >= 387 && gfx_ypos() <= 435){
				countdownMenu(t);
				}
				else if(gfx_ypos()>= 447 && gfx_ypos() <= 495 ){
				marathonMenu(output, r2);
				}
				printRAWImage(0, 0, XSIZE, YSIZE, buff);
			}
		}
		else if(c == 'q'){
			return 0;
		}
	}
}

void basicMenu(int *radius){
	char c;
	int x, y;
	gfx_clear();
	gfx_text(10,110,"Welcome to the first and most basic game mode of \"Lightning Loops\"!");
	gfx_text(10,120,"This game mode is designed to test your reaction times by ");
	gfx_text(10,130,"placing you into a high pressure situation before springing");
	gfx_text(10,140,"a wild bubble upon you at an undisclosed time. It could come");
	gfx_text(10,150,"in a few seconds, a bit longer than that, or even... RIGHT NOW!");
	gfx_text(10,160,"Just kidding, you haven't pressed 'start' yet. But once you do,");
	gfx_text(10,170,"the bubble could appear at any time and when it does a timer will begin");
	gfx_text(10,180,"Your goal is to click the button as quickly as you can without being");
	gfx_text(10,190,"premachure or inaccurate. If you succeed in hitting the bubble your");
	gfx_text(10,200,"reaction time will be reported. Can you beat the developer's record of");
	gfx_text(10,210,"0.34 seconds???");
	gfx_text(580,180, "SELECT BUBBLE RADIUS");
	drawbutton(600,200, 80, 20, "50"); // option  buttons
	drawbutton(600,230, 80, 20, "100");
	drawbutton(600,260, 80, 20, "200");
	drawbutton(550,300, 120, 30, "PLAY GAME");
	drawbutton(1100,700, 60, 15, "return"); // go back to the menu button
	while(1){
		c = gfx_wait();
		gfx_wait();
		if(c ==1){
			x = gfx_xpos();
			y = gfx_ypos();
			if(x>=600 && x<=680){ // alter variables within the actual game mode
				if(y>=200 && y<=220){
				*radius = 50;
				}
				else if(y>=230 && y<=250){
				*radius = 100;
				}
				else if(y>= 260 && y<=280){
				*radius = 200;
				}
			}
			if(x>=550 && x<=670 && y>=300 && y<=330){
				basic(*radius);
				return;
			}
			if(x>=1100 && x<= 1160 && y>=700 && y<= 715){
				return;
			}
		}
	}
}

void advancedMenu(int *number){
	char c;
	int x, y;
	gfx_clear();
	gfx_text(10,110,"This game is a big step up from the basic game mode,");
	gfx_text(10,120,"but it preserves the same core philosophy. You are supposed");
	gfx_text(10,130,"to click the bubbles that are present on the screen. A novel");
	gfx_text(10,140,"idea, fully realized in stunning gfx5. The major factor");
	gfx_text(10,150,"that differentiates this romp from your typical run of the ");
	gfx_text(10,160,"mill bubble clicker is the fact that multiple bubbles appear ");
	gfx_text(10,170,"simultaneously. You will be scored based on how fast you can ");
	gfx_text(10,180,"click every bubble. Luckily for you, there is not a penalty for ");
	gfx_text(10,190,"missed clicks. But then again, if you miss you'll probably be really slow");
	gfx_text(10,200,"Pro Tip: if the stars align, you can click multiple loops at once.");
	gfx_text(10,210,"Kill 'em till they're dead!");
	gfx_text(580,180, "SELECT NUMBER OF BUBBLES");
	drawbutton(600,200, 80, 20, "5");
	drawbutton(600,230, 80, 20, "10");
	drawbutton(600,260, 80, 20, "20");
	drawbutton(550,300, 120, 30, "PLAY GAME");
	drawbutton(1100,700, 60, 15, "return");
	drawbutton(20,700,30,10,"o_o"); //EASTER EGG YOU FOUND IT OMG
	while(1){
		c = gfx_wait();
		gfx_wait();
		if(c ==1){
			x = gfx_xpos();
			y = gfx_ypos();
			if(x>=600 && x<=680){
				if(y>=200 && y<=220){ //options
				*number = 5;
				}
				else if(y>=230 && y<=250){
				*number = 10;
				}
				else if(y>= 260 && y<=280){
				*number = 20;
				}
			}
			if(x>=550 && x<=670 && y>=300 && y<=330){
				advanced(*number);
				return;
			}
			if(x>=1100 && x<= 1160 && y>=700 && y<= 715){
				return;
			}
			if(x>=20 && x<=50 && y>=700 && y<=710){
				advanced(250);//OMG EASTER EGG
				return;
			}
		}
	}
}

void countdownMenu(int *timer){
	char c;
	int x, y, score3;
	char countdownnumChar[8], countdownOut[80] = "You got ";
	
	gfx_clear();
	gfx_text(10,110,"The object of this game is simple: you have an alotted");
	gfx_text(10,120,"amount of time to go on a bubble popping rampage. You");
	gfx_text(10,130,"have to pop every bubble that you see as quickly as you");
	gfx_text(10,140,"can before time runs out. There is no penalty for missing");
	gfx_text(10,150,"clicks, so feel free to go hog wild out there! It's time");
	gfx_text(10,160,"to teach those randomly appearing bubbles a lesson.");
	gfx_text(10,170,"Select your favorite time to the right. Good Luck!");
	gfx_text(580,180, "SELECT TIMER VALUE");
	drawbutton(600,200, 80, 20, "4");
	drawbutton(600,230, 80, 20, "8");
	drawbutton(600,260, 80, 20, "12");
	drawbutton(550,300, 120, 30, "PLAY GAME");
	drawbutton(1100,700, 60, 15, "return");
	while(1){
		c = gfx_wait();
		gfx_wait();
		if(c ==1){
			x = gfx_xpos();
			y = gfx_ypos();
			if(x>=600 && x<=680){
				if(y>=200 && y<=220){
				*timer = 4;
				}
				else if(y>=230 && y<=250){
				*timer = 8;
				}
				else if(y>= 260 && y<=280){
				*timer = 12;
				}
			}
			if(x>=550 && x<=670 && y>=300 && y<=330){
				score3 = countdown(*timer); // run the game mode
				
				sprintf(countdownnumChar, "%d", score3); //print your score
				strcat(countdownOut, countdownnumChar);
				strcat(countdownOut, " loops. Nice!");
					
				gfx_color(200,10,10);
				gfx_clear();
				gfx_text(XSIZE/2 - 100, YSIZE/2, countdownOut);
				gfx_flush();
				sleep(3);
					
				countdownnumChar[0] = '\0';
				countdownOut[0] = '\0';
				strcat(countdownOut, "You got "); //reset values
					
				gfx_clear();
				
				return;
			}
			if(x>=1100 && x<= 1160 && y>=700 && y<= 715){
				return;
			}
		}
	}
}

void marathonMenu(double output[2], int *radius){
	char c;
	char clicknumChar[8], clicktimeChar[8], marathonOut[80] = "You got ";
	int x, y, average;
	gfx_clear();
	gfx_text(10,110,"This game mode was inspired by the ancient Greek legend");
	gfx_text(10,120,"of the Battle of Thermopylae, the source for everyone's");
	gfx_text(10,130,"favorite catchphrase 'THIS IS SPARTA'. In it you must");
	gfx_text(10,140,"click on the bubbles as they appear until you miss. You");
	gfx_text(10,150,"are evaluated based on how many you click before missing");
	gfx_text(10,160,"as well as the average interval between bubble clicks.");
	gfx_text(10,170,"A true Spartan clicks a lot in a little time. But watch out!");
	gfx_text(10,180,"The bubbles get smaller as you go!");
	gfx_text(580,180, "SELECT INITIAL RADIUS");
	drawbutton(600,200, 80, 20, "50");
	drawbutton(600,230, 80, 20, "100");
	drawbutton(600,260, 80, 20, "150");
	drawbutton(550,300, 120, 30, "PLAY GAME");
	drawbutton(1100,700, 60, 15, "return");
	while(1){
		c = gfx_wait();
		gfx_wait();
		if(c ==1){
			x = gfx_xpos();
			y = gfx_ypos();
			if(x>=600 && x<=680){
				if(y>=200 && y<=220){
				*radius = 50;
				}
				else if(y>=230 && y<=250){
				*radius = 100;
				}
				else if(y>= 260 && y<=280){
				*radius = 150;
				}
			}
			if(x>=550 && x<=670 && y>=300 && y<=330){
				marathon(output, *radius); //run game
				average = output[1]/output[0];
					
				sprintf(clicknumChar, "%.0f", output[0]); //print score
				sprintf(clicktimeChar, "%.2f", average);
				strcat(marathonOut, clicknumChar);
				strcat(marathonOut, " loops with an average reaction of ");
				strcat(marathonOut, clicktimeChar);
				strcat(marathonOut, " seconds!");
				
				gfx_color(200,10,10);
				gfx_clear();
				gfx_text(XSIZE/2 - 100, YSIZE/2, marathonOut);
				gfx_flush();
				sleep(3);
				
				clicknumChar[0] = '\0';
				clicktimeChar[0] = '\0';
				marathonOut[0] = '\0';
				strcat(marathonOut, "You got "); //these reset the values
				
				output[0] = 0;
				output[1] = 0;
				gfx_clear();
				return;
			}
			if(x>=1100 && x<= 1160 && y>=700 && y<= 715){
				return;
			}
		}
	}
}

//The following game mode presents 5 multiple bubbles that all must be clicked

int advanced(int num){
	gfx_clear();
	int i, counter, all = num;
	double t, time;
	char c = 'l', timeChar[8], outputChar[] = "It took you ";
	circle circles[num]; // struct of circles
	for(i=0; i<num; i++){
		structXY(&circles[i]); // populates the struct with the proper number
	}
	putCircles(circles, num); // draws the circles for clicking
	while(all>0){
		if(gfx_event_waiting()){
			if(gfx_wait() == 1){ // operates on a click
				all=0;
				for(i=0; i<num; i++){ // checks all of the circles to see if they've been clicked on a click
									//Utilizes te distances formula and the radial symmetry of circles for hit detection
					if(sqrt(pow(gfx_xpos()-circles[i].x,2)+pow(gfx_ypos()-circles[i].y,2))<=RAD){
						circles[i].draw = 0; // sets the draw variable to false if clicked
						counter++;
					}
					if(circles[i].draw){
						all++; // increments if circles still remain
					}
				}
				putCircles(circles, num); //draws the circles that remain
			}
			else if(gfx_wait() == 'q'){ // quits on 'q' press
				return;
			}
		}
		t = t + 1; // timer functionalities
		usleep(10000);
	}
	time = t / 100 + num*.1; //we added .1*num to account for the time the user is pressing down on the mouse, as that time is not recorded
	sprintf(timeChar, "%.2f", time);
	strcat(outputChar, timeChar);
	strcat(outputChar, " seconds to click them all!"); //concatenate
	gfx_color(200,10,10);
	gfx_clear();
	gfx_text(XSIZE/2 - 100, YSIZE/2, outputChar);
	gfx_flush();
	sleep(3);

	timeChar[0] = '\0';

	return counter;
}

//populates the array of circle struct

void structXY(circle *c){
	c->x = rand()%(XSIZE-2*RAD)+RAD; //gives each a random position fully in the screen
	c->y = rand()%(YSIZE-2*RAD)+RAD;
	c->draw = 1; // initializes them as being drawn
}

void putCircles(circle circles[], int num){
	gfx_clear();
	int i;
	for(i=0; i<num; i++){
		if(circles[i].draw){ // draws all of the circles that have a true draw value
			gfx_circle(circles[i].x, circles[i].y, RAD);
		}
	}
}

//game mode with a decrementing timer and bubbles that appear on bubble clicks until timer reaches 0

int countdown(int timer){
	gfx_clear();
	int cx, cy, *x, *y, time=0, counter=0;
	x = &cx;
	y = &cy;
	getXY(x,y); // randomly places the first circle

	draw2(timer, cx, cy); // draws the appropriate time and circle

	while(timer>=1){ // before the game ends
		if(gfx_event_waiting()){
			if(gfx_wait() == 1){ // on a click
				if(sqrt(pow(gfx_xpos()-cx,2)+pow(gfx_ypos()-cy,2))<=RAD){ // distance formula for hit detection
					getXY(x,y); // new circle to draw
					draw2(timer, cx, cy); // draws the appropriate things
					counter++; // counts hits
				}
			}
		}
		usleep(100); // timer implementations
		time++;
		if(time==10000){
			timer--;
			time = 0;
			if(timer>=1)
				draw2(timer, cx, cy); // redraws with same circle on new timer decrement
		}
	}
	return counter;
}

//draws the circle and timer

void draw2(int timer, int cx, int cy){
	static char a[10], *p =a;
	gfx_clear();
	snprintf(p, 10, "%d", timer);
	gfx_text(XSIZE-50, YSIZE-50, p);
	gfx_circle(cx, cy, RAD);
	gfx_flush();
}

//generates locations for one circle

void getXY(int * x, int * y){
	*x = rand() % (XSIZE - 2*RAD) + RAD;
	*y = rand() % (YSIZE - 2*RAD) + RAD;
}

//used in the menu to draw buttons with text of desired size

void drawbutton(int x, int y, int w, int h, char string[]){
	gfx_rectangle(x, y, w, h);
	gfx_line(x, y, x - 5, y - 5);
	gfx_line(x, y + h, x - 5, y + h - 5);
	gfx_line(x - 5, y - 5, x - 5, y + h - 5);
	gfx_line(x - 5, y - 5, x + w - 5, y - 5);
	gfx_line(x + w, y, x + w - 5, y - 5);
	gfx_text(x+5, y+h-5, string);
}

//game mode that draws shrinking circles continuously

void marathon(double output[2], int radius){
	char c;
	int timer;
	double reaction, t = 0;
	int xpos, ypos, i = 1, *x, *y;
	x = &xpos;
	y = &ypos;
	timer = 600;
	gfx_wait();
	
	/*while(1){
		/*if(gfx_event_waiting()){
			c = gfx_wait();
			gfx_wait();
			if(c == 1){
				return;
			}
			if(c == 'q'){
				return;
			}
		}
		i++;
		if(i == timer){
			break;
		}
		usleep(3000);
	}*/
	gfx_color(30, 100, 200);
	gfx_clear();
	getXYc(x,y, radius);
	gfx_circle(xpos, ypos, radius);
	gfx_flush();
	if (radius>10){
		radius -= 5;
	}
	while(1){
		t = t + 1;
		usleep(100);
		if(gfx_event_waiting()){
			c = gfx_wait();
			gfx_wait();
			if(c == 'q'){
				gfx_clear();
				break;
			}
			if(c == 1){
				reaction = t / 10000;
				if(sqrt(pow(gfx_xpos()-xpos,2)+pow(gfx_ypos()-ypos,2))<=radius){
					output[0] = output[0] + 1; //# of correct clicks
					output[1] = output[1] + reaction; //total time passed.
					marathon(output, radius); //recursively call the function, using output as an array to constantly update values
					return;
				} else {
					break;
				}
			}
		}
	}
	return;
}

//generates x and y coordinates for variable radius circles

void getXYc(int * x, int * y, int radius){
	*x = rand()%(XSIZE-2*radius)+radius;
	*y = rand()%(YSIZE-2*radius)+radius;
}

//game mode where one delayed circle appears

void basic(int radius){ 
	char c, earlyclick[] = "You clicked too soon. You lose.", missedclick[] = "You missed the loop. You lose.";
	char reactionChar[8], printReact[80] = "Your reaction time was ";
	int  xpos, ypos, i = 1, timer, *x, *y;
	double reaction, t = 0;
	x = &xpos;
	y = &ypos;
	timer = rand()%500;
	gfx_clear();
	while(1){
		if(gfx_event_waiting()){
			c = gfx_wait();
			gfx_wait();
			if(c == 4){
				gfx_color(200,10,10);
				gfx_text(XSIZE/2 - 100, YSIZE/2, earlyclick);
				gfx_flush();
				sleep(3);
				return;
			}
			if(c == 'q'){
				return;
			}
		}
		i++;
		if(i == timer){
			break;
		}
		usleep(6000);
	}
	gfx_color(rand()%255, rand()%255, rand()%255);
	gfx_clear();
	getXYc(x, y, radius);
	gfx_circle(xpos, ypos, radius);
	while(1){
		if(gfx_event_waiting()){
			c = gfx_wait();
			gfx_wait();
			if(c == 1){
				reaction = t / 100;
				if(sqrt(pow(gfx_xpos()-xpos,2)+pow(gfx_ypos()-ypos,2))<=radius){
					sprintf(reactionChar, "%.2f", reaction);
					strcat(printReact, reactionChar);
					strcat(printReact, " seconds");
					gfx_color(200,10,10);
					gfx_clear();
					gfx_text(XSIZE/2 - 100, YSIZE/2, printReact);
					gfx_flush();
					sleep(3);
					break;
				} else {
					gfx_color(200,10,10);
					gfx_clear();
					gfx_text(XSIZE/2 - 100, YSIZE/2, missedclick);
					gfx_flush();
					sleep(3);
					return;
				}
				break;
			}
			if(c == 'q'){
				return;
			}
		}
	t = t + 1;
	usleep(10000);
	}
	return;
}
