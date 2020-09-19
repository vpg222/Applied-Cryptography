#include <iostream>
#include <map>
#include <vector>
#include <cstdlib>
#include <string>
#include <iomanip>
#include <ctime>

using namespace std;

const int KEY_MAP_SIZE = 106;


// key map generation function
// first randomly order the numbers 0 to 105
// then assign them to letters a-z and [space]
map<char, vector<int>> KeyGen() {
    map<char, vector<int>> key_map;
    int values[KEY_MAP_SIZE];
    for (int i = 0; i < KEY_MAP_SIZE; ++i) {
        values[i] = i;
    }

    srand((unsigned)time(0));
    for (int i = 0; i < KEY_MAP_SIZE; ++i) {
        int swap_index = rand() % (KEY_MAP_SIZE - i) + 1;
        int tmp = values[i];
        values[i] = values[swap_index];
        values[swap_index] = tmp;
    }


    char letters[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i','j','k', 'l', 'm', 'n', 'o',
                      'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y','z', ' '};
    int index = 0;
    for (int i = 0; i < 27; ++i) {
        char c = letters[i];
        int list_size;
        if (c == ' ') {
            list_size = 19;
        } else if (c == 'e') {
            list_size = 10;
        } else if (c == 'a' || c == 't') {
            list_size = 7;
        } else if (c == 'i' || c == 'n' || c == 'o') {
            list_size = 6;
        } else if (c == 'h' || c == 'r' || c == 's') {
            list_size = 5;
        } else if (c == 'd') {
            list_size = 4;
        } else if (c == 'l') {
            list_size = 3;
        } else if (c == 'c' || c == 'f' || c == 'g' || c == 'm' || c == 'p' || c == 'u' || c ==
        'w' || c == 'y') {
            list_size = 2;
        } else {
            list_size = 1;
        }

        vector<int> list;
        for (int j = 0; j < list_size; ++j) {
            list.push_back(values[index]);
            index++;
        }
        key_map.insert(pair<char, vector<int>>(c, list));
    }
    return key_map;
}


// format print key map
void PrintMapping(map<char, vector<int>> mapping) {
    for (map<char, vector<int>>::iterator it = mapping.begin(); it != mapping.end(); ++it) {
        cout << it->first << " : ";
        for (const int& value : it->second) {
            cout << value << ", ";
        }
        cout << endl;
    }
}


// encrypts the given string using the supplied key map
// uses scheduling algorithm j mod(len(list))
vector<int> Enc(string s, map<char, vector<int>> key_map) {
    vector<int> cipher;
    for (int i = 0 ; i < s.length(); ++i) {
        vector<int> list = key_map[s[i]];
        cipher.push_back(list[i % list.size()]);

    }
    return cipher;
}

map<int, int> GetCountCiphertext(const vector<int>& ciphertext) {
    map<int, int> map;

    // populate the map with all possible keys from 0 to 105
    for (int i = 0; i < KEY_MAP_SIZE; ++i) {
        map.insert(pair<int, int>(i, 0));
    }

    for (int i : ciphertext) {
        map[i]++;
    }
    return map;
}


// returns a map of integer and the frequency they appear
// count: total count of integers
map<int, double> GetFrequencyCiphertext(const map<int, int>& count, int total) {
    map<int, double> frequency;
    for (auto const& entry : count) {
        frequency.insert(pair<int, double>(entry.first, entry.second/(total + 0.0)));
    }
    return frequency;
}


map<char, int> GetCountPlaintext(const string& plaintext) {
    map<char, int> map;

    // populate the map with all possible keys a-z and [space]
    char letters[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i','j','k', 'l', 'm', 'n', 'o',
                      'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y','z', ' '};
    for (int i = 0; i < 27; ++i) {
        map.insert(pair<char, int>(letters[i], 0));
    }

    for (char c : plaintext) {
        map[c]++;
    }
    return map;
}


// returns a map of integer and the frequency they appear
// count: total count of integers
map<char, double> GetFrequencyPlaintext(const map<char, int>& count, int total) {
    map<char, double> frequency;
    for (auto const& entry : count) {
        frequency.insert(pair<char, double>(entry.first, entry.second/(total + 0.0)));
    }
    return frequency;
}



int main() {

    clock_t start, end;
    start = clock();


    map<char, vector<int>> key_map = KeyGen();
    PrintMapping(key_map);
    cout << endl;

    string s = "he was so preoccupied with whether or not he could that he failed to stop to "
               "consider if he should vet zip had events coming situation apologize kangaroo nice"
               " feeling anomaly characteristic gem steal scarf hat find has occupation something"
               " imagination education institution famous indirect ancient anthropology learning "
               "ancestor starry immobilize global eager questions bridge flag running bowling "
               "friends classroom textbook guess the a small the whole bread some that this "
               "discover obey anticipate touring roller skating ask me her she they must be ";
    cout << "length of the plaintext is " << s.length() << endl << endl;

    vector<int> cipher = Enc(s, key_map);
    cout << "Ciphertext is:" << endl;
    for (int i = 0; i < cipher.size(); ++i) {
        cout << cipher[i] << ", ";
    }
    cout << endl << endl << "Plaintext frequency analysis:" << endl;

    map<char, int> plaintext_count = GetCountPlaintext(s);
    for (auto const& entry : plaintext_count) {
        cout << entry.first << " appears " << entry.second << " times" << endl;
    }

    cout << endl;

    map<char, double> plaintext_freq = GetFrequencyPlaintext(plaintext_count, s.length());
    for (auto const& entry : plaintext_freq) {
        cout << entry.first << " has frequency " << setprecision(10) << entry.second * 106 <<
             endl;
    }

    cout << endl << "Ciphertext frequency analysis:" << endl;

    map<int, int> ciphertext_count = GetCountCiphertext(cipher);
    for (auto const& entry : ciphertext_count) {
        cout << entry.first << " appears " << entry.second << " times" << endl;
    }

    cout << endl;

    map<int, double> ciphertext_freq = GetFrequencyCiphertext(ciphertext_count, s.length());
    for (auto const& entry : ciphertext_freq) {
        cout << entry.first << " has frequency " << setprecision(10) << entry.second <<
        endl;
    }




    end = clock();
    double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    cout << "Time taken to run the program is " << fixed << time_taken << setprecision(5) << " "
                                                                                             "seconds" << endl;

    return 0;
}