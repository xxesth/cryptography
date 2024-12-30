#include "../include/crypto.hpp"
#include <fstream>
#include <sstream>
#include <cmath>
#include <stdexcept>
#include <iostream>

RSACrypto::RSACrypto() : n(0), e(0), d(0), p(0), q(0) {}

long long RSACrypto::modPow(long long base, long long exponent, long long modulus) {
    if (modulus == 1) return 0;
    long long result = 1;
    base = base % modulus;
    while (exponent > 0) {
        if (exponent % 2 == 1)
            result = (result * base) % modulus;
        base = (base * base) % modulus;
        exponent = exponent >> 1;
    }
    return result;
}

long long RSACrypto::gcd(long long a, long long b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

long long RSACrypto::multiplicativeInverse(long long e, long long phi) {
    long long m0 = phi, t, q;
    long long x0 = 0, x1 = 1;
    
    if (phi == 1) return 1;
    
    while (e > 1) {
        q = e / phi;
        t = phi;
        phi = e % phi;
        e = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }
    
    if (x1 < 0) x1 += m0;
    return x1;
}

long long RSACrypto::findPublicExponent(long long phi) {
    // Common public exponents to try
    std::vector<long long> candidates = {3, 5, 17, 257, 65537};
    
    for (long long candidate : candidates) {
        if (candidate < phi && gcd(candidate, phi) == 1) {
            return candidate;
        }
    }
    
    // If none of the common ones work, find the smallest valid e > 2
    for (long long i = 3; i < phi; i += 2) {
        if (gcd(i, phi) == 1) {
            return i;
        }
    }
    
    throw std::runtime_error("Could not find valid public exponent");
}

void RSACrypto::generateKeys(const std::string& primesFile) {
    std::ifstream file(primesFile);
    if (!file) throw std::runtime_error("Cannot open primes file");
    
    file >> p >> q;
    file.close();
    
    if (p <= 1 || q <= 1) {
        throw std::runtime_error("Invalid prime numbers");
    }
    
    n = p * q;
    long long phi = (p - 1) * (q - 1);
    
    // Find valid public exponent
    e = findPublicExponent(phi);
    std::cout << "Selected public exponent (e): " << e << std::endl;
    
    // Calculate private key d
    d = multiplicativeInverse(e, phi);
    std::cout << "Generated private exponent (d): " << d << std::endl;
}

std::vector<long long> RSACrypto::encrypt(const std::string& message) {
    std::vector<long long> ciphertext;
    for (char c : message) {
        ciphertext.push_back(modPow(static_cast<long long>(c), e, n));
    }
    return ciphertext;
}

std::string RSACrypto::decrypt(const std::vector<long long>& ciphertext) {
    std::string message;
    for (long long c : ciphertext) {
        message += static_cast<char>(modPow(c, d, n));
    }
    return message;
}

void RSACrypto::saveToFile(const std::vector<long long>& data, const std::string& filename) {
    std::ofstream file(filename);
    if (!file) throw std::runtime_error("Cannot open file for writing");
    
    for (const auto& num : data) {
        file << num << " ";
    }
    file.close();
}

std::vector<long long> RSACrypto::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) throw std::runtime_error("Cannot open file for reading");
    
    std::vector<long long> data;
    long long num;
    while (file >> num) {
        data.push_back(num);
    }
    file.close();
    return data;
}

std::string RSACrypto::loadTextFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) throw std::runtime_error("Cannot open file for reading");
    
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}
