///////////////////////////////////////////////////////////////////
//////////////////Coded by Maico Ditzel December 2019//////////////
///////////////////////////////////////////////////////////////////

#define FASTLED_INTERNAL

#include <Preferences.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <FastLED.h>
#include "charbinaries.h"
#include "variables.h"
#include "webpage.h"
#include "redirectpage.h"

#define NUM_LEDS 16
#define DATA_PIN 27

const char* ssid = "[your SSID]";
const char* password = "[your wireless password]";

WebServer server(80);

Preferences preferences;

CRGB leds[NUM_LEDS];

///set initial color & brightness & speed & text/////////////////
long startcolorval = 0xFF0000;
long colorval = startcolorval;
//------------------------------------------------------------///
int startbrightness = 9;
int brightness = startbrightness;
//------------------------------------------------------------///
int scrollspeed = 110; //initial scrollspeed
//------------------------------------------------------------///
int ipdisplaytimesmax = 2;
//------------------------------------------------------------///

void setup() {

  Serial.begin(115200);

  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);

  FastLED.setBrightness( brightness );

  wifilogin();

  server.on("/", handleRoot);

  server.on("/postForm", handlePostForm);

  server.begin();

  processtext();

  //if esp32 is 'new' and not having the texthistory array saved to its flash
  //this will write a default texthistory array to flash

  preferences.begin("storage", false);

  firstrun = preferences.getInt("firstrun");

  if (firstrun == 0) {

    writedefaulttexthistory(); //writes initial slot data

    firstrun = 1;

    preferences.putInt("firstrun", firstrun);

  }

  preferences.end();

  retrievetexthistoryfromflash();

  inputtext = hist[0];

  processtext();

}


void loop() {

  server.handleClient();

  if (ipdisplayoff == 1) {

    for (horzshift = 0; horzshift < 5; horzshift++) {

      for (horzlines = 0; horzlines < 5; horzlines ++) { //4 sideways vertical lines from font

        server.handleClient();

        pin = (horzlines * 4);

        for (vertpixels = 0; vertpixels < 4; vertpixels ++) { //4 vertical pixels from font

          horzlinesedit = horzlines + horzshift;

          if (horzlinesedit > 4)  {
            horzlinesedit = horzlinesedit - 5;
            writepixelcharnext();
          }
          else {
            writepixelcharprev();
          }

          //Serial.print ( font[ fontplace[pointer] ] [horzlinesedit] [vertpixels]);//not display position but font position !!!

          pin++;

        }

      }

      if (textfading == "on") {
        fadewason = 1;
        textfader();
      }
      else {
        if (fadewason == 1) {
          FastLED.setBrightness( startbrightness );
          fadewason = 0;
        }
      }

      if (ccycle == "on") {
        ccyclewason = 1;
        colorcycle();
      }
      else {
        if ( (ccyclewason == 1) && (textcolor == "0x000000") && (stdcolor == "") ) {
          colorval = startcolorval;
          ccyclewason = 0;
        }
        if (ccyclewason == 1) {
          ccyclewason = 0;
        }
      }

      FastLED.show();

      delay (scrollspeed);

      cleardisplay();

    }

    pointer++;

    if (pointer > (textlen - 1)) {
      pointer = 0;
      delay (2000); //wait some time before restarting scrolltext
    }

  }

  else {

    showip();

    cleardisplay();

    if (ipdisplaytimes == ipdisplaytimesmax) {
      ipdisplayoff = 1;
      processtext();
      FastLED.setBrightness( startbrightness );
      delay (500);
      stopipdisplay();
    }

  }

  server.handleClient();

  //Serial.println(ESP.getFreeHeap());//shows if ESP32 has enough heap space left

}


void showip()
{

  for (horzlines = 0; horzlines < 5; horzlines ++) { //4 sideways vertical lines from font

    pin = (horzlines * 4);

    for (vertpixels = 0; vertpixels < 4; vertpixels ++) { //4 vertical pixels from font

      if ( font[fontplace[pointer]][horzlines][vertpixels] == '1' ) {
        leds[pins [pin]] = colorval;
      }

      pin++;

    }

  }

  for (fade = 0; fade <= brightness; fade++) {
    FastLED.setBrightness(fade);
    FastLED.show();
    delay (25);
  }

  for (fade = brightness; fade >= 0; fade--) {
    FastLED.setBrightness(fade);
    FastLED.show();
    delay (25);
  }

  if (pointer == textlen - 1) {
    ipdisplaytimes++;
    pointer = 0;

    if (ipdisplaytimes < ipdisplaytimesmax) {
      delay (2000);
    }

  }
  else {
    pointer++;
  }

}


void writepixelcharprev ()
{

  if ( ( font[fontplace[pointer]][horzlinesedit][vertpixels] == '1' ) && (pin < 16) ) {
    leds[pins [pin]] = colorval;
  }

}


void writepixelcharnext ()
{
  pointernext = pointer + 1;
  if (pointernext > (textlen - 1)) {
    pointernext = 0;
  }

  if ( ( font[fontplace[pointernext]][horzlinesedit][vertpixels] == '1' ) && (pin < 16) ) {
    leds[pins [pin]] = colorval;
  }

}


void cleardisplay()
{
  for (fulldisp = 0; fulldisp < 16; fulldisp++) {
    leds[pins[fulldisp]] = CRGB::Black;
  }
  FastLED.show();
}


void stopipdisplay()
{

  for (fulldisp = 0; fulldisp < 16; fulldisp++) {
    leds[fadepins[fulldisp]] = CRGB::Red;
    FastLED.show();
    delay(15);
  }

  for (fulldisp = 15; fulldisp >= 0; fulldisp--) {
    leds[fadepins[fulldisp]] = CRGB::Black;
    FastLED.show();
    delay(15);
  }

}


void wifilogin() {

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  //connection not yet established symbol

  FastLED.setBrightness( startbrightness );
  for (int pos = 0; pos < 4; pos++) {
    leds[emptysquare[pos]] = CRGB::Red;
  }
  FastLED.show();

  //establishing connection

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  //connection established ! deleting symbol

  cleardisplay();

  Serial.println("\n");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

}


void processtext() {

  if (ipdisplayoff == 0) {

    text = (WiFi.localIP().toString());
  }

  else {
    text = " " + inputtext + "  ";

  }

  textlen = text.length();
  text.toUpperCase();

  for (pointer = 0; pointer < textlen; pointer++) {
    fontplace[pointer] = (text.charAt(pointer) - 65);
    if (fontplace[pointer] == -33) {
      fontplace[pointer] = 26;
    }
    if (fontplace[pointer] == -19) {
      fontplace[pointer] = 27;
    }
    if (fontplace[pointer] == -32) {
      fontplace[pointer] = 28;
    }
    if (fontplace[pointer] == -2)  {
      fontplace[pointer] = 29;
    }
    if (fontplace[pointer] == -21) {
      fontplace[pointer] = 30;
    }
    if ((fontplace[pointer] >= -17) && (fontplace[pointer] <= -7)) {
      fontplace[pointer] = fontplace[pointer] + 48;
    }
  }
  pointer = 0;
}


void handleRoot() {

  if (firstaccess == 0) {
    firstaccess = 1;
    ipdisplayoff = 1;
    inputtext = "welcome";
    processtext();
    FastLED.setBrightness( startbrightness );
  }


  savevarsinpage(); //write scrolltext user settings variables AND "text history array read from flash memory" into javascript code and build rest of returned webpage

  server.send(200, "text/html", message); //serve the built webpage

}


void handlePostForm() {

  retrievetexthistoryfromflash();

  feedbacktext = server.arg("mytext");

  if (feedbacktext.length() == 0) {
    feedbacktext = "please enter text";
  }

  if (feedbacktext != hist[0]) {
    savetexttoflash(); //saves new text in flash and shifts old text history one slot down
  }

  clearhist = server.arg("clearhist");

  if (clearhist == "yes") {
    preferences.begin("storage", false);
    writedefaulttexthistory();
    preferences.end();
    feedbacktext = hist[0];
  }

  inputtext = feedbacktext;
  processtext();
  firstaccess = 1;

  stdcolor = server.arg("stdcolor");
  textcolor = server.arg("color");
  sliderspeed = server.arg("myrange");
  brness = server.arg("brightness");
  textfading = server.arg("textfading");
  ccycle = server.arg("colcycle");

  slider = map((sliderspeed.toInt()), 70, 170, 170, 70);

  scrollspeed = slider;

  brightness = brness.toInt();

  textcolor.replace("#", "0x");

  if ((textcolor != "0x000000") && (stdcolor == "")) {
    colorval = (strtol(textcolor.c_str(), NULL, 16));
  }

  if (stdcolor != "") {
    colorval = (strtol(stdcolor.c_str(), NULL, 16));
  }

  if (ccycle == "on") {
    rgbcol[0] = (colorval / 65536);
    rgbcol[1] = (colorval - (rgbcol[0] * 65536)) / 256;
    rgbcol[2] = ( colorval - (rgbcol[0] * 65536) - (rgbcol[1] * 256) );
  }

  FastLED.setBrightness( brightness );

  redirect = redirectone + (WiFi.localIP().toString()) + redirecttwo;

  server.send(200, "text/html", redirect);

  //above command serves a webpage that redirects to the main webpage and then
  //the esp32 webserver automatically runs handleRoot() and that
  //function first adds the new settings the user posted into the HTML
  //(managed through this handlepostform function) and then serves
  //the new main webpage

}


void savetexttoflash() { //saves new text and shifts old text history one slot down

  preferences.begin("storage", false);
  preferences.putString("hist0", feedbacktext);
  for (ct = 1; ct < 30; ct++) {
    tname = "hist" + String(ct);
    tname.toCharArray(cname, 7);
    preferences.putString(cname, hist[(ct - 1)]);
  }
  preferences.end();

}


void savevarsinpage() { //build up complete webpage

  //retrieve texthistory array from flash storage (preferences library)

  retrievetexthistoryfromflash();

  //build javascript array from C++ texthistory array

  jsarraybuildstring = "";

  String quote = "\"";
  String comma = ",";
  String arrayend = "];\n\n";

  for (ct = 0; ct < 30; ct++) {
    jsarraybuildstring = jsarraybuildstring + quote + hist[ct] + quote;
    if (ct < 29) {
      jsarraybuildstring = jsarraybuildstring + comma;
    }
  }
  jsarraybuildstring = jsarraybuildstring + arrayend;


  //////adding jsarraybuildstring and adding start of building javascript returnedvariables function /////////////

  message = messageone + jsarraybuildstring + codestart + "\n\n";

  //////adding a getElementById javascript command for each scrolltext setting variable to the function/////////

  message = message + codepartone + "txt" + codeparttwo + hist[0] + codepartthree + "\n\n";

  if (stdcolor == "0xFF0000") {
    message = message + "selectred();\n\n";
  }

  if (stdcolor == "0x00FF00") {
    message = message + "selectgreen();\n\n";
  }

  if (stdcolor == "0x0000FF") {
    message = message + "selectblue();\n\n";
  }

  if ((textcolor != "0x000000") && (textcolor != "")) {
    textcolorholder = textcolor;
    textcolorholder.replace("0x", "#");
    message = message + codepartone + "colorwheel" + codeparttwo + textcolorholder + codepartthree + "\n\n";
  }

  message = message + codepartone + "speed" + codeparttwo + sliderspeed + codepartthree + "\n\n";

  message = message + codepartone + "brlevel" + codeparttwo + brness + codepartthree + "\n\n";

  if (textfading == "on") {
    fadestate = "true";
  } else {
    fadestate = "false";
  }

  message = message + codepartone + "textfading" + codechecked1 + fadestate + codechecked2 + "\n\n";

  if (ccycle == "on") {
    cyclestate = "true";
  } else {
    cyclestate = "false";
  }

  message = message + codepartone + "ccycle" + codechecked1 + cyclestate + codechecked2 + "\n\n";

  ///////closing javascript returnedvariables function/////////

  message = message + "\n" + codepartfour + messagetwo;

  //now message contains the whole webpage

}


void retrievetexthistoryfromflash() {

  preferences.begin("storage", false);
  for (ct = 0; ct < 30; ct++) {
    tname = "hist" + String(ct);
    tname.toCharArray(cname, 7);
    histreturn[ct] = preferences.getString(cname);
    hist[ct] = histreturn[ct];
    histreturn[ct] = "";
  }
  preferences.end();

}

void writedefaulttexthistory() {

  for (ct = 0; ct < 30; ct++) {

    hist[ct] = "empty slot";

    tname = "hist" + String(ct);

    tname.toCharArray(cname, 7);

    preferences.putString(cname, hist[ct]);

  }

}


void colorcycle() {

  colorval = ((rgbcol[0] * 65536) + (rgbcol[1] * 256) + rgbcol[2]);

  if ((rgbcol[colshiftone] + coloradd) > 255) {
    colshiftone++;

    if (colshiftone > 2) {
      colshiftone = 0;
    }

    rgbcol[colshiftone] = rgbcol[colshiftone] + coloradd;
  }
  else {
    rgbcol[colshiftone] = rgbcol[colshiftone] + coloradd;
  }


  if ((rgbcol[colshifttwo] - coloradd) < 0) {
    colshifttwo++;

    if (colshifttwo > 2) {
      colshifttwo = 0;
    }

    rgbcol[colshifttwo] = rgbcol[colshifttwo] - coloradd;
  }
  else {
    rgbcol[colshifttwo] = rgbcol[colshifttwo] - coloradd;
  }


  if (colshiftone == colshifttwo) {
    colshiftone++;
    if (colshiftone > 2) {
      colshiftone = 0;
    }
  }

}


void textfader() {

  brightness = brightness - fading;

  if (brightness < 2) {
    fading = -1;
  }

  if (brightness > 15) {
    fading = 1;
  }

  FastLED.setBrightness( brightness );

}
