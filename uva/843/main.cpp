
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <sstream>
#include <vector>

#define MAX_NUM_OF_ENCRYPTED_WORDS 40
#define MAX_WORD_LENGTH 16

/**
 * UVA 843: Crypt kicker
 *
 * Being 'n' the number of alphabet words and
 *   'r' the number of encrypted words
 *
 * Time complexity:
 *   n! / (n - r)! equivalent to [P(n,r)]
 *
 * Space complexity:
 *   n! / (n - r)! equivalent to [P(n,r)]
 * */

using namespace std;

struct word_bimap_t
{
    map<string,string> byAlphabetWord;
    map<string,string> byEncryptedWord;
};

struct letter_bimap_t
{
    map<char,char> byAlphabetLetter;
    map<char,char> byEncryptedLetter;
};

void split(const string& str, string *tokens, unsigned int& size, char delim = ' ')
{
    stringstream ss(str);
    std::string token;
    size = 0;
    while (std::getline(ss, token, delim)) {
        tokens[size++] = token;
    }
}

void groupWordsByLength(const string *words, unsigned int numberOfWords, map<int, set<string> >& wordsByLength)
{
    for (int i = 0; i < numberOfWords; i++)
        wordsByLength[words[i].size()].insert(words[i]);
}

bool matchWords(string alphabetWord, string encryptedWord,
    word_bimap_t& wordBimap, letter_bimap_t& letterBimap)
{
    for (int i = 0; i < encryptedWord.size(); i++)
    {
        char alphabetLetter = alphabetWord[i];
        char encryptedLetter = encryptedWord[i];
        if ((letterBimap.byEncryptedLetter[encryptedLetter] != '\0'
                && letterBimap.byEncryptedLetter[encryptedLetter] != alphabetLetter)
            || (letterBimap.byAlphabetLetter[alphabetLetter] != '\0'
                && letterBimap.byAlphabetLetter[alphabetLetter] != encryptedLetter)) {
            return false;
        } else {
            letterBimap.byEncryptedLetter[encryptedLetter] = alphabetLetter;
            letterBimap.byAlphabetLetter[alphabetLetter] = encryptedLetter;
        }
    }
    wordBimap.byAlphabetWord[alphabetWord] = encryptedWord;
    wordBimap.byEncryptedWord[encryptedWord] = alphabetWord;
    return true;
}

bool validateObviousCases(map<int, set<string> >& alphabetWordsByLength,
    map<int, set<string> >& encryptedWordsByLength,
    word_bimap_t& wordBimap, letter_bimap_t& letterBimap)
{
    for (int i = MAX_WORD_LENGTH; i > 0; i--)
    {
        set<string> encryptedWords = encryptedWordsByLength[i];
        if (encryptedWords.size() > 0)
        {
            set<string> alphabetWords = alphabetWordsByLength[i];
            if (encryptedWords.size() > alphabetWords.size())
            {
                // undecryptable text
                return false;
            } else if (alphabetWords.size() == 1)
            {
                bool wordsMatch = matchWords(*(alphabetWords.begin()),
                    *(encryptedWords.begin()), wordBimap, letterBimap);
                if (!wordsMatch)
                {
                    return false;
                } else
                {
                    encryptedWordsByLength[i].erase(encryptedWordsByLength[i].begin());
                    alphabetWordsByLength[i].erase(alphabetWordsByLength[i].begin());
                }
            }
        }
    }
    return true;
}

string decodeTextUsing(const string& encryptedText,
    letter_bimap_t letterBimap){
    string decodedText = "";
    for (int i = 0; i < encryptedText.size(); i++)
    {
        if (encryptedText[i] != ' ')
        {
            decodedText += letterBimap.byEncryptedLetter[encryptedText[i]];
        } else
        {
            decodedText += ' ';
        }
    }
    return decodedText;
}

string decodeTextUsing(const string& encryptedText, char character){
    string decodedText = "";
    for (int i = 0; i < encryptedText.size(); i++)
    {
        if (encryptedText[i] != ' ')
        {
            decodedText += character;
        } else
        {
            decodedText += ' ';
        }
    }
    return decodedText;
}

bool decryptTextGuessing(map<int, set<string> >& alphabetWordsByLength,
    map<int, set<string> >& encryptedWordsByLength,
    word_bimap_t* wordBimap, letter_bimap_t* letterBimap,
    unsigned int currentWordSize)
{
    bool undecryptable = false;
    for (int i = currentWordSize; i > 0 && !undecryptable; i--)
    {
        if (encryptedWordsByLength[i].size() > 0)
        {
            for (set<string>::iterator enc_it=encryptedWordsByLength[i].begin(); enc_it!=encryptedWordsByLength[i].end(); ++enc_it)
            {
                string nextEncryptedWordTry = *enc_it;
                for (set<string>::iterator alp_it=alphabetWordsByLength[i].begin();
                    alp_it!=alphabetWordsByLength[i].end() && wordBimap->byEncryptedWord[nextEncryptedWordTry] == "";
                    ++alp_it)
                {
                    string nextAlphabetTry = *alp_it;
                    if (wordBimap->byAlphabetWord[nextAlphabetTry] == "")
                    {
                        word_bimap_t wordBimapCopy = *wordBimap;
                        letter_bimap_t letterBimapCopy = *letterBimap;
                        bool successfulPartialDecryption = matchWords(nextAlphabetTry, nextEncryptedWordTry, wordBimapCopy, letterBimapCopy);

                        undecryptable = !successfulPartialDecryption || !decryptTextGuessing(alphabetWordsByLength,
                            encryptedWordsByLength, &wordBimapCopy, &letterBimapCopy, i);

                        if (!undecryptable)
                        {
                            *wordBimap = wordBimapCopy;
                            *letterBimap = letterBimapCopy;
                            return true;
                        }
                    }
                }
            }
        }
    }
    return !undecryptable;
}

string decryptText(map<int, set<string> > alphabetWordsByLength,
    const string& encryptedText)
{
    string encryptedWords[MAX_NUM_OF_ENCRYPTED_WORDS];
    unsigned int encryptedWordsSize = 0;

    // separate the encrypted text into words
    split(encryptedText, encryptedWords, encryptedWordsSize);

    map<int, set<string> > encryptedWordsByLength;

    // group the encrypted words by its length
    groupWordsByLength(encryptedWords, encryptedWordsSize, encryptedWordsByLength);

    word_bimap_t wordBimap;
    letter_bimap_t letterBimap;

    bool undecryptable = !validateObviousCases(alphabetWordsByLength,
        encryptedWordsByLength, wordBimap, letterBimap);

    bool solutionFound = !undecryptable && decryptTextGuessing(alphabetWordsByLength,
        encryptedWordsByLength, &wordBimap, &letterBimap, MAX_WORD_LENGTH);

    if (!solutionFound) {
        return decodeTextUsing(encryptedText, '*');
    }

    return decodeTextUsing(encryptedText, letterBimap);
}

int main()
{
    unsigned int alphabetSize;

    cin >> alphabetSize;

    string alphabet[alphabetSize];
    for (int i = 0; i < alphabetSize; i++)
    {
        cin >> alphabet[i];
    }

    map<int, set<string> > alphabetWordsByLength;

    // group the alphabet words by its length
    groupWordsByLength(alphabet, alphabetSize, alphabetWordsByLength);

    string encryptedText;
    string decryptedText;

    // read end of line, no used at all
    getline(cin, encryptedText);

    while (getline(cin, encryptedText)) {
        decryptedText = decryptText(alphabetWordsByLength,
            encryptedText);
        cout << decryptedText << endl;
    }
    return 0;
}
