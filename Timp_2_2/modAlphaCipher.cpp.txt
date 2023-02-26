#include <iostream>
#include <algorithm>
#include <string>
modAlphaCipher::modAlphaCipher(const std::string& skey)
{
    try {
        int r =std::stoi(skey) ;
        if (r< 0) 
            throw std::string("Negative value");
        key = r;
    } catch (std::invalid_argument e) {
        std::cerr << "Error: Key must be a number\n";
        exit (EXIT_FAILURE);
    } catch (std::string & e) {
        std::cerr << "Error: " << e << std::endl;
        exit (EXIT_FAILURE);
    }
}
std::string modAlphaCipher::encrypt(const std::string& text)
{
    std::string t = "";
    int poz = key - 1;
    while(poz >= 0) {
        for(uint i = poz; i < text.size(); i += key) {
            t+=text[i];
        }
    poz -= 1;
    }
 return t;
}
std::string modAlphaCipher::decrypt(const std::string& dctext)
{
    std::string dct = dctext;
    std::reverse(dct.begin(), dct.end());
    int pozition = 0;
    int strk = dct.size()/key;
    std::string last = "";
    int ost = dct.size()%key;
    for (int i = 0; i < ost ; i++) {
        last += dct[pozition];
        dct.erase(pozition,1);
        pozition += strk;
    }
    pozition = strk - 1;
    std::string rezult = "";
    while (pozition >= 0) {
        for (uint i = pozition; i < dct.size(); i = i + strk) {
            rezult += dct[i];
        }
        pozition -= 1;
    }
 return (rezult+last);
}