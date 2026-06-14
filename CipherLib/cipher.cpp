#include "cipher_api.h"
#include <string>
#include <vector>

std::vector<char> az = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
				'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };

std::vector<char> AZ = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
				'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };

int find_by_value(std::vector<char>& arr, char value) {
	for (int i = 0; i < arr.size(); ++i) {
		if (arr[i] == value) {
			return i;
		}
	}
	return -1;
}

class Cipher {
public:
	virtual std::string encrypt(const std::string& text) = 0;
	virtual std::string decrypt(const std::string& text) = 0;
	virtual ~Cipher() = default;
};

class CaesarCipher : public Cipher {
	int key_;
public:
	CaesarCipher(int key) {
		key_ = key;
	}

    std::string encrypt(const std::string& text) override {
        std::string res_text;

        for (int i = 0; i < text.length(); i++) {
            int small_idx = find_by_value(az, text[i]);
            int big_idx = find_by_value(AZ, text[i]);

            if (small_idx != -1) {
                int shifted = (small_idx + key_) % (int)az.size();
                if (shifted < 0) shifted += az.size();

                res_text += az[shifted];
            }
            else if (big_idx != -1) {
                int shifted = (big_idx + key_) % (int)AZ.size();
                if (shifted < 0) shifted += AZ.size();

                res_text += AZ[shifted];
            }
            else {
                res_text += text[i];
            }
        }

        return res_text;
    }
	std::string decrypt(const std::string& text) override {
		CaesarCipher inverseCaesar(-key_);
		return inverseCaesar.encrypt(text);
	};
};

class VigenereCipher : public Cipher {
	std::string key_;
public:
	VigenereCipher(const std::string& key);
	std::string encrypt(const std::string& text) override;
	std::string decrypt(const std::string& text) override;
};
