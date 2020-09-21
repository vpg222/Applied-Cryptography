#include <iostream>
#include <map>
#include <vector>
#include <cstdlib>
#include <string>
#include <iomanip>
#include <ctime>

using namespace std;

const int KEY_MAP_SIZE = 106;

map<char, int> frequency = {{' ', 19}, {'e', 10}, {'a', 7}, {'t', 7}, {'i', 6},
                            {'n', 6}, {'o',6}, {'h', 5}, {'r', 5}, {'s', 5},
                            {'d', 4}, {'l', 3}, {'c', 2}, {'f', 2}, {'g', 2},
                            {'m', 2}, {'p', 2}, {'u', 2}, {'w', 2}, {'y', 2},
                            {'b', 1}, {'j', 1}, {'k', 1}, {'q', 1}, {'v', 1},
                            {'x', 1}, {'z', 1}};

string p1 = "midwinter spring is its own seasonsempiternal though sodden towards sundown "
            "suspended in time between pole and tropic when the short day is brightest with frost and fire the brief sun flames the ice on pond and ditches in windless cold that is the hearts heat reflecting in a watery mirror a glare that is blindness in the early afternoon and glow more intense than blaze of branch or brazier stirs the dumb spirit no wind but pentecostal fire in the dark time of the year between melting and freezin";
string p2 = "gthe souls sap quivers there is no earth smellor smell of living thing this is the "
            "spring time but not in times covenant now the hedgerowis blanched for an hour with transitory blossom of snow a bloom more sudden than that of summer neither budding nor fading not in the scheme of generationwhere is the summer the unimaginable zero summerif you came this way taking the route you would be likely to take from the place you would be likely to come from if you came this way in may time you would find";
string p3 = " the hedges white again in may with voluptuary sweetness it would be the same at the"
            " end of the journey if you came at night like a broken king if you came by day not knowing what you came for it would be the same when you leave the rough road and turn behind the pigsty to the dull facade and the tombstone and what you thought you came foris only a shell a husk of meaning from which the purpose breaks only when it is fulfilled if at all either you had no purpose or the purpose is beyond the end ";
string p4 = "you figured and is altered in fulfilment there are other places which also are the "
            "worlds end some at the sea jaws or over a dark lake in a desert or a city but this is the nearest in place and time now and in englandif you came this way taking any route starting from anywhereat any time or at any season it would always be the same you would have to put off sense and notion you are not here to verifyinstruct yourself or inform curiosity or carry report you are here to kneel where prayer has been";
string p5 = " valid and prayer is more than an order of words the conscious occupationof the "
            "praying mind or the sound of the voice praying and what the dead had no speech for when living they can tell you being dead the communicationof the dead is tongued with fire beyond the language of the living here the intersection of the timeless momentis england and nowhere never and alwaysash on an old mans sleeveis all the ash the burnt roses leave dust in the air suspendedmarks the place where a story endeddust in";
string plaintexts[] = {p1, p2, p3, p4, p5};



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
        int list_size = frequency[c];

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
//        cipher.push_back(list[0]);
        cipher.push_back(list[(i * i) % list.size()]);

    }
    return cipher;
}



bool isValidPlaintext(string plaintext, vector<int> ciphertext) {
    int count[27];
    for (int i = 0; i < 27; ++i) {
        count[i] = 0;
    }
    map<int, char> key_map;
    if (plaintext.length() != ciphertext.size()) {
        cout << plaintext.length() << endl;
        cout << ciphertext.size() << endl;
        return false;
    }

    for (int i = 0; i < plaintext.length(); ++i) {
        if (key_map.find(ciphertext[i]) == key_map.end()) {
            key_map.insert(pair<int, char>(ciphertext[i], plaintext[i]));

            if (plaintext[i] == ' ') {
                count[26]++;
                if (count[26] > frequency[' ']) {
                    return false;
                }
            } else {
                count[plaintext[i] - 'a']++;
                if (count[plaintext[i] - 'a'] > frequency[plaintext[i]]) {
                    return false;
                }
            }
        } else if (key_map[ciphertext[i]] != plaintext[i]){
            return false;
        }
    }
    return true;
}



// get the n-gram frequency analysis of ciphertext
map<vector<int>, int> GetCountCiphertext(const vector<int>& ciphertext, int n) {
    map<vector<int>, int> map;

    if (ciphertext.size() < n) {
        return map;
    }

    for (int i = 0; i <= ciphertext.size() - n; ++i) {
        vector<int> ngram;
        for (int j = i; j < i + n ; ++j) {
            ngram.push_back(ciphertext[j]);
        }
        if (map.find(ngram) == map.end()) {
            map.insert(pair<vector<int>, int>(ngram, 1));
        } else {
            map[ngram]++;
        }
    }
    return map;
}


// returns a map of integer and the frequency they appear
// count: total count of integers
map<vector<int>, double> GetFrequencyCiphertext(const map<vector<int>, int>& count, int total) {
    map<vector<int>, double> frequency;
    for (auto const& entry : count) {
        frequency.insert(pair<vector<int>, double>(entry.first, entry.second/(total + 0.0)));
    }
    return frequency;
}


// get the n-gram frequency analysis of plaintext
map<vector<char>, int> GetCountPlaintext(const string& plaintext, int n) {
    map<vector<char>, int> map;

    if (plaintext.size() < n) {
        return map;
    }

    for (int i = 0; i <= plaintext.size() - n; ++i) {
        vector<char> ngram;
        for (int j = i; j < i + n ; ++j) {
            ngram.push_back(plaintext[j]);
        }
        if (map.find(ngram) == map.end()) {
            map.insert(pair<vector<char>, int>(ngram, 1));
        } else {
            map[ngram]++;
        }
    }
    return map;
}


// returns a map of ngrams and the frequency they appear in plaintext
map<vector<char>, double> GetFrequencyPlaintext(const map<vector<char>, int>& count, int total) {
    map<vector<char>, double> frequency;
    for (auto const& entry : count) {
        frequency.insert(pair<vector<char>, double>(entry.first, entry.second/(total + 0.0)));
    }
    return frequency;
}



int main() {

    clock_t start, end;
    start = clock();


    map<char, vector<int>> key_map = KeyGen();
    PrintMapping(key_map);
    cout << endl;

    srand((unsigned)time(0));
    int plaintextIndex = rand() % 5;
    cout << "The randomly chosen plaintext is p" << plaintextIndex << endl;

    string plaintext = plaintexts[plaintextIndex];
    vector<int> ciphertext = Enc(plaintexts[plaintextIndex], key_map);
//    cout << "Ciphertext is:" << endl;
//    for (int i = 0; i < ciphertext.size(); ++i) {
//        cout << ciphertext[i] << ", ";
//    }

    cout << endl;

    for (int i = 0; i < 5; ++i) {
        if (isValidPlaintext(plaintexts[i], ciphertext)) {
            cout << "p" << i << " is a match" << endl;
        } else {
            cout << "p" << i << " is not a match" << endl;
        }
    }


//    cout << endl << endl << "Plaintext frequency analysis:" << endl;
//    map<vector<char>, int> plaintext_count = GetCountPlaintext(plaintext, 1);
//    for (auto const& entry : plaintext_count) {
//        for (char c : entry.first) {
//            cout << c;
//        }
//        cout << " appears " << entry.second << " times" << endl;
//    }
//
//    cout << endl;

//    map<vector<char>, double> plaintext_freq = GetFrequencyPlaintext(plaintext_count, plaintext.length
//    ());
//    for (auto const& entry : plaintext_freq) {
//        for (char c : entry.first) {
//            cout << c;
//        }
//        cout << " has frequency " << setprecision(10) << entry.second << endl;
//    }

//    cout << endl << "Ciphertext frequency analysis:" << endl;
//
//    map<vector<int>, int> ciphertext_count = GetCountCiphertext(ciphertext, 1);
//    for (auto const& entry : ciphertext_count) {
//        if (entry.second > 2) {
//            for (int i : entry.first) {
//                cout << i << ", ";
//            }
//            cout << " appears " << entry.second << " times" << endl;
//        }
//    }
//
//    cout << endl;
//
//    map<vector<int>, double> ciphertext_freq = GetFrequencyCiphertext(ciphertext_count, plaintext.length
//    ());
//    for (auto const& entry : ciphertext_freq) {
//        for (int i : entry.first) {
//            cout << i << ", ";
//        }
//        cout << " has frequency " << setprecision(10) << entry.second << endl;
//    }




    end = clock();
    double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    cout << "Time taken to run the program is " << fixed << time_taken << setprecision(5) << " "
                                                                                             "seconds" << endl;

    return 0;
}
