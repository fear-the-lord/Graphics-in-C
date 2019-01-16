//Smiley face
#include<stdio.h>
#include<conio.h>
#include<graphics.h>
int bgcolor,lcolor;
void drawxy();
int signx(int x);
void line_draw(int x1,int y1,int x2,int y2,int lcolor);
int bresenham_line_draw(int x1,int y1,int x2,int y2,int x[],int y[]);
void bresenham_circle_draw(int xc,int yc,int r,int lcolor);
void halfcircle_draw(int xc,int yc,int r,int lcolor);
void seedfill(int x1,int y1,int o,int n);

int main()
{
	int i;
	printf("\nEnter the background color= ");
	scanf("%d",&bgcolor);
	printf("\nEnter line color= ");
	scanf("%d",&lcolor);
	 drawxy();
	bresenham_circle_draw(0,0,60,lcolor);
	bresenham_circle_draw(0,0,61,lcolor);
	bresenham_circle_draw(0,0,62,lcolor);
	bresenham_circle_draw(0,0,63,lcolor);
	bresenham_circle_draw(0,0,64,lcolor);
	for(i=0;i<10;i++)
	{
		bresenham_circle_draw(-30,30,i,lcolor);
		bresenham_circle_draw(30,30,i,lcolor);
		bresenham_circle_draw(0,0,i,4);
	}
	//for(i=0;i<20;i++)
		halfcircle_draw(0,-20,20,lcolor);
		seedfill(0,-30,lcolor,5);
		//seedfill(-50,0,lcolor,5);
       //	halfcircle_draw(0,-20,15,lcolor);
       //	halfcircle_draw(0,-20,10,lcolor);
       //	halfcircle_draw(0,-20,5,lcolor);
	getch();
	closegraph();
	return 0;
}

void seedfill(int x1,int y1,int o,int n)
{
	int c;
	c=getpixel(320+x1,240-y1);
	if(c!=o && c!=n)
	{
		putpixel(320+x1,240-y1,n);
		seedfill(x1+1,y1,o,n);
		seedfill(x1,y1+1,o,n);
		seedfill(x1-1,y1,o,n);
		seedfill(x1,y1+1,o,n);
	}
}

void drawxy()
{
	int i;
	int gd=DETECT,gm;
	initgraph(&gd,&gm,"C://TurboC3//bgi");
	setbkcolor(bgcolor);
	/*for(i=0;i<640;i++)
		putpixel(i,240,lcolor);
	for(i=0;i<480;i++)
		putpixel(320,i,lcolor);*/
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
			e=e-2*dx;
		}
			if(interchange==1)
				yy=yy+s2;
			else
				xx=xx+s1;
			e=e+2*dy;
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
		delay(5);

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

void halfcircle_draw(int xc,int yc,int r,int lcolor)

{

  int xk,yk,n;

  float d,pk;

  int x[1000],y[1000],xx[700],yy[700];

  int n1,n2,n3,i;

  xk=0;

  yk=r;

  n3=0;

  //To generate points in first quadrant

  while(yk>=0)

  {

    x[n3]=xk;

    y[n3]=yk;

    d=(xk+1)*(xk+1)+(yk-1)*(yk-1)-r*r;

    if(d<0)

    {

      pk=(xk+1)*(xk+1)+(yk-.5)*(yk-.5)-r*r;

      if(pk<=0)

        xk=xk+1;

      else

      {

        xk=xk+1;

        yk=yk-1;

      }

    }

    else

    if(d>0)

    {

      pk=(xk+.5)*(xk+.5)+(yk-1)*(yk-1)-r*r;

      if(pk<=0)

      {

        xk=xk+1;

        yk=yk-1;

      }

      else

        yk=yk-1;

    }

    else

    {

      xk=xk+1;

      yk=yk-1;

    }

    if(yk>=0)

      n3=n3+1;

  }

  //To take reflection along x-axis

  n1=2*n3;

  n2=n3-1;

  for(i=n3+1;i<=n1;i++)

  {

    x[i]=x[n2];

    y[i]=-y[n2];

    n2=n2-1;

  }

  //To take reflection along y-axis

  n1=4*n3-3;

  n2=2*n3-1;

  for(i=2*n3+1;i<=n1;i++)


  {

    x[i]=-x[n2];

    y[i]=y[n2];

    n2=n2-1;

  }

  for(i=n3+1;i<=3*n3;i++)

  {

    putpixel(320+xc+x[i],240-yc-y[i],lcolor);

  }

  n=bresenham_line_draw(x[n3],y[n3],x[3*n3],y[3*n3],xx,yy);

  for(i=0;i<=n;i++)

  {

    putpixel(320+xc+xx[i],240-yc+yy[i],lcolor);

  }

}