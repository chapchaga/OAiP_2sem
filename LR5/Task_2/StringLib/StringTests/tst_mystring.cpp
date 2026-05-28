#include <QtTest/QtTest>
#include "mystring.h"
#include <cstring>
#include <cerrno>
#include <vector>
#include <string>

// ═══════════════════════════════════════════════════════════════
//  Unit tests for MyString library
// ═══════════════════════════════════════════════════════════════
class TestMyString : public QObject
{
    Q_OBJECT

private slots:
    // ── Static memory functions ────────────────────────────────
    void test_strlen_basic()     { QCOMPARE(MyString::Strlen("hello"), size_t(5)); }
    void test_strlen_empty()     { QCOMPARE(MyString::Strlen(""),      size_t(0)); }
    void test_strlen_single()    { QCOMPARE(MyString::Strlen("a"),     size_t(1)); }

    void test_memcpy_basic()
    {
        char dst[8] = {};
        MyString::Memcpy(dst, "abcde", 5);
        QCOMPARE(std::string(dst, 5), std::string("abcde"));
    }
    void test_memcpy_partial()
    {
        char dst[8] = {'X','X','X','X','X','X','X','X'};
        MyString::Memcpy(dst, "hello", 3);
        QCOMPARE(dst[0], 'h'); QCOMPARE(dst[1], 'e'); QCOMPARE(dst[2], 'l');
        QCOMPARE(dst[3], 'X'); // untouched
    }
    void test_memcpy_zero_bytes()
    {
        char dst[4] = {'A','B','C','D'};
        MyString::Memcpy(dst, "xyz", 0);
        QCOMPARE(dst[0], 'A'); // nothing should change
    }

    void test_memmove_no_overlap()
    {
        char buf[16] = "Hello";
        MyString::Memmove(buf + 6, buf, 5);
        QCOMPARE(std::string(buf + 6, 5), std::string("Hello"));
    }
    void test_memmove_overlap_right()
    {
        char buf[] = "ABCDE";
        MyString::Memmove(buf + 1, buf, 4);  // ABCDE → AABCD
        QCOMPARE(std::string(buf), std::string("AABCD"));
    }
    void test_memmove_overlap_left()
    {
        char buf[] = "XABCDE";
        MyString::Memmove(buf, buf + 1, 5);  // XABCDE → ABCDEE
        QCOMPARE(std::string(buf, 5), std::string("ABCDE"));
    }

    void test_memset_basic()
    {
        char buf[6] = {};
        MyString::Memset(buf, 'Z', 5);
        QCOMPARE(std::string(buf, 5), std::string("ZZZZZ"));
    }
    void test_memset_zero()
    {
        char buf[4] = {'A','B','C','D'};
        MyString::Memset(buf, 0, 4);
        for (int i = 0; i < 4; ++i) QCOMPARE(buf[i], '\0');
    }

    void test_memcmp_equal()   { QCOMPARE(MyString::Memcmp("abc","abc",3),  0); }
    void test_memcmp_less()    { QVERIFY (MyString::Memcmp("abc","abd",3)  < 0); }
    void test_memcmp_greater() { QVERIFY (MyString::Memcmp("abd","abc",3)  > 0); }
    void test_memcmp_zero_n()  { QCOMPARE(MyString::Memcmp("abc","xyz",0),  0); }

    // ── Static string-copy functions ────────────────────────────
    void test_strcpy_basic()
    {
        char dst[16] = {};
        MyString::Strcpy(dst, "Hello");
        QCOMPARE(std::string(dst), std::string("Hello"));
    }
    void test_strcpy_empty()
    {
        char dst[4] = {'X','X','X','X'};
        MyString::Strcpy(dst, "");
        QCOMPARE(dst[0], '\0');
    }

    void test_strncpy_copies_n()
    {
        char dst[8] = {'X','X','X','X','X','X','X','X'};
        MyString::Strncpy(dst, "Hello", 3);
        QCOMPARE(dst[0], 'H'); QCOMPARE(dst[1], 'e'); QCOMPARE(dst[2], 'l');
        QCOMPARE(dst[3], 'X'); // beyond n
    }
    void test_strncpy_pads_nul()
    {
        char dst[8] = {};
        MyString::Strncpy(dst, "Hi", 6);
        QCOMPARE(dst[0], 'H'); QCOMPARE(dst[1], 'i');
        QCOMPARE(dst[2], '\0'); QCOMPARE(dst[5], '\0');
    }

    // ── Static concat functions ─────────────────────────────────
    void test_strcat_basic()
    {
        char buf[32] = "Hello, ";
        MyString::Strcat(buf, "World!");
        QCOMPARE(std::string(buf), std::string("Hello, World!"));
    }
    void test_strcat_empty_src()
    {
        char buf[16] = "abc";
        MyString::Strcat(buf, "");
        QCOMPARE(std::string(buf), std::string("abc"));
    }

    void test_strncat_n()
    {
        char buf[32] = "Hi ";
        MyString::Strncat(buf, "There!!!", 5);
        QCOMPARE(std::string(buf), std::string("Hi There"));
    }
    void test_strncat_zero()
    {
        char buf[16] = "abc";
        MyString::Strncat(buf, "xyz", 0);
        QCOMPARE(std::string(buf), std::string("abc"));
    }

    // ── Static compare functions ────────────────────────────────
    void test_strcmp_equal()    { QCOMPARE(MyString::Strcmp("abc","abc"),  0); }
    void test_strcmp_less()     { QVERIFY (MyString::Strcmp("abc","abd")  < 0); }
    void test_strcmp_greater()  { QVERIFY (MyString::Strcmp("abd","abc")  > 0); }
    void test_strcmp_prefix()   { QVERIFY (MyString::Strcmp("ab","abc")   < 0); }

    void test_strncmp_equal_prefix() { QCOMPARE(MyString::Strncmp("abcXX","abcYY",3), 0); }
    void test_strncmp_differ()       { QVERIFY (MyString::Strncmp("abcX","abcY",4) < 0); }
    void test_strncmp_zero()         { QCOMPARE(MyString::Strncmp("abc","xyz",0), 0); }

    void test_strcoll_equal() { QCOMPARE(MyString::Strcoll("abc","abc"), 0); }

    void test_strxfrm_returns_length()
    {
        char buf[32] = {};
        size_t n = MyString::Strxfrm(buf, "hello", 31);
        QVERIFY(n > 0);
    }

    // ── strtok ─────────────────────────────────────────────────
    void test_strtok_basic()
    {
        char buf[] = "one,two,,three";
        std::vector<std::string> tokens;
        char* t = MyString::Strtok(buf, ",");
        while (t) { tokens.push_back(t); t = MyString::Strtok(nullptr, ","); }
        QCOMPARE((int)tokens.size(), 3);
        QCOMPARE(tokens[0], std::string("one"));
        QCOMPARE(tokens[1], std::string("two"));
        QCOMPARE(tokens[2], std::string("three"));
    }
    void test_strtok_multi_delim()
    {
        char buf[] = "a:b;c:d";
        std::vector<std::string> tokens;
        char* t = MyString::Strtok(buf, ":;");
        while (t) { tokens.push_back(t); t = MyString::Strtok(nullptr, ":;"); }
        QCOMPARE((int)tokens.size(), 4);
    }
    void test_strtok_no_delim()
    {
        char buf[] = "hello";
        char* t = MyString::Strtok(buf, ",");
        QVERIFY(t != nullptr);
        QCOMPARE(std::string(t), std::string("hello"));
        t = MyString::Strtok(nullptr, ",");
        QVERIFY(t == nullptr);
    }

    // ── strerror ───────────────────────────────────────────────
    void test_strerror_not_null()
    {
        char* msg = MyString::Strerror(EINVAL);
        QVERIFY(msg != nullptr);
        QVERIFY(MyString::Strlen(msg) > 0);
    }

    // ── MyString constructors ───────────────────────────────────
    void test_default_ctor()
    {
        MyString s;
        QCOMPARE(s.size(),     size_t(0));
        QCOMPARE(std::string(s.c_str()), std::string(""));
    }
    void test_cstr_ctor()
    {
        MyString s("hello");
        QCOMPARE(s.size(), size_t(5));
        QCOMPARE(std::string(s.c_str()), std::string("hello"));
    }
    void test_fill_ctor()
    {
        MyString s(4, '*');
        QCOMPARE(s.size(), size_t(4));
        QCOMPARE(std::string(s.c_str()), std::string("****"));
    }

    // ── Rule of Three ──────────────────────────────────────────
    void test_copy_ctor_deep()
    {
        MyString orig("deep");
        MyString copy(orig);
        copy[0] = 'D';
        QCOMPARE(orig[0], 'd');  // orig must not change
    }
    void test_copy_assign_deep()
    {
        MyString orig("deep");
        MyString copy;
        copy = orig;
        orig[0] = 'X';
        QCOMPARE(std::string(copy.c_str()), std::string("deep"));
    }
    void test_self_assign()
    {
        MyString s("self");
        s = s;
        QCOMPARE(std::string(s.c_str()), std::string("self"));
    }

    // ── Operators ──────────────────────────────────────────────
    void test_concat_operator()
    {
        MyString a("Hello"), b(" World");
        MyString c = a + b;
        QCOMPARE(std::string(c.c_str()), std::string("Hello World"));
    }
    void test_concat_assign()
    {
        MyString a("Hello");
        a += MyString(" World");
        QCOMPARE(std::string(a.c_str()), std::string("Hello World"));
    }
    void test_cmp_operators()
    {
        MyString a("abc"), b("abd");
        QVERIFY(a <  b);
        QVERIFY(b >  a);
        QVERIFY(a != b);
        QVERIFY(a <= b);
        QVERIFY(b >= a);
        QVERIFY(a == MyString("abc"));
    }
    void test_subscript()
    {
        MyString s("hello");
        QCOMPARE(s[0], 'h');
        QCOMPARE(s[4], 'o');
        s[0] = 'H';
        QCOMPARE(s[0], 'H');
    }
    void test_at_throws()
    {
        MyString s("abc");
        bool threw = false;
        try { s.at(100); } catch (const std::out_of_range&) { threw = true; }
        QVERIFY(threw);
    }

    // ── Iterator ───────────────────────────────────────────────
    void test_iterator_forward()
    {
        MyString s("test");
        std::string collected;
        for (auto it = s.begin(); it != s.end(); ++it)
            collected += *it;
        QCOMPARE(collected, std::string("test"));
    }
    void test_range_for()
    {
        MyString s("iter");
        std::string collected;
        for (char c : s) collected += c;
        QCOMPARE(collected, std::string("iter"));
    }
    void test_iterator_distance()
    {
        MyString s("abcd");
        QCOMPARE(s.end() - s.begin(), ptrdiff_t(4));
    }
    void test_const_iterator()
    {
        const MyString s("const");
        std::string collected;
        for (auto it = s.cbegin(); it != s.cend(); ++it)
            collected += *it;
        QCOMPARE(collected, std::string("const"));
    }

    // ── reserve / resize ───────────────────────────────────────
    void test_reserve()
    {
        MyString s("Hi");
        s.reserve(100);
        QVERIFY(s.capacity() >= size_t(100));
        QCOMPARE(std::string(s.c_str()), std::string("Hi"));
    }
    void test_resize_extend()
    {
        MyString s("Hi");
        s.resize(5, '!');
        QCOMPARE(std::string(s.c_str()), std::string("Hi!!!"));
        QCOMPARE(s.size(), size_t(5));
    }
    void test_resize_shrink()
    {
        MyString s("Hello");
        s.resize(2);
        QCOMPARE(std::string(s.c_str()), std::string("He"));
    }

    // ── empty / size ───────────────────────────────────────────
    void test_empty()
    {
        MyString s;
        QVERIFY(s.empty());
        s += MyString("x");
        QVERIFY(!s.empty());
    }
};

QTEST_MAIN(TestMyString)
#include "tst_mystring.moc"
