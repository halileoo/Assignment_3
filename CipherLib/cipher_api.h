#pragma once

#ifdef WIN32
	#define EXPORT __declspec(dllexport)
#else
	#define EXPORT __attribute__((visibility("default")))
#endif

extern "C" {
	typedef void* cipher_t;

	/* Factory — creates the cipher object and returns an opaque handle */
	export cipher_t* cipher_create_caesar(int key);
	export cipher_t* cipher_create_vigenere(const char* key);
	/* Operations — behave differently depending on which cipher was
	created */
	export char* cipher_encrypt(cipher_t* cipher, const char* text);
	export char* cipher_decrypt(cipher_t* cipher, const char* text);
	/* Cleanup */
	export void  cipher_destroy(cipher_t* cipher);
	export void  cipher_free(char* str);
}
