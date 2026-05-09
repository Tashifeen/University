#include <iostream>
#include <fstream>
#include <map>
#include <queue>
#include <vector>
#include <string>

using namespace std;

/* Abstract base class */
class HuffmanTree {
protected:
    unsigned occurrence_frequency;

public:
    int occurrence() const {
        return occurrence_frequency;
    }

    virtual void extractCodes(map<char, string>& codeMap,
                              string codeString) const = 0;

    virtual HuffmanTree* decode(char ch) = 0;

    virtual bool is_leaf() const = 0;

    virtual char symbol() const = 0;

    virtual ~HuffmanTree() {}
};

/* Leaf node */
class HuffmanTreeLeaf : public HuffmanTree {
private:
    char character;

public:
    HuffmanTreeLeaf(char ch, int occ) {
        character = ch;
        occurrence_frequency = occ;
    }

    void extractCodes(map<char, string>& codeMap,
                      string codeString) const override {
        codeMap[character] = codeString;
    }

    HuffmanTree* decode(char ch) override {
        return this;
    }

    bool is_leaf() const override {
        return true;
    }

    char symbol() const override {
        return character;
    }
};

/* Non-leaf node */
class HuffmanTreeNode : public HuffmanTree {
private:
    HuffmanTree* left_child;
    HuffmanTree* right_child;

public:
    HuffmanTreeNode(HuffmanTree* left,
                    HuffmanTree* right) {
        left_child = left;
        right_child = right;

        occurrence_frequency =
            left->occurrence() + right->occurrence();
    }

    void extractCodes(map<char, string>& codeMap,
                      string codeString) const override {

        left_child->extractCodes(codeMap, codeString + "0");
        right_child->extractCodes(codeMap, codeString + "1");
    }

    HuffmanTree* decode(char ch) override {
        if (ch == '0')
            return left_child;
        else
            return right_child;
    }

    bool is_leaf() const override {
        return false;
    }

    char symbol() const override {
        return '\0';
    }
};

/* Comparison class for priority queue */
class CompareHuffman {
public:
    bool operator()(HuffmanTree* ht1,
                    HuffmanTree* ht2) {

        return ht1->occurrence() > ht2->occurrence();
    }
};

int main() {

    string filename = "input.txt";

    ifstream file(filename);

    if (!file) {
        cout << "Could not open file\n";
        return 1;
    }

    /* Count character occurrences */
    map<char, int> charCount;

    char ch;

    while (file.get(ch)) {
        charCount[ch]++;
    }

    /* Priority queue */
    priority_queue<
        HuffmanTree*,
        vector<HuffmanTree*>,
        CompareHuffman
    > pq;

    /* Create leaf nodes */
    for (auto& pair : charCount) {
        pq.push(new HuffmanTreeLeaf(pair.first,
                                    pair.second));
    }

    /* Build Huffman tree */
    while (pq.size() > 1) {

        HuffmanTree* left = pq.top();
        pq.pop();

        HuffmanTree* right = pq.top();
        pq.pop();

        HuffmanTree* parent =
            new HuffmanTreeNode(left, right);

        pq.push(parent);
    }

    HuffmanTree* root = pq.top();

    /* Extract codes */
    map<char, string> codeMap;

    root->extractCodes(codeMap, "");

    /* Print codes */
    cout << "Huffman Encoding\n";

    for (auto& code : codeMap) {

        if (code.first == '\n')
            cout << "\\n";
        else
            cout << code.first;

        cout << " : "
             << code.second
             << endl;
    }

    cout << "---------------------\n";

    /* Encode file */
    file.clear();
    file.seekg(0);

    string encoded_text_filename = "encoded_text.txt";

    ofstream encoded_file(encoded_text_filename);

    int length = 0;

    while (file.get(ch)) {

        string code = codeMap[ch];

        encoded_file << code;

        length += code.size();
    }

    encoded_file.close();

    cout << "Length of encoding = "
         << length / 8
         << " bytes\n";

    cout << "---------------------\n";

    /* Decode file */
    ifstream in_file(encoded_text_filename);

    ofstream decompressed_file("decompressed_text.txt");

    HuffmanTree* decoder = root;

    while (in_file.get(ch)) {

        decoder = decoder->decode(ch);

        if (decoder->is_leaf()) {

            decompressed_file
                << decoder->symbol();

            decoder = root;
        }
    }

    in_file.close();
    decompressed_file.close();

    cout << "Decoding complete\n";

    return 0;
}
