#include <iostream>
#include <string>
#include <cctype>
#include <vector>

// Hàm giải mã bằng mã dịch vòng với khóa k
std::string decryptCaesar(const std::string &ciphertext, int k) {
    std::string plaintext = "";
    for (char c : ciphertext) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            plaintext += (c - base - k + 26) % 26 + base;
        } else {
            plaintext += c;
        }
    }
    return plaintext;
}

// Hàm thám mã với tất cả các khóa dịch vòng
void bruteForceCaesar(const std::string &ciphertext) {
    for (int k = 1; k < 26; ++k) {
        std::string decryptedText = decryptCaesar(ciphertext, k);
        std::cout << "Với khóa " << k << ": " << decryptedText << std::endl;
    }
}


// Hàm để lặp lại khóa cho đủ chiều dài bản mã
std::string repeatKey(const std::string &key, int length) {
    std::string repeatedKey;
    for (int i = 0; i < length; ++i) {
        repeatedKey += key[i % key.length()];
    }
    return repeatedKey;
}

// Hàm giải mã bằng Vigenere với khóa đã biết
std::string decryptVigenere(const std::string &ciphertext, const std::string &key) {
    std::string plaintext = "";
    std::string repeatedKey = repeatKey(key, ciphertext.length());

    for (size_t i = 0; i < ciphertext.length(); ++i) {
        if (isalpha(ciphertext[i])) {
            char base = isupper(ciphertext[i]) ? 'A' : 'a';
            plaintext += (ciphertext[i] - repeatedKey[i] + 26) % 26 + base;
        } else {
            plaintext += ciphertext[i];
        }
    }
    return plaintext;
}

// Hàm thám mã với các độ dài khóa khác nhau
void bruteForceVigenere(const std::string &ciphertext) {
    std::vector<std::string> possibleKeys = {"a", "ab", "abc", "abcd"}; // Ví dụ một vài khóa thử nghiệm
    for (const auto &key : possibleKeys) {
        std::string decryptedText = decryptVigenere(ciphertext, key);
        std::cout << "Với khóa \"" << key << "\": " << decryptedText << std::endl;
    }
}

int main() {
    // Bản mã cần giải mã
    std::string ciphertext = "tyltsrekyreytflex";
    std::cout << "Thám mã bằng mã dịch vòng (Caesar Cipher):\n";
    bruteForceCaesar(ciphertext);

	std::cout << "\n----------------------------------------------\n";

	    // Bản mã cần giải mã
    // std::string ciphertext = "tyltsrekyreytflex";
    std::cout << "Thám mã Vigenere với các khóa thử nghiệm:\n";
    bruteForceVigenere(ciphertext);

    return 0;
}
