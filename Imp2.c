#include<stdio.h>
#include<conio.h>
#include<graphics.h>
int bgcolor;
void drawxy();
int signx(int x);
int bresenham_line_draw(int x1,int y1,int x2,int y2,int x[],int y[]);
void line_draw(int x1,int y1,int x2,int y2,int lcolor);
void bresenham_circle_draw(int xc,int yc,int r,int lcolor);

int main()
{
	int i,y,x;
	int a,b;
	float PI=3.14;
	printf("\nEnter the background color= ");
	scanf("%d",&bgcolor);
	drawxy();
	for(i=50;i>=10;i--)
	line_draw(-80,i,80,i,4);
	for(i=10;i>=-30;i--)
	line_draw(-80,i,80,i,15);
	for(i=-30;i>=-70;i--)
	line_draw(-80,i,80,i,2);
	bresenham_circle_draw(0,-9,22,1);
	a=0;
	b=-9;
	for(i=0;i<=360;i+=15)
	{
		x=22*cos(i*PI/180);
		y=22*sin(i*PI/180);
		line_draw(0,-9,x,-9-y,2);
	}
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

int bresenham_line_draw(int x1,int y1,int x2,int y2,int x[],int y[])
{
	int xx,yy,dx,dy,e,interchange,s1,s2,i,delx,dely,temp;;
	xx=x1;
	yy=y1;
	dx=x2-x1;
	dy=y2-y1;
	if(dx<0)
		delx=-dx;
	else
		delx=dx;
	if(dy<0)
		dely=-dy;
	else
		dely=dy;
	s1=signx(dx);
	s2=signx(dy);
	if(dely>delx)
	{
		temp=dely;
		dely=delx;
		delx=temp;
		interchange=1;
	}
	else
		interchange=0;
	e=2*dely-delx;
	for(i=0;i<delx;i++)
	{
		x[i]=xx;
		y[i]=yy;
		while(e>=0)
		{
			if(interchange==1)
				xx=xx+s1;
			else
				yy=yy+s2;
			e=e-2*delx;
		}
			if(interchange==1)
				yy=yy+s2;
			else
				xx=xx+s1;
			e=e+2*dely;
	}
	return delx;
}

void line_draw(int x1,int y1,int x2,int y2,int lcolor)
{
	int n,x[700],y[700],i;
	n=bresenham_line_draw(x1,y1,x2,y2,x,y);
	for(i=0;i<n;i++)
	{
		putpixel(320+x[i],240-y[i],lcolor);
	       //	delay(5);

	}
}

int signx(int x)
{
	if (x<0)
		return -1;
	if(x==0)
		return 0;
	else
		return 1;
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
		d=(xk+1)*(xk+1)+(yk-1)*(yk-1)-r*r;
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