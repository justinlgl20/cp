#include <bits/stdc++.h>
using namespace std;


//BigInt template taken from https://github.com/wps5422/C-Big-Integer/blob/main/integer.hpp
#ifdef _MSC_VER
#include <sstream>
#endif

#include <climits>
#include <vector>
#include <string>
#include <iostream>
#include <cassert>
#include <chrono>
#include <algorithm>

#define CHECK_INT_TYPE(type) static_assert(std::is_same_v<type, int8_t> || std::is_same_v<type, int16_t> || std::is_same_v<type, int32_t> || std::is_same_v<type, int64_t>, "type must be int8, int16, int32, or int64")

class Integer {
public:
    using word = uint64_t;
    static constexpr word BASE_DIGIT = 10;
    std::vector<word> words;
    bool is_negative = false;
    static constexpr bool SAFE_INITIALIZATION = false;

    Integer() : is_negative(false) {};

    Integer(size_t n, word w, bool negative = false) : words(n, w), is_negative(negative) {}

    [[maybe_unused]] Integer(const word *a, const word *b, bool negative = false) : words(a, b),
                                                                                    is_negative(negative) {}

    Integer(const Integer &a) { words = a.words, is_negative = a.is_negative; }

    Integer &operator=(const Integer &a) = default;

    static constexpr char MIN_NUMERIC_CHARACTER = '0';

    template<class type>
    Integer(type number) {
        CHECK_INT_TYPE(type);
        if (number < 0) {
            is_negative = true;
            number *= -1;
            // When the number is equal to the smallest number of its type. It will cause an error. Since the smallest number of integers multiplied by -1 is equal to itself. Example: INT_MIN * -1 = INT_MIN, LONG_LONG_MIN * -1 = LONG_LONG_MIN. Use the read function for a safer initialization.
        }
        while (number != 0) {
            words.push_back(number);
            for (int j = 0; j < 64; j++) number >>= 1;
        }
    }

    void read(const std::string &s) {
        words.clear();
        this->is_negative = false;
        size_t i = 0, end = s.size();
        if (s[i] == '-') {
            ++i;
            is_negative = true;
        }
        for (; i != end; ++i) {
            mul_word(BASE_DIGIT);
            if constexpr (SAFE_INITIALIZATION) {
                assert(isdigit(s[i]));
            }
            word carry = s[i] - MIN_NUMERIC_CHARACTER;
            if (words.empty()) words.resize(1);
            for (size_t j = 0; j < words.size() && carry; j++) carry = add_carry(&words[j], carry);
            if (carry) words.push_back(carry);
            while (!words.empty() && words.back() == 0) words.pop_back();
        }
    }

    [[maybe_unused]] explicit Integer(const std::string &s) : is_negative(false) { read(s); }

    [[maybe_unused]] explicit Integer(const char *s) : is_negative(false) { read((std::string) s); }

    inline word &operator[](size_t i) { return words[i]; }

    const word &operator[](size_t i) const { return words[i]; }

    inline bool is_zero() const { return words.empty(); }

    Integer &set_negative(bool b) {
        this->is_negative = b;
        return *this;
    }

    Integer &truncate() {
        while (!words.empty() && words.back() == 0) words.pop_back();
        return *this;
    }

    size_t bit_size() const {
        if (words.empty()) return 0;
        size_t last = words.size() - 1;
        size_t result = word_bit_size(words[last]) + last * 64;
        return result;
    }

    static int cmp_abs(const Integer &a, const Integer &b) {
        if (a.words == b.words) return 0;
        return std::lexicographical_compare(a.words.rbegin(), a.words.rend(), b.words.rbegin(), b.words.rend()) ? -1
                                                                                                                : 1;
    }

    static inline int cmp(const Integer &a, const Integer &b) {
        if (a.words.empty() && b.words.empty()) return 0;
        else if (!a.is_negative && !b.is_negative) return +cmp_abs(a, b);
        else if (a.is_negative && b.is_negative) return -cmp_abs(a, b);
        else return a.is_negative && !b.is_negative ? -1 : +1;
    }

    static size_t word_bit_size(word a) {
        for (int i = 64 - 1; i >= 0; i--) if ((a >> i) & 1) return i + 1;
        return 0;
    }

    static word add_carry(word *a, word b) { return (*a += b) < b; }

    static word sub_carry(word *a, word b) {
        word tmp = *a;
        return (*a = tmp - b) > tmp;
    }

    static word word_mul_high(word a, word b) {
        word a_high = a >> 32, a_low = a & UINT_MAX, b_high = b >> 32, b_low = b & UINT_MAX;
        word tmp = ((a_low * b_low) >> 32) + a_high * b_low;
        tmp = (tmp >> 32) + ((a_low * b_high + (tmp & UINT_MAX)) >> 32);
        return tmp + a_high * b_high;
    }

    static Integer &add_unsigned_overwrite(Integer &a, const Integer &b) {
        size_t i, na = a.words.size(), nb = b.words.size(), n = std::max(na, nb);
        a.words.resize(n);
        word carry = 0;
        for (i = 0; i < nb; i++) {
            carry = add_carry(&a[i], carry);
            carry += add_carry(&a[i], b[i]);
        }
        for (; i < n && carry; i++) carry = add_carry(&a[i], carry);
        if (carry) a.words.push_back(carry);
        return a.truncate();
    }

    static Integer &sub_unsigned_overwrite(Integer &a, const Integer &b) {
        size_t i, na = a.words.size(), nb = b.words.size();
        word carry = 0;
        for (i = 0; i < nb; i++) {
            carry = sub_carry(&a[i], carry);
            carry += sub_carry(&a[i], b[i]);
        }
        for (; i < na && carry; i++) carry = sub_carry(&a[i], carry);
        return a.truncate();
    }

    static Integer native_multiple(const Integer &a, const Integer &b) {
        size_t na = a.words.size(), nb = b.words.size(), nc = na + nb + 1;
        Integer c(nc, 0, a.is_negative ^ b.is_negative), carries(nc, 0);
        for (size_t ia = 0; ia < na; ia++) {
            for (size_t ib = 0; ib < nb; ib++) {
                size_t i = ia + ib, j = i + 1;
                carries[i + 1] += add_carry(&c[i], a[ia] * b[ib]);
                carries[j + 1] += add_carry(&c[j], word_mul_high(a[ia], b[ib]));
            }
        }
        return add_unsigned_overwrite(c, carries).truncate();
    }

    static void split(const Integer &a, Integer &lhs, Integer &rhs, size_t size_) {
        size_t i = 0;
        lhs.words.resize(size_);
        for (size_t j = 0; j < size_ && i < a.words.size(); j++) lhs[j] = a[i++];
        lhs = lhs.truncate();
        rhs.words.resize(a.words.size() - size_);
        for (size_t j = 0; j < a.words.size() - size_ && i < a.words.size(); j++) rhs[j] = a[i++];
        rhs = rhs.truncate();
    }

    static Integer karatsuba_multiple(const Integer &a, const Integer &b) {
        size_t na = a.words.size(), nb = b.words.size(), n = std::max(na, nb), m2 = n / 2 + (n & 1);
        Integer a0, a1, b0, b1;
        split(a, a0, a1, m2);
        split(b, b0, b1, m2);
        m2 *= 64;
        Integer z0 = a0 * b0;
        Integer z1 = (a0 + a1) * (b0 + b1);
        Integer z2 = a1 * b1;
        Integer result = z2;
        result <<= m2;
        result += z1 - z2 - z0;
        result <<= m2;
        result += z0;
        return result;
    }

    static constexpr size_t threshold = 20;

    static Integer multiple(const Integer &a, const Integer &b) {
        return (a.words.size() > threshold && b.words.size() > threshold ? karatsuba_multiple(a, b) : native_multiple(a,
                                                                                                                      b));
    }

    static Integer add_signed(const Integer &a, bool a_negative, const Integer &b, bool b_negative) {
        if (a_negative == b_negative) return add_unsigned(a, b).set_negative(a_negative);
        if (cmp_abs(a, b) >= 0) return sub_unsigned(a, b).set_negative(a_negative);
        return sub_unsigned(b, a).set_negative(b_negative);
    }

    Integer &operator>>=(size_t n_bits) {
        if (n_bits == 0) return *this;
        size_t n_words = n_bits / 64;
        if (n_words >= words.size()) {
            words.resize(0);
            return *this;
        }
        n_bits %= 64;
        if (n_bits == 0) {
            for (size_t i = 0; i < words.size() - n_words; i++) {
                words[i] = words[i + n_words];
            }
        } else {
            word high, low = words[n_words];
            for (size_t i = 0; i < words.size() - n_words - 1; i++) {
                high = words[i + n_words + 1];
                words[i] = (high << (64 - n_bits)) | (low >> n_bits);
                low = high;
            }
            words[words.size() - n_words - 1] = low >> n_bits;
        }
        words.resize(words.size() - n_words);
        return truncate();
    }

    Integer &operator<<=(size_t n_bits) {
        if (n_bits == 0) return *this;
        size_t n_words = n_bits / 64;
        n_bits %= 64;
        size_t old_size = words.size();
        size_t n = old_size + n_words + (n_bits != 0);
        words.resize(n);
        if (n_bits == 0) {
            for (size_t i = n; i-- > n_words;) words[i] = words[i - n_words];
        } else {
            word low, high = 0;
            for (size_t i = n - 1; i > n_words; i--) {
                low = words[i - n_words - 1];
                words[i] = (high << n_bits) | (low >> (64 - n_bits));
                high = low;
            }
            words[n_words] = high << n_bits;
        }
        for (size_t i = 0; i < n_words; i++) words[i] = 0;
        return truncate();
    }

    static void div_mod(const Integer &generator, Integer denominator, Integer &quotient, Integer &remainder) {
        quotient = 0;
        remainder = generator;
        if (cmp_abs(remainder, denominator) >= 0) {
            int n = int(generator.bit_size() - denominator.bit_size());
            denominator <<= n;
            for (; n >= 0; n--) {
                if (cmp_abs(remainder, denominator) >= 0) {
                    sub_unsigned_overwrite(remainder, denominator);
                    quotient.set_bit(n);
                }
                denominator >>= 1;
            }
        }
        quotient.set_negative(generator.is_negative ^ denominator.is_negative);
        remainder.set_negative(generator.is_negative);
    }

    static void div_mod_half_word(const Integer &generator, Integer &quotient, word &remainder) {
        remainder = 0;
        Integer dst(generator.words.size(), 0);
        for (size_t i = generator.words.size(); i-- > 0;) {
            word dst_word = 0;
            word src_word = generator[i];

            word part_0 = src_word >> 32, part_1 = src_word & UINT_MAX;
            remainder <<= 32;
            remainder |= part_0;
            word div_word = remainder / BASE_DIGIT;
            word mod_word = remainder % BASE_DIGIT;
            remainder = mod_word;
            dst_word <<= 32;
            dst_word |= div_word;

            remainder <<= 32;
            remainder |= part_1;
            div_word = remainder / BASE_DIGIT;
            mod_word = remainder % BASE_DIGIT;
            remainder = mod_word;
            dst_word <<= 32;
            dst_word |= div_word;

            dst[i] = dst_word;
        }
        quotient = dst.truncate().set_negative(generator.is_negative);
    }

    static Integer div(const Integer &generator, const Integer &denominator) {
        Integer quotient, remainder;
        div_mod(generator, denominator, quotient, remainder);
        return quotient;
    }

    static Integer mod(const Integer &generator, const Integer &denominator) {
        Integer quotient, remainder;
        div_mod(generator, denominator, quotient, remainder);
        return remainder;
    }

    static Integer add_unsigned(const Integer &a, const Integer &b) {
        Integer result(a);
        return add_unsigned_overwrite(result, b);
    }

    static Integer sub_unsigned(const Integer &a, const Integer &b) {
        Integer result(a);
        return sub_unsigned_overwrite(result, b);
    }

    static Integer add(const Integer &a, const Integer &b) {
        Integer result = add_signed(a, a.is_negative, b, b.is_negative);
        return result;
    }

    static Integer sub(const Integer &a, const Integer &b) {
        Integer result = add_signed(a, a.is_negative, b, !b.is_negative);
        return result;
    }

    Integer &set_bit(int i) {
        size_t i_word = i / 64, i_bit = i % 64;
        if (words.size() <= i_word) words.resize(i_word + 1);
        words[i_word] |= ((word) 1) << i_bit;
        return *this;
    }

    void mul_word(word b) {
        word carry = 0;
        for (word &i: words) {
            word a = i;
            word tmp = a * b;
            carry = add_carry(&tmp, carry);
            carry += word_mul_high(a, b);
            i = tmp;
        }
        if (carry) words.push_back(carry);
        while (!words.empty() && words.back() == 0) words.pop_back();
    }

    std::string to_string() const {
        if (words.empty()) return "0";
        std::string result;
        Integer tmp(*this);
        while (!tmp.words.empty()) {
            word remainder;
            div_mod_half_word(tmp, tmp, remainder);
            result.push_back(char(MIN_NUMERIC_CHARACTER + remainder));
        }
        if (is_negative) result.push_back('-');
        std::reverse(result.begin(), result.end());
        return result;
    }

    Integer &operator+=(const Integer &b) { return *this = add(*this, b); }

    Integer &operator-=(const Integer &b) { return *this = sub(*this, b); }

    Integer &operator*=(const Integer &b) { return *this = multiple(*this, b); }

    Integer &operator/=(const Integer &b) {
        assert(!b.is_zero());
        return *this = div(*this, b);
    }

    Integer &operator%=(const Integer &b) {
        assert(!b.is_zero());
        return *this = mod(*this, b);
    }

    bool operator==(const Integer &b) const { return cmp(*this, b) == 0; }

    bool operator!=(const Integer &b) const { return cmp(*this, b) != 0; }

    bool operator<=(const Integer &b) const { return cmp(*this, b) <= 0; }

    bool operator>=(const Integer &b) const { return cmp(*this, b) >= 0; }

    bool operator<(const Integer &b) const { return cmp(*this, b) < 0; }

    bool operator>(const Integer &b) const { return cmp(*this, b) > 0; }

    Integer operator+(const Integer &b) const { return add(*this, b); }

    Integer operator-(const Integer &b) const { return sub(*this, b); }

    Integer operator*(const Integer &b) const { return multiple(*this, b); }

    Integer operator/(const Integer &b) const {
        assert(!b.is_zero());
        return div(*this, b);
    }

    Integer operator%(const Integer &b) const {
        assert(!b.is_zero());
        return mod(*this, b);
    }

    Integer operator-() const { return Integer(*this).set_negative(!is_negative); }

    Integer operator>>(size_t n_bits) const { return Integer(*this) >>= n_bits; }

    Integer operator<<(size_t n_bits) const { return Integer(*this) <<= n_bits; }

    friend std::istream &operator>>(std::istream &stream, Integer &v) {
        std::string s;
        stream >> s;
        v.read(s);
        return stream;
    }

    friend std::ostream &operator<<(std::ostream &stream, const Integer &v) {
        std::cout << v.to_string();
        return stream;
    }

    template<class type>
    void operator*=(type number) {
        CHECK_INT_TYPE(type);
        if (number < 0) {
            is_negative = !is_negative;
            number *= -1;
        }
        mul_word((word) number);
    }
};
#define int Integer
#define double __float128
#define all(x) (x).begin(), (x).end()

#define dbg(x...)

int32_t nxt() {
    int32_t x; cin >> x; return x;
}

int32_t main() {
    const double EPILISON = 0.000000000000000000000000005;
    int32_t n = nxt();
    int A = ((Integer)1)<<((size_t)100000);
    cout << A << "\n";
    vector<int32_t> a(n+5), b(n+5);
    vector<int> give(n+5);
    vector<double> m(n+5);
    vector<double> constant(n+5);
    for (int32_t i = 1; i <= n; i++) cin >> a[i] >> b[i];
    bool all_zero = true;
    for (int32_t i = 1; i <= n; i++) all_zero = all_zero and (b[i] == 0);
    bool al_zero = true;
    for (int32_t i = 1; i <= n; i++) al_zero = al_zero and (a[i] == 0);
    if (all_zero and al_zero) {
        cout << "Yes\n";
        return 0;
    }
    if (all_zero) {
        cout << "No\n";
        return 0;
    }
    double pass_on = 1;
    int sums = 0;
    for (int32_t i = 1; i <= n; i++) {
        sums += ((Integer)(1)<<((size_t)(i-1)))*(b[i]-a[i]);
    }
    int c = ((Integer)(1)-(((Integer)(1))<<((size_t)n)));
    give[0] = sums/((Integer)(1)-(((Integer)(1))<<((size_t)n)));
    for (int32_t i = 1; i <= n; i++) {
        give[i] = (give[i-1]-b[i]+a[i])/2;
    }
    assert(give[0] == give[n]);
    bool works = true;
    for (int32_t i = 1; i <= n; i++) {
        if (give[i] < 0) works = false;
        if ((Integer)a[i]+give[i-1]-(Integer)(2)*give[i] != (Integer)b[i]) works = false;
    }
    dbg(works);
    if (works) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
    }
}
