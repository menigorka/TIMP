#include <iostream>
#include <getopt.h>
using namespace std;
int main(int argc, char *argv[])
{
    try {
        static struct option long_options[] = {
            {"operation", 1, NULL, 'o'},
            {NULL, 0, NULL, 0}
        };
        int opt;
        opt = getopt_long(argc, argv, ":ho:", long_options, NULL);
        if (opt == -1 or (char)opt == 'h') {
            cout << "Малоточный и слабофункциональный калькулятор способен только на две операции:\n";
            cout << "1. Умножение\nВызывается параметрами: -o mult или --operation mult\n";
            cout << "Умножает последующие числа (от 3 до 5 чисел)\n";
            cout << "2. Деление\nВызывается параметрами: -o del или --operation del\n";
            cout << "Делит первое число на последующие (от 3 до 5 чисел с учётом первого)\n";
            cout << "ВНИМАНИЕ: в дробных числах должна использоваться точка\n";
        } else if ((char)opt == 'o') {
            if (argc > 8 or argc < 6) {
                cout << "Возможно использование отлько от 3 до 5 чисел\n";
            } else {
                if (string(optarg) == "mult") {
                    float rez = 1;
                    for (int i = 3; i < argc; i++) {
                        rez *= stof(argv[i]);
                    }
                    cout << rez << "\n";
                } else if (string(optarg) == "del") {
                    float rez = stof(argv[3]);
                    for (int i = 4; i < argc; i++) {
                        rez /= stof(argv[i]);
                    }
                    cout << rez << "\n";
                } else cout << "Данному калькулятору неизвестна эта операция.\nДля вызова справки используйте -h"<<"\n";
            }
        }
    } catch (...) {
        cerr << "Ошибка: буквы это не цифры" << endl;
    }
    return 0;
}
