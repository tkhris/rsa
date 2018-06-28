#include <iostream>
#include <string>
#include <math.h>

class RSA
{
private:
    int pub;
    int priv;
    int n;

    int gcd(int a, int b)
    {
        while(b > 0)
        {
            int temp = a % b;
            a = b;
            b = temp;
        }
        return a;
    }

    int lcm(int a, int b)
    {
        int multipleA = a;
        int multipleB = b;

        while(multipleA != multipleB)
        {   
            if (multipleA > multipleB)
                multipleB += b;
            else
                multipleA += a;
        }

        return multipleA;
    }

    int mmi(int e, int coprime)
    {
        int mmi = 1;
        while((mmi * e) % coprime != 1)
        {
            mmi++;
        } 
        return mmi;
    }

    int createPublic(int totient)
    {
        // e < totient
        // and e is coprime to totient
        int num = 0;
        int primes[] = {2, 3, 5, 7, 11, 13, 
        17, 19, 23, 29, 31, 
        37, 41, 43, 47, 53, 
        59, 61, 67, 71, 73, 
        79, 83, 89, 97, 101, 
        103, 107, 109, 113, 127, 
        131, 137, 139, 149, 151, 
        157, 163, 167, 173, 179, 
        181, 191, 193, 197, 199};
        while(num < 46)
        {
            if(totient % primes[num] != 0)
                return primes[num];
            num++;
        }

        return 1;
    }

    int random_prime(int bits)
    {
        return 1;
    }
public:
    RSA()
    {
        // int p = 11;
        // int q = 5;
        // n = 55;
        // pub = 7;
        // priv = 23;
        int p = 11;
        int q = 7;
        n = p * q;
        int lambda = lcm(p - 1, q - 1);
        pub = createPublic(lambda);
        priv = mmi(pub, lambda);
    }

    std::string encrypt(std::string message)
    {
        std::string output;
        for(int i = 0; i < message.length(); i++)
        {
            int temp = 1;
            int letter = message[i] - 97;

            for(int q = 0; q < pub; q++)
            {
                temp = temp * letter;
                temp = temp % n;
            }
            output += (char)temp;
        }
        return output;
    }

    /***
     * decrypt
     * decrypts an encrypted message from a given string
     * ***/
    std::string decrypt(std::string encrypted)
    {
        // create a string as the output
        std::string output;

        // loop across the encrypted message
        for(int i = 0; i < encrypted.length(); i++)
        {
            // hold the ascii value of the character as an int
            int temp = 1;
            int letter = encrypted[i];

            // this is just a hand written pow function
            for(int q = 0; q < priv; q++)
            {
                temp = temp * letter;
                temp = temp % n;
            }
            
            output += (char)(temp + 97);
        }
        return output;
    }

    /**********************
     * display keys
     * Displays the Private key, Public key, and N
     * ********************/
    void displayKeys()
    {
        std::cout << "Private: " << priv << std::endl;
        std::cout << "Public : " << pub << std::endl;
        std::cout << "N      : " << n << std::endl;
    }
};

class grandpre
{
private:
    std::string key;
public:
    void setKey(std::string input)
    {
        std::string alphabet = "abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        int index = 0;
        for(; index < input.length() && index < 64; index++)
        {
            key += input[index];
            std::size_t found = alphabet.find(input[index]);
            if (found != std::string::npos)
            {
                alphabet.erase(alphabet.begin() + found);
            }
        }

        while (key.length() < 64)
        {
            key += alphabet;
        }

        key.erase(64);
    }   

    void displayKey()
    {
        for(int i = 0; i < key.length(); i++)
        {
            if (!(i % 8))
            {
                std::cout << std::endl;
            }
            std::cout << key[i] << " ";
        }

        std::cout << std::endl;
        std::cout << std::endl;
    }

    std::string encrypt(std::string input)
    {
        std::string encrypted;
        
        for(int i = 0; i < input.length(); i++)
        {
            int pos = key.find(input[i]);
            encrypted += (pos / 8) + 49;
            encrypted += (pos % 8) + 49;
            encrypted += " ";
        }

        return encrypted;
    }

    std::string decrypt(std::string input)
    {
        std::string decrypted;
        
        for(int i = 0; i < input.length(); i += 3)
        {
            int x = input[i] - 49;
            int y = input[i + 1] - 49;
            decrypted += key[(x * 8) + y];
        }

        return decrypted;
    }
};

int main()
{
    RSA encryption;
    // The secret message we want to encode
    std::string message = "encryptionisreallycool";
    // encrypt it
    std::string encrypted = encryption.encrypt(message);
    // decrypt it
    std::string decrypted = encryption.decrypt(encrypted);
    
    // Display function
    encryption.displayKeys();

    // is the original message equal to the decrypted
    std::cout << message   << std::endl;
    std::cout << encrypted << std::endl;
    std::cout << decrypted << std::endl;
    std::cout << ((message == decrypted) ? "True" : "False") << std::endl << std::endl;

    grandpre cipher;
    cipher.setKey("ladybugsazimuthscalfskinquackishunjovialevulsionrowdyismsextuply");
    std::string e2 = cipher.encrypt(message);
    std::string d2 = cipher.decrypt(e2);

    cipher.displayKey();

    std::cout << message << std::endl;
    std::cout << e2 << std::endl;
    std::cout << d2 << std::endl;
}