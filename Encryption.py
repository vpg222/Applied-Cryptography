#!/bin/python3

import random

key_map = {
    '32': [19],
    '97': [7],
    '98': [1],
    '99': [2],
    '100': [4],
    '101': [10],
    '102': [2],
    '103': [2],
    '104': [5],
    '105': [6],
    '106': [1],
    '107': [1],
    '108': [3],
    '109': [2],
    '110': [6],
    '111': [6],
    '112': [2],
    '113': [1],
    '114': [5],
    '115': [5],
    '116': [7],
    '117': [2],
    '118': [1],
    '119': [2],
    '120': [1],
    '121': [2],
    '122': [1],
}


def key_generation(**key_map):
    # print("test: {}".format(key_map.get('116')[0]))
    for key, value in key_map.items():
        length = key_map.get(key)[0]
        # print("key: {}".format(type(key)))
        # print("length: {}".format(length))
        counter = 0
        while counter < length:
            key_map[key].append(random.randrange(0, 105))
            counter += 1
    return 0


def print_key(**key_map):
    for key, value in key_map.items():
        print("{}: {}".format(key, value))
    return 0


def encryption(message, **key_map):
    ciphertext = ''
    for i in message:
        # print("This is: {}".format(i))
        ord_i = str(ord(i))
        # print("This is ord_i: {}, {}".format(ord_i, type(ord_i)))
        list = key_map.get(ord_i)
        choice = random.choice(list[1:])
        # print("This is encrpted: {}".format(choice))
        ciphertext = ciphertext + str(choice) + ", "
    return ciphertext


if __name__ == "__main__":
    message = str(input("Enter your plaintext: "))
    key_generation(**key_map)
    print_key(**key_map)
    ciphertext = encryption(message, **key_map)
    print("\nThe Ciphertext: \n{}".format(ciphertext))
