///////////////////////////////////////////////////////////////////
//////////////////Maico Ditzel December 2019///////////////////////
///////////////////////////////////////////////////////////////////
int pins[16] = {0, 7, 8, 15, 1, 6, 9, 14, 2, 5, 10, 13, 3, 4, 11, 12};
int fontplace[400];
int textlen;
int pointer;
int fulldisp;
int horzlines;
int vertpixels;
int horzshift;
int horzlinesedit;
int pin;
int pointernext;
String textcolor;
String feedbacktext;
String text;
int fade;
String redirect;
String sliderspeed;
String textfading;
String ccycle;
String stdcolor;
int slider;
String brness;
int fading=1;
int coloradd=10;
int colshiftone=1;
int colshifttwo=0;
int fadewason;
int ccyclewason;
String textcolorholder;
String fadestate;
String cyclestate;
String message;
int firstaccess;
int firstrun;
String hist[30];
String histreturn[30];
int ct;
String tname;
char cname[6];
String jsarraybuildstring;
String clearhist;
int rgbcol[3]; //colorcycle register
String inputtext;
int ipdisplaytimes;
int ipdisplayoff;
int fadepins[16] = {0,1,2,3,7,6,5,4,8,9,10,11,15,14,13,12};
int emptysquare[4] = {6,5,9,10};

String codestart      = R"foo(function returnedvariables() {)foo";
String codepartone    = R"foo(document.getElementById(')foo";
String codeparttwo    = R"foo(').value=')foo";
String codepartthree  = R"foo(';)foo";
String codepartfour   = R"foo(})foo";
String codechecked1   = R"foo(').checked = )foo";
String codechecked2   = R"foo(;)foo";
