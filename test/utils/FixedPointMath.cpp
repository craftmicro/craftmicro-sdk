#include "catch.hpp"
#include "utils/FixedPointMath.h"
#include <iostream>

using namespace craft;

TEST_CASE("General") {

    SECTION("Underlying type") {
        Number n(1);
        REQUIRE(sizeof(n.value) == sizeof(long));
    }

    SECTION("Precision") {
        Number n(1, 1);
        REQUIRE(n.radixBits == 1);
        REQUIRE(n.value == 0b10);

        // Increase
        n.precision(2);
        REQUIRE(n.radixBits == 2);
        REQUIRE(n.value == 0b100);

        // Increase
        n.precision(5);
        REQUIRE(n.radixBits == 5);
        REQUIRE(n.value == 0b100000);

        // No change
        n.precision(5);
        REQUIRE(n.radixBits == 5);
        REQUIRE(n.value == 0b100000);

        // Decrease
        n.precision(3);
        REQUIRE(n.radixBits == 3);
        REQUIRE(n.value == 0b1000);

        // From another number
        Number n2(4);
        n.precision(n2);
        REQUIRE(n.radixBits == 4);
        REQUIRE(n.value == 0b10000);

        // Negative
        n = -64;
        n.precision(5);
        REQUIRE(n.value == -2048);
    }

    SECTION("Conversion") {
        Number n(100, 0);
        REQUIRE(n.toFloat() == 100.0f);
        REQUIRE(n.toInt() == 100);

        Number n2(100, 5);
        REQUIRE(n2.toFloat() == 100.0f);
        REQUIRE(n2.toInt() == 100);

        Number n3(21);
        n3 = 100.5f;
        REQUIRE(n3.toFloat() == 100.5f);
        REQUIRE(n3.toInt() == 100);

        Number n4(10);
        n4 = 100;
        REQUIRE(n4.toFloat() == 100.0f);
        REQUIRE(n4.toInt() == 100);
    }

    SECTION("Sign") {
        Number n(0);

        n = 100;
        REQUIRE(n.toFloat() > 0);

        n = -100;
        REQUIRE(n.toFloat() < 0);

        n.radixBits = 8;
        n = 0.03f;
        REQUIRE(n.toFloat() > 0);

        n = -0.03f;
        REQUIRE(n.toFloat() < 0);
    }

    SECTION("Values") {
        float f = 12.5812f;
        Number n(f, 8);
        REQUIRE(n.value == 3220);

        n.radixBits = 2;
        n = 12.5f;
        REQUIRE(n.value == 50);

        n.radixBits = 13;
        n = 730.23357f;
        REQUIRE(n.value == 5982073);

        n.radixBits = 21;
        n = -0.9700351f;
    }

}

TEST_CASE("Comparison") {

    SECTION("Float") {
        float f = 12.5812f;
        float f2 = 12.5922f;

        Number n(f, 8);
        bool result = (n == f);
        REQUIRE(result == true);

        result = (n != f);
        REQUIRE(result == false);

        result = (n != f2);
        REQUIRE(result == true);
    }

    SECTION("Number") {
        float f = 12.5812f;
        float fHigh = 12.5922f;
        float fLow = 9.003f;

        Number n(f, 8);
        Number nHigh(fHigh, 10);
        Number nLow(fLow, 13);
        Number nSame(n);

        bool result = (n < nHigh);
        REQUIRE(result == true);

        result = (n > nLow);
        REQUIRE(result == true);

        result = (n >= nSame);
        REQUIRE(result == true);

        result = (n <= nSame);
        REQUIRE(result == true);

        result = (n == nSame);
        REQUIRE(result == true);

        result = (n != nSame);
        REQUIRE(result == false);

        result = (n != nLow);
        REQUIRE(result == true);
    }

}

TEST_CASE("Mathematics") {

    SECTION("Addition") {

        // Both positive
        Number na(12.34f, 8);
        Number nb(3.45f, 8);
        Number nc(8);

        float c = na.toFloat() + nb.toFloat();
        nc = na + nb;

        bool result = (nc == c);
        REQUIRE(result == true);

        // One negative
        na = 12.34f;
        nb = -3.45f;

        c = na.toFloat() + nb.toFloat();
        nc = na + nb;

        result = (nc == c);
        REQUIRE(result == true);

        // Both negative
        na = -12.34f;
        nb = -3.45f;

        c = na.toFloat() + nb.toFloat();
        nc = na + nb;

        result = (nc == c);
        REQUIRE(result == true);

        // Different precisions
        na = -12.34f;
        na.precision(6);
        nb = -3.45f;
        nc.precision(0);

        c = na.toFloat() + nb.toFloat();
        nc = na + nb;

        result = (nc == c);
        REQUIRE(result == true);
        REQUIRE(nc.radixBits == 8);
    }

    SECTION("Increment") {
        int a = 1003;
        Number na(a, 15);
        na++;
        a++;
        REQUIRE(na.toInt() == a);

        a = -312;
        na = a;
        na++;
        a++;
        REQUIRE(na.toInt() == a);

        float b = 12.44f;
        Number nb(b, 15);
        nb++;
        b++;
        bool res = (nb == b);
        REQUIRE(res == true);

        b = -12.44f;
        nb = b;
        nb++;
        b++;
        res = (nb == b);
        REQUIRE(res == true);
    }

    SECTION("Subtraction") {

        // Both positive
        Number na(12.34f, 8);
        Number nb(3.45f, 8);
        Number nc(8);

        float c = na.toFloat() - nb.toFloat();
        nc = na - nb;

        bool result = (nc == c);
        REQUIRE(result == true);

        // One negative
        na = 12.34f;
        nb = -3.45f;

        c = na.toFloat() - nb.toFloat();
        nc = na - nb;

        result = (nc == c);
        REQUIRE(result == true);

        // Both negative
        na = -12.34f;
        nb = -3.45f;

        c = na.toFloat() - nb.toFloat();
        nc = na - nb;

        result = (nc == c);
        REQUIRE(result == true);

        // Different precisions
        na = -12.34f;
        na.precision(6);
        nb = -3.45f;
        nc.precision(0);

        c = na.toFloat() - nb.toFloat();
        nc = na - nb;

        result = (nc == c);
        REQUIRE(result == true);
        REQUIRE(nc.radixBits == 8);
    }

    SECTION("Decrement") {
        int a = 1003;
        Number na(a, 15);
        na--;
        a--;
        REQUIRE(na.toInt() == a);

        a = -312;
        na = a;
        na--;
        a--;
        REQUIRE(na.toInt() == a);

        float b = 12.44f;
        Number nb(b, 15);
        nb--;
        b--;
        bool res = (nb == b);
        REQUIRE(res == true);

        b = -12.44f;
        nb = b;
        nb--;
        b--;
        res = (nb == b);
        REQUIRE(res == true);
    }

    SECTION("Unary minus") {
        int a = 1003;
        Number na(a, 15);
        na = -na;
        a = -a;
        REQUIRE(na.toInt() == a);

        float b = -12.44f;
        Number nb(b, 15);
        nb = -nb;
        b = -b;
        bool res = (nb == b);
        REQUIRE(res == true);
    }

    SECTION("Multiplication") {

        // Both positive
        Number na(12.34f, 8);
        Number nb(3.45f, 8);
        Number nc(8);

        float c = na.toFloat() * nb.toFloat();
        nc = na * nb;

        bool result = (nc == c);
        REQUIRE(result == true);

        // One negative
        na = 0.78f;
        nb = -30.009f;

        c = na.toFloat() * nb.toFloat();
        nc = na * nb;

        result = (nc == c);
        REQUIRE(result == true);

        // Both negative
        na = -72.22f;
        nb = -42.98f;

        c = na.toFloat() * nb.toFloat();
        nc = na * nb;

        result = (nc == c);
        REQUIRE(result == true);
    }

    SECTION("Division") {

        // Both positive
        Number na(26.25f, 8);
        Number nb(3.5f, 8);
        Number nc(8);

        float c = na.toFloat() / nb.toFloat();
        nc = na / nb;

        bool result = (nc == c);
        REQUIRE(result == true);

        // One negative
        na = -30.009f;
        nb = 0.78f;

        c = na.toFloat() / nb.toFloat();
        nc = na / nb;

        result = (nc == c);
        REQUIRE(result == true);

        // Both negative
        na = -72.22f;
        nb = -42.98f;

        c = na.toFloat() / nb.toFloat();
        nc = na / nb;

        result = (nc == c);
        REQUIRE(result == true);
    }

    SECTION("Bit shifting") {
        float f = 12.5812f;
        Number n(f, 8);
        f = n.toFloat();
        REQUIRE(n.value == 0b110010010100);
        n <<= 2;
        REQUIRE(n.value == 0b11001001010000);
        REQUIRE(n.toFloat() == (f * 4));

        f = 26.25f;
        n = f;
        Number nf(20);
        nf = n >> 1;
        f = f / 2;
        REQUIRE(nf.toFloat() == f);
    }
}
