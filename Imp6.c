#include<stdio.h>
#include<conio.h>
#include<graphics.h>
int bgcolor;
void bresenham_circle_draw(int xc,int yc,int r,int lcolor);
void drawxy();
void seedfill(int x1,int y1,int o,int n);

int main()
{
	printf("\nEnter the background color= ");
	scanf("%d",&bgcolor);
	drawxy();
	bresenham_circle_draw(0,0,50,2);
	seedfill(50,0,2,3);
	getch();
	closegraph();
	return 0;
}

void drawxy()
{
	int i;
	int gd=DETECT,gm;
	initgraph(&gd,&gm,"C://TurboC3//bgi");
	setbkcolor(bgcolor);
}

void seedfill(int x1,int y1,int o,int n)
{
	int c;
	c=getpixel(320+x1,240-y1);
	if(c!=o && c!=n)
	{
		putpixel(320+x1,240-y1,n);
		seedfill(x1+1,y1,o,n);
		//seedfill(x1+1,y1+1,o,n);
		seedfill(x1,y1+1,o,n);
		//seedfill(x1-1,y1+1,o,n);
		seedfill(x1-1,y1,o,n);
		//seedfill(x1-1,y1-1,o,n);
		seedfill(x1,y1+1,o,n);
		//seedfill(x1+1,y1-1,o,n);
	}
}

void bresenham_circle_draw(int xc,int yc,int r,int lcolor)
{
	int xk,yk;
	float d,pk;
	int x[1000],y[1000];
	int n1,n2,n3,i;
	xk=0;
	yk=r;
	n3=0;
	while(yk>=0)
	{
		x[n3]=xk;
		y[n3]=yk;
		d=(xk+1)*(xk+1)+(yk+1)*(yk+1)-r*r;
		if(d<0)
		{
			pk=(xk+1)*(xk+1)+(yk-.5)*(yk-.5)-r*r;
			if(pk<=0)
			{
				xk=xk+1;
			}
			else
			{
				xk=xk+1;
				yk=yk-1;
			}
		}
		else if(d>0)
		{
			pk=(xk+.5)*(xk+.5)+(yk-1)*(yk-1)-r*r;
			if(pk<=0)
			{
				xk=xk+1;
				yk=yk-1;
			}
			else
			{
				yk=yk-1;
			}
		}
		else
		{
			xk=xk+1;
			yk=yk+1;
		}
		if(yk>=0)
			n3++;
	}
	n1=2*n3;
	n2=n3-1;
	for(i=n3+1;i<=n1;i++)
	{
		x[i]=x[n2];
		y[i]=-y[n2];
		n2--;
	}
	n1=4*n3-1;
	n2=2*n3-1;
	for(i=2*n3+1;i<=n1;i++)
	{
		x[i]=-x[n2];
		y[i]=y[n2];
		n2--;
	}
	for(i=0;i<=n1;i++)
	{
		putpixel(320+xc+x[i],240-yc+y[i],lcolor);
	}
}