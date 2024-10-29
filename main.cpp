#include <iostream>
#include <cctype>
#include "modAlphaChiper.h"
#include <locale>
#include "modAlphaChiper.cpp"
using namespace std;

bool isValid(const std::wstring& s) {
    for (auto c : s) {
        if (!iswupper(c) && c != L'Ё') {
            return false;
        }
    }
    return true;
}
int main(int argc, char **argv)
{
	try {
    	locale loc("ru_RU.UTF-8");
    	locale::global(loc);
    	wstring key;
    	wstring text;
    	int op;
    	wcout<<L"Введите ключ:  ";
    	wcin>>key;
    	modAlphaCipher cipher(key);
    	do {
        	wcout<<L"Выберите опреацию (0-exit, 1-encrypt, 2-decrypt): ";
        	wcin>>op;
        	if (op > 2) {
            	wcout<<L"Не корректная операция\n";
        	} else if (op >0) {
            	wcout<<L"Введите текст ";
            	wcin>>text;
            	if (isValid(text)) {
                	if (op==1) {
                    	wcout<<L"Зашифрованный текст: "<<cipher.encrypt(text)<<endl;
                	} else {
                    	wcout<<L"Расшифрованный текст: "<<cipher.decrypt(text)<<endl;
                	}
            	} else {
                	wcout<<L"Некорректный текст для шифрования/расшифрования\n";
            	}
        	}
    	} while (op!=0);
     } catch (const std::exception& e) {
        std::wcerr << L"Ошибка: " << e.what() << std::endl;
    }
    return 0;
}
