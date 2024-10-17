#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

long long modExp(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}

int charToValue(char c) {
    if (c >= 'A' && c <= 'Z') {
        return c - 'A';
    } else if (c >= 'a' && c <= 'z') {
        return c - 'a';
    }
    return -1;
}

std::vector<long long> rsaEncrypt(const std::string &message, long long e, long long n) {
    std::vector<long long> encryptedMessage;
    for (char c : message) {
        int mValue = charToValue(c);
        if (mValue == -1) {
            std::cerr << "Ký tự không hợp lệ trong thông điệp: " << c << std::endl;
            return {};
        }
        long long cValue = modExp(mValue, e, n);
        encryptedMessage.push_back(cValue);
    }
    return encryptedMessage;
}

int main() {
    std::string message = "IloveCode";

    long long e = 5;
    long long n = 703;

    std::vector<long long> encryptedMessage = rsaEncrypt(message, e, n);
    if (encryptedMessage.empty()) {
        return 1;

    std::ofstream outFile("rsa-encrypt.dat");
    if (outFile.is_open()) {
        for (long long cValue : encryptedMessage) {
            outFile << cValue << " ";
        }
        outFile.close();
        std::cout << "Bản mã đã được ghi ra tệp rsa-encrypt.dat" << std::endl;
    } else {
        std::cerr << "Không thể mở tệp để ghi." << std::endl;
        return 1;
    }

    return 0;
}
