#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

std::string decryptCaesar(const std::string& cipherText, int shift) {
    std::string plainText = "";
    for (char c : cipherText) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            plainText += (c - base - shift + 26) % 26 + base;
        } else {
            plainText += c;
        }
    }
    return plainText;
}

std::vector<int> getFrequency(const std::string& text) {
    std::vector<int> freq(26, 0);
    for (char c : text) {
        if (isalpha(c)) {
            freq[tolower(c) - 'a']++;
        }
    }
    return freq;
}

int estimateKeyLength(const std::string& cipherText) {
    int maxLength = 10;
    for (int length = 1; length <= maxLength; ++length) {
        int coincidences = 0;
        for (int i = 0; i < cipherText.size() - length; ++i) {
            if (cipherText[i] == cipherText[i + length]) {
                coincidences++;
            }
        }
        if (coincidences > 5) {
            return length;
        }
    }
    return 1;
}

std::string decryptVigenere(const std::string& cipherText, const std::string& key) {
    std::string plainText = "";
    int keyLength = key.size();
    for (int i = 0; i < cipherText.size(); ++i) {
        if (isalpha(cipherText[i])) {
            char base = isupper(cipherText[i]) ? 'A' : 'a';
            char shift = tolower(key[i % keyLength]) - 'a';
            plainText += (cipherText[i] - base - shift + 26) % 26 + base;
        } else {
            plainText += cipherText[i];
        }
    }
    return plainText;
}

int main() {
    std::string cipherText = "tyltsrekyreytfex";
    
    std::cout << "Thám mã bằng Caesar Cipher:\n";
    for (int shift = 1; shift <= 25; ++shift) {
        std::string decrypted = decryptCaesar(cipherText, shift);
        std::cout << "Shift " << shift << ": " << decrypted << std::endl;
    }
    
    int keyLength = estimateKeyLength(cipherText);
    std::cout << "\nDự đoán độ dài khóa Vigenère: " << keyLength << std::endl;
    
    std::string possibleKey(keyLength, 'a');
    for (int i = 0; i < 26; ++i) {
        for (int j = 0; j < keyLength; ++j) {
            possibleKey[j] = 'a' + i;
        }
        std::string decrypted = decryptVigenere(cipherText, possibleKey);
        std::cout << "Thử khóa \"" << possibleKey << "\": " << decrypted << std::endl;
    }
    
    return 0;
}
