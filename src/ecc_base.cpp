#include "../inc/ecc.h"
using namespace cxz;

//map integers to a finite field
size_t cxz::ECC::normal(const int &s)
{
    int i=s/int(p);
    int temp=s-i*p+p;
    return temp%p;
}

//sqrt s
size_t cxz::ECC::my_sqrt(const int &s)
{
    size_t ss=normal(s);
    size_t temp_s,sqrt_s;
    for(size_t i=0;i<p;i++){
        temp_s=ss+i*p;
        sqrt_s=sqrt(temp_s);
        if((temp_s-pow(sqrt_s,2))==0)
            return normal(sqrt_s);
    }
    return size_t(-1);
}

//sqrt s by n 
size_t cxz::ECC::my_sqrt(const int &s,const size_t &n)
{
    size_t temp_s,sqrt_s;
    size_t ss=normal(s);
    temp_s=ss+n*p;
    sqrt_s=sqrt(temp_s);
    if((temp_s-pow(sqrt_s,2))==0)
        return normal(sqrt_s);
    return size_t(-1);
}

// plus p1 and p2
Point cxz::ECC::plus(const Point &p1,const Point &p2)
{
    int t;
	int tx,ty,x3,y3;
	int flag=0;
	//point1 == point2
	if(p1==p2){
		if(p1.y==0)
			flag=1;
        else
			t=int((3*p1.x*p1.x+a)*inverse(p,2*p1.y)) % (int(p));
	}
    //point1 != point2
    else{
		ty=normal(p2.y-p1.y);
		tx=normal(p2.x-p1.x);
		if(tx==0 && ty !=0)
			flag=1;
		else
			t=int(ty*inverse(p,tx)) % (int(p));
	}
    //create return point
	if(flag==1){
        Point temp(-1,-1);
        return temp;
    }
    else{
		x3=int(t*t-p1.x-p2.x) % (int(p));
		y3=int(t*(p1.x-x3)-p1.y) % (int(p));
        Point temp(normal(x3),normal(y3));
        return temp;
	}	
}

//k*p
Point cxz::ECC::k_point(const size_t &k,const Point &p)
{
    if(k==1)
		return p;
	else if(k==2)
		return plus(p,p);
    else
		return plus(p,k_point(k-1,p));
}

// inverse
size_t cxz::ECC::inverse(const size_t &n,const size_t &b)
{
    int q,r,r1=n,r2=b,t,t1=0,t2=1,i=1; 
	while(r2>0)
	{ 
		q=r1/r2; 
		r=r1%r2; 
		r1=r2; 
		r2=r; 
		t=t1-q*t2; 
		t1=t2; 
		t2=t; 
	} 
	if(t1>=0) 
		return t1%n; 
	else{  
		while((t1+i*n)<0) 
			i++; 
		return t1+i*n; 
	} 
}

// juedge if is a prime
bool cxz::ECC::judge_if_prime(const size_t &s)
{
    size_t k = sqrt(s);
    for (size_t i = 2; i <= k;i++){
    	if (s%i == 0)
            return 0;
	}
    return 1;
}