#include <unordered_map>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

template<typename T1, typename T2>
unordered_map<T1, T2> swag(vector<pair<T1, T2>> in, int op) {

	// Step 1: group values by key
	unordered_map<T1, vector<T2>> groups;

	for (const auto& p : in) {
		groups[p.first].push_back(p.second);
	}

	// Step 2: compute the required mean per key
	unordered_map<T1, T2> result;

	for (auto& entry : groups) {
	    const T1& key = entry.first;
	    vector<T2>& vals = entry.second;   // <-- FIXED (no const)
	
	    sort(vals.begin(), vals.end());
	
	    T2 answer = T2();
	    int n = vals.size();
	
	    if (op == 0) {
	        for (const auto& x : vals) answer += x;
	    }
	    else if (op == 1) {
	        answer = vals.front();
	    }
	    else if (op == 2) {
	        int idx = (n % 2 == 1) ? (n / 2) : (n / 2 - 1);
	        answer = vals[idx];
	    }
	    else if (op == 3) {
	        answer = vals.back();
	    }
	
	    result[key] = answer;
	}
	return result;
}
