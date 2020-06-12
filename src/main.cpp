#include "../inc/ecc.h"
using namespace cxz;

int main(int argc,char *argv[])
{
    PublicKey ecc1_publicKey;
    EncryptMessage ecc2_encryptMessage;
    std::string ecc2_published_infor;
    std::string ecc1_received_infor;

    // initialize ECC1/ECC2
    // ************** you can change the parameter, if you want **************
    std::cout<<"ECC1:"<<std::endl;
    ECC ecc1(101,-1,0);
    std::cout<<"ECC2:"<<std::endl;
    ECC ecc2(89,-1,0);

    // print points and class
    //ecc1.print_primitive_points_class();
    //ecc2.print_primitive_points_class();

    //ecc1 publishs public_key to public
    std::cout<<"ECC1:"<<std::endl;
    ecc1_publicKey=ecc1.release_public_key();
    ecc1_publicKey.print();
    std::cout<<std::endl;

    //ECC2 encrypts the infor by publicKey, generate encryption sequence
    // ************** you can change the infor, if you want **************
    std::cout<<"ECC2:"<<std::endl;
    ecc2_published_infor="hello world";
    ecc2.encrypt_ecc(ecc2_published_infor,ecc1_publicKey,ecc2_encryptMessage);
    ecc2_encryptMessage.print();
    std::cout<<std::endl;

    // ECC1 decrypt message and print Decrypted message
    std::cout<<"ECC1:"<<std::endl;
    ecc1.decrypt_ecc(ecc2_encryptMessage,ecc1_received_infor);
    std::cout<<ecc1_received_infor<<std::endl;
    return 0;
}