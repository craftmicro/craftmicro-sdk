#pragma once

#include <iostream>
#include <string>

namespace craft {

    #define FPM_TYPE long
    #define FPM_TYPE_BITS 32

    #define FPM_TYPE_BITS_2 (FPM_TYPE_BITS >> 1)
    #define FPM_LOW_MASK ((1 << FPM_TYPE_BITS_2) - 1)

    /**
     * @brief Fixed-point math class
     */
    class Number {
    public:
        // Internal value of the number
        FPM_TYPE value = 0;

        // Radix bits
        unsigned char radixBits = 0;

        /**
         * @brief Construct a new Number as a copy
         */
        Number(Number& other) {
            this->radixBits = other.radixBits;
            this->value = other.value;
        }

        /**
         * @brief Construct a new Number with a set number of radix bits
         */
        Number(unsigned char radixBits) {
            this->radixBits = radixBits;
        }

        /**
         * @brief Construct a new Number from a float with a set number of radix bits
         */
        Number(float value, unsigned char radixBits) {
            this->radixBits = radixBits;
            this->value = FPM_TYPE(value * (1 << radixBits));
        }

        /**
         * @brief Construct a new Number from an integer with a set number of radix bits
         */
        Number(int value, unsigned char radixBits) {
            this->radixBits = radixBits;
            this->value = value * (1 << radixBits);
        }

        /**
         * @brief Change the precision of the number
         */
        void precision(unsigned char radixBits) {
            char d = this->radixBits - radixBits;
            if (d > 0) {
                this->value >>= d;
                this->radixBits = radixBits;
                delta = 0;
            }
            else if (d < 0) {
                this->value <<= -d;
                this->radixBits = radixBits;
                delta = 0;
            }
        }

        /**
         * @brief Change the precision of the number to match another number
         */
        void precision(Number& other) {
            this->precision(other.radixBits);
        }

        /**
         * @brief Assignment of another Number
         */
        Number& operator = (const Number& other) {
            this->value = other.value;
            if (this->radixBits != other.radixBits) {
                this->radixBits = other.radixBits;
                this->delta = 0;
            }
            return *this;
        }

        /**
         * @brief Assignment of a float value
         */
        Number& operator = (float other) {
            this->value = FPM_TYPE(other * (1 << radixBits));
            return *this;
        }

        /**
         * @brief Assignment of an integer value
         */
        Number& operator = (int other) {
            this->value = other << radixBits;
            return *this;
        }

        /**
         * @brief Equals
         */
        bool operator == (Number& other) {
            if (radixBits == other.radixBits) {
                return value == other.value;
            }
            else if (radixBits > other.radixBits) {
                Number n(other);
                n.precision(*this);
                return value == n.value;
            }
            else {
                Number n(*this);
                n.precision(other);
                return n.value == other.value;
            }
        }

        /**
         * @brief Equal to float
         */
        bool operator == (float other) {
            //std::cout << toFloat() << " [==] " << other;
            other -= toFloat();
            if (other < 0) other = -other;
            calcDelta();

            //std::cout << ", diff:" << other << ", delta:" << delta << std::endl;

            return other < delta;
        }

        /**
         * @brief Not equals
         */
        bool operator != (Number& other) {
            return !(*this == other);
        }

        /**
         * @brief Not equal to float
         */
        bool operator != (float other) {
            return !(*this == other);
        }

        /**
         * @brief Greater than
         */
        bool operator > (Number& other) {
            if (radixBits == other.radixBits) {
                return value > other.value;
            }
            else if (radixBits > other.radixBits) {
                Number n(other);
                n.precision(*this);
                return value > n.value;
            }
            else {
                Number n(*this);
                n.precision(other);
                return n.value > other.value;
            }
        }

        /**
         * @brief Greater than or equal
         */
        bool operator >= (Number& other) {
            if (radixBits == other.radixBits) {
                return value >= other.value;
            }
            else if (radixBits > other.radixBits) {
                Number n(other);
                n.precision(*this);
                return value >= n.value;
            }
            else {
                Number n(*this);
                n.precision(other);
                return n.value >= other.value;
            }
        }

        /**
         * @brief Less than
         */
        bool operator < (Number& other) {
            if (radixBits == other.radixBits) {
                return value < other.value;
            }
            else if (radixBits > other.radixBits) {
                Number n(other);
                n.precision(*this);
                return value < n.value;
            }
            else {
                Number n(*this);
                n.precision(other);
                return n.value < other.value;
            }
        }

        /**
         * @brief Less than or equal
         */
        bool operator <= (Number& other) {
            if (radixBits == other.radixBits) {
                return value <= other.value;
            }
            else if (radixBits > other.radixBits) {
                Number n(other);
                n.precision(*this);
                return value <= n.value;
            }
            else {
                Number n(*this);
                n.precision(other);
                return n.value <= other.value;
            }
        }

        /**
         * @brief Increment
         */
        void operator ++ (int x) {
            value += (1 << radixBits);
        }

        /**
         * @brief Decrement
         */
        void operator -- (int x) {
            value -= (1 << radixBits);
        }

        /**
         * @brief Unary minus (negative)
         */
        Number& operator - () {
            value = -value;
            return *this;
        }

        /**
         * @brief Shift right
         */
        Number operator >> (int bits) {
            Number n(*this);
            n.value >>= bits;
            return n;
        }

        /**
         * @brief Shift right assignment
         */
        Number& operator >>= (int bits) {
            value >>= bits;
            return *this;
        }

        /**
         * @brief Shift left
         */
        Number operator << (int bits) {
            Number n(*this);
            n.value <<= bits;
            return n;
        }

        /**
         * @brief Shift left assignment
         */
        Number& operator <<= (int bits) {
            value <<= bits;
            return *this;
        }

        /**
         * @brief Add
         *
         * The result will have the higher precision of the two operands
         */
        Number operator + (Number& other) {
            if (radixBits == other.radixBits) {
                Number n(*this);
                n.value += other.value;
                return n;
            }
            else if (radixBits > other.radixBits) {
                Number n(other);
                n.precision(*this);
                n.value += value;
                return n;
            }
            else {
                Number n(*this);
                n.precision(other);
                n.value += other.value;
                return n;
            }
        }

        /**
         * @brief Subtract
         *
         * The result will have the higher precision of the two operands
         */
        Number operator - (Number& other) {
            if (radixBits == other.radixBits) {
                Number n(*this);
                n.value -= other.value;
                return n;
            }
            else if (radixBits > other.radixBits) {
                Number n(other);
                n.precision(*this);
                n.value = value - n.value;
                return n;
            }
            else {
                Number n(*this);
                n.precision(other);
                n.value -= other.value;
                return n;
            }
        }

        /**
         * @brief Multiply
         *
         * The result will have the higher precision of the two operands
         */
        Number operator * (Number& other) {
            Number a(*this);
            Number b(other);
            Number n(a.radixBits + b.radixBits);
            unsigned char maxRadixBits = a.radixBits > b.radixBits ? a.radixBits : b.radixBits;

            char neg = 0;
            if (a.value < 0) {
                neg = 1;
                a.value = -a.value;
            }
            if (b.value < 0) {
                neg = !neg;
                b.value = -b.value;
            }

            FPM_TYPE h = ((a.value >> FPM_TYPE_BITS_2) * (b.value >> FPM_TYPE_BITS_2));
            FPM_TYPE m1 = ((a.value >> FPM_TYPE_BITS_2) * (b.value & FPM_LOW_MASK));
            FPM_TYPE m2 = ((b.value >> FPM_TYPE_BITS_2) * (a.value & FPM_LOW_MASK));
            FPM_TYPE l = (((a.value & FPM_LOW_MASK) * (b.value & FPM_LOW_MASK)));

            n.value = ((h << FPM_TYPE_BITS_2) + m1 + m2 + l) >> (n.radixBits - maxRadixBits);
            n.radixBits = maxRadixBits;

            //std::cout << "[a] val:" << a.value << " float:" << a.toFloat() << " rbits:" << int(a.radixBits) << std::endl;
            //std::cout << "[b] val:" << b.value << " float:" << b.toFloat() << " rbits:" << int(b.radixBits) << std::endl;
            //std::cout << "[n] val:" << n.value << " float:" << n.toFloat() << " rbits:" << int(n.radixBits) << std::endl;

            return neg ? -n : n;
        }

        Number operator / (Number& other) {
            Number a(*this);
            Number b(other);
            matchPrecision(a, b);

            // XXX: This is just a floating point division because I have not yet
            // found an integer divide that is faster!
            Number n(a.radixBits);
            n.value = FPM_TYPE(float(a.value) / float(b.value) * (1 << n.radixBits));
            return n;
        }

        /**
         * @brief Number converted to int (whole part of the number)
         */
        inline int toInt() { return value >> radixBits; }

        /**
         * @brief Number converted to float
         */
        inline float toFloat() {
            calcDelta();
            return float(value) * delta;
        }

        /**
         * @brief Change the operands to match the highest precision operand
         */
        inline static void matchPrecision(Number& a, Number& b) {
            if (a.radixBits > b.radixBits) {
                b.precision(a);
            }
            else if (a.radixBits < b.radixBits) {
                a.precision(b);
            }
        }

        /**
         * @brief Debug trace
         */
        void trace(std::string s = "") {
            calcDelta();
            if (s != "") std::cout << s << ": ";
            std::cout << "[" << toFloat() << " ~" << delta << "] q" << int(FPM_TYPE_BITS - radixBits) << "." << int(radixBits) << " (" << value << ")" << std::endl;
        }

    private:

        // Precision delta
        float delta = 0;

        // Calculate precision delta
        inline void calcDelta() {
            if (delta == 0) delta = 1.0f / (1 << radixBits);
        }

    };

} // craft