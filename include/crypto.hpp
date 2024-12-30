#ifndef CRYPTO_HPP
#define CRYPTO_HPP

#include <string>
#include <vector>

class RSACrypto {
private:
    long long n;        // n = p * q
    long long e;        // public exponent
    long long d;        // private exponent
    long long p;        // first prime
    long long q;        // second prime

    long long modPow(long long base, long long exponent, long long modulus);
    long long gcd(long long a, long long b);
    long long multiplicativeInverse(long long e, long long phi);
    long long findPublicExponent(long long phi);

public:
    RSACrypto();
    void generateKeys(const std::string& primesFile);
    std::vector<long long> encrypt(const std::string& message);
    std::string decrypt(const std::vector<long long>& ciphertext);
    void saveToFile(const std::vector<long long>& data, const std::string& filename);
    std::vector<long long> loadFromFile(const std::string& filename);
    std::string loadTextFile(const std::string& filename);
};

#endif
