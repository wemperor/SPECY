/* The STS Protocoll http://oceanoptics.com/support/technical-documents/ for control messages is build up by 64 Bytes,
 most of them always have the same value and order and are presented in the
 functions:

 sts_header - the head of the message
 sts_middle - the unchanging middle part of the protocol
 sts_footer - the end of the message

 those functions do not include a checksum functionality and only
 messages with a input data up to 4 byte.

 A message will be built in the following:

 sts_header()
 4 bytes of message type
 sts_middle()
 1 byte of input length
 4 bytes of input
 sts_footer()

 see the sts_example_message() for an example

 */

void sts_header() {

  Serial1.write((byte)0xC1);  //0   Start Byte 1
  Serial1.write((byte)0xC0);  //1   Start Byte 2

  Serial1.write((byte)0x00);  //2   Protokoll Version
  Serial1.write((byte)0x10);  //3   Protokoll Version

  Serial1.write((byte)0x00);  //4   Flag
  Serial1.write((byte)0x00);  //5   Flag

  Serial1.write((byte)0x00);  //6   Error Number
  Serial1.write((byte)0x00);  //7  Error Number
}

void sts_middle() {
  Serial1.write((byte)0x00);  //12  User specific
  Serial1.write((byte)0x00);  //13  User specific
  Serial1.write((byte)0x00);  //14  User specific
  Serial1.write((byte)0x00);  //15  User specific

  Serial1.write((byte)0x00);  //16  Reserved
  Serial1.write((byte)0x00);  //17  Reserved
  Serial1.write((byte)0x00);  //18  Reserved
  Serial1.write((byte)0x00);  //19  Reserved
  Serial1.write((byte)0x00);  //20  Reserved
  Serial1.write((byte)0x00);  //21  Reserved

  Serial1.write((byte)0x00);  //22  Checksum type (0x00) = no checksum given

}

void sts_footer() {

  Serial1.write((byte)0x00);  //28  unused
  Serial1.write((byte)0x00);  //29  unused
  Serial1.write((byte)0x00);  //30  unused
  Serial1.write((byte)0x00);  //31  unused
  Serial1.write((byte)0x00);  //32  unused
  Serial1.write((byte)0x00);  //33  unused
  Serial1.write((byte)0x00);  //34  unused
  Serial1.write((byte)0x00);  //35  unused
  Serial1.write((byte)0x00);  //36  unused
  Serial1.write((byte)0x00);  //37  unused
  Serial1.write((byte)0x00);  //38  unused
  Serial1.write((byte)0x00);  //39  unused

  Serial1.write((byte)0x14);  //40  Bytes remaining
  Serial1.write((byte)0x00);  //41
  Serial1.write((byte)0x00);  //42
  Serial1.write((byte)0x00);  //43

  //No Payload here

  Serial1.write((byte)0x00);  //44  unused Checksum bytes
  Serial1.write((byte)0x00);  //45  unused
  Serial1.write((byte)0x00);  //46  unused
  Serial1.write((byte)0x00);  //47  unused
  Serial1.write((byte)0x00);  //48  unused
  Serial1.write((byte)0x00);  //49  unused
  Serial1.write((byte)0x00);  //50  unused
  Serial1.write((byte)0x00);  //51  unused
  Serial1.write((byte)0x00);  //52  unused
  Serial1.write((byte)0x00);  //53  unused
  Serial1.write((byte)0x00);  //54  unused
  Serial1.write((byte)0x00);  //55  unused
  Serial1.write((byte)0x00);  //56  unused
  Serial1.write((byte)0x00);  //57  unused
  Serial1.write((byte)0x00);  //58  unused
  Serial1.write((byte)0x00);  //59  unused

  Serial1.write((byte)0xC5);  //60  Footer
  Serial1.write((byte)0xC4);  //61  Footer
  Serial1.write((byte)0xC3);  //62  Footer
  Serial1.write((byte)0xC2);  //63  Footer
}


void sts_get_spectrum() { //asks the STS for a spectrum

  sts_header();

  Serial1.write(byte(0));  //8
  Serial1.write((byte)0x10);  //9
  Serial1.write((byte)0x10);  //10
  Serial1.write(byte(0));  //11  Message Type

  sts_middle();

  Serial1.write(byte(0));  //23  Immediate length

  Serial1.write(byte(0));  //24  unused
  Serial1.write(byte(0));  //25  unused
  Serial1.write(byte(0));  //26  unused
  Serial1.write(byte(0));  //27  unused

  sts_footer();

}

void sts_set_baudrate(unsigned long val) {

  sts_header();

  Serial1.write((byte)0x10);  //8
  Serial1.write((byte)0x08);  //9
  Serial1.write((byte)0x00);  //10
  Serial1.write((byte)0x00);  //11  Message Type

  sts_middle();

  Serial1.write((byte)0x04);  //23  Immediate length

  byte byte1 = val & 0xff;
  byte byte2 = (val >> 8) & 0xff;
  byte byte3 = (val >> 16) & 0xff;
  byte byte4 = (val >> 24) & 0xff;

  Serial1.write((byte)byte1);  //24  baudrate
  Serial1.write((byte)byte2);  //25  baudrate
  Serial1.write((byte)byte3);  //26  baudrate
  Serial1.write((byte)byte4);  //27  baudrate

  sts_footer();

}

void sts_reset() {

  sts_header();

  Serial1.write(byte(0));  //8
  Serial1.write(byte(0));  //9
  Serial1.write(byte(0));  //10
  Serial1.write(byte(0));  //11  Message Type

  sts_middle();

  Serial1.write(byte(0));  //23  Immediate length

  Serial1.write(byte(0));  //24  unused
  Serial1.write(byte(0));  //25  unused
  Serial1.write(byte(0));  //26  unused
  Serial1.write(byte(0));  //27  unused

  sts_footer();

}

void sts_set_it(unsigned long val) {

  sts_header();

  Serial1.write((byte)0x10);  //8
  Serial1.write((byte)0x00);  //9
  Serial1.write((byte)0x11);  //10
  Serial1.write((byte)0x00);  //11  Message Type

  sts_middle();

  Serial1.write((byte)0x04);  //23  Immediate length

  //split the long value to 4 bytes
  byte byte1 = val & 0xff;
  byte byte2 = (val >> 8) & 0xff;
  byte byte3 = (val >> 16) & 0xff;
  byte byte4 = (val >> 24) & 0xff;

  Serial1.write((byte)byte1);  //24  Int Time
  Serial1.write((byte)byte2);  //25  Int Time
  Serial1.write((byte)byte3);  //26  Int Time
  Serial1.write((byte)byte4);  //27  Int Time

  sts_footer();

}


unsigned long strTolong(String number) {
  unsigned long num = 0;
  for (int i = 0; i < number.length(); i++) {
    num = num * 10 + (number[i] - '0');
  }
  return num;
}


void STS_get_full_spectrum() {
  //stores a 1024 byte spectrum in the spectrum[] global array
  //finetuned for speed, it takes IT + 219ms to read the full spectrum to the array 20130730

  int counter = 0;
  long wait_for = 0;
  byte sent_byte;
  sts_get_spectrum();
  while ((Serial1.available() == 0) && (wait_for < int_time + 100)) {
    delayMicroseconds(1); //taking into account the integration time
    wait_for++;
  } //wait for the STS to send Data

  for (int i = 0; i < 400000; i++) { //the loop is necessary to catch all data as the arduino sometimes reads the buffer to fast
    while (Serial1.available()) {
      sent_byte = (Serial1.read());
      if ((counter > 43) && (counter < 1072)) { //cuts the 2048 bytes of payload out of the message
        spectrum[counter - 44] = sent_byte; //saves the byte value in the spectrum array
      }
      counter++;
      if ((counter == 1088) && (Serial1.available() == 0)) i = 400000; //jumps out of the loop if the message is received and the serial buffer empty
    }
  }

  if (counter == 1088)
  {
    //Serial.print(("spec done "));
  }
  else {
    Serial.println(("spec error "));
    Serial.print(counter - 64);
    spectrum_count = counter - 64; //how many pixel were saved
    Serial.println((" bytes"));
  }
}


float sts_get_temp(int sensor_number) {
  //20130730 adapted to Arduino DUE and 115200 BAUD -> working
  //optimised for speed (takes around 14 ms)

  sts_header();

  Serial1.write((byte)0x01);  //8
  Serial1.write((byte)0x00);  //9
  Serial1.write((byte)0x40);  //10
  Serial1.write((byte)0x00);  //11  Message Type

  sts_middle();

  Serial1.write((byte)0x01);  //23  Immediate length

  //split the long value to 4 bytes
  byte byte1 = byte((sensor_number >> 0) & 0xff);

  Serial1.write((byte)byte1);  //24  Int Time
  Serial1.write((byte)0x00);  //25  Int Time
  Serial1.write((byte)0x00);  //26  unused
  Serial1.write((byte)0x00);  //27  unused

  sts_footer();

  int counter = 0;
  float temp = 0;
  long wait_for = 0;
  while ((Serial1.available() == 0) && (wait_for < 10000)) {
    wait_for++;
  } //wait for the STS to send Data usually after 1000 cycles the STS should sent the temp value
  delay(1);
  while (Serial1.available()) {
    int dummy = Serial1.read(); //waste the header and footer informations
    if ((counter > 22) && (counter < 27)) {
      byte data[] = {
        byte(Serial1.read()), byte(Serial1.read()), byte(Serial1.read()), byte(Serial1.read())
      };
      temp = byteArrayToFloat(data);

      counter = counter + 3; //jump to the footer block
    }
    counter++;
    delayMicroseconds(100); //necessary to wait for the coming data
  }

  return temp;
}

float byteArrayToFloat(byte byteArray[]) {
  float value;

  union u_tag {
    byte b[4];
    float fval;
  }
  u;

  u.b[0] = byteArray[0];
  u.b[1] = byteArray[1];
  u.b[2] = byteArray[2];
  u.b[3] = byteArray[3];

  value = u.fval;
  return value;
}


void initialise_STS(byte binning) {
  //intialises the STS on Serial1 and sets speed to 115200 BAUD

  Serial1.begin(9600); // (PIN 18TX/19RX, STS will after startup listen at 9600 baud
  sts_reset();
  delay(1000);  //after reset STS needs 1 second for initialization
  sts_set_baudrate(115200);  //set baudrate to maximum speed
  Serial1.end();
  delay(100);
  Serial1.begin(115200);  //initialise STS serial at defined baudrate
  delay(100);
  sts_set_it(int_time);  //set integration time in µs
  delay(100);
  sts_set_binning(binning);

  //check of the STS by trying to readout the temperature (fails in the winter when temperature = 0.0 °C)
  float start_temp1 = (sts_get_temp(0));
  float start_temp2 = (sts_get_temp(2));

  if (start_temp1 != 0) { //if sts_get_temp has timeout it gives 0 back

    Serial.println("STS ok");
    Serial.print("Temp: ");
    Serial.print(start_temp1);
    Serial.println(" C");
    STS_ok = true;
  }
  else {
    Serial.println("STS error");
    while (1 == 1) { //if there is something wrong, just keep blinking
      blink_wildly(1000);
    }
  }
}


int STS_find_peak() {
  //searches through the White Reference array and gives the highest value
  int maxE = 0;
  int pointer = 0;
  for (int i = 100; i < spectrum_length - 100; i += 2) {
    pointer = (word(spectrum[i + 1], spectrum[i]));
    if ((pointer > maxE) && (pointer < 17000)) maxE = pointer;
    //values bigger than 17.000 are wrong readings
  }
  return maxE;
}


long STS_optimise_it() {//using the unit to find a good integration time
  //seems to work 05.02.2013
  unsigned long the_moment = millis();

  int peak = 0;
  int last_peak = 0;
  int_time = 8000;
  sts_set_it(int_time);

  while ( (peak < 8000) && (int_time < 4000000)) {  //search for the right light amount

    int_time = int_time * 2;
    sts_set_it(int_time);

    STS_get_full_spectrum();

    peak = STS_find_peak();
    //Serial.println(int_time);
    //Serial.println(peak);

    if (peak < 8000) last_peak = peak;
  }

  float  it_slope = (peak - last_peak) / (float(int_time) - (float(int_time) / 2)); //calculates the slope of the signal dependent on the IT time
  unsigned long opt_it = long(13000 / it_slope);

  if (opt_it > max_int_time) opt_it = max_int_time;  //maximum integration time

  //Serial.print(F("optimised IT: "));
  //Serial.println(opt_it);

  if (peak == last_peak) { //no good IT was found
    sts_set_it(max_int_time);
    int_time = max_int_time;
    //Serial.println(F("IT max"));
  }
  else {
    sts_set_it(opt_it);
    int_time = opt_it;
  }

  return  millis() - the_moment;

}


void sts_set_binning(byte binning) {

  sts_header();

  Serial1.write((byte)0x90);  //8
  Serial1.write((byte)0x02);  //9
  Serial1.write((byte)0x11);  //10
  Serial1.write((byte)0x00);  //11  Message Type

  sts_middle();

  Serial1.write((byte)0x01);  //23  Immediate length

  //split the long value to 4 bytes
  byte byte1 = byte((binning >> 0) & 0xff);

  Serial1.write((byte)byte1);  //24  Int Time
  Serial1.write((byte)0x00);  //25  Int Time
  Serial1.write((byte)0x00);  //26  unused
  Serial1.write((byte)0x00);  //27  unused

  sts_footer();
}







