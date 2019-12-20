/////////////////////////////////////////////////////////////////
////////////////javascript & HTML by Maico Ditzel////////////////
/////////////////////////////////////////////////////////////////

String messageone = R"foo(

<!doctype html><html><head><script type="text/javascript">

var texthistory = [)foo";

String messagetwo = R"foo(

var arrayLength = texthistory.length;
var i=0;
var istring;
var times=0;

function clearhistory() {
times++;
if (times == 1) {
document.getElementById("clr").style="color: #FF0000;font-size: 14px; vertical-align: middle;";
document.getElementById("clr").value=" PLEASE CONFIRM ";
}
if (times == 2) {
document.getElementById("clearh").value="yes";
document.getElementById("form1").submit();
}
}

function increase() {
i++;
if (i > (arrayLength-1)) {
i=0;
}

if (i<9){
istring="0"+(i+1); <!--making the slotnumbers displayed one higher for human readability -->
}
else{
istring=(i+1); <!--making the slotnumbers displayed one higher for human readability -->
}

document.getElementById("txt").value=texthistory[i];
document.getElementById("posdisp").value=istring;
}

function decrease() {
i--;
if (i < 0) {
i=arrayLength-1;
}

if (i<9){
istring="0"+(i+1); <!--making the slotnumbers displayed one higher for human readability -->
}
else{
istring=(i+1); <!--making the slotnumbers displayed one higher for human readability -->
}

document.getElementById("txt").value=texthistory[i];
document.getElementById("posdisp").value=istring;
}


function cleartextfield(){
document.getElementById("txt").value="";
}

function selectred() { 
document.getElementById("stdcolor").value="0xFF0000";
document.getElementById("redbutton").value="RED";
document.getElementById("redbutton").style.color = "#000000";
document.getElementById("greenbutton").value="G";
document.getElementById("greenbutton").style.color = "#FFFFFF";
document.getElementById("bluebutton").value="B";
document.getElementById("bluebutton").style.color = "#FFFFFF";
document.getElementById("colorwheel").value="#000000";
clearccyclecheckmark();
}

function selectgreen() { 
document.getElementById("stdcolor").value="0x00FF00";
document.getElementById("redbutton").value="R";
document.getElementById("redbutton").style.color = "#FFFFFF";
document.getElementById("greenbutton").value="GREEN";
document.getElementById("greenbutton").style.color = "#000000";
document.getElementById("bluebutton").value="B";
document.getElementById("bluebutton").style.color = "#FFFFFF";
document.getElementById("colorwheel").value="#000000";
clearccyclecheckmark();
}

function selectblue() { 
document.getElementById("stdcolor").value="0x0000FF";
document.getElementById("redbutton").value="R";
document.getElementById("redbutton").style.color = "#FFFFFF";
document.getElementById("greenbutton").value="G";
document.getElementById("greenbutton").style.color = "#FFFFFF";
document.getElementById("bluebutton").value="BLUE";
document.getElementById("bluebutton").style.color = "#000000";
document.getElementById("colorwheel").value="#000000";
clearccyclecheckmark();
}

function clearstdcolorbuttons() {
document.getElementById("stdcolor").value="";
document.getElementById("redbutton").value="R";
document.getElementById("redbutton").style.color = "#FFFFFF";
document.getElementById("greenbutton").value="G";
document.getElementById("greenbutton").style.color = "#FFFFFF";
document.getElementById("bluebutton").value="B";
document.getElementById("bluebutton").style.color = "#FFFFFF";
clearccyclecheckmark();
}

function clearstdcolorbuttons_and_colorwheel(){
document.getElementById("stdcolor").value="";
document.getElementById("redbutton").value="R";
document.getElementById("redbutton").style.color = "#FFFFFF";
document.getElementById("greenbutton").value="G";
document.getElementById("greenbutton").style.color = "#FFFFFF";
document.getElementById("bluebutton").value="B";
document.getElementById("bluebutton").style.color = "#FFFFFF";
document.getElementById("colorwheel").value="#000000";
}

function clearbrightness() {
   document.getElementById("brlevel").value = 9;
}

function clearfadecheckmark(){
document.getElementById("textfading").checked = false;
}

function clearccyclecheckmark(){
document.getElementById("ccycle").checked = false;
}

</script>

<meta http-equiv="Cache-Control" content="no-cache, no-store, must-revalidate" />
<meta http-equiv="Pragma" content="no-cache" />
<meta http-equiv="Expires" content="0" />

<meta name="viewport" content="user-scalable=no, initial-scale=1.0, maximum-scale=1.0, width=device-width">

<style>

.mybutton {
  box-shadow: 0px 10px 14px -7px #276873;
  background:linear-gradient(to bottom, #599bb3 5%, #408c99 100%);
  background-color:#599bb3;
  border-radius:42px;
  border:4px solid #29668f;
  display:inline-block;
  cursor:pointer;
  color:#ffffff;
  font-family:Arial;
  font-size:20px;
  font-weight:bold;
  padding:5px 20px;
  text-decoration:none;
  text-shadow:0px 1px 0px #3d768a;
}
.mybutton:hover {
  background:linear-gradient(to bottom, #408c99 5%, #599bb3 100%);
  background-color:#408c99;
}
.mybutton:active {
  position:relative;
  top:1px;
}
    
</style>

</head>

<body onload="returnedvariables()">


<FORM METHOD="POST" autocomplete="off" name="form1" id="form1" action="/postForm">

<center>

<input type="button" style="font-size: 30px; vertical-align: middle;padding: 5;border: none;background: none;color: #FFFFFF;background-color: #0000FF;" id="posdisp" value="01">

&nbsp;&nbsp;

<input type="button" onclick="decrease()" style="font-size: 30px;width: 75px;vertical-align: middle;" value="<">
&nbsp;
<input type="button" onclick="increase()" style="font-size: 30px;width: 75px;vertical-align: middle;" value=">">


<input type="hidden" name="clearhist" id="clearh" value="">

&nbsp;&nbsp;


<input type="submit" value="SAVE" class="mybutton">

<BR><BR>

<input type="text" autocomplete="off" onclick="cleartextfield()" style="text-align: center;vertical-align: middle;height:40px;width:290px;font-size:22px;" name="mytext" id="txt" value="">

<BR><BR>

<span style="background-color: #FFFF00;">Choose your scrolltext colour:
</span>

<BR><BR>

<input type="hidden" name="stdcolor" id="stdcolor" value="">

<input type="button" onclick="selectred()" style="color:#FFFFFF;font-size:20px;height:50px;width:85px;border:none;background-color: #FF0000;" id="redbutton" value="R">
<input type="button" onclick="selectgreen()" style="color:#FFFFFF;font-size:20px;height:50px;width:85px;border:none;background-color: #00FF00;" id="greenbutton" value="G">
<input type="button" onclick="selectblue()" style="color:#FFFFFF;font-size:20px;height:50px;width:85px;border:none;background-color: #0000FF;" id="bluebutton" value="B">

<BR><BR>

<span>Custom color :&nbsp;&nbsp;</span>

<input type="color" onclick="clearstdcolorbuttons()" id="colorwheel" style="vertical-align: middle;height:40px;width:60px;border:none;" name="color" value="">

<BR><BR>

<span style="background-color: #FFFF00;">Scrolling Speed:
</span>

<BR>

<input type="range" min="70" max="170" value="120" step="25" style="margin-left: 10px;width: 300px;background-color: whitesmoke;" name="myrange" id="speed" list="steplist">

<datalist id="steplist">
    <option>70</option>
    <option>95</option>
    <option>120</option>
    <option>145</option>
    <option>170</option>
</datalist>

<BR>

<span style="background-color: #FFFF00;">Brightness Level:
</span>

<BR>

<input type="range" onclick="clearfadecheckmark()" min="3" max="15" value="9" step="3" style="margin-left: 10px;width: 300px;background-color: whitesmoke;" name="brightness" id="brlevel" list="steplist2">

<datalist id="steplist2">
    <option>3</option>
    <option>6</option>
    <option>9</option>
    <option>12</option>
    <option>15</option>
</datalist>

<BR><BR>

<span style="font-size: 16px;">fade text&nbsp; ?&nbsp;</span>

<input type="checkbox" onclick="clearbrightness()" name="textfading" id="textfading" style="transform: scale(2);">

<span style="font-size: 16px;">&nbsp;color-cycle text&nbsp; ?&nbsp;</span>

<input type="checkbox" onclick="clearstdcolorbuttons_and_colorwheel()" name="colcycle" id="ccycle" style="color:#FF0000;transform: scale(2);">

<BR><BR>

<input type="button" onclick="clearhistory()" style="font-size: 14px; vertical-align: middle;" id="clr" value="CLEAR TEXTHISTORY">

<BR><BR>

<span style="font-size: 18px;background-color: #1A4176;color: #FFFFFF;">Maico Ditzel (2019)</span>

</center>

<BR><BR>

</form>
</body>
</html>

)foo";
