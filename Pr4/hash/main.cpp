#include <iostream>
#include <vector>
#include <fstream>
#include <cryptopp/hex.h> 
#include <cryptopp/sha.h> 
#include <cryptopp/files.h> 

using namespace std;

int main ()
{
    using namespace CryptoPP;
    
    SHA1 hash;

    /*
    ifstream f("TextToHash.txt");
    f.seekg(0,ios::end);
    int fsize = f.tellg();             // для сохранения
    f.seekg(0,ios::beg);             //  содержимого файла
    char* buf = new char[fsize];
    f.read(buf,fsize);                  
    string file = string(buf);
    f.close();
    */
    string digest;

    /*
    StringSource(file, true,             
                 new HashFilter(hash,                          // при чтении 
                                new HexEncoder(             // содержимого файла
                                    new StringSink(digest))));
    */
    
    FileSource("TextToHash.txt", true,             
                 new HashFilter(hash,       
                                new HexEncoder(     
                                    new StringSink(digest))));
    // cout << file << endl; // демонстрация содержимого файла
    cout << digest << endl;

    return 0;
}
