#include <iostream>
#include <map>
#include <fstream>
using namespace std;

int main(int argc, char* argv[]) {
  /* Get filename to compress */
  if (argc != 2) {
    cerr << "Usage: " << argv[0] << " <filename>" << endl;
    return 1;
  }
  ifstream file(argv[1]);  // file we are going to compress
  if (!file) {
    cerr << "error: cant open " << argv[1] << endl;
    exit(1);
  }

  /* Count frequency of all characters */
  map<char, int> charCount;  // map used for counting characters in text
  char ch;
  while (file.get(ch)) {
    charCount[ch]++;
  }

  // print out the characters and their frequency
  for(auto& c: charCount) {
    cout << c.first << ": " << c.second << endl;
  }
}
