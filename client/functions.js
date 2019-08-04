var time = 0;
var unitsString = "null";
var updateRate = 1000; // ie every 1000ms
var devIP = "null"; // who knows that this will be
var scaleUnits = 1.00;
var intervalID = setInterval(pollDevice, updateRate);

var socketConnected = 0; // used to show not connected on live val but zeros on graph

var websocketController = new websocketControl();


// put a check for a cookie here, and if present attempt to connect to the
// device


function pollDevice()
{
  //console.log("Time: " + time.toString());
  var d = new Date();
  document.getElementById("val").innerHTML = "<h3>" +
  d.getHours().toString() + ":" +
  d.getMinutes().toString() + ":" +
  d.getSeconds().toString() +
  unitsString + "</h3>";
  time = time + 1;
}

function setDevIP()
{
  devIP = document.getElementById('ipInput').value;
  if(devIP.length > 0)
  {
    console.log("setting dev IP: " + devIP);
    websocketController.setIP(devIP);
    websocketController.connect();
  }
  else
  {
    console.log("Please actually enter an ip....")
  }
}

function setUpdateRate()
{
  updateRate = parseInt(document.getElementById('rateInput').value);
  console.log("setting update rate: " +
  updateRate.toString() + "ms");
  clearInterval(intervalID);
  intervalID = setInterval(pollDevice, updateRate);
}

function setUnits()
{
  unitsString = document.getElementById('unitInput').value;
  console.log("setting units: " + unitsString);
}

function setScaling()
{
  scaleUnits = parseFloat(document.getElementById('scaleInput').value);
  console.log("setting scale: " + scaleUnits);
}

function webSocketOpened(event)
{
  socketConnected = 1;
  console.log("Websocket connected");
}
function webSocketClosed(event)
{
  socketConnected = 0;
  console.log("websocket disconnected");
}
