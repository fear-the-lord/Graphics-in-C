//Sutherland Cohen
#include <stdio.h>
#include <graphics.h>
#include <conio.h>
#include <math.h>

//GLOBAL DEFINITION OF WINDOW CO-ORDINATES
int xl,xr,yb,yt;


void frame(int bc){
	int gd=DETECT,gm;
	int i;
	initgraph(&gd,&gm,"C:\\TurboC3\\bgi");
	setbkcolor(bc);
	//To draw x-axis
	for(i=0;i<640;i++)
	{
		putpixel(i,240,15);
	}
	//To draw y-axis
	for(i=0;i<480;i++)
	{
		putpixel(320,i,15);
	}

	//To display +x,-x,O(0,0)
	outtextxy(10,245,"-X");
	outtextxy(620,245,"+X");
	outtextxy(325,245,"O(0,0)");
	//To display +y,-y
	outtextxy(325,10,"+Y");
	outtextxy(325,470,"-Y");
}
int abs(int n)
{
	if(n<0)
		return (-1*n);
	else
		return n;
}

int sign(int x)
{
	if(x==0)
		return 0;
	else if(x>0)
		return 1;
	else
		return -1;
}

void Bresenhams(int x1,int y1,int x2,int y2,int tc)
{

	int dx,dy,i,x,y,e,interchange,t,pk,s1,s2;

	//BRESENHAMS STARTS
	dx = abs(x2-x1);
	dy = abs(y2-y1);
	s1 = sign(x2-x1);
	s2 = sign(y2-y1);
	//if m>1
	if(dy>dx)
	{
		t = dy;
		dy = dx;
		dx = t;
		interchange = 1;
	}
	else
		interchange = 0;

	pk = 2*dy - dx;
	i=1;
	x=x1;
	y=y1;
	putpixel(320 + x,240 - y,tc);
	while(i<=dx)
	{
		if(pk>=0)
		{
			x = x + s1;
			y = y + s2;
			pk = pk + 2*(dy - dx);
		}
		else
		{
			if(interchange == 1)
				y = y + s2;
			else
				x = x + s1;

			pk = pk + 2*dy;
		}
		delay(10);
		putpixel(320 + x,240 - y,tc);
		i++;
	}
}
void view_frame(int tc){
	char a[100];
	sprintf(a,"A(%d,%d)",xl,yb);
	outtextxy(xl+320+10,240-yb-10,a);
	sprintf(a,"B(%d,%d)",xr,yb);
	outtextxy(xr+320+10,240-yb-10,a);
	sprintf(a,"C(%d,%d)",xr,yt);
	outtextxy(xr+320+10,240-yt-10,a);
	sprintf(a,"D(%d,%d)",xl,yt);
	outtextxy(xl+320+10,240-yt-10,a);
	Bresenhams(xl,yb,xr,yb,tc);
	Bresenhams(xr,yb,xr,yt,tc);
	Bresenhams(xr,yt,xl,yt,tc);
	Bresenhams(xl,yt,xl,yb,tc);

}
void bitcode(int x,int y,int b[4]){
	int i;
	for(i=0;i<4;i++){
		b[i]=0;
	}
	i=0;
	while(i<4){
		if(x<xl)
			b[i]=1;
		i++;
		if(x>xr)
			b[i]=1;
		i++;
		if(y<yb)
			b[i]=1;
		i++;
		if(y>yt)
			b[i]=1;
		i++;
	}
}
int main(){
	char a[100];
	int p1[10],p2[10],r[10];
	int i,cl,flag,found,bc,x1,x2,y1,y2,outside;
	int sum1,sum2;
	float m,px,py,qx,qy;
	int xm1,xm2,ym1,ym2,pym,pxm,qym,qxm;
	clrscr();
	printf("\nEnter the background color: ");
	scanf("%d",&bc);
	printf("\nEnter the frame color: ");
	scanf("%d",&cl);

	printf("enter xl,xr,yb,yt\n");
	scanf("%d%d%d%d",&xl,&xr,&yb,&yt);
	printf("enter the initial points:");
	scanf("%d %d",&x1,&y1);
	printf("enter the end points:");
	scanf("%d %d",&x2,&y2);

	px=x1;
	py=y1;
	qx=x2;
	qy=y2;
	frame(bc);
	view_frame(cl);
	//bitcode of 1st point
	bitcode(x1,y1,p1);
	//bitcode of 2nd point
	bitcode(x2,y2,p2);
	//check wheather bitcode clashes or not
	outside=0;
	for(i=0;i<4;i++){
		if((p1[i] & p2[i])!=0)
			outside=1;
	}
	sum1=0;
	sum2=0;
	for(i=0;i<4;i++){
		sum1=sum1+p1[i];
	}
	for(i=0;i<4;i++){
		sum2=sum2+p2[i];
	}
	if(sum1==0 && sum2==0)
		printf("\n clipping is not prequired.");
	if(outside==1)
		printf("\n clipping is not possible.");
	else
	{
		flag=0;
		found=0;
		m=(qy-py)/(qx-px);//always calculate m in float
		ym1=m*(xl-x1)+y1;
		ym2=m*(xr-x1)+y1;
		xm1=(1.0/m)*(yb-y1)+x1;
		xm2=(1.0/m)*(yt-y1)+x1;
		if(ym1>=yb && ym1<=yt){
			flag=1;
			pym=ym1;
			pxm=xl;
		}

		if(ym2>=yb && ym2<=yt){
			if(flag==0){
				flag=1;
				pym=ym2;
				pxm=xr;
			}
			else{
				found=1;
				qym=ym2;
				qxm=xr;
			}
		}
		if(found==0 && xm1>=xl && xm1<=xr){
			if(flag==0){
				flag=1;
				pxm=xm1;
				pym=yb;
			}
			else{
				found=1;
				qxm=xm1;
				qym=yb;
			}
		}
		if(found==0 && xm2>=xl && xm2<=xr){
			found=1;
			qxm=xm2;
			qym=yt;
		}
		if(flag==0){
			printf("\n all intersection are invalid Line does not lie inside the window!");
			Bresenhams(x1,y1,x2,y2,15);
		}
		printf("%d,%d\n",pxm,pym);
		printf("%d,%d",qxm,qym);
		Bresenhams(x1,y1,pxm,pym,3);
		Bresenhams(pxm,pym,qxm,qym,4);
		Bresenhams(qxm,qym,x2,y2,5);
	}
	getch();
	return 0;
}