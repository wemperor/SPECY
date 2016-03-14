#define DS1307_I2C_ADDRESS 0x68  // This is the I2C address

// Convert normal decimal numbers to binary coded decimal
byte decToBcd(byte val)
{
  return ( (val / 10 * 16) + (val % 10) );
}

// Convert binary coded decimal to normal decimal numbers
byte bcdToDec(byte val)
{
  return ( (val / 16 * 10) + (val % 16) );
}

// Gets the date and time from the ds1307 and prints result
String getDateRTC()
{
  // Reset the register pointer
  Wire.beginTransmission(DS1307_I2C_ADDRESS);
  byte zero = 0x00;
  Wire.write(zero);
  Wire.endTransmission();
  Wire.requestFrom(DS1307_I2C_ADDRESS, 7);

  byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;
  // A few of these need masks because certain bits are control bits
  second     = bcdToDec(Wire.read() & 0x7f);
  minute     = bcdToDec(Wire.read());
  hour       = bcdToDec(Wire.read() & 0x3f);  // Need to change this if 12 hour am/pm
  dayOfWeek  = bcdToDec(Wire.read());
  dayOfMonth = bcdToDec(Wire.read());
  month      = bcdToDec(Wire.read());
  year       = bcdToDec(Wire.read());

  String date = "";

  
  if (year < 10) date += ("0");
  date  += String(year, DEC);
  if (month < 10) date += "0";
  date += String(month, DEC);
  if (dayOfMonth < 10) date += "0";
  date += String(dayOfMonth, DEC);

    
  return(date);

}

String getTimeRTC()
{
  // Reset the register pointer
  Wire.beginTransmission(DS1307_I2C_ADDRESS);
  byte zero = 0x00;
  Wire.write(zero);
  Wire.endTransmission();
  Wire.requestFrom(DS1307_I2C_ADDRESS, 7);

   byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;
  // A few of these need masks because certain bits are control bits
  second     = bcdToDec(Wire.read() & 0x7f);
  minute     = bcdToDec(Wire.read());
  hour       = bcdToDec(Wire.read() & 0x3f);  // Need to change this if 12 hour am/pm
  dayOfWeek  = bcdToDec(Wire.read());
  dayOfMonth = bcdToDec(Wire.read());
  month      = bcdToDec(Wire.read());
  year       = bcdToDec(Wire.read());
  
  String time = "";

  if (hour < 10)  time += ("0");
  time += String(hour, DEC);
  if (minute < 10) time += ("0");
  time += String(minute, DEC);
  if (second < 10) time += ("0");
  time += String(second, DEC);
  
  return(time);

}


String getTimeRTCScreen()
{
  // Reset the register pointer
  Wire.beginTransmission(DS1307_I2C_ADDRESS);
  byte zero = 0x00;
  Wire.write(zero);
  Wire.endTransmission();
  Wire.requestFrom(DS1307_I2C_ADDRESS, 7);

   byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;
  // A few of these need masks because certain bits are control bits
  second     = bcdToDec(Wire.read() & 0x7f);
  minute     = bcdToDec(Wire.read());
  hour       = bcdToDec(Wire.read() & 0x3f);  // Need to change this if 12 hour am/pm
  dayOfWeek  = bcdToDec(Wire.read());
  dayOfMonth = bcdToDec(Wire.read());
  month      = bcdToDec(Wire.read());
  year       = bcdToDec(Wire.read());
  
  String time = "";

  if (hour < 10)  time += ("0");
  time += String(hour, DEC);
  time +=":";
  if (minute < 10) time += ("0");
  time += String(minute, DEC);
  time +=":";
  if (second < 10) time += ("0");
  time += String(second, DEC);
  
  return(time);

}

