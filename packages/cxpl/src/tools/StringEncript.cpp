// Verification of http://www.cnblogs.com/atyuwen/archive/2012/02/19/impossible_codification.html
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

string XOREncode(string &str)
{
	unsigned char x = 0, px = 1;
	bool is_odd = (str.length() % 2 != 0);
    while (px != x)
	{
        px = x;
        x = 0;
        for (const auto &c : str) x += px ^ static_cast<unsigned char>(c);
		if (is_odd) x += px;
    }
	size_t len = (is_odd ? str.length() + 1 : str.length());
	string code(len, 0);
    for (size_t i = 0; i < str.length(); i++) code[i] = str[i] ^ x;
    if (is_odd) code[len - 1] = static_cast<char>(x);
	return code;
}
string XORDecode(string &code)
{
	string str(code.length(), 0);
	unsigned char x = 0;
    for (const auto &i : code) x += static_cast<unsigned char>(i);
    for (size_t i = 0; i < code.length(); i++) str[i] = static_cast<char>(code[i] ^ x);
	return str;
}
int main()
{
    string str("And then there were none.");
    cout << "Original String: " << str << endl;

	string code = XOREncode(str);
    cout << "Encoded String: " << hex << setfill('0') << setw(2);
    for (const auto &i : code) cout << int(static_cast<unsigned char>(i)) << ' ';
	cout << endl;

	string decode = XORDecode(code);
    cout << "Decoded String: " << decode << endl;

    return 0;
}
