#include <iostream>
#include <string>

// Hàm chuyển ký tự thành giá trị số trên Z29
int charToValue(char c) {
    if (c >= 'a' && c <= 'z') {
        return c - 'a'; // Chữ cái thường từ 0 đến 25
    } else if (c == '@') {
        return 26;
    } else if (c == '.') {
        return 27;
    } else if (c == '-') {
        return 28;
    }
    return -1; // Ký tự không hợp lệ
}

// Hàm chuyển giá trị số thành ký tự
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
    return '?'; // Giá trị không hợp lệ
}

// Hàm mã hóa Affine
std::string affineEncrypt(const std::string &email, int a, int b) {
    std::string encryptedEmail;
    for (char c : email) {
        int pValue = charToValue(c);
        if (pValue == -1) {
            std::cerr << "Ký tự không hợp lệ trong email: " << c << std::endl;
            return "";
        }
        // Mã hóa theo công thức Affine: C = (a * P + b) mod 29
        int cValue = (a * pValue + b) % 29;
        encryptedEmail += valueToChar(cValue);
    }
    return encryptedEmail;
}

int main() {
    std::string email;
    int a = 7, b = 13;

    std::cout << "Nhập địa chỉ email: ";
    std::cin >> email;

    std::string encryptedEmail = affineEncrypt(email, a, b);
    if (!encryptedEmail.empty()) {
		std::cout << "Email sau khi mã hóa: " << encryptedEmail << std::endl;
    }


    return 0;
}
