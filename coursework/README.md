# Decision Tree Coursework

## Summary
For this project, I implemented a full decision tree classifier in C++. The system reads binary feature data, builds a greedy best‑first decision tree using Gini impurity, and predicts class labels for unseen data. I designed the full architecture myself, including data structures, node classes, split evaluation, tree construction, prediction, and accuracy measurement.

The implementation uses a priority queue to select the best leaf to split, weighting impurity improvements by leaf size to avoid misleading splits. I built a polymorphic node system (Node, LeafNode, RuleNode), implemented Gini impurity and CART scoring, and handled memory management manually through destructors and pointer‑to‑pointer tree updates.

I tested performance across different split limits and analysed overfitting behaviour. To verify correctness, I compared my C++ results against scikit‑learn’s DecisionTreeClassifier using the same dataset. The outputs matched to within 0.1 percent across all split counts.

This project strengthened my skills in C++, algorithms, data structures, memory management, and implementing machine learning models from first principles.
 
## Files
 
### Source Code
- `main.cpp` - Decision Tree classifier implementation
- `verify.py` - Scikit-learn implementation used to verify results
 
### Data Files
- `training.dat` - Training dataset
- `test.dat` - Test dataset
 
## Features
 
- Loads training and test datasets
- Builds a binary Decision Tree for classification
- Uses Gini impurity to evaluate splits
- Supports three output classes
- Uses a priority queue to greedily select the best leaf to split
- Predicts class labels for unseen data
- Measures training and test accuracy
- Evaluates performance for different tree sizes
 
## Testing
 
The implementation was tested incrementally by:
 
- Verifying dataset loading
- Testing leaf and rule node creation
- Validating Gini impurity calculations
- Verifying feature selection and split quality
- Testing tree construction
- Evaluating classification accuracy
 
A separate Python implementation using Scikit-learn (`verify.py`) was used to compare results and verify correctness.
 
## Building
 
Compile using:
 
```bash
g++ -std=c++17 -O2 main.cpp -o decision_tree
```
 
Run using:
 
```bash
./decision_tree
```
 
## Verification
 
Run the Scikit-learn comparison:
 
```bash
python3 verify.py
```
 
## References
 
- Decision Tree implementation examples and tutorials
- Course lecture notes
- Scikit-learn documentation
- GeeksforGeeks articles on decision trees and greedy search
- AI-assisted debugging and explanation of C++ concepts
 
## Notes
 
- Written in C++17.
- Uses STL containers including `vector`, `priority_queue`, and `pair`.
- Implements a custom binary tree structure using inheritance (`Node`, `LeafNode`, and `RuleNode`).
- Includes extensive testing and debugging comments documenting the development process.
