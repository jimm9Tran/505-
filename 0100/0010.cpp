#include <iostream>
#include <string>
#include <fstream>
#include <cryptopp/sha.h>
#include <cryptopp/aes.h>
#include <cryptopp/modes.h>
#include <cryptopp/filters.h>
#include <cryptopp/hex.h>
#include <cryptopp/files.h>
#include <cryptopp/osrng.h> // Thư viện cho AutoSeededRandomPool

using namespace CryptoPP;
using namespace std;

// Hàm tạo khóa 128-bit từ mật khẩu
void GenerateKeyFromPassword(const std::string& password, CryptoPP::byte key[AES::DEFAULT_KEYLENGTH]) {
    SHA256 hash;
    hash.CalculateDigest(key, (const CryptoPP::byte*)password.data(), password.size());
}

// Hàm mã hóa AES với chế độ CBC
std::string AESEncrypt(const std::string& plaintext, const CryptoPP::byte key[AES::DEFAULT_KEYLENGTH], const CryptoPP::byte iv[AES::BLOCKSIZE]) {
    std::string ciphertext;
    
    // AES CBC mã hóa
    try {
        CBC_Mode<AES>::Encryption encryption;
        encryption.SetKeyWithIV(key, AES::DEFAULT_KEYLENGTH, iv);
        
        // Mã hóa và lưu kết quả vào ciphertext
        StringSource(plaintext, true,
            new StreamTransformationFilter(encryption,
                new StringSink(ciphertext)
            )
        );
    } catch (const Exception& e) {
        cerr << e.what() << endl;
        exit(1);
    }

    return ciphertext;
}

// Hàm ghi bản mã ra file
void WriteToFile(const std::string& filename, const std::string& ciphertext) {
    ofstream file(filename, ios::binary);
    file.write(ciphertext.c_str(), ciphertext.size());
    file.close();
}

int main() {
    std::string password;
    std::string plaintext = "IlovePhenikaa";
    CryptoPP::byte key[AES::DEFAULT_KEYLENGTH];   // Khóa 128-bit
    CryptoPP::byte iv[AES::BLOCKSIZE];            // IV 128-bit (16 bytes)

    // Nhập mật khẩu từ bàn phím
    cout << "Enter password: ";
    cin >> password;

    // Tạo khóa từ mật khẩu
    GenerateKeyFromPassword(password, key);

    // Khởi tạo vector IV ngẫu nhiên
    AutoSeededRandomPool rnd;
    rnd.GenerateBlock(iv, AES::BLOCKSIZE);

    // Mã hóa thông điệp
    std::string ciphertext = AESEncrypt(plaintext, key, iv);

    // Ghi bản mã ra file
    WriteToFile("aes-encrypt.dat", ciphertext);

    // Thông báo hoàn thành
    cout << "Ciphertext has been written to aes-encrypt.dat" << endl;

    return 0;
}
