#include<stdio.h>
#include<conio.h>
#include<graphics.h>
int lcolor,bgcolor;

void draw_xy();
void bresenham_circle_draw(int xc,int yc,int r);

int main()
{
	int xc,yc,r,i;
	printf("Enter xc=");
	scanf("%d",&xc);
	printf("Enter yc=");
	scanf("%d",&yc);
	printf("Enter radius=");
	scanf("%d",&r);
	printf("Enter background color=");
	scanf("%d",&bgcolor);
	printf("Enter line color=");
	scanf("%d",&lcolor);
	draw_xy();
	/*for(i=0;i<=640;i++)
	{
		if(i==640)
		{
			for(i=640;i>=0;i--)
			{
				clearviewport();
				bresenham_circle_draw(xc+i,yc,(r+i*0.1));
				delay(10);
			}
		}
		clearviewport();
		bresenham_circle_draw(xc+i,yc,(r+i*0.1));
		delay(10);
	}*/
	for(i=0;i<=480;i++)
	{
		if(i==480)
		{
			for(i=480;i>=0;i--)
			{
				clearviewport();
				bresenham_circle_draw(xc,yc+i,(r+i*0.1));
				delay(10);
			}
		}
		clearviewport();
		bresenham_circle_draw(xc,yc+i,(r+i*0.1));
		delay(10);
	}
	getch();
	closegraph();
	return 0;
}

void draw_xy()
{
	int gd=DETECT,gm;
	initgraph(&gd,&gm,"C://TurboC3//BGI");
	setbkcolor(bgcolor);
}

void bresenham_circle_draw(int xc,int yc,int r)
{
	int xk,yk,i;
	float d,pk;
	int n1,n2,n3;
	int x[1000],y[1000];
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
