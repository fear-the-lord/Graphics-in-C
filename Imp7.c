#include<stdio.h>

	#include<graphics.h>

	int c;

	int n;

	void draw_xy();

	float sine(float x);

	void sine_draw(float theta1,float theta2);
	void bresenham_circle_draw(int xc,int yc,int r,int lcolor);



	void main()

	{

	int xc,yc,r,i;

	float theta1,theta2;

	char a[100];

	clrscr();

	printf("\nEnter starting theta in degree(theta1)=");

	scanf("%f",&theta1);

	printf("Enter Ending  theta in degree(theta2)=");

	scanf("%f",&theta2);

	printf("\nEnter color code of line(1,2,3,4,5,15)=");

	scanf("%d",&c);

	draw_xy();

	sine_draw(theta1,theta2);


	getch();

	closegraph();

	}

	float sine(float x)

	{

	float csin,psin,eps,fact,xrad,xp;

	int i,sf,n;

	xrad=3.141593*x/180;

	csin=xrad;

	psin=1;

	eps=csin-psin;

		if(eps<0)

		eps=-eps;

	n=3;

	sf=-1;

		while(eps>1e-06)

		{

		psin=csin;

		fact=1;

		xp=1;

			for(i=1;i<=n;i++)

			{

			fact=fact*i;

			xp=xp*xrad;

			}

		csin=csin+sf*xp/fact;

		eps=csin-psin;

			if(eps<0)

			eps=-eps;

		n=n+2;

		sf=-sf;

		}

	return csin;

	}
	

	void sine_draw(float theta1,float theta2)

	{

	float x,y;

	int x1,y1,i;

		for(x=theta1;x<=theta2;x++)

		{

		for(i=theta1;i<=theta2;i++)
		{
			y=sine(i);
			y1=100*y;
			x1=i/2;
			putpixel(320+x1,240-y1,15);
		}
		y=sine(x);
		y1=100*y;
		x1=x/2;
		bresenham_circle_draw(x1,y1,10,5);
		clearviewport();
		delay(5);

		}

	}


	void draw_xy()

	{

	int gd=DETECT, gm;

	int i;

	initgraph(&gd,&gm,"c://TurboC3//bgi");

	setbkcolor(0);

	setcolor(1);

	/* To draw x-axis */

		for(i=0;i<640;i++)

		{

		putpixel(i,240,15);

		}

	/* To draw y-axis */

		for(i=0;i<480;i++)

		{

		putpixel(320,i,15);

		}

	/* To display -X, +X, +Y , -Y and O(0,0) */

	outtextxy(10,245,"-X");

	outtextxy(620,245,"+X");

	outtextxy(325,10,"+Y");

	outtextxy(325,470,"-Y");

	outtextxy(325,245,"O(0,0)");

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