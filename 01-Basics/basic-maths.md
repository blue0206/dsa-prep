# Basic Maths

## Extract Digit

- $num\%10$ gives us the digit at ones place.  
- $num/10$ removes the digit at ones place and gives the remaining number.

For example,
```c++
int num = 1654;
cout << num % 10 << endl; // 4
cout << num / 10 << endl; // 165
```

## Reverse Number

$reverseNumber = (reverseNumber * 10) + lastDigit$


## Armstrong Number

The number the sum of the *power* of each of whose digits is the same as the number itself is called an armstrong number (with the *power* being the number of digits in that number), i.e.,  
1634 = $1^4 + 6^4 + 3^4 + 4^4 = 1634$

## Divisors

The divisors of 16 are 1, 2, 4, 8, 16.

1. Brute-force approach is to loop till 16 and check remainder == 0.
2. Optimal approach is to loop till `sqrt(16)`, check remainder == 0 and print the factor and number itself. For example:

1 x 16 = 16
2 x 8 = 16
4 x 4 = 16
8 x 2 = 16
16 x 1 = 16

Here, we only need check till 4 and then just print number itself and the other factor.

```c++
void fn(int n)
{
    vector<int> v;

    for (int i = 1; i*i <= n; i++)
    {
        if (n % i == 0)
        {
            v.push_back(i);
            if (i != n / i)
                v.push_back(n / i);
        }
    }
    sort(v.begin(), v.end());

    cout << n << ": [ ";
    for (auto i : v)
    {
        if (i == n)
            cout << i << " ]" << endl;
        else
            cout << i << ", ";
    }
}
```

## Prime Numbers

- Exactly 2 factors: 1 and itself. For example, 11.

1. Loop from 2 till $(n-1)$, if at any time you get remainder of 0, then the number is not prime. $O(N)$ 
2. Loop from 2 till $sqrt(n)$, and same as approach 1. $O(sqrt(n))$ 

## GCD | HCF

- The greatest number that is a factor of 2 numbers. For example, the GCD/HCF of 9 and 12 is 3.
- The GCD/HCF of two prime numbers is always 1.

## Euclidean Algorithm

#### $gcd(a,b) = gcd(a-b, b)$ where $a > b$ 

*This method is not optimised.*

## Optimised Method for Calculating GCD

#### $gcd(a, b) = gcd(a\%b, b)$ where $a > b$

- In short, we go $greater \% smaller$ until one of them is 0. The non-zero would be the GCD.
- $O(log_ϕ (min(a,b)))$ 

```c++
void fn(int n1, int n2)
{
    int gcd = 1;
    int num1 = n1;
    int num2 = n2;

    while (num1 > 0 && num2 > 0)
    {
        if (num1 > num2)
        {
            num1 = num1 % num2;
        }
        else
        {
            num2 = num2 % num1;
        }
    }

    if (num1)
        gcd = num1;
    else
        gcd = num2;

    cout << "The GCD of " << n1 << " and " << n2 << " is " << gcd << endl;
}
```
