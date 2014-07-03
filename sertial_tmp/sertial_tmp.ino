#define DBGLED 13
#define DATASET 9

// prototype
void sendData( unsigned char dat );

unsigned char dat_tmp[DATASET] = {50, 90, 100, 120, 180, 200, 220, 240, 255};
//unsigned char dat_tmp[DATASET] = {255, 255, 255, 255, 255, 255, 255, 255, 255};

void setup()
{
  pinMode( DBGLED, OUTPUT );
  Serial.begin( 9600 );
}

void loop()
{
  int i = 0;
  digitalWrite( DBGLED, HIGH );
  for( i = 0; i < DATASET; i++  ) {
    sendData( dat_tmp[i] );
  }
}

void sendData( unsigned char dat )
{
  Serial.write( dat );
  delay( 500 );
}
