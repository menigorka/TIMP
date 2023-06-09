#include <iostream>
#include <vector>
#include <string.h>
#include <fstream>
#include <cryptopp/hex.h>
#include <cryptopp/sha.h>
#include <cryptopp/aes.h>
#include <cryptopp/osrng.h>
#include <cryptopp/modes.h>
#include <cryptopp/pwdbased.h>
#include <cryptopp/files.h>
#include <getopt.h>

using namespace std;

int main (int argc, char* argv[])
{
    string rjournal = "Rez.txt";
    const char * sourse = "Text.txt";
    const char * journal = "Rez.txt";
    const char * iv_file = "iv.hex";
    string parol = "";
    string salt = "Зачем соль если есть сахар?";
    int mode = 0;
    static struct option long_options[] = {
        {"mode", 1, 0, 'm'},
        {"sourse", 1, NULL, 's'},
        {"journal", 1, NULL, 'j'},
        {"parol", 1, NULL, 'p'},
        {NULL, 0, NULL, 0}
    };
    int opt;
    while((opt = getopt_long(argc, argv, ":m:s:j:p:", long_options, NULL))!= -1) {
        if ((char)opt == 'm') {
            if (string(optarg) == "encrypt" or string(optarg) == "e") {
                mode = 2;
            } else if (string(optarg) == "decrypt" or string(optarg) == "d") {
                mode = 1;
            } else {
                cout << "Неизвестная опция\n";
                return 0;
            }
        } else if ((char)opt == 's') {
            sourse = optarg;
        } else if ((char)opt == 'j') {
            journal = optarg;
        }  else if ((char)opt == 'p') {
            parol = string(optarg);
        } else if ((char)opt == ':') {
            cout << "Введенный параметр требует аргумент. Для вызова справки воспользуйтесь параметрами \"h\" или \"help\"\n";
            return 0;
        } else {
            cout << "Неизвестный параметр. Для вызова справки воспользуйтесь параметрами \"h\" или \"help\"\n";
            return 0;
        }
    }
    if (parol == "") {
        cout << "Не введён пароль\n";
        return 0;
    }
    using namespace CryptoPP;
    
        SecByteBlock key(AES::DEFAULT_KEYLENGTH);
        PKCS12_PBKDF <SHA384> pbksha;
        pbksha.DeriveKey(key.data(), key.size(), 0, (byte*)parol.data(), parol.size(), (byte*)salt.data(), salt.size(), 1500, 0.0f);
    if (mode == 1) {
        try {
            byte iv[AES::BLOCKSIZE];
            FileSource(iv_file, true,
                       new HexDecoder(
                           new ArraySink(iv, sizeof iv)));
            CBC_Mode<AES>::Decryption decr;
            decr.SetKeyWithIV(key, sizeof key, iv);
            FileSource (sourse, true,
                            new HexDecoder(
                                  new StreamTransformationFilter(decr,
                                          new FileSink(journal))));
        } catch(const Exception& e) {
            cerr << e.what() << endl;
            exit(1);
        }
    } else if (mode == 2) {
        AutoSeededRandomPool prng;
        byte iv[AES::BLOCKSIZE];
        prng.GenerateBlock(iv, sizeof(iv));
        StringSource(iv, sizeof(iv), true,
                               new HexEncoder(
                                   new FileSink(iv_file)));
        CBC_Mode<AES>::Encryption encr;
        encr.SetKeyWithIV( key, sizeof key, iv );
        FileSource (sourse, true,
                              new StreamTransformationFilter(encr,
                                    new HexEncoder(
                                        new FileSink(journal))));
    } else {
        cout << "Не был указан режим работы\n";
    }
}