

#define OUTPUT__DATA_INTERVAL 20  // in milliseconds

#define MAGN_X_MIN ((float) -575) //Normal -600 to 600
#define MAGN_X_MAX ((float) 318)
#define MAGN_Y_MIN ((float) -316)
#define MAGN_Y_MAX ((float) 563)
#define MAGN_Z_MIN ((float) -390)
#define MAGN_Z_MAX ((float) 507)
#define MAGN_X_OFFSET ((MAGN_X_MIN + MAGN_X_MAX) / 2.0f)
#define MAGN_Y_OFFSET ((MAGN_Y_MIN + MAGN_Y_MAX) / 2.0f)
#define MAGN_Z_OFFSET ((MAGN_Z_MIN + MAGN_Z_MAX) / 2.0f)
#define MAGN_X_SCALE (100.0f / (MAGN_X_MAX - MAGN_X_OFFSET))
#define MAGN_Y_SCALE (100.0f / (MAGN_Y_MAX - MAGN_Y_OFFSET))
#define MAGN_Z_SCALE (100.0f / (MAGN_Z_MAX - MAGN_Z_OFFSET))

#define MAGN_ADDRESS  ((int) 0x1E) // 0x1E = 0x3C / 2

double CompassGet();
void CompassSetup();
