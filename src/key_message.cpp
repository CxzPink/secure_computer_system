#include "../inc/key_message.h"
using namespace cxz;

cxz::PublicKey::PublicKey()
{
    a=b=p=0;
    G.x=G.y=0;
    K.x=K.y=0;
}

void cxz::PublicKey::update(const int &a_,const int &b_,const int &p_,const Point &G_,const Point &K_)
{
    a=a_;
    b=b_;
    p=p_;
    G=G_;
    K=K_;
}

void cxz::PublicKey::print()
{
    std::cout<<"----------public key----------"<<std::endl;
    std::cout<<"elliptic curve parameter a:"<<a<<std::endl;
    std::cout<<"elliptic curve parameter b:"<<b<<std::endl;
    std::cout<<"finite field parameter p:"<<p<<std::endl;
    std::cout<<"base point G:"<<"("<<G.x<<","<<G.y<<")"<<std::endl;
    std::cout<<"public key K:"<<"("<<K.x<<","<<K.y<<")"<<std::endl;
    std::cout<<"------------------------------"<<std::endl;
}

cxz::PrivateKey::PrivateKey()
{
    k=0;
}

void cxz::PrivateKey::update(const size_t k_)
{
    k=k_;
}

void cxz::PrivateKey::print()
{
    std::cout<<"----------private key----------"<<std::endl;
    std::cout<<"private key k:"<<k<<std::endl;
    std::cout<<"------------------------------"<<std::endl;
}

cxz::EncryptMessage::EncryptMessage()
{
    message.clear();
    C1.x=C1.y=0;
    C2.x=C2.y=0;
}

void cxz::EncryptMessage::update(const std::vector<size_t> &message_,const Point &C1_,const Point &C2_)
{
    message=message_;
    C1=C1_;
    C2=C2_;
}

void cxz::EncryptMessage::print()
{
    std::cout<<"----------encrpt message----------"<<std::endl;
    std::cout<<"message:";
    for(auto i:message)
        std::cout<<i<<" ";
    std::cout<<std::endl;
    std::cout<<"parameter C1:"<<"("<<C1.x<<","<<C1.y<<")"<<std::endl;
    std::cout<<"parameter C2:"<<"("<<C2.x<<","<<C2.y<<")"<<std::endl;
    std::cout<<"-----------------------------------"<<std::endl;
}