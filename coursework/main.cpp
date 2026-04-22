#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

// One row of data
struct DataPoint {
    std::vector<int> features;   // the 10 binary features
    int label;                   // the class: 0, 1, or 2
};

// ── Node classes ─────────────────────────────────────────────

class Node {
public:
    virtual ~Node() {}          // virtual destructor — always needed for base classes
    virtual bool isLeaf() const = 0;  // pure virtual: every subclass must implement this
};

// A leaf holds the indices of data points that have landed here
class LeafNode : public Node {
public:
    std::vector<int> indices;   // which rows from the dataset belong here

    LeafNode(std::vector<int> idx) : indices(idx) {}

    bool isLeaf() const override { return true; }
};

// A rule node splits on one binary feature
class RuleNode : public Node {
public:
    int featureIndex;           // which feature to test (0–9)
    Node* left;                 // feature == 0  → go left
    Node* right;                // feature == 1  → go right

    RuleNode(int fi, Node* l, Node* r)
        : featureIndex(fi), left(l), right(r) {}

    bool isLeaf() const override { return false; }

    ~RuleNode() {               // destructor cleans up children
        delete left;
        delete right;
    }
};

// Load data from a file
std::vector<DataPoint> loadData(const std::string& filename) {
    std::vector<DataPoint> dataset;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: cannot open " << filename << "\n";
        return dataset;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::istringstream ss(line);
        DataPoint dp;
        int val;

        // Read all integers on the line
        std::vector<int> vals;
        while (ss >> val) vals.push_back(val);

        // Last value is the label, rest are features
        dp.label = vals.back();
        vals.pop_back();
        dp.features = vals;

        dataset.push_back(dp);
    }

    return dataset;
}

int main() {
    // Load data
    auto data = loadData("training.dat");
    std::cout << "Loaded " << data.size() << " data points\n";

    // Create a leaf with ALL data point indices (0, 1, 2, ... 999)
    std::vector<int> allIndices;
    for (int i = 0; i < (int)data.size(); i++)
        allIndices.push_back(i);

    LeafNode* root = new LeafNode(allIndices);

    std::cout << "Root leaf holds " << root->indices.size() << " points\n";
    std::cout << "Is leaf? " << root->isLeaf() << "\n";

    // Manually split on feature 0:
    //   left  → feature[0] == 0
    //   right → feature[0] == 1
    std::vector<int> leftIdx, rightIdx;
    for (int i : root->indices) {
        if (data[i].features[0] == 0)
            leftIdx.push_back(i);
        else
            rightIdx.push_back(i);
    }

    // Build a rule node replacing the root
    Node* tree = new RuleNode(0, new LeafNode(leftIdx), new LeafNode(rightIdx));

    std::cout << "Split on feature 0:\n";
    std::cout << "  Left  leaf: " << leftIdx.size() << " points\n";
    std::cout << "  Right leaf: " << rightIdx.size() << " points\n";
    std::cout << "Is leaf? " << tree->isLeaf() << "\n";

    delete root;
    delete tree;
    return 0;
}
