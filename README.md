# RC4 Encryption Implementation in C
This project contains a simple implementation of the RC4 (Rivest Cipher 4) encryption algorithm written in C. The code includes both a header file (`arcfour.h`) and a source file (`arcfour.c`) for encrypting and decrypting data using the RC4 stream cipher.

## Table of Contents
- [RC4 Encryption Implementation in C](#rc4-encryption-implementation-in-c)
  - [Table of Contents](#table-of-contents)
  - [Introduction](#introduction)
    - [Features](#features)
  - [Installation \& Usage](#installation--usage)
    - [Installation](#installation)
    - [Functions](#functions)
    - [Usage](#usage)
  - [Example usage](#example-usage)

## Introduction
RC4 is a stream cipher that is widely known for its simplicity and speed. It's a symmetric key cipher, which means the same key is used for both encryption and decryption. This implementation uses the basic RC4 algorithm to initialize the key, generate a pseudo-random byte stream, and perform XOR operations to encrypt and decrypt data. You can read more about RC4 from [here](https://en.wikipedia.org/wiki/RC4)

### Features
- Basic RC4 encryption and decryption.
- A key-scheduling algorithm (KSA) to initialize the state.
- A pseudo-random generation algorithm (PRGA) to produce the keystream.

## Installation & Usage
### Installation
```bash
    git clone https://github.com/LilSuperUser/rc4-c
    cd ./rc4-c
```
### Functions
- **`Arcfour *rc4init(int8 *key, int16 ksize);`**
  - Initializes the RC4 state with a provided key (dynamically allocates memory for Arcfour structure).
  - The key should be a string of maximum length 256.
  - Returns a pointer to the allocated memory.
- **`int8 rc4byte(Arcfour *p);`**
  - Generates a single byte of pseudo-random data from the RC4 state.
- **`int8 *rc4encrypt(Arcfour *p, int8 *clear_text, int16 size);`**  
  - Encrypts the `clear_text` of length `size` using the RC4 state.
  - Dynamically allocates memory for the resultig ciphertext.
  - Returns a pointer to dynamically allocated resulting ciphertext.
- **`void printbin(int8*, const int16)`**
  - Takes a pointer to binary data and number of bytes to read
  - prints the binary data in the hexadecimal format (to print cipher text)
- **`#define rc4uninit(x)            free(x)`**
  - function macro to unintialize rc4 state.
- **`#define rc4decrypt(x, y, z)     rc4encrypt(x, y, z)`**
  - function macro to decrypt a cipher text.
  - takes three arguments (Arcfour pointer, pointer to cipher text, size of cipher text).
  - calls the rc4encrypt with these arguments
  - returns a pointer to dynamically allocated char array (clear text) after decrypting.
### Usage
1. Include the rc4 header file `arcfour.h`.
2. Initialize the rc4 state using `rc4init` and a key.
3. Use `rc4encrypt` to encrypt a clear text.
4. Print the clear text using `printbin` function.
5. Re-initialize the rc4 state using `rc4init` using the same key.
6. Use `rc4decrypt` to decrypt a clear text.
7. Print the clear text using normal `printf` or some other function.
8. Once you're done, free the allocated memory for Arcfour structure, cipher and clear text.

## Example usage
```c
#include "arcfour.h"
int main(void){
    // defining char pointers to hold key, clearText, encrypted and decrypted text
    char *key, *clearText;
    key = "This is a dummy key";    // init key char pointer with key
    clearText = "This is a dummy clear text";  // init clearText char pointer with clear text

    // defining int8 pionters for encrypted and decrypted texts
    int8 *encrypted, *decrypted;

    // defining & init int16 variables to hold size of key and text
    int16 skey = (int16)strlen(key), size = (int16)strlen(clearText);

    // Initializing rc4 state
    Arcfour *rc4 = rc4init(key, skey);

    // encrypting the clearText
    encrypted = rc4encrypt(rc4, (int8*)clearText, size);

    // printing the encrypted text using printbin (binary data)
    printf("The encrypted text is: ");
    fflush(stdout);
    printbin(encrypted, size);

    // reinitializing the rc4 state to decrypt the encrypted text
    rc4uninit(rc4);
    rc4 = rc4init(key, skey);

    // decrypting the encrypted text, and printing the clear text
    decrypted = rc4decrypt(rc4, encrypted, size);
    printf("The decrypted string is: %s\n", (char*)decrypted);  

    // uninitliazing (freeing) rc4 state, encrypted and decrypted strings
    rc4uninit(rc4);
    free(encrypted);
    free(decrypted);

    return 0;
}
```