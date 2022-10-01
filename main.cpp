#include <iostream>

using namespace std;

int main() {
    int n;

    cout << "Introduce-ti numarul de repetitii" << endl;
    cin >> n;

    for (int i = 0; i <= n; ++i) {
        cout << i << ": " << "Hello, World!" << endl;
    }

    return 0;
}
