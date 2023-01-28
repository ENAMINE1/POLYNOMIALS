#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef struct Polyn_
{
    double coff;
    int power;
    struct Polyn_ *next;
} Polyn;

void printlist(Polyn *p1)
{
    Polyn *r = p1;
    if (r == NULL)
    {
        cout << "NO terms in the polynomial!!" << endl
             << "Add few terms to the polynomial to see them." << endl
             << endl;
    }

    while (r != NULL)
    {
        if (r->power != 0)
        {
            cout << setprecision(1) << fixed << r->coff << "x^" << r->power;
        }
        else
        {
            cout << setprecision(1) << fixed << r->coff;
        }

        r = r->next;
        if (r != NULL)
        {
            cout << " + ";
        }
    }
}

// function to add a term in the the polynomial
Polyn *addremoveterm(Polyn *p1, int d, double c)
{
    int flag = 0;
    // searching for a particular power in the polynomial
    // if available then just add the new cofficient to the previous one
    {
        Polyn *p = p1;
        while (p != NULL)
        {
            if (p->power == d)
            {
                flag = 1;
                p->coff += c;
                break;
            }
            p = p->next;
        }
    }
    // inserting the element at the desired postion
    if (flag != 1)
    {
        // creating a new node for that particular term
        Polyn *p, *q, *n;
        n = (Polyn *)malloc(sizeof(Polyn));
        // then we populate the node
        n->coff = c;
        n->power = d;
        n->next = NULL;
        // then we check for the number just greator than the input given by the user
        p = p1;
        q = p;
        while (p != NULL)
        {
            if (p->power > n->power) // the number just greator than user input data
            {
                if (p == p1)
                {
                    // inserting the node at the begining of the list as the number enered by user is the smalleest of all
                    n->next = p1;
                    return n;
                }
                else
                {
                    // inserting the node somewhere in the middle of the list
                    q->next = n;
                    n->next = p;
                    return p1;
                }
            }
            // we traverse through the list to find the number greator than the user input

            // we assign the address of the previous node of p to q each time we iterate
            q = p;
            // we update the argument of while loop so that we can traverse through the list
            p = p->next;
        }
        // if an empty list has been passed then we return the pointer tho the new node that we have created
        if (p1 == NULL)
        {
            return n;
        }
        // also a case is possible that the number the user has entered is greatest of all number in the list so we need to add this node at the last of the list
        else
        {
            q->next = n;
        }
    }
    return p1;
}

Polyn *scan(Polyn *header)
{
    int n;
    printf("Enter how many terms you want to add to the Polynomial : ");
    cin >> n;
    if (n > 0)
    {
        double coff;
        int power;
        cout << "Enter the term you want to add in the polynomial as Follows - Enter the coefficient and power of the term separately!!!\n";
        for (int i = 0; i < n; i++)
        {
            cin >> coff >> power;
            header = addremoveterm(header, power, coff);
        }
    }
    else
    {
        cout << "No terms were added!";
    }

    return header;
}

// function to remove terms of degree d
Polyn *addremoveterm(Polyn *p1, int d)
{
    // searching the link list for the degree d
    Polyn *r = p1, *previous = r;
    while (r != NULL)
    {
        if (r->power == d)
        {
            if (r == p1)
            {
                previous = r->next;
                free(r);
                return previous;
            }
            else
            {
                previous->next = r->next;
                free(r);
                return p1;
            }
        }
        previous = r;
        r = r->next;
    }
    cout << "NO such element found in the polynomial with the degree " << d << endl;
    return p1;
}

// function to remove terms with absolute coefficients values less than epsilon
//  this functio takes O(n) time as it has to traverse the whole linklist to compare the absolute values of the coefficient with epsilon
Polyn *addremoveterm(Polyn *p1, int d, int c, int epsilon = 10 ^ (-9))
{
    Polyn *r = p1, *pre = r;
    while (r != NULL)
    {
        if (abs(r->coff) < epsilon)
        {
            if (r == p1)
            {
                pre = r->next;
                p1 = pre;
                free(r);
            }
            else
            {
                pre->next = r->next;
                free(r);
            }
        }
        pre = r;
        r = r->next;
    }
    return p1;
}

// function to evaluate the value of the polynomial at a given value of the variable
double evaluate(Polyn *p1, double x)
{
    double sum = 0;
    Polyn *r = p1;
    while (r != NULL)
    {
        sum += r->coff * pow(x, r->power);
        r = r->next;
    }
    return sum;
}

// adding two polynomials
Polyn *add(Polyn *p1, Polyn *p2)
{
    Polyn *r1 = p1, *r2 = p2, *r = NULL;
    while (r1 != NULL)
    {
        r = addremoveterm(r, r1->power, r1->coff);
        r1 = r1->next;
    }
    while (r2 != NULL)
    {
        r = addremoveterm(r, r2->power, r2->coff);
        r2 = r2->next;
    }
    return r;
}

// utility function to calculate the derivative of a polynomial
Polyn *derivative(Polyn *p1)
{
    Polyn *r1 = p1, *r = NULL;
    while (r1 != NULL)
    {
        if (r1->power != 0)
        {
            r = addremoveterm(r, r1->power - 1, r1->coff * r1->power);
        }

        r1 = r1->next;
    }
    return r;
}

// utility function to find a root of a poylnomial using newtons method
void zero_newton(Polyn *p1, double x0, int epsilon = 10 ^ (-9))
{
    double x = x0;
    double y = evaluate(p1, x);
    double y_p = evaluate(derivative(p1), x);
    double x1;
    for (int i = 0; i < 500; i++)
    {
        if (y_p < epsilon)
        {
            break;
        }

        x1 = x - y / y_p;
        x = x1;
        y = evaluate(p1, x);
        y_p = evaluate(derivative(p1), x);
    }
    cout << "\nThe polynomial is : ";
    printlist(p1);
    cout << "\nOne of the roots of the polynomial is " << x << endl;
}

int main()
{    /********************************************************************************************/
    Polyn *z = NULL, *sum, *y = NULL;
    vector<Polyn *> v;
here:
    cout << endl
         << "FUNCTIONS!!" << endl
         << "1 :: Create A Polynomial." << endl
         << "2 :: Choose a Polynomial." << endl
         << "3 :: Add two Polynomials." << endl
         << "4 :: Display All Polynomials." << endl
         << "5 :: Exit Program." << endl;
    int a;
    cin >> a;
    if (a <= 5)
    {
        int b = 0;
        double answer;
        int choose;
        switch (a)
        {
        case 2:
            if (v.size() != 0)
            {
                int r;
                for (int i = 1; i <= v.size(); i++)
                {
                    cout << i << " :: "
                         << "P" << i <<" : ";
                    printlist(v[i-1]);
                    cout << endl;
                    r = i;
                }
                cin >> choose;
                cout << "Polynomial p" << choose << " chosen!" << endl;
                z = v[choose - 1];
                printlist(z);
                cout << endl;
                goto here2;
            }
            else
            {
                cout << endl
                     << "First create a Polynomial!" << endl;
                goto here;
            }

            break;

        case 1:
            z = NULL;
            z = scan(z);
            cout << "Your Polynomial is : ";
            printlist(z);
            cout << endl
                 << endl;
            v.push_back(z);
            z = NULL;
            goto here;
            break;
            // v.push_back(NULL);
        case 3:
            for (int i = 0; i < v.size(); i++)
            {
                cout << i + 1 << " :: "
                     << "p" << i + 1 << " :: ";
                printlist(v[i]);
                cout << endl;
            }
            cout << "Choose two Polynomials that you want to Add!" << endl;
            int aa, bb;
            cin >> aa >> bb;
            v.push_back(add(v[aa - 1], v[bb - 1]));
            printlist(v.back());
            goto here;
            break;
        case 4:
            if (v.size() != 0)
            {
                for (int i = 0; i < v.size(); i++)
                {
                    cout << "P" << i + 1 << " :: ";
                    printlist(v[i]);
                    cout << endl;
                }
            }
            else
            {
                cout << "No Polynomials to Display!!";
            }

            goto here;
            break;
        case 5:
            cout << "Program Exited!!!";
            return 0;
            break;
        default:
            break;
        }
    here2:

        while (b != 1)
        {
            cout << endl
                 << "1 :: Go back to Previous commands." << endl
                 << "2 :: Add terms to the Polynomial." << endl
                 << "3 :: Remove terms from the Polynomial." << endl
                 << "4 :: Remove terms with Coefficient less than a Given Value." << endl
                 << "5 :: Display The Chosen Polynomial." << endl
                 << "6 :: Evaluate Polynomial for a given x." << endl
                 << "7 :: Derivative of Polynomial." << endl
                 << "8 :: Find a root of the Polynomial." << endl;
            cin >> b;
            switch (b)
            {
            case 1:
                goto here;
                break;
            case 2:
                z = scan(z);
                cout << "Your Polynomial is : ";
                printlist(z);
                cout << endl
                     << endl;
                z = NULL;
                goto here2;
                break;
            case 3:
                int temp;
                cout << "Enter How Many Terms You Want to Remove" << endl;
                cin >> temp;
                // vector<int> v;
                cout << "Enter the degree of terms you want to remove separated with spaces!" << endl;
                for (int i = 0; i < temp; i++)
                {
                    int degree;
                    cin >> degree;
                    z = addremoveterm(z, degree);
                }
                cout << "Your Polynomial is : ";
                printlist(z);
                cout << endl;
                goto here2;
                break;
            case 4:
                cout << "Enter value below which all terms with absolute value of coefficient less than that particular value will be removed!" << endl;
                int limit;
                cin >> limit;
                z = addremoveterm(z, 0, 0, limit);
                // goto here1;
                cout << "The Polynomial now is : ";
                printlist(z);
                goto here2;
                break;
            case 5:
                if (v.size() == 0)
                {
                    cout << "First Create a Polynomial!" << endl;
                }
                else
                {
                    cout << endl;
                    printlist(z);
                    cout << endl;
                }
                goto here2;
                break;

            default:
                break;

            case 6:
                cout << "Enter the value of the variable for which you want to Evaluate the Polynomial!" << endl;
                double x;
                cin >> x;
                answer = evaluate(z, x);
                cout << "The value of Polynomial at x = " << x << " is equal to " << answer
                     << endl;
                goto here2;
                break;
            case 7:
                Polyn *der;
                der = derivative(z);
                cout << endl
                     << "The derivative of the Polynomial is :";
                printlist(der);
                cout << endl;
                goto here2;
                break;
            case 8:
                cout << endl
                     << "Enter the Initial value of x." << endl;
                double x0;
                cin >> x0;
                zero_newton(z, x0);
                goto here2;
                break;
            }
        }
    }
    else
    {
        goto here;
    }

    return 0;
}