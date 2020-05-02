#pragma once

// Effekt-IDs werden genutzt zum Verbinden der Effekt-Definitionen hier weiter unten und in effectTricker
#define EFF_WHITE_COLOR         ( 0U)    // Белый свет
#define EFF_COLOR               ( 1U)    // Цвет
#define EFF_MADNESS             ( 2U)    // Безумие
#define EFF_CLOUDS              ( 3U)    // Облака
#define EFF_LAVA                ( 4U)    // Лава
#define EFF_PLASMA              ( 5U)    // Плазма
#define EFF_RAINBOW             ( 6U)    // Радуга 3D
#define EFF_RAINBOW_STRIPE      ( 7U)    // Павлин
#define EFF_ZEBRA               ( 8U)    // Зебра
#define EFF_FOREST              ( 9U)    // Лес
#define EFF_OCEAN               (10U)    // Океан
#define EFF_BBALLS              (11U)    // Мячики
#define EFF_BBALLS_WHITE        (12U)    // Белые мячики
#define EFF_BBALLS_TRACES       (13U)    // Мячики со шлейфом
#define EFF_SPIRO               (14U)    // Спирали
#define EFF_PRISMATA            (15U)    // Призмата
#define EFF_FLOCK               (16U)    // Стая
#define EFF_FLOCK_N_PR          (17U)    // Стая и хищник
#define EFF_SINUSOID3           (18U)    // Синусоид
#define EFF_METABALLS           (19U)    // Метаболз

#define EFF_MATRIX              (20U)    // Матрица
#define EFF_FIRE_2018           (21U)    // Огонь 2018
#define EFF_FIRE                (22U)    // Огонь
#define EFF_FIRE_WHITTE         (23U)    // Белый огонь
#define EFF_FIRE_BLUE           (24U)    // Голубой огонь
#define EFF_FIRE_GREEN          (25U)    // Зелёный огонь
#define EFF_WHIRL               (26U)    // Вихри пламени
#define EFF_WHIRL_MULTI         (27U)    // Разноцветные вихри
#define EFF_WATERFALL           (28U)    // Водопад
#define EFF_WATERFALL_WHITE     (29U)    // Белый водопад
#define EFF_WATERFALL_4IN1      (30U)    // Водопад 4 в 1
#define EFF_POOL                (31U)    // Бассейн
#define EFF_PULSE_SLOW          (32U)    // Медленный пульс
#define EFF_PULSE_FAST          (33U)    // Быстрый пульс
#define EFF_PULSE_RAINBOW       (34U)    // Радужный пульс
#define EFF_PULSE_WHITE         (35U)    // Белый пульс
#define EFF_COMET               (36U)    // Комета
#define EFF_COMET_WHITE         (37U)    // Белая комета
#define EFF_COMET_COLOR         (38U)    // Одноцветная комета
#define EFF_COMET_PULSING       (39U)    // Пульсирующая комета
#define EFF_COMET_TWO           (40U)    // Две кометы
#define EFF_COMET_THREE         (41U)    // Три кометы

#define EFF_FIREFLY             (42U)    // Парящий огонь
#define EFF_FIREFLY_TOP         (43U)    // Верховой огонь
#define EFF_SNAKE               (44U)    // Радужный змей
#define EFF_SPARKLES            (45U)    // Конфетти
#define EFF_RAINBOW_VER         (46U)    // Радуга вертикальная
#define EFF_RAINBOW_HOR         (47U)    // Радуга горизонтальная
#define EFF_RAINBOW_DIAG        (48U)    // Радуга диагональная
#define EFF_WAVES               (49U)    // Волны
#define EFF_SNOW                (50U)    // Снегопад
#define EFF_RAIN                (51U)    // Цветной дождь
#define EFF_SNOWSTORM           (52U)    // Метель
#define EFF_STARFALL            (53U)    // Звездопад
#define EFF_LIGHTERS            (54U)    // Светлячки
#define EFF_LIGHTER_TRACES      (55U)    // Светлячки со шлейфом
#define EFF_PAINTBALL           (56U)    // Пейнтбол
#define EFF_CUBE                (57U)    // Блуждающий кубик
#define EFF_COLORS              (58U)    // Смена цвета
#define EFF_SIMPLE_RAIN         (59U)    // Тучка в банке
#define EFF_STORMY_RAIN         (60U)    // Гроза в банке
#define EFF_TWINKLES            (61U)    // МЕРЦАНИЕ
#define EFF_TEXT                (62U)    // Бегущая строка


#define MAX_EFF_NAME_LNG (50U)    // Maximale Länge des Effektnamen
// Effect
struct EffectType {
  uint8_t Id;
  char Name[MAX_EFF_NAME_LNG];
  uint8_t SpeedMin;
  uint8_t SpeedMax;
  uint8_t ScaleMin;
  uint8_t ScaleMax;
  uint8_t ScaleType;
  uint8_t defaultBrightness;
  uint8_t defaultSpeed;
  uint8_t defaultScale;
};

// Effect-List
// Id, name, min speed, max speed, min scale, max scale, scale type (0-scale,1-color, 2-for comet (1/2 scale + 1/2 color), defaultBrightness, defaultSpeed, defaultScale
// Die Reihenfolge im Array bestimmt die Reihenfolge der Anzeige in WebUI und App, sie kann beliebig geändert werden. 
// Das gilt nicht für die IDs! Sie werden fürs Bestimmen der Effekt-Routine verwendet. Weiterhin müssen sie selbstverständlich einmalig sein.
static const EffectType effects[] PROGMEM = {
  { 0, "White Light",            1,255,1,100,0,     9, 207,  26}, // Белый свет
  { 1, "Color",                  1,255,1,100,1,     7,  20,  45}, // Цвет
  { 2, "Madness",                1,150,1,100,0,    11,  33,  58}, // Безумие
  { 3, "Clouds",                 1,15,1,50,0,       8,   4,  34}, // Облака
  { 4, "Lava",                   5,60,1,100,0,      8,   9,  24}, // Лава
  { 5, "Plasma",                 1,30,1,100,0,     11,  19,  59}, // Плазма
  { 6, "Rainbow 3D",             1,70,1,100,0,     11,  13,  60}, // Радуга 3D
  { 7, "Peacock",                1,15,1,30,0,      11,   5,  12}, // Павлин
  { 8, "Zebra",                  1,30,7,40,0,       7,   8,  21}, // Зебра
  { 9, "Forest",                 2,30,70,100,0,     7,   3,  95}, // Лес
  {10, "Ocean",                  2,15,4,30,0,       7,   6,  12}, // Океан
  {11, "Bouncing balls",         1,255,1,100,0,    24, 255,  60}, // Мячики
  {12, "White bouncing balls",   1,255,1,100,0,    12, 255,  60}, // Белые мячики
  {13, "Balls with a train",     1,255,1,100,0,    18,  19,  60}, // Мячики со шлейфом
  {14, "Spirals",                1,255,1,100,0,     9,  46,   3}, // Спирали
  {15, "Prismata",               1,255,1,100,0,    16, 100,   8}, // Призмата
  {16, "Flock",                  1,255,1,100,0,    15, 136,   1}, // Стая
  {17, "Flock and predator",     1,255,1,100,0,    15, 128,   1}, // Стая и хищник
  {18, "Sinusoid",               1,255,1,100,0,     7, 175,  30}, // Синусоид
  {19, "Metaballs",              1,255,1,100,0,     7,  85,   7}, // Метаболз

  {20, "Matrix",                100,240,1,100,0,    27, 186,  23}, // Матрица
  {21, "Fire 2018",            50,255,100,100,0,    50, 220, 100}, // Огонь 2018
  {22, "Fire",                   50,255,1,100,1,    19, 206,   1}, // Огонь
  {23, "White Fire",             50,255,1,100,1,     7, 180, 100}, // Белый огонь
  {24, "Blue Fire",              50,255,1,100,1,    12, 181,  53}, // Голубой огонь
  {25, "Green Fire",             50,255,1,100,1,    13, 185,  36}, // Зелёный огонь
  {26, "Whirls of flame",       100,255,1,100,1,     9, 240,   1}, // Вихри пламени
  {27, "Color whirls",          100,255,1,100,1,     9, 240,   1}, // Разноцветные вихри
  {28, "Waterfall",              50,255,1,100,1,     7, 188,  63}, // Водопад
  {29, "White waterfall",        50,255,1,100,1,     5, 176, 100}, // Белый водопад
  {30, "Waterfall 4 in 1",       50,255,1,100,0,     7, 183,  85}, // Водопад 4 в 1
  {31, "Pool",                  100,255,1,100,1,     8, 222,  63}, // Бассейн
  {32, "Slow pulse",             50,255,1,100,0,    12, 185,   6}, // Медленный пульс
  {33, "Fast pulse",             50,255,1,100,0,    11, 185,  81}, // Быстрый пульс
  {34, "Rainbow pulse",          50,255,1,100,0,    11, 185,  31}, // Радужный пульс
  {35, "White pulse",            50,255,1,100,0,     9, 179,  11}, // Белый пульс
  {36, "Comet",                  60,255,1,100,2,    16, 220,  28}, // Комета
  {37, "White comet",            60,255,1,100,0,    12, 208, 100}, // Белая комета
  {38, "Plain Comet",            60,255,1,100,1,    14, 212,  69}, // Одноцветная комета
  {39, "Pulsating comet",        60,255,1,100,0,    14, 209,   1}, // Пульсирующая комета
  {40, "Two comets",             60,255,1,100,0,    27, 186,  19}, // Две кометы
  {41, "Three comets",           60,255,1,100,0,    24, 186,   9}, // Три кометы

  {42, "Soaring fire",           60,255,1,100,0,    26, 206,  15}, // Парящий огонь
  {43, "Top fire",               60,255,1,100,0,    26, 190,  15}, // Верховой огонь
  {44, "Rainbow snake",        60,255,100,100,0,    12, 178, 100}, // Радужный змей
  {45, "Confetti",               60,255,1,100,0,    16, 142,  63}, // Конфетти
  {46, "Rainbow vertical",       50,255,1,100,0,     8, 196,  18}, // Радуга вертикальная
  {47, "Rainbow horizontal",     50,255,1,100,0 ,    8, 196,  23}, // Радуга горизонтальная
  {48, "Rainbow diagonal",       50,255,1,100,0,     8, 180,  24}, // Радуга диагональная
  {49, "Waves",                 220,255,1,100,0,     9, 236, 100}, // Волны
  {50, "Snowfall",               50,255,1,100,0,     9, 180,  90}, // Снегопад
  {51, "Colored rain",           60,255,1,100,1,    15, 225,  63}, // Цветной дождь
  {52, "Snowstorm",              50,255,1,100,0,     7, 193,  37}, // Метель
  {53, "Starfall",               50,255,1,100,0,    12, 199,  40}, // Звездопад
  {54, "Fireflies",              50,240,1,100,0,    15, 157,  23}, // Светлячки
  {55, "Fireflies with a train", 50,240,1,100,0,    21, 198,  93}, // Светлячки со шлейфом
  {56, "Paintball",             215,255,1,100,0,    11, 236,   7}, // Пейнтбол
  {57, "Wandering Cube",         70,235,1,100,0,     7, 160,  69}, // Блуждающий кубик
  {58, "Change of color",         1,255,1,100,0,     6,  50,   5}, // Смена цвета

  {59, "Cloud in the jar",       100,1,1,100,0,      15, 225,  63}, // Тучка в банке
  {60, "Thunder in the jar",     255,1,1,100,0,      15, 225,  63}, // Гроза в банке
  {61, "Twinkles",               255,1,1,100,0,      16, 142,  63}, // Мерцание

  {62, "Ticker",                 1,255,1,100,1,      10,  99,  38} // Бегущая строка
};
const uint8_t MODE_AMOUNT = ARRAY_ROWS(effects);

static String getEffectsListJson(bool withNumbers) {
  String ret = String("{\"effectsCount\":")+String(MODE_AMOUNT);
  ret+= String(", \"effects\":");

  ret+="[";
  for (uint8_t i = 0; i < MODE_AMOUNT; i++) {
    ret+="{";

    ret+="\"id\": ";
    ret+= pgm_read_byte(&effects[i].Id);
    ret+=", ";

    ret+="\"num\": ";
    ret+= i;
    ret+=", ";

    ret+="\"name\": \"";

    if(withNumbers){
      ret+= i;
      ret+=". ";
    }
    char buf[MAX_EFF_NAME_LNG];
    strcpy_P (buf, effects[i].Name);
    ret+= String(buf);
    ret+="\"";

    ret+="}";
    
    if(i < MODE_AMOUNT-1) {
      ret+=", ";
    }
  }
  ret+="]";
  ret+="}";
  return ret;
}

static EffectType getEffect(uint8_t num) {
  EffectType effect;

  effect.Id = pgm_read_byte(&effects[num].Id);
  strcpy_P (effect.Name, effects[num].Name);
  effect.SpeedMin= pgm_read_byte(&effects[num].SpeedMin);
  effect.SpeedMax= pgm_read_byte(&effects[num].SpeedMax);
  effect.ScaleMin= pgm_read_byte(&effects[num].ScaleMin);
  effect.ScaleMax= pgm_read_byte(&effects[num].ScaleMax);
  effect.ScaleType= pgm_read_byte(&effects[num].ScaleType);
  effect.defaultBrightness= pgm_read_byte(&effects[num].defaultBrightness);
  effect.defaultSpeed= pgm_read_byte(&effects[num].defaultSpeed);
  effect.defaultScale= pgm_read_byte(&effects[num].defaultScale);
  
  return effect;
}

static ModeType getEffectDefaultSetting(uint8_t num) {
  ModeType mode;
  mode.Brightness = pgm_read_byte(&effects[num].defaultBrightness);
  mode.Speed = pgm_read_byte(&effects[num].defaultSpeed);
  mode.Scale = pgm_read_byte(&effects[num].defaultScale);
  return mode;
}

#define CNT_LISTS                (3U)
static String getEffectsList(uint8_t num, bool withNumbers) {
  /* Format: Name, min speed, max speed, min scale, max scale, scale type (0-scale,1-color, 2-for comet (1/2 scale + 1/2 color)
   *   String("[42. ]Soaring fire,60,255,1,100,0;") +
   *  ...
   *   String("[41. ]Three comets,60,255,1,100,0;") +
   *   String(+ "\n");
   */

  if (num > (CNT_LISTS-1)) {
    num = CNT_LISTS-1;
  }
  uint8_t tX = MODE_AMOUNT / CNT_LISTS;
  uint8_t iFrom = num*tX;
  uint8_t iTo = iFrom+tX;
  if(iTo > MODE_AMOUNT) {
    iTo = MODE_AMOUNT;
  }

  String ret = String("LIST");
  ret+= String(num+1);
  ret+= ";";
  for (uint8_t i = iFrom; i < iTo; i++) {
    EffectType effect = getEffect(i);
    if(withNumbers) {
      ret+=String(i+1);
      ret+=". ";
    }
    // name
    ret+=String(effect.Name);
    ret+=",";
    // min speed
    ret+=String(effect.SpeedMin);
     ret+=",";
    // max speed
    ret+=String(effect.SpeedMax);
    ret+=",";
    // min scale
    ret+=String(effect.ScaleMin);
    ret+=",";
    // max scale
    ret+=String(effect.ScaleMax);
    ret+=",";
    // scale type
    ret+=String(effect.ScaleType);
    ret+=";";
  }
  ret+="\n";
  
  return ret;
}
