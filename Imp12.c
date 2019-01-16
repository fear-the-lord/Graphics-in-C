#include<stdio.h>

#include<graphics.h>

#include<conio.h>

#include<math.h>

    int c_bgcolor,c_line;

    int xo1,yo1,xo2,yo2,xo3,yo3;

    float c1; /* y=mx + c1 , c1=translation along  y-axis*/

    float slope,th1;

    void draw_xy();

    int signx(int x);

    void line_draw(int x1,int y1,int x2,int y2,int c);

    int bresenham(int x1,int y1,int x2,int y2,int x[],int y[]);

    void triangle_draw(int x1,int y1,int x2,int y2,int x3,int y3);

    void general_reflection(int x1,int y1,int x2,int y2,int x3,int y3);

    void translation(int x1,int y1,int x2,int y2,int x3,int y3,int xa,int yb);

    void rotation(int x1,int y1,int x2,int y2,int x3,int y3);

    void reflection_x(int x1,int y1,int x2,int y2,int x3,int y3);

int main()

{

    int x1,y1,x2,y2,x3,y3,i,j;

    clrscr();

    printf("\nEnter x - coordinate of 1st point(x1) =  ");

    scanf("%d",&x1);

    printf("\nEnter y - coordinate of 1st point(y1) =  ");

    scanf("%d",&y1);

    printf("\nEnter x - coordinate of 2nd point(x2) =  ");

    scanf("%d",&x2);

    printf("\nEnter y - coordinate of 2nd point(y2) =  ");

    scanf("%d",&y2);

    printf("\nEnter x - coordinate of 3rd point(x3) =  ");

    scanf("%d",&x3);

    printf("\nEnter y - coordinate of 3rd point(y3) =  ");

    scanf("%d",&y3);

    printf("Enter Background color(2-14) = ");

    scanf("%d",&c_bgcolor);

    printf("Enter Line color(1 or 15) = ");

    scanf("%d",&c_line);

    printf("Enter value of slope of general line(m)=");

    scanf("%f",&slope);

    printf("Enter translation along y-axis(c1)=");

    scanf("%f",&c1);

    draw_xy();

    triangle_draw(x1,y1,x2,y2,x3,y3);

    /* To draw general line */

    for(i=-320;i<=320;i=i+1)

    {

	j=slope*i+c1;

	putpixel(320+i,240-j,c_line);

    }

    general_reflection(x1,y1,x2,y2,x3,y3);

    triangle_draw(xo1,yo1,xo2,yo2,xo3,yo3);/* To draw modified triangle */

    getch();

    closegraph();

    return 0;

}

/* void general_reflection(int x1,int y1,int x2,int y2,int x3,int y3)

	Function to take reflection of a triangle along a general line. */



	void general_reflection(int x1,int y1,int x2,int y2,int x3,int y3)

	{

	int xa,yb;

	/* To take inverse translation */

	xa=0;

	yb=-c1;

	translation(x1,y1,x2,y2,x3,y3,xa,yb);



	/* To take inverse rotation on transformed points */

	th1=-atan(slope); /* th1=clock-wise rotation */

	rotation(xo1,yo1,xo2,yo2,xo3,yo3); /* Apply inverse rotation */



	/* To take reflection along x-axis */

	reflection_x(xo1,yo1,xo2,yo2,xo3,yo3);



	/* To take rotation in anti-clock wise direction */

	th1=atan(slope);

	rotation(xo1,yo1,xo2,yo2,xo3,yo3); /* Apply inverse rotation */



	/* To take translation */

	xa=0;

	yb=c1;

	translation(xo1,yo1,xo2,yo2,xo3,yo3,xa,yb);



	/* All transformations are over */

	}



	/* void translation(int x1,int y1,int x2,int y2,int x3,int y3,int xa,int yb)

	Function to take translation along x and y-axes */

  void translation(int x1,int y1,int x2,int y2,int x3,int y3,int xa,int yb)

	{

	xo1=x1+xa;

	yo1=y1+yb;

	xo2=x2+xa;

	yo2=y2+yb;

	xo3=x3+xa;

	yo3=y3+yb;

	}

  /*  : Function void reflection_x(int x1,int y1,int x2,int y2,int x3,int y3)

  to take reflection along x-axis */



     void reflection_x(int x1,int y1,int x2,int y2,int x3,int y3)

     {

     xo1=x1;

     yo1=-y1;

     xo2=x2;

     yo2=-y2;

     xo3=x3;

     yo3=-y3;

     }

  /* void rotation(int x1,int y1,int x2,int y2,int x3,int y3) : Function

  to take rotation around origin. */

	void rotation(int x1,int y1,int x2,int y2,int x3,int y3)

	{

	float rot[3][3],obj[3][3],obj1[3][3];

	int i,j,k;

	float s;

	rot[0][0]=cos(th1);

	rot[0][1]=-sin(th1);

	rot[0][2]=0;

	rot[1][0]=sin(th1);

	rot[1][1]=cos(th1);

	rot[1][2]=0;

	rot[2][0]=0;

	rot[2][1]=0;

	rot[2][2]=1;



	obj[0][0]=x1;

	obj[0][1]=x2;

	obj[0][2]=x3;

	obj[1][0]=y1;

	obj[1][1]=y2;

	obj[1][2]=y3;

	obj[2][0]=1;

	obj[2][1]=1;

	obj[2][2]=1;

	/* To calculate transformed points we apply matrix product */

		for(i=0;i<3;i++)

			for(j=0;j<3;j++)

			{

			s=0;

				for(k=0;k<3;k++)

				s=s+rot[i][k]*obj[k][j];

			obj1[i][j]=s;

			}

	xo1=obj1[0][0];

	yo1=obj1[1][0];

	xo2=obj1[0][1];

	yo2=obj1[1][1];

	xo3=obj1[0][2];

	yo3=obj1[1][2];

	}

/* Function to draw x and y axes on screen */

void draw_xy()

{

    int i;

    int gd=DETECT,gm;

    initgraph(&gd,&gm,"c://TurboC3//bgi");

    setbkcolor(c_bgcolor);

    /* To draw x-axis and y-axis */

    for(i=0;i<640;i++)

    {

        putpixel(i,240,c_line);

        delay(0);

    }

    for(i=0;i<480;i++)

    {

        putpixel(320,i,c_line);

        delay(0);

    }

/* To display +x, -x, +y, -y, O(0,0) */

    outtextxy(10,245,"-X");

    outtextxy(620,245,"+X");

    outtextxy(325,10,"+Y");

    outtextxy(325,470,"-Y");

    outtextxy(325,245,"O(0,0)");

}

void line_draw(int x1,int y1,int x2,int y2,int c)

{

    int x[700],y[700],i,n;

    n=bresenham(x1,y1,x2,y2,x,y);  /* Calling bresenham function to generate 'n' pixel co-ordinates */

    /* To plot all points */

    for(i=0;i<n;i++)

    {

        putpixel(320+x[i],240-y[i],c);

        delay(0);

    }

}

/* Function to generate pixel co-ordinates using Bresenham algorithm */

int bresenham(int x1,int y1,int x2,int y2,int x[],int y[])

{

  int xx,yy,delx,dely,e,s1,s2,interchange,temp;

  int i,dx,dy;

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

  for(i=0;i<=delx;i++)

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

int signx(int x)

{

  if(x<0)

    return -1;

  else if(x==0)

    return 0;

  else

    return 1;

}

void triangle_draw(int x1,int y1,int x2,int y2,int x3,int y3)

{

   char a[100];

   line_draw(x1,y1,x2,y2,c_line);

   line_draw(x2,y2,x3,y3,c_line);

   line_draw(x3,y3,x1,y1,c_line);

   setcolor(2);

   sprintf(a,"A(%d, %d)",x1,y1);

   outtextxy(320+x1,240-y1,a);

   setcolor(1);

   sprintf(a,"B(%d, %d)",x2,y2);

   outtextxy(320+x2,240-y2,a);

   setcolor(3);

   sprintf(a,"C(%d, %d)",x3,y3);

   outtextxy(320+x3,240-y3,a);

}
