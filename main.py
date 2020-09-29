#!/bin/python3

import random
import time
import string
import threading
import queue
from nltk.corpus import words
import matplotlib.pyplot as plot
import matplotlib as mpl


# Input Information
path_to_file = "C:\\Cloud\\学校\\NYU\\CS-GY 6903 Applied Cryptography\\Projects\\dictionary.txt"


# Global Values
wordlist = []
set_length = [19, 7, 1, 2, 4, 10, 2, 2, 5, 6, 1, 1, 3, 2, 6, 6, 2, 1, 5, 5, 7, 2, 1, 2, 1, 2, 1]


# Structure Define
class key_map(dict):
    # This will be a class for homophonic dictionary management
    def __init__(self):
        self = dict()

    def add(self, new_key, new_value):
        if new_key in self.keys():
            self[new_key].append(new_value)
        else:
            self[new_key] = [new_value]

    def remove_value(self, key, remove_value):
        if key in self.keys() and remove_value in self[key]:
            self[key].remove(remove_value)
        else:
            print("[Error] No such key or value")

    def print(self):
        self.sort()
        for key, value in sorted(self.items()):
            print("{}: {}".format(chr(key), value))

    def ret_length(self, s_key):
        return len(self[s_key])

    def swap(self, key1, value1, key2, value2):
        if (        key1 in self.keys() 
                and key2 in self.keys()
                and value1 in self[key1]
                and value2 in self[key2]
            ):
            self.add(key1, value2)
            self.remove_value(key1, value1)
            self.add(key2, value1)
            self.remove_value(key2, value2)
            self.sort()
        else:
            print("[Error] No such key or value")
            return 0

    def sort(self):
        for key, value in sorted(self.items()):
            value.sort()

    def initiation(self):
        # Adding space
        self[ord(' ')] = []

        # Initiate an empty set of key_map structure
        for i in range(ord('a'), ord('{'), 1):
            self[i] = []

        self.sort()

    def key_generation(self):
        key_possible_values = list(range(0, 106, 1))

        for key, value in self.items():
            length = set_length[list(self.keys()).index(key)]
            while self.ret_length(key) < length:
                choice = random.choice(key_possible_values)
                self[key].append(choice)
                key_possible_values.remove(choice)

    def return_key(self, given_value):
        found_key = -1
        for key, value in self.items():
            if given_value in self[key]:
                found_key = key

        if found_key == -1:
            print("[Error] No key found")
            return found_key
        else:
            return found_key


class trad_dict(dict):
    # This is the traditional 1-1 dictionary
    def __init__(self):
        self = dict()

    def add(self, new_key, new_value):
        if new_key in self.keys():
            self[new_key] = new_value
        else:
            self[new_key] = new_value

    def print(self):
        for key, value in sorted(self.items()):
            print("{}: {}".format(key, value))

    def swap(self, key1, value1, key2, value2):
        temp_value_holder = value1
        self[key1] = value2
        self[key2] = temp_value_holder

    def plot(self):
        labels, data = [*zip(self.items())]
        plot.bar(labels, data)
        plot.show()

    def initiation(self):
        # Initiate an empty set of key_map structure
        for i in range(ord('a'), ord('{'), 1):
            self[i] = 0

        # Adding space
        self[ord(' ')] = 0
        self.sort()


# Function Define
def import_file():
    with open(path_to_file) as file:
        for line in file:
            line = line.strip()
            wordlist.append(line)


def generate_random_words(length):
    # A function is used to generate random strings
    message = ' '.join(random.sample(words.words(), 100))
    message = message[:length]
    return message


def generate_plaintext(length):
    # A function is used to generate string from given wordlist
    message = ' '.join(random.sample(wordlist, 200))
    message = message[:length]
    return message


def encryption(plaintext, dictionary):
    ciphertext = ''
    for i in plaintext:
        # print("This is: {}".format(i))
        if ((ord(i) <= 90) and (ord(i) >= 65)):
            ord_i = int(ord(i) + 32)
        elif ((ord(i) <= 122) and (ord(i) >= 97)):
            ord_i = int(ord(i))
        elif ord(i) == 32:
            ord_i = int(ord(i))
        else:
            print("[Error] Wrong Input")
        # print("This is ord_i: {}, {}".format(ord_i, type(ord_i)))
        list = dictionary[ord_i]
        # print(list)
        choice = random.choice(list)
        # print("This is encrpted: {}".format(choice))
        ciphertext = ciphertext + str(choice) + ","

    ciphertext = ciphertext[:-1]
    return ciphertext


def generating_raw_key_map():
    raw_key_map = key_map()
    raw_key_map.initiation()
    raw_key_map.key_generation()
    return raw_key_map


def evaluation(message):
    # How do I evaluate this?
    score = 0
    score = score + 1
    return score


def invert_func(ciphertext, key_map):
    plaintext = ''
    for i in list(ciphertext.split(",")):
        plaintext = plaintext + chr(key_map.return_key(int(i)))
    return plaintext


def guessing(ciphertext, key_map):
    guess = ''
    score = 0
    while score == 0:
        # Decryption
        guess = invert_func(ciphertext, key_map)
        # Evaluation
        score = evaluation(guess)
        # Substition key pairs
        # How should I swap the keys?
        print("\nGuessing Key Map: \n")
        key_map.print()

    return guess


# Main Function
if __name__ == "__main__":
    # Timer
    start_time = time.time()
    # Import files
    import_file()

    # Test Envrionment
    new_key_map = key_map()
    new_key_map.initiation()
    # Generating Dictionary
    new_key_map.key_generation()
    print("Key Map: \n")
    new_key_map.print()

    """
    user_input = int(input("\nWhat key? "))
    print("{}".format(chr(new_key_map.return_key(user_input))))
    """

    # Generating plaintext
    print("\nPlaintext: \n")
    # plaintext = generate_random_words(500)
    plaintext = generate_plaintext(500)
    print("{}".format(plaintext))

    # Encryption
    print("\nCiphertext: \n")
    ciphertext = encryption(plaintext, new_key_map)
    print("{}".format(ciphertext))

    # Breaking with Dictionary
    raw_key_map = generating_raw_key_map()

    guessing_plaintext = guessing(ciphertext, raw_key_map)
    print("\nMy guess: \n")
    print(guessing_plaintext)

    # Timer
    end_time = time.time()
    print("Total Time: {}".format(end_time - start_time))
