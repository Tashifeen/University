// References used throughout:
//   [1] bowbowbow GitHub - https://github.com/bowbowbow/DecisionTree/blob/master/decision_tree.cpp
//   [2] CodeSignal lesson - "Building a Decision Tree from Scratch in C++"
//   [3] Lamotte, H. - "Implementing a Decision Tree from Scratch using C++" (Towards Data Science)
//   [4] AI Assistant (Claude, Anthropic) - used for debugging and explaining new C++ concepts
//   [5] Course lecture notes: CDTREE and C++ Conditions Lesson 08
//   [6] Greedy Best first search algorithm - https://www.geeksforgeeks.org/dsa/greedy-best-first-search-algorithm/

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <queue>
#include <utility>   // for std::pair


/* 1. DATA STRUCTURE
   Each row in the dataset (training.dat/test.dat) has
   10 binary features and a class label
*/

struct DataPoint {
    std::vector<int> features;  // the 10 binary features (0 or 1)
    int label;                  // class label: 0, 1 or 2
};



/* 2. NODE CLASSES
	- This was inspired by the Node structure in [1] and the TreeNode struct in [2].
	- The key difference here is that I'm using two seperate classes (LeafNode and
	  RuleNode) which both inherit from a base Node class, as recommended in
	  the coursework spec. This lets us store both types behind a Node* pointer.
	- Claude [4] explained why the virtual destructor is needed in the base class,
	  and it explained how deleting a derived object through a base pointer
	  causes undefined behaviour (memory leak or crash).
*/
class Node {
public:
    virtual ~Node() {}               // always needed for base classes - [4]
    virtual bool isLeaf() const = 0; // pure virtual forces subclasses to implement
};


/* LeafNode stores which training points have landed here (by index)
// Rather than copying the actual data we just store the row numbers
// and look them up later - idea adapted from [1] */
class LeafNode : public Node {
public:
    std::vector<int> indices;  // indices (row numbers) into the training dataset

    // constructor taking a list of indicies
    LeafNode(std::vector<int> idx) : indices(idx) {}

    bool isLeaf() const override { return true; }
};


/* RuleNode splits on a single binary feature
   If feature == 0, go left. If feature == 1, go right
   Structure loosly inspired by TreeNode in [2] but simplified for binary features */
class RuleNode : public Node {
public:
    int   featureIndex;  // which feature (0-9) this node tests
    Node* left;          // branch for feature value == 0
    Node* right;         // branch for feature value == 1

    RuleNode(int fi, Node* l, Node* r)
        : featureIndex(fi), left(l), right(r) {}

    bool isLeaf() const override { return false; }

    // destructor recursivley deletes children so we only need delete root
    ~RuleNode() {
        delete left;
        delete right;
    }
};



/* 3. SPLIT CANDIDATE
   This struct holds everything I'll need for evaluating a potential split.
   This was easily the trickiest C++ concept for me this whole implementation
   with the double pointers!!! */
struct SplitCandidate {
    double    improvement;  // weighted gini improvement (higher = better)
    int       bestFeature;  // which feature to split on
    LeafNode* leaf;         // the leaf we want to split
    Node**    treeSlot;     // pointer to the Node* slot in the tree that holds this leaf
                            // lets us replace the leaf with a RuleNode in-place

    // comparison operator for the priority queue (max-heap, so higher = first)
    bool operator<(const SplitCandidate& other) const {
        return improvement < other.improvement;
    }
};


/* 4. DATA LOADING
   Reading a file where each line is: f0 f1 f2 ... f9 label */
std::vector<DataPoint> loadData(const std::string& filename) {
    std::vector<DataPoint> dataset;
    std::ifstream file(filename); // File reader in C++ (like 'fopen' in C)

    if (!file.is_open()) {
        std::cerr << "Error: cannot open " << filename << "\n";
        return dataset;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::istringstream ss(line); // Turns that string into a strem to read numbers from
        DataPoint dp;
        int val;

        // read all numbers on the line into a temp vector
        std::vector<int> vals;
        while (ss >> val) vals.push_back(val); // loop pulls ints one at a time until line over

        // last value is the label, everything else is a feature
        dp.label = vals.back(); // get last element
        vals.pop_back(); // remove label, leaving just the features
        dp.features = vals;

        dataset.push_back(dp);
    }

    return dataset;
}


/*
   5. PURITY FUNCTIONS
   
   - Gini impurity measures how mixed the classes are in a set of points
   - Formula: Gini = 1 - sum(pi^2) where pi is proportion of class i
   - A pure node (all one class) gives Gini = 0
   - An equal mix of 3 classes gives Gini ~0.667

   Sources:
   - Understanding came form from Wikipedia on decision trees and the CDTREE lecture [5]
   - The getMajorityLabel function in [1] also informed how I count classes
*/

double gini(const std::vector<int>& indices,
            const std::vector<DataPoint>& data,
            int numClasses = 3) {

    if (indices.empty()) return 0.0;

    // count how many points belong to each class
    std::vector<int> counts(numClasses, 0);
    for (int i : indices)
        counts[data[i].label]++;

    int n = (int)indices.size();
    double impurity = 1.0;
    for (int c = 0; c < numClasses; c++) {
        double p = (double)counts[c] / n;
        impurity -= p * p;  // subtract pi^2 for each class
    }
    return impurity;
}


// Computing weighted gini score of splitting a set of points on one feature
// Returns a score between 0 (perfect split) and ~0.667 (no improvement)
double splitScore(const std::vector<int>& indices,
                  const std::vector<DataPoint>& data,
                  int featureIndex) {

    std::vector<int> leftIdx, rightIdx;
    for (int i : indices) {
        if (data[i].features[featureIndex] == 0)
            leftIdx.push_back(i);
        else
            rightIdx.push_back(i);
    }

    int n = (int)indices.size();

    // weighted average of the two children's gini scores
    double weightedGini =
        ((double)leftIdx.size()  / n) * gini(leftIdx,  data)
      + ((double)rightIdx.size() / n) * gini(rightIdx, data);

    return weightedGini;
}


// Finds the best feature to split on for a given set of points
// Returns the feature index and the improvement in gini
std::pair<int, double> bestSplit(const std::vector<int>& indices,
                                 const std::vector<DataPoint>& data,
                                 int numFeatures = 10) {

    double parentGini      = gini(indices, data);
    double bestImprovement = -1.0;
    int    bestFeature     = 0;

    // try every feature and track the one with most improvement
    for (int f = 0; f < numFeatures; f++) {
        double improvement = parentGini - splitScore(indices, data, f);
        if (improvement > bestImprovement) {
            bestImprovement = improvement;
            bestFeature     = f;
        }
    }

    return {bestFeature, bestImprovement};
}


// Returns the most common class label among a set of training points.
// This is what the leaf predicts. Adapted from create_terminal() in [2]
// which does the same thing but using a map - I used a simpler vector
// since we know theres only 3 classes
int majorityClass(const std::vector<int>& indices,
                  const std::vector<DataPoint>& data,
                  int numClasses = 3) {

    std::vector<int> counts(numClasses, 0);
    for (int i : indices)
        counts[data[i].label]++;

    // finding the class with the highest count
    int bestClass = 0;
    for (int c = 1; c < numClasses; c++)
        if (counts[c] > counts[bestClass])
            bestClass = c;

    return bestClass;
}



/* 6. TREE BUILDING

   Uses a priority queue to greedily pick the best leaf to split next.
   The key insight (from the coursework spec and confirmed by [3]) is that
   I needed to weight the improvement by leaf size - otherwise I end up
   splitting tiny leaves with artificaly high gini scores.

   BUG found during testing: before adding the leaf size weighting, split 8
   was scoring 0.5 because it perfectly separated just 2 points. Claude [4]
   helped identify this by looking at the printed improvement values which
   were not decreasing as expected. */

// Evaluating a leaf and pushes it onto the priority queue if its worth splitting
void evaluateLeaf(LeafNode* leaf,
                  Node**    treeSlot,
                  const std::vector<DataPoint>& data,
                  std::priority_queue<SplitCandidate>& pq) {

    // cant split a single point or empty leaf
    if (leaf->indices.size() <= 1) return;

    auto [bestFeature, improvement] = bestSplit(leaf->indices, data);

    // no point splitting if there is no improvement
    if (improvement <= 0.0) return;

    // multiply by leaf size so big improvements on big leaves beat
    // small improvements on tiny leaves - fix suggested by [4]
    pq.push({improvement * (double)leaf->indices.size(), bestFeature, leaf, treeSlot});
}


// Builds the decision tree using greedy best-first splitting [6]
// Stops after maxSplits rule nodes have been created
Node* buildTree(const std::vector<DataPoint>& data, int maxSplits) {

    // start with one leaf containing all training points
    std::vector<int> allIndices;
    for (int i = 0; i < (int)data.size(); i++)
        allIndices.push_back(i);

    // root starts as a leaf - to be replaced when we make the first split
    Node* root = new LeafNode(allIndices);

    std::priority_queue<SplitCandidate> pq;
    evaluateLeaf((LeafNode*)root, &root, data, pq);

    int splits = 0;
    while (splits < maxSplits && !pq.empty()) {

        // pop the best candidate split
        SplitCandidate best = pq.top();
        pq.pop();

        LeafNode* leaf = best.leaf;
        int feature = best.bestFeature;
        Node** slot = best.treeSlot;

        // split the leaf's data points into left and right groups
        std::vector<int> leftIdx, rightIdx;
        for (int i : leaf->indices) {
            if (data[i].features[feature] == 0)
                leftIdx.push_back(i);
            else
                rightIdx.push_back(i);
        }

        // create the two new leaf nodes
        LeafNode* leftLeaf  = new LeafNode(leftIdx);
        LeafNode* rightLeaf = new LeafNode(rightIdx);

        // replace the old leaf in the tree with a new rule node
        // *slot dereferences the pointer-to-pointer to update the tree in place
        RuleNode* rule = new RuleNode(feature, leftLeaf, rightLeaf);
        *slot = rule;
        delete leaf;  // free the old leaf since RuleNode now owns that slot

        splits++;

        // evaluate the two new leaves and add to queue if worth splitting
        evaluateLeaf(leftLeaf,  &rule->left,  data, pq);
        evaluateLeaf(rightLeaf, &rule->right, data, pq);
    }

    return root;
}


/* 7. PREDICTION

   - Here we walk the tree from root to leaf for a single data point
   - At each rule node check the relevant feature and go left or right
   - At the leaf return the majority class of the training points there
   - This traversal approach is kinda similar to dfs() in [1] but iterative
     rather than recursive so it's simpler and avoids stack overflow on deep trees */

int predict(Node* node,
            const DataPoint& point,
            const std::vector<DataPoint>& trainData) {

    // walk down the tree until we hit a leaf
    while (!node->isLeaf()) {
        RuleNode* rule = (RuleNode*)node;
        if (point.features[rule->featureIndex] == 0)
            node = rule->left;
        else
            node = rule->right;
    }

    // return majority class at this leaf
    LeafNode* leaf = (LeafNode*)node;
    return majorityClass(leaf->indices, trainData);
}


// Calculating accuracy over a dataset (correct predictions / total points)
double accuracy(Node* tree,
                const std::vector<DataPoint>& trainData,
                const std::vector<DataPoint>& testData) {

    int correct = 0;
    for (const DataPoint& dp : testData) {
        int predicted = predict(tree, dp, trainData);
        if (predicted == dp.label)
            correct++;
    }
    return (double)correct / (double)testData.size();
}


// 8. MAIN
// Builds the tree at various split counts and reports accuracy

int main() {
    auto trainData = loadData("training.dat");
    auto testData  = loadData("test.dat");

    std::cout << "Loaded " << trainData.size() << " train, "
              << testData.size()  << " test points\n\n";

    // testing at a range of split counts to see how performance changes
    std::vector<int> splitCounts = {1, 2, 3, 5, 7, 10, 15, 20, 30, 50, 75, 100};

    std::cout << "Splits  |  Train Accuracy  |  Test Accuracy\n";
    std::cout << "--------|-----------------|---------------\n";

    for (int n : splitCounts) {
        Node* tree = buildTree(trainData, n);
        double trainAcc = accuracy(tree, trainData, trainData); // on training set
        double testAcc  = accuracy(tree, trainData, testData);  // on unseen test set
        std::cout << "  " << n << "\t |  " << trainAcc * 100.0
                  << "%\t\t |  " << testAcc * 100.0 << "%\n";
        delete tree;
    }

    return 0;
}



// OLD TEST MAINS - kept here to show the incremental testing process
// Each block was used to verify one stage before moving to the next
// Compile with: g++ -std=c++17 -o dt main.cpp


// TEST 1: Data Loading
// First test written - just checks the file loads correctly and
// prints the first data point to verify parsing worked
/*
int main() {
    auto data = loadData("training.dat");
    std::cout << "Loaded " << data.size() << " data points\n";
    std::cout << "First point features: ";
    for (int f : data[0].features) std::cout << f << " ";
    std::cout << "\nLabel: " << data[0].label << "\n";
    return 0;
}
*/
// Output was:
//   Loaded 1000 data points
//   First point features: 0 1 1 1 0 0 1 1 0 0
//   Label: 2
// Confirmed the file was being read and parsed correctly.


// TEST 2: Node Classes
// Tested that LeafNode and RuleNode could be created and that
// manually splitting on feature 0 gave reasonable left/right sizes
/*
int main() {
    auto data = loadData("training.dat");

    std::vector<int> allIndices;
    for (int i = 0; i < (int)data.size(); i++)
        allIndices.push_back(i);

    LeafNode* root = new LeafNode(allIndices);
    std::cout << "Root leaf holds " << root->indices.size() << " points\n";
    std::cout << "Is leaf? " << root->isLeaf() << "\n";

    // manually split on feature 0 to check the logic works
    std::vector<int> leftIdx, rightIdx;
    for (int i : root->indices) {
        if (data[i].features[0] == 0)
            leftIdx.push_back(i);
        else
            rightIdx.push_back(i);
    }

    Node* tree = new RuleNode(0, new LeafNode(leftIdx), new LeafNode(rightIdx));
    std::cout << "Split on feature 0:\n";
    std::cout << "  Left  leaf: " << leftIdx.size() << " points\n";
    std::cout << "  Right leaf: " << rightIdx.size() << " points\n";
    std::cout << "Is leaf? " << tree->isLeaf() << "\n";

    delete root;
    delete tree;
    return 0;
}
*/
// Output was:
//   Root leaf holds 1000 points
//   Is leaf? 1
//   Split on feature 0:  Left=416  Right=584
//   Is leaf? 0
// Node classes working correctly.


// TEST 3: Gini + bestSplit
// Tested the purity functions before wiring them into the tree builder.
// Wanted to check: root gini should be ~0.667 for 3 balanced classes,
// and bestSplit should identify a sensible first feature.
/*
int main() {
    auto data = loadData("training.dat");

    std::vector<int> allIndices;
    for (int i = 0; i < (int)data.size(); i++)
        allIndices.push_back(i);

    double rootGini = gini(allIndices, data);
    std::cout << "Root Gini: " << rootGini << "\n";

    auto [bestFeature, improvement] = bestSplit(allIndices, data);
    std::cout << "Best first split: feature " << bestFeature << "\n";
    std::cout << "Gini improvement: " << improvement << "\n";

    std::cout << "\nAll feature split scores:\n";
    for (int f = 0; f < 10; f++) {
        double score = splitScore(allIndices, data, f);
        std::cout << "  Feature " << f << ": weighted Gini = " << score << "\n";
    }

    return 0;
}
*/
// Output was:
//   Root Gini: 0.666392   (close to 0.667 as expected for balanced classes)
//   Best first split: feature 4
//   Improvement: 0.0713621
// Feature 4 and feature 1 clearly stood out as the most informative.


// TEST 4: Tree Building (before leaf-size weighting fix)
// This was the version with the bug - improvements were NOT decreasing.
// Kept here to show the debugging process.
// Claude [4] helped spot that split 8 (0.5 improvement on 2 points)
// was clearly wrong - it was more "pure" but completely useless.
/*
int main() {
    auto data = loadData("training.dat");
    Node* tree = buildTree(data, 10);  // at this point evaluateLeaf did NOT
                                       // multiply improvement by leaf size
    delete tree;
    return 0;
}
*/
// Bad output (improvements not decreasing, tiny leaves scoring highest):
//   Split 1: feature 4  improvement 0.0713621  left=408  right=592
//   Split 2: feature 1  improvement 0.0861881  left=312  right=280  <- went UP
//   ...
//   Split 8: feature 3  improvement 0.5  left=1  right=1  <- 0.5 on just 2 points!
//
// Fix: multiply improvement by leaf->indices.size() before pushing to queue.
// After fix improvements correctly decreased from 71.3 down to 2.7 over 10 splits.


// TEST 5: Accuracy (test.dat not found)
// First run of the accuracy sweep - failed because test.dat wasnt in
// the right directory. Kept as a reminder of that debugging step.
/*
int main() {
    auto trainData = loadData("training.dat");
    auto testData  = loadData("test.dat");   // <- gave "Error: cannot open test.dat"

    std::vector<int> splitCounts = {1, 2, 5, 10, 20, 50, 100};
    for (int n : splitCounts) {
        Node* tree = buildTree(trainData, n);
        double acc = accuracy(tree, trainData, testData);
        std::cout << "  " << n << "  |  " << acc * 100.0 << "%\n";
        delete tree;
    }
    return 0;
}
*/
// All results were -nan% because testData was empty (size=0, division by zero).
// Fixed by copying test.dat into the coursework directory.








//---------- PYTHON FILE: verify.py ----------- //
/*
"""Sources:
    - https://scikit-learn.org/stable/modules/generated/sklearn.tree.DecisionTreeClassifier.html
    - https://www.geeksforgeeks.org/machine-learning/building-and-implementing-decision-tree-classifiers-with-scikit-learn-a-comprehensive-guide/
"""

from sklearn.tree import DecisionTreeClassifier
from sklearn.metrics import accuracy_score
import numpy as np

# Loading data
def load_data(filename):
    X, y = [], []
    with open(filename) as f:
        for line in f:
            vals = list(map(int, line.split()))
            X.append(vals[:-1])
            y.append(vals[-1])
    return np.array(X), np.array(y)

X_train, y_train = load_data("training.dat")
X_test,  y_test  = load_data("test.dat")

print(f"Train: {len(X_train)} points, Test: {len(X_test)} points\n")

print(f"{'Splits':<10} {'Train Acc':<15} {'Test Acc'}")
print(f"{'-'*10} {'-'*15} {'-'*10}")

for max_nodes in [2, 3, 4, 6, 8, 11, 16, 21, 31, 51, 76, 101]:
    # max_leaf_nodes = splits + 1
    clf = DecisionTreeClassifier(criterion="gini", max_leaf_nodes=max_nodes)
    clf.fit(X_train, y_train)
    train_acc = accuracy_score(y_train, clf.predict(X_train)) * 100
    test_acc  = accuracy_score(y_test,  clf.predict(X_test))  * 100
    splits = max_nodes - 1
    print(f"  {splits:<8} {train_acc:<15.1f} {test_acc:.1f}%")
*/
