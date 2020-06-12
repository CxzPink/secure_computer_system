/*************************************************************************\
  All the code was completed by June 1, 2020

  The author(CHEN Xingzhou) may be contacted via:

  EMail:               3170101630@zju.edu.cn

  Phone:               18888921302
\**************************************************************************/

#ifndef _CXZ_ECC_H_
#define _CXZ_ECC_H_

#include <cstddef>
#include <vector>
#include <math.h>
#include <iostream>
#include <string>
#include "../inc/key_message.h"

namespace cxz
{
    // y^2=x^3+ax+b(mod p)
    class Fp_parameter
    {  
    protected:
        size_t p; //Finite field parameter
        int a, b;
    public:
        Fp_parameter(const size_t p_input, const int a_parameter_input, const int b_parameter_input);
    };

    // ECC
    class ECC:public Fp_parameter
    {
    protected:
        PrivateKey privateKey_;
        PublicKey publicKey_;
        std::vector<Point> primitive_points;  //the points on an elliptic curve
        std::vector<size_t> primitive_class;  //order of elliptic curve points in a finite field
        size_t primitive_number;  //the number of points on an elliptic curve
    public:
        ECC(const size_t p, const int a, const int b); //use parameter to init
        ECC(const PublicKey & publicKey); //use public key to init
        PublicKey release_public_key(); //release the public key to the public
        void print_primitive_points();// print primitive_points
        void print_primitive_points_class();//print primitive_points and primitive_class
        //Encrypt the input by publicKey, generate encryption sequence
        void encrypt_ecc(const std::string &input, PublicKey & publicKey,EncryptMessage &encryptMessage);
        //Decrypt the encryptMessage, and get the decryption message
        void decrypt_ecc(const EncryptMessage &encryptMessage,std::string &output);
    private:
        void init_primitive_points(); //find every points on an elliptic curve
        void get_class_for_primitive(); //compute order of elliptic curve points in a finite field
        size_t normal(const int &s); //map integers to a finite field
        size_t my_sqrt(const int &s); //sqrt s
        size_t my_sqrt(const int &s,const size_t &n); //sqrt s by n 
        size_t inverse(const size_t &n,const size_t &b);// inverse
        bool judge_if_prime(const size_t &s); // juedge if is a prime
        Point plus(const Point &p1,const Point &p2); // plus p1 and p2
        Point k_point(const size_t &k,const Point &p); //k*p
    };
} // namespace cxz

#endif