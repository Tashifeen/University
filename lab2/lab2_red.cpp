#include <iostream>
#include <vector>

// for the string& symbol: Take the string by const reference to avoid copying and allow fast read‑only access
int brainfart_red(char std::string& commands) { // i meam u could just write &string instead but techincally this is more effiecent (by very little!)
	std::vector<int> arr(20, 0); // replaces calloc
	int p = 0;

	for (char op : commands) {
		std::cout << op << '\n';

		switch (op) {
			case '+':
                arr[p] += 1;
                break;

            case '-':
                arr[p] -= 1;
                break;

            case '>':
                p = (p == 19) ? 0 : p + 1;
                break;

            case '<':
                p = (p == 0) ? 19 : p - 1;
                break;

            default:
                break;		
		}
	}
	return arr[p]
}

int main() {
	std::cout << "output: "
			  << brainfart_red("+++>--<+<octopus>")
}			  << '\n'; // Should print 4
