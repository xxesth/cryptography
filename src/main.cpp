#include "crypto/crypto.hpp"
#include <iostream>
#include <fstream>
#include <filesystem>

int main() {
    try {
        RSACrypto crypto;
        
        // Generate keys using primes from file
        crypto.generateKeys("data/input/primes.txt");
        
        // Load message from file
        std::string message = crypto.loadTextFile("data/input/message.txt");
        std::cout << "Original message: " << message << std::endl;
        
        // Encrypt
        std::vector<long long> encrypted = crypto.encrypt(message);
        crypto.saveToFile(encrypted, "data/output/encrypted.txt");
        std::cout << "Message encrypted and saved to encrypted.txt" << std::endl;
        
        // Decrypt
        std::vector<long long> loadedEncrypted = crypto.loadFromFile("data/output/encrypted.txt");
        std::string decrypted = crypto.decrypt(loadedEncrypted);
        std::cout << "Decrypted message: " << decrypted << std::endl;
        
        // Save decrypted text
        std::ofstream decryptedFile("data/output/ciphertext.txt");
        decryptedFile << decrypted;
        decryptedFile.close();
        std::cout << "Decrypted message saved to ciphertext.txt" << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}
