void initialise_SD() {
  if (!SD.begin(4)) {
    Serial.println("SD error");
    while (1 == 1) {  //if there is something wrong, just keep blinking
      blink_wildly(1000);
    }
    return;
  }
  else {
    Serial.println("SD ok");
    delay(300);
    SD_ok = true;
    
    //write startup line to logfile
    SDcard = SD.open("specylog.csv", O_CREAT | O_WRITE);
    SDcard.print(getDateRTC());
    SDcard.print(";");
    SDcard.print(getTimeRTC());
    SDcard.print(";temp=;");
    SDcard.print(sts_get_temp(0));
    SDcard.print(";Version 0.1;");
    SDcard.print("save_every_s=;");
    SDcard.println(spec_every_sec);
    SDcard.close();
  }
}


String set_dir_and_file() {

  getDateRTC().toCharArray(current_path, 8);
  //creates the current working directory
  if (SD.mkdir(current_path)) {
    Serial.print(current_path);
    Serial.println(" DIR ok");
    delay(500);
  }
  else {
    Serial.print(current_path);
    Serial.println(" DIR error");
    while (1 == 1) { //if there is something wrong, just keep blinking
      blink_wildly(1000);
    }
  }

  //sets the current_file name inside the directory
  String current_file = getDateRTC() + "/" + getTimeRTC() + ".csv";
  current_file.toCharArray(current_file_name, 18); //current_file_name is a global variable
  //Serial.println(current_file);

  return current_file;
}

void save_to_sd() {
  SDcard = SD.open(current_file_name, O_CREAT | O_WRITE);

  SDcard.print(getDateRTC());
  SDcard.print(";");
  SDcard.print(getTimeRTC());
  SDcard.print(";");
  SDcard.print("ms_since_start=;");
  SDcard.print(millis());
  SDcard.print(";temp=;");
  SDcard.print(sts_get_temp(0));
  SDcard.print(";IT=;");
  SDcard.print(int_time);
  SDcard.print(";spec num=;");
  SDcard.print(cycle_number);
  SDcard.print(";");

  for (int i = 0; i < 1024; i += 2) {
    SDcard.print(word(spectrum[i + 1], spectrum[i]));
    SDcard.print(";");
  }

  SDcard.println(";");
  SDcard.close();

  Serial.println("spec saved");
}


