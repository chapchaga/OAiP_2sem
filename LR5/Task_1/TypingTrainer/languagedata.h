#pragma once
#include <QString>
#include <QVector>
#include <QMap>

enum class Language {
    German,
    French,
    Arabic,
    Chinese,
    Belarusian,
    Hebrew,
    English
};

struct LanguageInfo {
    QString name;
    QString nativeName;
    QString flag;
    bool rtl;
    QVector<QVector<QString>> keyboardRows; // display labels
    QString sampleText;
};

inline QMap<Language, LanguageInfo> getLanguageData() {
    QMap<Language, LanguageInfo> data;

    // German
    LanguageInfo german;
    german.name = "German";
    german.nativeName = "Deutsch";
    german.flag = "🇩🇪";
    german.rtl = false;
    german.keyboardRows = {
        {"^", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "ß", "´"},
        {"q", "w", "e", "r", "t", "z", "u", "i", "o", "p", "ü", "+"},
        {"a", "s", "d", "f", "g", "h", "j", "k", "l", "ö", "ä", "#"},
        {"<", "y", "x", "c", "v", "b", "n", "m", ",", ".", "-"},
        {"SPACE"}
    };
    german.sampleText = "Die Sonne scheint hell und warm. Der Wind weht sanft durch die Bäume. Kinder spielen fröhlich im Garten. Das Leben ist schön und voller Freude. Jeder Tag bringt neue Möglichkeiten mit sich.";
    data[Language::German] = german;

    // French
    LanguageInfo french;
    french.name = "French";
    french.nativeName = "Français";
    french.flag = "🇫🇷";
    french.rtl = false;
    french.keyboardRows = {
        {"²", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "°", "+"},
        {"a", "z", "e", "r", "t", "y", "u", "i", "o", "p", "^", "$"},
        {"q", "s", "d", "f", "g", "h", "j", "k", "l", "m", "ù", "*"},
        {"<", "w", "x", "c", "v", "b", "n", ",", ";", ":", "!"},
        {"SPACE"}
    };
    french.sampleText = "Le soleil brille dans le ciel bleu. Les oiseaux chantent mélodieusement dans les arbres. La vie est belle et pleine de joie. Chaque jour apporte de nouvelles aventures magnifiques. Le café est délicieux le matin.";
    data[Language::French] = french;

    // Arabic
    LanguageInfo arabic;
    arabic.name = "Arabic";
    arabic.nativeName = "العربية";
    arabic.flag = "🇸🇦";
    arabic.rtl = true;
    arabic.keyboardRows = {
        {"ذ", "١", "٢", "٣", "٤", "٥", "٦", "٧", "٨", "٩", "٠", "-", "="},
        {"ض", "ص", "ث", "ق", "ف", "غ", "ع", "ه", "خ", "ح", "ج", "د"},
        {"ش", "س", "ي", "ب", "ل", "ا", "ت", "ن", "م", "ك", "ط"},
        {"ئ", "ء", "ؤ", "ر", "لا", "ى", "ة", "و", "ز", "ظ"},
        {"SPACE"}
    };
    arabic.sampleText = "الشمس تشرق كل صباح جميل. الأطفال يلعبون في الحديقة بسعادة. الحياة جميلة ومليئة بالأمل والفرح. كل يوم جديد يحمل فرصاً رائعة ومميزة. القهوة العربية لها رائحة زكية.";
    data[Language::Arabic] = arabic;

    // Chinese
    LanguageInfo chinese;
    chinese.name = "Chinese";
    chinese.nativeName = "中文";
    chinese.flag = "🇨🇳";
    chinese.rtl = false;
    chinese.keyboardRows = {
        {"·", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "-", "="},
        {"q", "w", "e", "r", "t", "y", "u", "i", "o", "p", "[", "]"},
        {"a", "s", "d", "f", "g", "h", "j", "k", "l", ";", "'"},
        {"z", "x", "c", "v", "b", "n", "m", ",", ".", "/"},
        {"SPACE"}
    };
    chinese.sampleText = "太阳每天早晨升起照耀大地。孩子们在公园里快乐地玩耍游戏。生活充满了美好和希望与快乐。每一天都带来新的机会和挑战。春天的花朵美丽芬芳令人陶醉。";
    data[Language::Chinese] = chinese;

    // Belarusian
    LanguageInfo belarusian;
    belarusian.name = "Belarusian";
    belarusian.nativeName = "Беларуская";
    belarusian.flag = "🇧🇾";
    belarusian.rtl = false;
    belarusian.keyboardRows = {
        {"ё", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "-", "="},
        {"й", "ц", "у", "к", "е", "н", "г", "ш", "ў", "з", "х", "'"},
        {"ф", "ы", "в", "а", "п", "р", "о", "л", "д", "ж", "э"},
        {"я", "ч", "с", "м", "і", "т", "ь", "б", "ю", "."},
        {"SPACE"}
    };
    belarusian.sampleText = "Сонца свеціць ярка і цёпла кожны дзень. Дзеці гуляюць весела на зялёнай траве. Жыццё прыгожае і поўнае радасці і шчасця. Кожны новы дзень прыносіць новыя магчымасці. Беларускі лес зачароўвае сваёй прыгажосцю.";
    data[Language::Belarusian] = belarusian;

    // Hebrew
    LanguageInfo hebrew;
    hebrew.name = "Hebrew";
    hebrew.nativeName = "עברית";
    hebrew.flag = "🇮🇱";
    hebrew.rtl = true;
    hebrew.keyboardRows = {
        {";", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "-", "="},
        {"/", "'", "ק", "ר", "א", "ט", "ו", "ן", "ם", "פ", "[", "]"},
        {"ש", "ד", "ג", "כ", "ע", "י", "ח", "ל", "ך", "ף", ","},
        {"ז", "ס", "ב", "ה", "נ", "מ", "צ", "ת", "ץ", "."},
        {"SPACE"}
    };
    hebrew.sampleText = "השמש זורחת בכל בוקר יפה ומואר. הילדים משחקים בשמחה בגן הירוק. החיים יפים ומלאי שמחה ואושר. כל יום חדש מביא הזדמנויות נפלאות. ירושלים עיר קדושה ויפה מאוד.";
    data[Language::Hebrew] = hebrew;

    LanguageInfo english;
    english.name = "English";
    english.nativeName = "English";
    english.flag = "🇬🇧";
    english.rtl = false;
    english.keyboardRows = {
        {"`","1","2","3","4","5","6","7","8","9","0","-","="},
        {"q","w","e","r","t","y","u","i","o","p","[","]"},
        {"a","s","d","f","g","h","j","k","l",";","'"},
        {"z","x","c","v","b","n","m",",",".","/"},
        {"SPACE"}
    };
    english.sampleText = "The quick brown fox jumps over the lazy dog. Pack my box with five dozen liquor jugs. How vexingly quick daft zebras jump. The five boxing wizards jump quickly.";
    data[Language::English] = english;

    return data;
}
