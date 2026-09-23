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
