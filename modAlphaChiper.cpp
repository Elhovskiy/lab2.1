#include <stdexcept> // Для обработки исключений
#include <string>
#include <iostream>
#include <cctype>
#include "modAlphaChiper.h"

// конструктор
modAlphaCipher::modAlphaCipher(const std::wstring& skey) {
    if (skey.empty()) {
        throw std::invalid_argument("Ключ не может быть пустым");
    }
    for (unsigned i = 0; i < numAlpha.size(); i++) {
        alphaNum[numAlpha[i]] = i;
    }
    key = convert(skey);
    if (key.empty()) {
        throw std::invalid_argument("Ключ должен содержать только буквы алфавита");
    }
}

// Метод encrypt()
std::wstring modAlphaCipher::encrypt(const std::wstring& open_text) {
    if (open_text.empty()) {
        throw std::invalid_argument("Текст для шифрования не может быть пустым");
    }
    std::vector<int> work = convert(open_text);
    if (work.empty()) {
        throw std::invalid_argument("Текст для шифрования должен содержать только буквы алфавита");
    }
    for (unsigned i = 0; i < work.size(); i++) {
        work[i] = (work[i] + key[i % key.size()]) % alphaNum.size();
    }
    return convert(work);
}

// Метод decrypt()
std::wstring modAlphaCipher::decrypt(const std::wstring& cipher_text) {
    if (cipher_text.empty()) {
        throw std::invalid_argument("Текст для дешифрования не может быть пустым");
    }
    std::vector<int> work = convert(cipher_text);
    if (work.empty()) {
        throw std::invalid_argument("Текст для дешифрования должен содержать только буквы алфавита");
    }
    for (unsigned i = 0; i < work.size(); i++) {
        work[i] = (work[i] + alphaNum.size() - key[i % key.size()]) % alphaNum.size();
    }
    return convert(work);
}

//
inline std::vector<int> modAlphaCipher::convert(const std::wstring& s) {
    std::vector<int> result;
    for (auto c : s) {
        if (alphaNum.find(c) == alphaNum.end()) {
            throw std::invalid_argument("Текст содержит недопустимые символы");
        }
        result.push_back(alphaNum[c]);
    }
    return result;
}

inline std::wstring modAlphaCipher::convert(const std::vector<int>& v) {
    std::wstring result;
    for (auto i : v) {
        result.push_back(numAlpha[i]);
    }
    return result;
}



