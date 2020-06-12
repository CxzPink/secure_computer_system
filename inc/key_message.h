/*************************************************************************\
  All the code was completed by June 1, 2020

  The author(CHEN Xingzhou) may be contacted via:

  EMail:               3170101630@zju.edu.cn

  Phone:               18888921302
\**************************************************************************/
#ifndef _CXZ_KEY_MESSAGE_H_
#define _CXZ_KEY_MESSAGE_H_

#include <cstddef>
#include <vector>
#include <iostream>
#include <string>
#include "../inc/point.h"

namespace cxz
{
    struct PublicKey
    {
    public:
        int a,b,p; // y^2=x^3+ax+b(mod p)
        Point G,K; //G is base point,K is public key
    
        PublicKey();
        void update(const int &a_,const int &b_,const int &p_,const Point &G_,const Point &K_);
        void print();
    };

    struct PrivateKey
    {
    public:
        size_t k; //k is private key
    
        PrivateKey();
        void update(const size_t k_);
        void print();
    };

    struct EncryptMessage
    {
    public:
        std::vector<size_t> message; //Encrypted message
        Point C1,C2; //two points
    
        EncryptMessage();
        void update(const std::vector<size_t> &message_,const Point &C1_,const Point &C2_);
        void print();
    };
}

#endif