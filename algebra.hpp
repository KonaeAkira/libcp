#ifndef ALGEBRA_HPP
#define ALGEBRA_HPP
namespace libcp
{
    template<class T, T MOD>
    class field_type
    {
    private:
        T val;
        static T normalize(const T n)
        {
            return n >= 0 && n < MOD ? n : (n % MOD + MOD) % MOD;
        }
    public:
        field_type(): val() {}
        field_type(const T val): val(normalize(val)) {}
        field_type(const field_type &src): val(src.val) {}
        T get() const { return val; }
        void set(const T n) { val = normalize(n); }
        field_type operator + (const field_type rhs)
        {
            return field_type(val + rhs.val);
        }
        field_type &operator += (const field_type rhs)
        {
            val = val + rhs.val >= MOD ? val + rhs.val - MOD : val + rhs.val;
            return *this;
        }
        field_type operator - (const field_type rhs)
        {
            return field_type(val - rhs.val);
        }
        field_type &operator -= (const field_type rhs)
        {
            val = val - rhs.val >= 0 ? val - rhs.val : val - rhs.val + MOD;
            return *this;
        }
        field_type operator * (const field_type rhs)
        {
            return field_type(val * rhs.val);
        }
        field_type &operator *= (const field_type rhs)
        {
            val = val * rhs.val % MOD;
            return *this;
        }
        field_type operator / (const field_type rhs)
        {
            assert(rhs.get() != 0);
            return field_type(val * pow(rhs.val, MOD - 2));
        }
        field_type &operator /= (const field_type rhs)
        {
            assert(rhs.get() != 0);
            val = val * pow(rhs.val, MOD - 2) % MOD;
            return *this;
        }
        static T pow(field_type base, T exp)
        {
            field_type res(1);
            for (; exp != 0; exp >>= 1)
            {
                if (exp & 1) res = res * base;
                base = base * base;
            }
            return res.val;
        }
    };
    template<class T, T MOD>
    std::istream &operator >> (std::istream &stream, field_type<T, MOD> &rhs)
    {
        T t; stream >> t;
        rhs.set(t);
        return stream;
    }
    template<class T, T MOD>
    std::ostream &operator << (std::ostream &stream, const field_type<T, MOD> rhs)
    {
        stream << rhs.get();
        return stream;
    }
}
#endif