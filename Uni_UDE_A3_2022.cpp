#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>
using namespace std;

const int binary_size = 10;

struct BinaryNumber 
{
    bool bits[binary_size];
};

istream& operator>>(istream& input, BinaryNumber &binary) 
{
    for (int i = 0; i < binary_size; i++) 
    {
        char bit;
        input >> bit;
        binary.bits[i] = (bit == '1');
    }
    return input;
}

ostream& operator<<(ostream& output, BinaryNumber& binary) 
{
    for (int i = 0; i < binary_size; i++) 
    {
        output << binary.bits[i];
    }
    return output;
}

BinaryNumber operator!(const BinaryNumber& binary) 
{
    BinaryNumber result;
    for (int i = 0; i < binary_size; i++) 
    {
        result.bits[i] = !binary.bits[i];
    }
    return result;
}

bool operator==(const BinaryNumber& a, const BinaryNumber& b) 
{
    for (int i = 0; i < binary_size; i++) 
    {
        if (a.bits[i] != b.bits[i]) 
        {
            return false;
        }
    }
    return true;
}

bool operator!=(const BinaryNumber& a, const BinaryNumber& b) 
{
    for (int i = 0; i < binary_size; i++) 
    {
        if (a.bits[i] != b.bits[i]) {
            return true;
        }
    }
    return false;
}

BinaryNumber operator+(const BinaryNumber& a, const BinaryNumber& b) 
{
    BinaryNumber result;
    bool carry = false;

    for (int i = binary_size - 1; i >= 0; i--) {
        result.bits[i] = (a.bits[i] ^ b.bits[i]) ^ carry;
        carry = (a.bits[i] && b.bits[i]) || (carry && (a.bits[i] || b.bits[i]));
    }
    return result;
}

BinaryNumber operator-(const BinaryNumber& a, const BinaryNumber& b) 
{
    BinaryNumber result;
    bool borrow = true;

    for (int i = binary_size - 1; i >= 0; i--) 
    {
        bool diff = a.bits[i] ^ b.bits[i];
        result.bits[i] = diff ^ borrow;
        borrow = (borrow && (b.bits[i] || !diff)) || (!a.bits[i] && b.bits[i]);
    }
    return result;
}

BinaryNumber operator-(const BinaryNumber& x) 
{
    BinaryNumber result;
    for (int i = 0; i < binary_size; i++) 
    {
        result.bits[i] = -x.bits[i];
    }
    return result;
}

BinaryNumber operator++(const BinaryNumber& x) 
{
    BinaryNumber increment = {false, false, false, false, false, false, false, false, true};
    return operator+(x, increment);
}

int binaryToDecimal(const BinaryNumber& x) 
{
    int sum = 0, power = 0;
    for (int i = binary_size - 1; i >= 0; i--) 
    {
        int bit = x.bits[i];
        sum += (pow(2, power) * bit);
        power++;
    }
    return sum;
}

BinaryNumber leftShift(const BinaryNumber& x, int k) 
{
    BinaryNumber result;
    for (int i = binary_size - 1; i - k >= 0; i--) 
    {
        result.bits[i - k] = x.bits[i];
    }
    return result;
}

int main() 
{
    BinaryNumber a, b, result;
    BinaryNumber increment = {false, false, false, false, false, false, false, false, true};
    int shift_amount;
    bool are_equal, are_not_equal;

    // Initialize binary numbers
    for (int i = 0; i < binary_size; i++) 
    {
        a.bits[i] = false;
        b.bits[i] = false;
        result.bits[i] = false;
    }

    while (true) 
    {
        cout << right << setw(10) << "a = " << left << a << " (" << binaryToDecimal(a) << ")" << endl;
        cout << right << setw(10) << "b = " << left << b << " (" << binaryToDecimal(b) << ")" << endl;
        cout << right << setw(10) << "result = " << left << result << " (" << binaryToDecimal(result) << ")" << endl;
        cout << "q      quit\n" << "a      input a\n" << "b      input b\n" << "va, vb value of result copied to a, b\n"
             << "!a, !b bitwise negation\n" << "ma, mb unary minus -a, -b\n" << "+      binary addition a+b\n"
             << "-      binary subtraction a-b\n" << "e      equality check a == b\n" << "u      inequality check a != b\n"
             << "na, nb is_negative(a), is_negative(b)?\n" << "za, zb is_zero(a), is_zero(b)?\n" << "ia, ib   pre-increment operator ++a, ++b\n"
             << "lak, lbk left shift operator a << k, b << k\n";
        string choice;
        cin >> choice;

        if (choice.size() == 1) 
        {
            switch (choice[0]) 
            {
                case 'q':
                    exit(0);
                    break;
                case 'a':
                    cout << "Enter a binary number of length " << binary_size << " for a:" << endl;
                    cin >> a;
                    break;
                case 'b':
                    cout << "Enter a binary number of length " << binary_size << " for b:" << endl;
                    cin >> b;
                    break;
                case '+':
                    result = operator+(a, b);
                    break;
                case '-':
                    result = operator-(a, b);
                    break;
                case 'e':
                    are_equal = operator==(a, b);
                    cout << "a == b returns " << are_equal << endl;
                    break;
                case 'u':
                    are_not_equal = operator!=(a, b);
                    cout << "a != b returns " << are_not_equal << endl;
                    break;
            }
        } 
        else if (choice == "va") 
        {
            result = a;
        } 
        else if (choice == "vb") 
        {
            b = result;
        } 
        else if (choice == "ma") 
        {
            result = operator+(operator!(a), increment);
        } 
        else if (choice == "mb") 
        {
            result = operator+(operator!(b), increment);
        } 
        else if (choice == "!a") 
        {
            result = operator!(a);
        } 
        else if (choice == "!b") 
        {
            result = operator!(b);
        } 
        else if (choice == "za") 
        {
            bool is_zero = true;
            for (int i = 0; i < binary_size; i++)
             {
                if (a.bits[i] == 1) 
                {
                    is_zero = false;
                    break;
                }
            }
            cout << "is_zero? " << is_zero << endl;
        } 
        else if (choice == "zb") 
        {
            bool is_zero = true;
            for (int i = 0; i < binary_size; i++) 
            {
                if (b.bits[i] == 1) 
                {
                    is_zero = false;
                    break;
                }
            }
            cout << "is_zero? " << is_zero << endl;
        } 
        else if (choice == "na") 
        {
            bool is_negative = (a.bits[binary_size - 1] == 1);
            cout << "is negative? " << is_negative << endl;
        } 
        else if (choice == "nb") 
        {
            bool is_negative = (b.bits[binary_size - 1] == 1);
            cout << "is negative? " << is_negative << endl;
        } 
        else if (choice == "ia") 
        {
            a = operator++(a);
        } 
        else if (choice == "ib") 
        {
            b = operator++(b);
        } 
        else if (choice == "lak") 
        {
            cout << "Enter the shift amount k:" << endl;
            cin >> shift_amount;
            a = leftShift(a, shift_amount);
        } 
        else if (choice == "lbk") 
        {
            cout << "Enter the shift amount k:" << endl;
            cin >> shift_amount;
            b = leftShift(b, shift_amount);
        } 
        else 
        {
            cout << "Enter a valid choice" << endl;
        }
    }
    return 0;
}