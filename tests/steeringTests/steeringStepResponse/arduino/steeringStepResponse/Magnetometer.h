

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

//magn x,y,z (min/max) = -427.00/637.00  -416.00/520.00  -173.00/603.00
//magn x,y,z (min/max) = -400.00/500.00  -272.00/523.00  -205.00/603.00
//magn x,y,z (min/max) = -432.00/639.00  -400.00/591.00  -233.00/654.00
//magn x,y,z (min/max) = -464.00/698.00  -386.00/577.00  -265.00/608.00


//magn x,y,z (min/max) = -451.00/630.00  -434.00/586.00  -180.00/661.00
//magn x,y,z (min/max) = -423.00/686.00  -432.00/564.00  -235.00/666.00
//magn x,y,z (min/max) = -494.00/608.00  -419.00/595.00  -284.00/568.00
