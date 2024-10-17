#include <iostream>
#include <string>
#include <vector>

int charToValue(char c) {
    if (c >= 'a' && c <= 'z') {
        return c - 'a';
    } else if (c == '@') {
        return 26;
    } else if (c == '.') {
        return 27;
    } else if (c == '-') {
        return 28;
    }
    return -1;
}

char valueToChar(int value) {
    if (value >= 0 && value <= 25) {
        return 'a' + value;
    } else if (value == 26) {
        return '@';
    } else if (value == 27) {
        return '.';
    } else if (value == 28) {
        return '-';
    }
    return '?';
}

std::string vigenereEncrypt(const std::string &email, const std::vector<int> &key) {
    std::string encryptedEmail;
    int keyLength = key.size();

    for (size_t i = 0; i < email.length(); ++i) {
        int pValue = charToValue(email[i]);
        if (pValue == -1) {
            std::cerr << "Ký tự không hợp lệ trong email: " << email[i] << std::endl;
            return "";
        }
        int kValue = key[i % keyLength];
        int cValue = (pValue + kValue) % 29;

        encryptedEmail += valueToChar(cValue);
    }

    return encryptedEmail;
}

int main() {
    std::string email;
    std::vector<int> key = {2, 7, 15, 27};

    std::cout << "Nhập địa chỉ email: ";
    std::cin >> email;

    std::string encryptedEmail = vigenereEncrypt(email, key);
    if (!encryptedEmail.empty()) {
        std::cout << "Email sau khi mã hóa: " << encryptedEmail << std::endl;
    }

    return 0;
}
