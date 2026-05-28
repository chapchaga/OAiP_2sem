/**
 * test_lab6.cpp — Функциональные тесты для Lab6_Task1
 *
 * Тестируется бизнес-логика программы без Qt UI:
 *   - Структура Odezhda: инициализация, форматирование, указатели, ссылки
 *   - Файловые операции: текст (посимвольно), массив, структура txt, структура bin, строки
 *
 * Сборка (без Qt):
 *   g++ -std=c++17 -o test_lab6 test_lab6.cpp && ./test_lab6
 *
 * Интеграция в CMakeLists.txt — добавьте в конец существующего CMakeLists.txt:
 *   add_executable(test_lab6 tests/test_lab6.cpp)
 *   target_compile_options(test_lab6 PRIVATE -DTEST_MODE)
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <cassert>
#include <vector>
#include <filesystem>

// ──────────────────────────────────────────────
// Структура из mainwindow.h (скопирована для автономности)
// ──────────────────────────────────────────────
struct Odezhda {
    int size;
    double price;
    char gender;
    bool inStock;
    char brand[50];
    int articleNumbers[5];
};

// ──────────────────────────────────────────────
// Вспомогательные функции из mainwindow.cpp
// (извлечены из Qt-зависимого кода для тестирования)
// ──────────────────────────────────────────────

std::string formatOdezhda(const Odezhda &o, const std::string &sep = " | ")
{
    std::string articles;
    for (int i = 0; i < 5; i++) {
        if (i > 0) articles += ",";
        articles += std::to_string(o.articleNumbers[i]);
    }
    return std::to_string(o.size) + sep
         + std::to_string(o.price) + sep
         + o.gender + sep
         + (o.inStock ? "true" : "false") + sep
         + o.brand + sep
         + "[" + articles + "]";
}

Odezhda makeOdezhda(int sz, double pr, char gnd, bool stk,
                    const std::string &brand,
                    const std::vector<int> &arts)
{
    Odezhda o{};
    o.size = sz;
    o.price = pr;
    o.gender = gnd;
    o.inStock = stk;
    strncpy(o.brand, brand.c_str(), sizeof(o.brand) - 1);
    o.brand[sizeof(o.brand) - 1] = '\0';
    for (int i = 0; i < 5; i++)
        o.articleNumbers[i] = (i < (int)arts.size()) ? arts[i] : 0;
    return o;
}

// ──────────────────────────────────────────────
// Мини-фреймворк тестов
// ──────────────────────────────────────────────

static int passed = 0, failed = 0;

#define TEST(name, condition)                                          \
    do {                                                               \
        if (condition) {                                               \
            std::cout << "  [PASS] " << name << "\n";                 \
            ++passed;                                                   \
        } else {                                                       \
            std::cerr << "  [FAIL] " << name << "\n";                 \
            ++failed;                                                  \
        }                                                              \
    } while (0)

#define SECTION(name) std::cout << "\n=== " << name << " ===\n"

// ──────────────────────────────────────────────
// ТЕСТЫ ЗАДАНИЯ 1: Структура Odezhda
// ──────────────────────────────────────────────

void test_struct_init_string()
{
    SECTION("Task 1.1 — Инициализация через строку инициализации");

    Odezhda o = {44, 2499.99, 'M', true, "Adidas", {2001, 2002, 2003, 2004, 2005}};

    TEST("size == 44",         o.size == 44);
    TEST("price == 2499.99",   o.price == 2499.99);
    TEST("gender == 'M'",      o.gender == 'M');
    TEST("inStock == true",    o.inStock == true);
    TEST("brand == Adidas",    std::string(o.brand) == "Adidas");
    TEST("article[0] == 2001", o.articleNumbers[0] == 2001);
    TEST("article[4] == 2005", o.articleNumbers[4] == 2005);
}

void test_struct_field_by_field()
{
    SECTION("Task 1.2 — Присвоение полей по одному");

    Odezhda o;
    o.size = 38;
    o.price = 999.50;
    o.gender = 'F';
    o.inStock = false;
    strncpy(o.brand, "Zara", sizeof(o.brand));
    o.articleNumbers[0] = 3001; o.articleNumbers[1] = 3002;
    o.articleNumbers[2] = 3003; o.articleNumbers[3] = 3004;
    o.articleNumbers[4] = 3005;

    TEST("size == 38",         o.size == 38);
    TEST("price == 999.50",    o.price == 999.50);
    TEST("gender == 'F'",      o.gender == 'F');
    TEST("inStock == false",   o.inStock == false);
    TEST("brand == Zara",      std::string(o.brand) == "Zara");
    TEST("article[2] == 3003", o.articleNumbers[2] == 3003);
}

void test_struct_pointer_access()
{
    SECTION("Task 1.4 — Доступ через указатель");

    Odezhda o;
    Odezhda *ptr = &o;

    ptr->size = 50;
    ptr->price = 5100.75;
    ptr->gender = 'M';
    ptr->inStock = true;
    strncpy(ptr->brand, "Gucci", sizeof(ptr->brand));
    ptr->articleNumbers[0] = 7001;
    ptr->articleNumbers[4] = 7005;

    TEST("ptr->size == 50",         ptr->size == 50);
    TEST("ptr->price == 5100.75",   ptr->price == 5100.75);
    TEST("ptr == &o (same object)", ptr == &o);
    TEST("brand == Gucci",          std::string(ptr->brand) == "Gucci");
    TEST("article[4] == 7005",      ptr->articleNumbers[4] == 7005);
}

void test_struct_reference_access()
{
    SECTION("Task 1.5 — Доступ через ссылку");

    Odezhda o;
    Odezhda &ref = o;

    ref.size = 36;
    ref.price = 899.00;
    ref.gender = 'F';
    ref.inStock = false;
    strncpy(ref.brand, "Mango", sizeof(ref.brand));
    ref.articleNumbers[0] = 9001;
    ref.articleNumbers[4] = 9005;

    TEST("ref.size == 36",           ref.size == 36);
    TEST("ref aliases o (size)",     o.size == 36);
    TEST("ref aliases o (brand)",    std::string(o.brand) == "Mango");
    TEST("ref.inStock == false",     ref.inStock == false);
    TEST("article[4] == 9005",       ref.articleNumbers[4] == 9005);
}

void test_format_odezhda()
{
    SECTION("Task 1 — Форматирование структуры");

    Odezhda o = makeOdezhda(44, 1500.0, 'M', true, "Nike", {1,2,3,4,5});
    std::string s = formatOdezhda(o);

    TEST("contains size",      s.find("44") != std::string::npos);
    TEST("contains gender",    s.find("M")  != std::string::npos);
    TEST("contains true",      s.find("true") != std::string::npos);
    TEST("contains brand",     s.find("Nike") != std::string::npos);
    TEST("contains articles",  s.find("[1,2,3,4,5]") != std::string::npos);

    // Другой разделитель
    std::string s2 = formatOdezhda(o, " ; ");
    TEST("custom sep present", s2.find(" ; ") != std::string::npos);
}

void test_brand_boundary()
{
    SECTION("Task 1 — Граничные случаи бренда");

    Odezhda o{};
    // Пустой бренд
    strncpy(o.brand, "", sizeof(o.brand));
    TEST("empty brand", std::string(o.brand).empty());

    // Максимальная длина (49 символов + '\0')
    std::string longBrand(49, 'X');
    strncpy(o.brand, longBrand.c_str(), sizeof(o.brand) - 1);
    o.brand[sizeof(o.brand) - 1] = '\0';
    TEST("long brand stored",       std::string(o.brand) == longBrand);
    TEST("null terminator intact",  o.brand[49] == '\0');

    // Слишком длинный — обрезается
    std::string veryLong(100, 'A');
    strncpy(o.brand, veryLong.c_str(), sizeof(o.brand) - 1);
    o.brand[sizeof(o.brand) - 1] = '\0';
    TEST("overlong brand truncated", std::strlen(o.brand) == 49);
}

// ──────────────────────────────────────────────
// ТЕСТЫ ЗАДАНИЯ 2: Файловые операции
// Используем временную директорию
// ──────────────────────────────────────────────

static std::string tmpDir()
{
    return std::filesystem::temp_directory_path().string() + "/lab6_test_";
}

void test_file_text_char_by_char()
{
    SECTION("Task 2.1 — Текст посимвольно");

    std::string path = tmpDir() + "text.txt";
    std::string text = "Привет мир! Hello 123.";

    // Запись посимвольно (логика из onTask2_TextSaveClicked)
    {
        std::ofstream file(path);
        assert(file.is_open());
        for (char ch : text) file.put(ch);
    }

    // Чтение (логика из onTask2_TextLoadClicked)
    {
        std::ifstream file(path);
        assert(file.is_open());
        std::string result;
        char ch;
        while (file.get(ch)) result += ch;
        TEST("text roundtrip", result == text);
    }

    std::filesystem::remove(path);
}

void test_file_array_with_delimiter()
{
    SECTION("Task 2.2 — Массив с разделителем");

    std::string path = tmpDir() + "array.txt";
    std::vector<int> nums = {10, 200, 3000, -5, 0};

    // Запись (логика из onTask2_ArraySaveClicked)
    {
        std::ofstream file(path);
        for (int i = 0; i < (int)nums.size(); i++) {
            file << nums[i];
            if (i < (int)nums.size() - 1) file << '\'';
        }
    }

    // Чтение (логика из onTask2_ArrayLoadClicked)
    {
        std::ifstream file(path);
        std::string content((std::istreambuf_iterator<char>(file)),
                             std::istreambuf_iterator<char>());
        file.close();

        std::istringstream ss(content);
        std::string part;
        std::vector<int> loaded;
        while (std::getline(ss, part, '\'')) {
            std::istringstream vs(part);
            int val;
            if (vs >> val) loaded.push_back(val);
        }

        TEST("count matches",    loaded.size() == nums.size());
        TEST("first element",    loaded[0] == 10);
        TEST("negative element", loaded[3] == -5);
        TEST("zero element",     loaded[4] == 0);
        TEST("large element",    loaded[2] == 3000);
    }

    std::filesystem::remove(path);
}

void test_file_struct_txt()
{
    SECTION("Task 2.3 — Структура в текстовый файл");

    std::string path = tmpDir() + "struct.txt";

    Odezhda orig = makeOdezhda(42, 1299.99, 'M', true, "Puma", {11,22,33,44,55});

    // Запись (логика из onTask2_StructTxtSaveClicked)
    {
        std::ofstream file(path, std::ios::app);
        file << orig.size     << "\n"
             << orig.price    << "\n"
             << orig.gender   << "\n"
             << (orig.inStock ? 1 : 0) << "\n"
             << orig.brand    << "\n";
        for (int i = 0; i < 5; i++)
            file << orig.articleNumbers[i] << (i < 4 ? " " : "\n");
    }

    // Чтение (логика из onTask2_StructTxtLoadClicked)
    {
        std::ifstream file(path);
        Odezhda o{};
        int stockInt;
        std::string brandStr;
        file >> o.size >> o.price >> o.gender >> stockInt;
        file.ignore();
        std::getline(file, brandStr);
        strncpy(o.brand, brandStr.c_str(), sizeof(o.brand) - 1);
        o.brand[sizeof(o.brand) - 1] = '\0';
        o.inStock = (stockInt != 0);
        for (int i = 0; i < 5; i++) file >> o.articleNumbers[i];

        TEST("size roundtrip",    o.size == orig.size);
        TEST("gender roundtrip",  o.gender == orig.gender);
        TEST("inStock roundtrip", o.inStock == orig.inStock);
        TEST("brand roundtrip",   std::string(o.brand) == "Puma");
        TEST("article[0]",        o.articleNumbers[0] == 11);
        TEST("article[4]",        o.articleNumbers[4] == 55);
    }

    std::filesystem::remove(path);
}

void test_file_struct_txt_multiple()
{
    SECTION("Task 2.3 — Несколько структур (дозапись)");

    std::string path = tmpDir() + "multi.txt";

    auto writeOne = [&](const Odezhda &o) {
        std::ofstream file(path, std::ios::app);
        file << o.size << "\n" << o.price << "\n" << o.gender << "\n"
             << (o.inStock ? 1 : 0) << "\n" << o.brand << "\n";
        for (int i = 0; i < 5; i++)
            file << o.articleNumbers[i] << (i < 4 ? " " : "\n");
    };

    Odezhda a = makeOdezhda(40, 500.0, 'F', false, "Gap",  {1,2,3,4,5});
    Odezhda b = makeOdezhda(52, 9000.0, 'M', true, "Boss", {6,7,8,9,10});
    writeOne(a);
    writeOne(b);

    // Чтение обоих
    std::ifstream file(path);
    int count = 0;
    std::vector<Odezhda> loaded;
    while (file.peek() != EOF) {
        Odezhda o{};
        int stockInt;
        std::string brandStr;
        if (!(file >> o.size >> o.price >> o.gender >> stockInt)) break;
        file.ignore();
        std::getline(file, brandStr);
        strncpy(o.brand, brandStr.c_str(), sizeof(o.brand) - 1);
        o.brand[sizeof(o.brand) - 1] = '\0';
        o.inStock = (stockInt != 0);
        for (int i = 0; i < 5; i++) file >> o.articleNumbers[i];
        file.ignore();
        loaded.push_back(o);
        ++count;
    }
    file.close();

    TEST("two records read",    count == 2);
    TEST("first brand == Gap",  std::string(loaded[0].brand) == "Gap");
    TEST("second brand == Boss",std::string(loaded[1].brand) == "Boss");
    TEST("first size == 40",    loaded[0].size == 40);
    TEST("second size == 52",   loaded[1].size == 52);
    TEST("first inStock false", loaded[0].inStock == false);
    TEST("second inStock true", loaded[1].inStock == true);

    std::filesystem::remove(path);
}

void test_file_struct_binary()
{
    SECTION("Task 2.4 — Структура в бинарный файл");

    std::string path = tmpDir() + "struct.bin";

    Odezhda orig = makeOdezhda(48, 7499.0, 'U', true, "Versace", {111,222,333,444,555});

    // Запись
    {
        std::ofstream file(path, std::ios::binary | std::ios::app);
        file.write(reinterpret_cast<char*>(&orig), sizeof(Odezhda));
    }

    // Чтение
    {
        std::ifstream file(path, std::ios::binary);
        Odezhda o{};
        file.read(reinterpret_cast<char*>(&o), sizeof(Odezhda));
        TEST("size  roundtrip", o.size == 48);
        TEST("price roundtrip", o.price == 7499.0);
        TEST("brand roundtrip", std::string(o.brand) == "Versace");
        TEST("article[2] == 333", o.articleNumbers[2] == 333);
        TEST("sizeof preserved", sizeof(o) == sizeof(orig));
    }

    std::filesystem::remove(path);
}

void test_file_struct_binary_multiple()
{
    SECTION("Task 2.4 — Несколько структур бинарно (дозапись)");

    std::string path = tmpDir() + "multi.bin";

    Odezhda a = makeOdezhda(36, 300.0, 'F', false, "Mango",  {1,0,0,0,0});
    Odezhda b = makeOdezhda(54, 15000.0,'M', true,  "Armani",{9,9,9,9,9});

    auto writeOne = [&](const Odezhda &o) {
        std::ofstream f(path, std::ios::binary | std::ios::app);
        f.write(reinterpret_cast<const char*>(&o), sizeof(Odezhda));
    };
    writeOne(a);
    writeOne(b);

    std::ifstream file(path, std::ios::binary);
    std::vector<Odezhda> records;
    Odezhda tmp{};
    while (file.read(reinterpret_cast<char*>(&tmp), sizeof(Odezhda)))
        records.push_back(tmp);

    TEST("two binary records", records.size() == 2);
    TEST("first == Mango",     std::string(records[0].brand) == "Mango");
    TEST("second == Armani",   std::string(records[1].brand) == "Armani");
    TEST("second price",       records[1].price == 15000.0);

    std::filesystem::remove(path);
}

void test_file_lines()
{
    SECTION("Task 2.5 — Построчная запись и чтение");

    std::string path = tmpDir() + "lines.txt";

    std::vector<std::string> lines = {
        "Первая строка",
        "Second line with numbers 123",
        "Третья строка с символами !@#"
    };

    // Дозапись строк
    for (const auto &line : lines) {
        std::ofstream file(path, std::ios::app);
        file << line << "\n";
    }

    // Чтение
    std::ifstream file(path);
    std::vector<std::string> loaded;
    std::string line;
    while (std::getline(file, line)) loaded.push_back(line);

    TEST("line count",   loaded.size() == lines.size());
    TEST("line 1 match", loaded[0] == lines[0]);
    TEST("line 2 match", loaded[1] == lines[1]);
    TEST("line 3 match", loaded[2] == lines[2]);

    std::filesystem::remove(path);
}

void test_file_nonexistent()
{
    SECTION("Task 2 — Чтение несуществующего файла");

    std::string path = tmpDir() + "nonexistent_xyz.txt";
    std::ifstream file(path);
    TEST("file not open", !file.is_open());
}

// ──────────────────────────────────────────────
// Точка входа
// ──────────────────────────────────────────────

int main()
{
    std::cout << "╔══════════════════════════════════════════╗\n";
    std::cout << "║  Функциональные тесты Lab6_Task1         ║\n";
    std::cout << "╚══════════════════════════════════════════╝\n";

    // Task 1
    test_struct_init_string();
    test_struct_field_by_field();
    test_struct_pointer_access();
    test_struct_reference_access();
    test_format_odezhda();
    test_brand_boundary();

    // Task 2
    test_file_text_char_by_char();
    test_file_array_with_delimiter();
    test_file_struct_txt();
    test_file_struct_txt_multiple();
    test_file_struct_binary();
    test_file_struct_binary_multiple();
    test_file_lines();
    test_file_nonexistent();

    std::cout << "\n──────────────────────────────────────────────\n";
    std::cout << "Результат: " << passed << " прошли, " << failed << " упали\n";

    return (failed == 0) ? 0 : 1;
}
