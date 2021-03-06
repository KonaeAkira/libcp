#include <iostream>
// https://github.com/KonaeAkira/libcp/blob/master/include/modular_arithmetic.hpp
template<class T, T MOD>
class modular_number
{
private:
    T val;
    static T normalize(const T n)
    {
        return __builtin_clz(n) && n < MOD ? n : (n % MOD + MOD) % MOD;
    }
public:
    modular_number(): val() {}
    modular_number(const T val): val(normalize(val)) {}
    modular_number(const modular_number &src): val(src.val) {}
    T get() const { return val; }
    void set(const T n) { val = normalize(n); }
    modular_number operator + (const modular_number rhs) const
    {
        return modular_number(val + rhs.val);
    }
    modular_number &operator += (const modular_number rhs)
    {
        val = val + rhs.val >= MOD ? val + rhs.val - MOD : val + rhs.val;
        return *this;
    }
    modular_number operator - (const modular_number rhs) const
    {
        return modular_number(val >= rhs.val ? val - rhs.val : val + MOD - rhs.val);
    }
    modular_number &operator -= (const modular_number rhs)
    {
        val = val >= rhs.val ? val - rhs.val : val + MOD - rhs.val;
        return *this;
    }
    // assumes that MOD * MOD doesn't overflow T
    // TODO fix?
    modular_number operator * (const modular_number rhs) const
    {
        return modular_number(val * rhs.val);
    }
    modular_number &operator *= (const modular_number rhs)
    {
        val = val * rhs.val % MOD;
        return *this;
    }
    modular_number operator / (const modular_number rhs) const
    {
        assert(rhs.get() != 0);
        return modular_number(val * pow(rhs.val, MOD - 2));
    }
    modular_number &operator /= (const modular_number rhs)
    {
        assert(rhs.get() != 0);
        val = val * pow(rhs.val, MOD - 2) % MOD;
        return *this;
    }
    static T pow(modular_number base, T exp)
    {
        modular_number res(1);
        for (; exp != 0; exp >>= 1)
        {
            if (exp & 1) res = res * base;
            base = base * base;
        }
        return res.val;
    }
};
template<class T, T MOD>
std::istream &operator >> (std::istream &stream, modular_number<T, MOD> &rhs)
{
    T t; stream >> t;
    rhs.set(t);
    return stream;
}
template<class T, T MOD>
std::ostream &operator << (std::ostream &stream, const modular_number<T, MOD> rhs)
{
    stream << rhs.get();
    return stream;
}
