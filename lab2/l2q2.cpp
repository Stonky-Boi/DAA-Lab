// Determine big O, Omega, Theta relations
// Inequality checks and ratio trend analysis

#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#include <algorithm>
using namespace std;

long double custom_log2(long double x)
{
    return log(x) / log((long double)2);
}

struct Term
{
    long double coefficient;
    int n_power;
    int log_power;
};

map<string, Term> base_terms = {
    {"n", {1.0L, 1, 0}},
    {"n^2", {1.0L, 2, 0}},
    {"n^3", {1.0L, 3, 0}},
    {"logn", {1.0L, 0, 1}},
    {"log^2n", {1.0L, 0, 2}},
    {"nlogn", {1.0L, 1, 1}},
    {"nlog^2n", {1.0L, 1, 2}},
    {"n^2logn", {1.0L, 2, 1}}};

long double evaluate_term(const Term &t, long double n)
{
    return t.coefficient * pow(n, t.n_power) * pow(custom_log2(n), t.log_power);
}

vector<Term> parse_expression(string expr)
{
    vector<Term> terms;
    expr.erase(remove(expr.begin(), expr.end(), ' '), expr.end());
    size_t i = 0;
    while (i < expr.size())
    {
        long double coeff = 1.0L;
        if (isdigit(expr[i]))
        {
            size_t j = i;
            while (j < expr.size() && isdigit(expr[j]))
                j++;
            coeff = stold(expr.substr(i, j - i));
            i = j;
        }
        if (i < expr.size() && expr[i] == '+')
        {
            i++;
            continue;
        }
        string core;
        while (i < expr.size() && expr[i] != '+')
            core += expr[i++];
        if (base_terms.count(core))
        {
            Term t = base_terms[core];
            t.coefficient *= coeff;
            terms.push_back(t);
        }
    }
    return terms;
}

long double evaluate_function(const vector<Term> &terms, long double n)
{
    long double sum = 0.0L;
    for (const auto &t : terms)
        sum += evaluate_term(t, n);
    return sum;
}

bool converges_to_finite(const vector<long double> &r)
{
    for (size_t i = 1; i < r.size(); i++)
    {
        long double prev = max((long double)1.0, fabsl(r[i - 1]));
        long double delta = fabsl(r[i] - r[i - 1]) / prev;
        if (delta > 0.05L)
            return false;
    }
    return true;
}

bool converges_to_zero(const vector<long double> &r)
{
    return r.back() < r.front() * 0.1L;
}

int main()
{
    string f, g;
    getline(cin, f);
    getline(cin, g);
    vector<Term> f_terms = parse_expression(f);
    vector<Term> g_terms = parse_expression(g);
    vector<long double> ratios;
    vector<long double> test_n = {1000, 2000, 5000, 10000, 20000, 50000, 100000};
    for (long double n : test_n)
    {
        long double fv = evaluate_function(f_terms, n);
        long double gv = evaluate_function(g_terms, n);
        if (gv == 0.0L)
        {
            cout << "NO\nNO\nNO\n";
            return 0;
        }
        ratios.push_back(fv / gv);
    }
    bool finite = converges_to_finite(ratios);
    bool zero = converges_to_zero(ratios);
    bool big_o = finite;
    bool big_omega = !zero;
    bool theta = finite && !zero;
    cout << (big_o ? "YES" : "NO") << endl;
    cout << (big_omega ? "YES" : "NO") << endl;
    cout << (theta ? "YES" : "NO") << endl;
    return 0;
}