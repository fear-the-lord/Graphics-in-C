//Chess Board
#include <stdio.h>
#include <graphics.h>
#include <conio.h>
#include <math.h>
void vertical(int x1,int y1,int y2,int tc)
{
	int i;
	for(i=y1;i<=y2;i++)
		putpixel(x1,i,tc);
	delay(5);
}

void chessboard()
{
	int i;
	for(i=120;i<=520;i++)
		putpixel(i,440,4);

	for(i=440;i>=40;i--)
		putpixel(520,i,4);

	for(i=520;i>=120;i--)
		putpixel(i,40,4);

	for(i=40;i<=440;i++)
		putpixel(120,i,4);

	for(i=115;i<=525;i++)
		putpixel(i,445,4);

	for(i=445;i>=35;i--)
		putpixel(525,i,4);

	for(i=525;i>=115;i--)
		putpixel(i,35,4);

	for(i=35;i<=445;i++)
		putpixel(115,i,4);

}

int main()
{
	int i,val,count,y;
	int gd=DETECT,gm;
	clrscr();
	initgraph(&gd,&gm,"C:\\TurboC3\\bgi");
	setbkcolor(15);

	//Draw chess board

	chessboard();

	val = 120;
	count=1;
	y=40;
	while(count<=8)
	{
		if(count%2!=0)
			val = 120;
		else
			val=170;
		while(val<520)
		{
			for(i=val;i<=(val+50);i++)
			{
				vertical(i,y,(y+50),4);
			}
			val += 100;
		}
		count++;
		y+=50;
	}

	getch();
	return 0;
}