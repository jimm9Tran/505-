#include <iostream>
#include <fstream>
#include <openssl/md5.h>
#include <openssl/des.h>
#include <cstring>

// Hàm tính giá trị băm MD5 của tệp
std::string calculateMD5(const std::string &filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Không thể mở tệp: " << filename << std::endl;
        return "";
    }

    MD5_CTX md5Context;
    MD5_Init(&md5Context);
    char buffer[1024];
    while (file.read(buffer, sizeof(buffer))) {
        MD5_Update(&md5Context, buffer, file.gcount());
    }
    MD5_Update(&md5Context, buffer, file.gcount());

    unsigned char md5Digest[MD5_DIGEST_LENGTH];
    MD5_Final(md5Digest, &md5Context);

    char md5String[33];
    for (int i = 0; i < MD5_DIGEST_LENGTH; ++i) {
        sprintf(&md5String[i * 2], "%02x", (unsigned int)md5Digest[i]);
    }
    return std::string(md5String);
}

// Hàm thêm giá trị băm vào cuối tệp
bool appendMD5ToFile(const std::string &filename, const std::string &md5) {
    std::ofstream file(filename, std::ios::app | std::ios::binary);
    if (!file) {
        std::cerr << "Không thể mở tệp: " << filename << std::endl;
        return false;
    }
    file << md5;
    file.close();
    return true;
}

// Hàm mã hóa DES
bool encryptDES(const std::string &inputFile, const std::string &outputFile, const std::string &key) {
    DES_cblock keyBlock;
    DES_key_schedule schedule;
    std::memcpy(keyBlock, key.c_str(), DES_KEY_SZ);
    DES_set_key_checked(&keyBlock, &schedule);

    std::ifstream inFile(inputFile, std::ios::binary);
    std::ofstream outFile(outputFile, std::ios::binary);

    if (!inFile || !outFile) {
        std::cerr << "Không thể mở tệp để mã hóa." << std::endl;
        return false;
    }

    unsigned char input[8], output[8];
    while (inFile.read(reinterpret_cast<char*>(input), sizeof(input))) {
        DES_ecb_encrypt((DES_cblock*)input, (DES_cblock*)output, &schedule, DES_ENCRYPT);
        outFile.write(reinterpret_cast<char*>(output), sizeof(output));
    }

    inFile.close();
    outFile.close();
    return true;
}

// Kiểm tra tính toàn vẹn của tệp
bool verifyFileIntegrity(const std::string &filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Không thể mở tệp: " << filename << std::endl;
        return false;
    }

    file.seekg(-32, std::ios::end);
    std::string originalMD5(32, '\0');
    file.read(&originalMD5[0], 32);
    file.seekg(0, std::ios::beg);

    std::string tempFile = "temp_file.dat";
    std::ofstream tempOut(tempFile, std::ios::binary);
    tempOut << file.rdbuf();
    tempOut.close();

    std::string calculatedMD5 = calculateMD5(tempFile);
    return (calculatedMD5 == originalMD5);
}

int main() {
    std::string filename = "X.txt";
    std::string encryptedFilename = "X_encrypted.dat";

    // Bước 1: Tính MD5
    std::string md5 = calculateMD5(filename);
    std::cout << "MD5 của tệp: " << md5 << std::endl;

    // Bước 2: Thêm MD5 vào cuối tệp
    appendMD5ToFile(filename, md5);

    // Bước 3: Mã hóa DES
    std::string key = "12345678"; // Khóa DES cần có độ dài 8 byte
    encryptDES(filename, encryptedFilename, key);

    // Bước 4: Kiểm tra tính toàn vẹn
    bool isIntact = verifyFileIntegrity(filename);
    std::cout << "Tệp có đảm bảo tính toàn vẹn không? " << (isIntact ? "Có" : "Không") << std::endl;

    return 0;
}
