#include "../include/crypto.hpp"
#include <iostream>
#include <fstream>

int main() {
    try {
        RSACrypto crypto;
        
        // Generate keys using primes from file
        crypto.generateKeys("tests/data/primes.txt");
        
        // Load message from file
        std::string message = crypto.loadTextFile("tests/data/message.txt");
        std::cout << "Original message: " << message << std::endl;
        
        // Encrypt
        std::vector<long long> encrypted = crypto.encrypt(message);
        crypto.saveToFile(encrypted, "tests/data/encrypted.txt");
        std::cout << "Message encrypted and saved to encrypted.txt" << std::endl;
        
        // Decrypt
        std::vector<long long> loadedEncrypted = crypto.loadFromFile("tests/data/encrypted.txt");
        std::string decrypted = crypto.decrypt(loadedEncrypted);
        std::cout << "Decrypted message: " << decrypted << std::endl;
        
        // Save decrypted text
        std::ofstream decryptedFile("tests/data/ciphertext.txt");
        decryptedFile << decrypted;
        decryptedFile.close();
        std::cout << "Decrypted message saved to ciphertext.txt" << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
