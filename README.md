# Project 1 Cryptanalysis of a class of ciphers

## Requirement

- Time:
    + Test 1: 1 minutes
    + Test 2: 3 minutes

- UI:
    + "Enter the ciphertext: "
    + "My plaintext guess is: "

- Filename:
    + `<last name1>-<last name2>-<last name3>-decrypt`

- Report:
    + Title
    + Introduction of team member and effort
    + Approaches
        * Informal explanation
        * Rigorous description

## Objective

A software implementation of an algorithm that attempt to decrypt a ciphertext computed using a special algorithm in a reasonable time.

## Detailed Description

### What we have?

- The ciphertext
- A plaintext dictionary, contain a number of plaintexts
    + each one obtained as a sequence of space-separated words from the English Dictionary
- Partial Knowledge of the encryption algorithm

### Restriction

- The key used by the permutation cipher
- Part of the encryption scheme

### What we know?

- Plaintext: {<space>, a,b,c...,z}^(Length)

- Key: a map from each English alphabet letter (lower case) + Space

    + Weighted: based on frequency [DISTINCT]
        * The number of possible keys for this letter
        * map to a randomly chosen number from 0 to 105 
    + the set of random maps from {0,..,26} to a permutation of all numbers in {0,…,105}, grouped in 27 lists, each list having length pre-determined

- Ciphertext: comma-separated numbers between 0 and 105
    + {0,...,105}^(Length)

- Encryption:
    + Map the message m[i] with key map, return any possible c[i]
    + The algorithm may depends on j, L and the length of the list on that row

- Decryption
    + Given c[i], finding the possible key map, and return the m[i]
    + Question: Are they distinguishable?

### Test 1

Given a plaintext dictionary, ciphertext to decrypt

- L = 500


### Test 2

Given a new ciphertext, to compute the plaintext with a given `english_words.txt`

- L = 500

## BrainStorming

### Approach #1


Using Bruteforce + Frequency Table

![](https://github.com/GreyFox-Z/Applied-Cryptography/blob/Project-1/Project%201/Project%2010.png)

可能不行， 106^500 有点大…

### Approach #2

Word Pattern

there is no certain word pattern without sufficient delimiter. Also due to the uniform distribution, it is relatively hard to approach in this method

### Approach #3 Non sense approach

use the whatever the cipher we have perform modulus calculation with 27. Use that to create a raw map.


## How to evaluate the plaintext

Using frequency analysis


## Interesting Reference

[Cryptopals crypto challenges](https://cryptopals.com/)

[Stack Exchange](https://crypto.stackexchange.com/)

[Cipher Tools](http://rumkin.com/tools/cipher/)

[Average_English_Word](https://medium.com/@wolfgarbe/the-average-word-length-in-english-language-is-4-7-35750344870f)

[Dummy Substitution](https://www.dummies.com/games/cryptograms/cryptography-101-basic-solving-techniques-for-substitution-ciphers/)
