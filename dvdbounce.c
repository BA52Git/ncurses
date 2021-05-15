#include <ncurses.h>

//Precompile variables to avoid magic numbers and make for easy tuning
#define BOX_WIDTH  24
#define BOX_HEIGHT 7
#define MVDELAY    200

int main(){
	WINDOW *dvdbox;
	int ydir = 1;
	int xdir = 2;
	int ypos = 1;
	int xpos = 1;

	initscr();
	refresh();

	start_color();
	init_pair(1,COLOR_WHITE,COLOR_CYAN);

//create dvdbox window
	dvdbox = newwin(BOX_HEIGHT,BOX_WIDTH,ypos,xpos);
	if( dvdbox == NULL)
	{
		endwin();
		puts("Unable to create window");
		return(1);
	}

//put text on dvdbox window
	wbkgd(dvdbox,COLOR_PAIR(1));
	mvwaddstr(dvdbox,1,2,"DDDD  VV    VV  DDDD");
	mvwaddstr(dvdbox,2,2,"DD DD  VV  VV   DD DD");
	mvwaddstr(dvdbox,3,2,"DD DD   VVVV    DD DD");
	mvwaddstr(dvdbox,4,2,"DDDD     VV     DDDD");
	mvwaddstr(dvdbox,5,2,"        VIDEO");
	wborder(dvdbox,0,0,0,0,0,0,0,0);
	wrefresh(dvdbox);

	nodelay(dvdbox,TRUE);
	nodelay(stdscr,TRUE);
//	nodelay(TRUE);

	while(getch() == -1)
	{

		if(ypos + BOX_HEIGHT >= LINES)
		{
			ydir = -1;
		}

		if( ypos <= 0)
		{
			ypos = 0;
			ydir = 1;
		}

		if(xpos + BOX_WIDTH >= COLS)
		{
			xdir = -1;
		}

		if( xpos <= 0)
		{
			xpos = 0;
			xdir = 1;
		}

		
		ypos += ydir;
		xpos += xdir;

		mvwin(dvdbox, ypos, xpos);

		touchwin(stdscr);
		refresh();
		wrefresh(dvdbox);
		napms(MVDELAY);
	}

//added in screen refresh as per instructions


	endwin();
	return(0);
}
