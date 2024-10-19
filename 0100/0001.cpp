#include <iostream>
#include <string>


std::string decryptCaesarCipher(const std::string& ciphertext, int key) {
    std::string plaintext = "";

    for (char c : ciphertext) {
        if (c >= 'a' && c <= 'z') {
            char decryptedChar = (c - 'a' - key + 26) % 26 + 'a';
            plaintext += decryptedChar;
        } else {
            plaintext += c;
        }
    }
    
    return plaintext;
}

int main() {
    std::string ciphertext = "vybircuravxnn";
    
    for (int key = 0; key < 26; key++) {
        std::string decryptedText = decryptCaesarCipher(ciphertext, key);
        std::cout << "Key: " << key << " -> Decrypted text: " << decryptedText << std::endl;
    }

    return 0;
}
