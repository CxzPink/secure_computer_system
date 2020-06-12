#include "../inc/ecc.h"
using namespace cxz;

// y^2=x^3+ax+b(mod p)
cxz::Fp_parameter::Fp_parameter(const size_t p_input, const int a_parameter_input, const int b_parameter_input)
{
    p = p_input;
    a = a_parameter_input;
    b = b_parameter_input;
    if((4*pow(a,3)+27*pow(b,2)) == 0){
        std::cout<<"---initialize parameter error!---"<<std::endl;
        exit(1);
    }
};

//use parameter to init
cxz::ECC::ECC(const size_t p, const int a, const int b):Fp_parameter(p,a,b)
{
    std::cout<<"-----------successfully initialize Elliptic Curve------------"<<std::endl;
    init_primitive_points();
    get_class_for_primitive();
	
    //Random generator
	size_t num=rand()%primitive_number;
	size_t gene_class=primitive_class[num];
	while(!judge_if_prime(gene_class))
	{
	 	num=rand()%(primitive_number-3)+3;
	 	gene_class=primitive_class[num];
	}

    //generate public key and private key
	Point G=primitive_points[num];
	size_t k=rand()%(gene_class-1)+1;
	Point K=k_point(k,G);
    publicKey_.update(a,b,p,G,K);
    privateKey_.update(k);

    std::cout<<"------successfully generate public key and private key-------"<<std::endl;
    std::cout<<std::endl;
}

//use public key to init
cxz::ECC::ECC(const PublicKey & publicKey):Fp_parameter(publicKey.p,publicKey.a,publicKey.b)
{
    init_primitive_points();
    get_class_for_primitive();
}

//release the public key to the public
PublicKey cxz::ECC::release_public_key()
{
    std::cout<<"----------successfully publish the public key----------"<<std::endl;
    return publicKey_;
}

//find every points on an elliptic curve
void cxz::ECC::init_primitive_points()
{
	int s,y;
    bool flag;
    std::vector<Point> temp_points;
	for(int i=0;i<p;i++){
		s=normal(pow(i,3)+ a * i + b);
        for(size_t n=0;n<p;n++){
            if(my_sqrt(s,n)!=size_t(-1)){
                y=my_sqrt(s,n);
                Point temp(i,y);
                temp_points.push_back(temp);
            }
        }
	}
    for(auto i:temp_points){
        flag=1;
        for(auto j:primitive_points){
            if(i==j){
                flag=0;
                break;
            }
        }
        if(flag==1){
            primitive_points.push_back(i);
        }
    }
    primitive_number=primitive_points.size();
}

//compute class of elliptic curve points in a finite field
void cxz::ECC::get_class_for_primitive()
{
	int count;
    Point break_point(-1,-1);
	for(auto i:primitive_points)
	{
		count=1;
        Point p1=i,p2=i;		
		while(count<primitive_number)
		{
            p2=plus(p1,p2);	
			if(p2==break_point)
				break;
			count++;
			if(p2.x==p1.x)
				break;					
		}
		count++;
        primitive_class.push_back(count);	
	}
}

//Encrypt the input by publicKey, generate encryption sequence
void cxz::ECC::encrypt_ecc(const std::string &input, PublicKey & publicKey,EncryptMessage &encryptMessage)
{
    std::vector<size_t> encrpt;
    srand(time(NULL)); 
    
    // build a new ecc by publicKey 
    ECC temp_ecc(publicKey);

	//Convert using ASCII
	std::vector<size_t> step1;
    for(size_t i=0;i<input.length();i++)
        step1.push_back(input[i]);

    //find index of G
    size_t gene_class=-1;
    for(size_t i=0;i<temp_ecc.primitive_number;i++){
        if(temp_ecc.primitive_points[i]==publicKey.G)
            gene_class=temp_ecc.primitive_class[i];
    }

	//encryption
    size_t r=rand()%(gene_class-1)+1;
	Point C2=temp_ecc.k_point(r,publicKey.G);
	Point M=temp_ecc.primitive_points[rand()%temp_ecc.primitive_number];
	Point C1=temp_ecc.plus(M,temp_ecc.k_point(r,publicKey.K));
	for(size_t i=0;i<input.length();i++)
		encrpt.push_back(step1[i]*M.x+M.y);
    
    //publish
    encryptMessage.update(encrpt,C1,C2);
    std::cout<<"-----------successfully encrypt message------------"<<std::endl;
}

//Decrypt the encryptMessage, and get the decryption message
void cxz::ECC::decrypt_ecc(const EncryptMessage &encryptMessage,std::string &output)
{
	Point temp,temp1;
	temp=k_point(privateKey_.k,encryptMessage.C2);
    output.clear();
	temp.y=-temp.y;
	temp1=plus(encryptMessage.C1,temp);
    for(size_t i=0;i<encryptMessage.message.size();i++){
        output.push_back(char((encryptMessage.message[i]-temp1.y)/temp1.x));
    }
    std::cout<<"-----------successfully decrypt message------------"<<std::endl;
}

// print primitive_points
void cxz::ECC::print_primitive_points()
{
    size_t count=0;
    std::cout<<"---------------print points on the elliptic curve---------------"<<std::endl;
    for(auto i:primitive_points){
        std::cout<<"("<<i.x<<","<<i.y<<")"<<"  ";
        count++;
        if(count%5==0)
            std::cout<<std::endl;
    }
    if(count%5!=0)
        std::cout<<std::endl;
    std::cout<<"-------------------------finish print-------------------------"<<std::endl;
}

// print primitive_points and primitive_class
void cxz::ECC::print_primitive_points_class()
{
    size_t count=0;
    std::cout<<"---------------print points and class on the elliptic curve---------------"<<std::endl;
    for(size_t i=0;i<primitive_number;i++){
        std::cout<<"("<<primitive_points[i].x<<","<<primitive_points[i].y<<")->"<<primitive_class[i]<<"  ";
        count++;
        if(count%5==0)
            std::cout<<std::endl;
    }
    if(count%5!=0)
        std::cout<<std::endl;
    std::cout<<"------------------------------finish print---------------------------"<<std::endl;
}