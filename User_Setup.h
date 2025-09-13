//                            USER SETUP FOR LILYGO H621
//   Setup for the ESP32 based Lilygo H621 with 2.4" TFT display and touch
//                            Touch pins need to be defined

// Define to disable all use of the TFT_ESPI library setups files
#define USER_SETUP_LOADED

// ESP32 based TFT display, 2.4 inch, 320x240 pixels, ILI9341 or similar driver
#define TFT_WIDTH  240
#define TFT_HEIGHT 320

// Generic ESP32 setup for TFT display connections
#define TFT_MISO 19
#define TFT_MOSI 23  
#define TFT_SCLK 18
#define TFT_CS   5   // Chip select control pin
#define TFT_DC   2   // Data Command control pin (RS)
#define TFT_RST  4   // Reset pin (could connect to RST pin)
#define TFT_BL   15  // LED backlight control pin

// Touch screen chip select pin
#define TOUCH_CS 33  // Chip select pin (T_CS) of touch screen

// Use HSPI port for TFT
#define TFT_SPI_PORT HSPI_HOST

// Display driver for ILI9341 (common on Lilygo H621)
#define ILI9341_DRIVER

// Color order
#define TFT_RGB_ORDER TFT_BGR  // Colour order Red-Green-Blue

// Font loading
#define LOAD_GLCD   // Font 1. Original Adafruit 8 pixel font needs ~1820 bytes in FLASH
#define LOAD_FONT2  // Font 2. Small 16 pixel high font, needs ~3534 bytes in FLASH, 96 characters
#define LOAD_FONT4  // Font 4. Medium 26 pixel high font, needs ~5848 bytes in FLASH, 96 characters  
#define LOAD_FONT6  // Font 6. Large 48 pixel font, needs ~2666 bytes in FLASH, only characters 1234567890:-.apm
#define LOAD_FONT7  // Font 7. 7 segment 48 pixel font, needs ~2438 bytes in FLASH, only characters 1234567890:.
#define LOAD_FONT8  // Font 8. Large 75 pixel font needs ~3256 bytes in FLASH, only characters 1234567890:-.
#define LOAD_GFXFF  // FreeFonts. Include access to the 48 Adafruit_GFX free fonts FF1 to FF48 and custom fonts

// Smooth graphics
#define SMOOTH_FONT

// SPI frequency for TFT
#define SPI_FREQUENCY  27000000 // 27MHz for display

// Optional: SPI frequency for reading from TFT  
#define SPI_READ_FREQUENCY  20000000

// SPI frequency for the touch controller
#define SPI_TOUCH_FREQUENCY  2500000