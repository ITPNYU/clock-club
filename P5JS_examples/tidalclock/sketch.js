/*
Draws a clock. Outside radius arcs with seconds
Circle goes:
3*PI/2 at the top
|
PI on the left    - o -       0 on the right
|
PI/2 at the bottom

Program works by rotating the drawing surface proportional to the angle
of each hand, then drawing the line for the hand.

created 22 Aug 2012
re-written for P5.js 1 May 2016
by Tom Igoe
*/

// parameters of the clock:
var clockRadius = 200;
var hourHand = 60;
var minuteHand = 90;
var secondHand = minuteHand;
var handStart = -10;
var tidePosition = 0;
var nextTide = 0;
var latestTides;
var apiKey = '5017d720-2082-482e-8c85-8644527ee0dc';
function setup() {
  // set the general parameters for drawing:
  createCanvas(windowWidth, windowHeight);
  frameRate(1);
  smooth();
  strokeWeight(2);
  strokeCap(ROUND);
  // Turn on location watcher:
  if ("geolocation" in navigator) {
    var watcher = navigator.geolocation.watchPosition(geoSuccess, geoError);
  }
}

function draw() {
  background(255); // white background
  translate(width / 2, height / 2); // move to the center of the window
  rotate(3 * PI / 2); // rotate drawing 270 degrees to get 0 at the top

  // draw second hand:
  drawHand(second(), '#ccc', secondHand, 60);
  // draw minute hand:
  drawHand(minute(), '#ace', minuteHand, 60);
  // draw hour hand:
  drawHand(minute(), '#ace', hourHand, 12);

  // draw arc from 0 to current second:
  push();
  stroke("#5597cf"); // set arc color
  noFill(); // no fill for the arc
  arc(0, 0, clockRadius, clockRadius, 0, second() * PI / 30);
  pop();

  if (latestTides) {
    console.log('calculating');
    calculateTide(latestTides);
  }
}

// this function draws a hand, given the unit value, hand color, length,
// and how many divisions in a circle (e.g. minute: 60, hour: 12):
function drawHand(unitValue, handColor, handLength, divisions) {
  push();
  rotate(unitValue * 2 * PI / divisions); // rotate to draw hand
  stroke(handColor); // set line color
  line(handStart, 0, handLength + handStart, 0);
  pop();
}

function calculateTide(newTides) {
  var next = 0;
  var now = new Date();
  var tides = JSON.parse(newTides);
  let lowest = 1000;
  let highest = -1000;
  // for (var x in tides.extremes) {
  //   let foo = tides.extremes[x].height;
  //   if (foo < lowest) {
  //     lowest = foo;
  //   }
  //
  //   if (foo > highest) {
  //     highest = foo;
  //   }
  // }
  // console.log(tides);
  // console.log(now.toISOString());
  // console.log("lowest: " + lowest);
  // console.log("highest: " + highest);

  // for (var h in tides.heights) {
  //   let fie = new Date(tides.heights[h].date);
  //   if (fie <= now ) {
  //     console.log(tides.heights[h].date);
  //   }
  // }
  let height = 0;
  let readingNum =0;
  let nextReadingTime =  new Date(tides.extremes[readingNum].date);
  let timeSince = abs(now - nextReadingTime);
  let nextTideType = '';
  let lastTideTime = '';
  while (nextReadingTime <= now) {
    let tideDiff = nextReadingTime - lastTideTime;
    console.log('last time diff: ' + tideDiff);
    lastTideTime = nextReadingTime / tideDiff;
    timeSince = abs(now - nextReadingTime);
    readingNum++;
    nextReadingTime =  new Date(tides.extremes[readingNum].date);
    nextTideType = tides.extremes[readingNum].type;
  }

  console.log('now: ' + now);
  console.log('last tide: ' + lastTideTime);
  console.log('next Tide: ' + nextReadingTime);
  console.log('next type: ' + nextTideType);
  console.log("time since: " + timeSince);
//  console.log('percentage '  + percentage);
//  var currentHeight = (latestHeight * percentage) + nextHeight * (1-percentage);
//  console.log(currentHeight);

//  drawTide(currentHeight);
}

function drawTide(tidePosition) {
  push();
  rotate(3 * PI / 2); // rotate so that 0 is in the right place
  rotate(tidePosition * 2 * PI / 12); // rotate for the tidal height and direction
  noStroke();
  fill("#455ace"); // dot color
  ellipse(0, clockRadius / 2, 7, 7);
  pop();
}

function geoSuccess(position) {
  var latitude = position.coords.latitude;
  var longitude = position.coords.longitude;
  console.log(latitude + ", " + longitude);
  if (!latestTides) {
    console.log('getting tides');
    //getTides(latitude, longitude);

    latestTides = '{\"status\":200,\"callCount\":4,\"copyright\":\"Tidal data retrieved from www.worldtide.info. Copyright (c) 2014-2017 Brainware LLC. Licensed for use of individual spatial coordinates on behalf of\/by an end-user. Source data created by the Center for Operational Oceanographic Products and Services (CO-OPS) and is not subject to copyright protection. NO GUARANTEES ARE MADE ABOUT THE CORRECTNESS OF THIS DATA. You may not use it if anyone or anything could come to harm as a result of using it (e.g. for navigational purposes).\",\"requestLat\":40.43,\"requestLon\":-73.99,\"responseLat\":40.4671,\"responseLon\":-74.0099,\"atlas\":\"NOAA\",\"station\":\"Sandy Hook\",\"heights\":[{\"dt\":1524421800,\"date\":\"2018-04-22T18:30+0000\",\"height\":0.616},{\"dt\":1524423600,\"date\":\"2018-04-22T19:00+0000\",\"height\":0.554},{\"dt\":1524425400,\"date\":\"2018-04-22T19:30+0000\",\"height\":0.445},{\"dt\":1524427200,\"date\":\"2018-04-22T20:00+0000\",\"height\":0.301},{\"dt\":1524429000,\"date\":\"2018-04-22T20:30+0000\",\"height\":0.14},{\"dt\":1524430800,\"date\":\"2018-04-22T21:00+0000\",\"height\":-0.02},{\"dt\":1524432600,\"date\":\"2018-04-22T21:30+0000\",\"height\":-0.166},{\"dt\":1524434400,\"date\":\"2018-04-22T22:00+0000\",\"height\":-0.293},{\"dt\":1524436200,\"date\":\"2018-04-22T22:30+0000\",\"height\":-0.399},{\"dt\":1524438000,\"date\":\"2018-04-22T23:00+0000\",\"height\":-0.486},{\"dt\":1524439800,\"date\":\"2018-04-22T23:30+0000\",\"height\":-0.553},{\"dt\":1524441600,\"date\":\"2018-04-23T00:00+0000\",\"height\":-0.593},{\"dt\":1524443400,\"date\":\"2018-04-23T00:30+0000\",\"height\":-0.597},{\"dt\":1524445200,\"date\":\"2018-04-23T01:00+0000\",\"height\":-0.556},{\"dt\":1524447000,\"date\":\"2018-04-23T01:30+0000\",\"height\":-0.469},{\"dt\":1524448800,\"date\":\"2018-04-23T02:00+0000\",\"height\":-0.338},{\"dt\":1524450600,\"date\":\"2018-04-23T02:30+0000\",\"height\":-0.176},{\"dt\":1524452400,\"date\":\"2018-04-23T03:00+0000\",\"height\":0.002},{\"dt\":1524454200,\"date\":\"2018-04-23T03:30+0000\",\"height\":0.18},{\"dt\":1524456000,\"date\":\"2018-04-23T04:00+0000\",\"height\":0.347},{\"dt\":1524457800,\"date\":\"2018-04-23T04:30+0000\",\"height\":0.494},{\"dt\":1524459600,\"date\":\"2018-04-23T05:00+0000\",\"height\":0.618},{\"dt\":1524461400,\"date\":\"2018-04-23T05:30+0000\",\"height\":0.713},{\"dt\":1524463200,\"date\":\"2018-04-23T06:00+0000\",\"height\":0.772},{\"dt\":1524465000,\"date\":\"2018-04-23T06:30+0000\",\"height\":0.788},{\"dt\":1524466800,\"date\":\"2018-04-23T07:00+0000\",\"height\":0.755},{\"dt\":1524468600,\"date\":\"2018-04-23T07:30+0000\",\"height\":0.672},{\"dt\":1524470400,\"date\":\"2018-04-23T08:00+0000\",\"height\":0.548},{\"dt\":1524472200,\"date\":\"2018-04-23T08:30+0000\",\"height\":0.395},{\"dt\":1524474000,\"date\":\"2018-04-23T09:00+0000\",\"height\":0.23},{\"dt\":1524475800,\"date\":\"2018-04-23T09:30+0000\",\"height\":0.069},{\"dt\":1524477600,\"date\":\"2018-04-23T10:00+0000\",\"height\":-0.081},{\"dt\":1524479400,\"date\":\"2018-04-23T10:30+0000\",\"height\":-0.217},{\"dt\":1524481200,\"date\":\"2018-04-23T11:00+0000\",\"height\":-0.341},{\"dt\":1524483000,\"date\":\"2018-04-23T11:30+0000\",\"height\":-0.456},{\"dt\":1524484800,\"date\":\"2018-04-23T12:00+0000\",\"height\":-0.559},{\"dt\":1524486600,\"date\":\"2018-04-23T12:30+0000\",\"height\":-0.642},{\"dt\":1524488400,\"date\":\"2018-04-23T13:00+0000\",\"height\":-0.693},{\"dt\":1524490200,\"date\":\"2018-04-23T13:30+0000\",\"height\":-0.699},{\"dt\":1524492000,\"date\":\"2018-04-23T14:00+0000\",\"height\":-0.655},{\"dt\":1524493800,\"date\":\"2018-04-23T14:30+0000\",\"height\":-0.562},{\"dt\":1524495600,\"date\":\"2018-04-23T15:00+0000\",\"height\":-0.429},{\"dt\":1524497400,\"date\":\"2018-04-23T15:30+0000\",\"height\":-0.27},{\"dt\":1524499200,\"date\":\"2018-04-23T16:00+0000\",\"height\":-0.1},{\"dt\":1524501000,\"date\":\"2018-04-23T16:30+0000\",\"height\":0.072},{\"dt\":1524502800,\"date\":\"2018-04-23T17:00+0000\",\"height\":0.234},{\"dt\":1524504600,\"date\":\"2018-04-23T17:30+0000\",\"height\":0.382},{\"dt\":1524506400,\"date\":\"2018-04-23T18:00+0000\",\"height\":0.505},{\"dt\":1524508200,\"date\":\"2018-04-23T18:30+0000\",\"height\":0.595},{\"dt\":1524510000,\"date\":\"2018-04-23T19:00+0000\",\"height\":0.642},{\"dt\":1524511800,\"date\":\"2018-04-23T19:30+0000\",\"height\":0.637},{\"dt\":1524513600,\"date\":\"2018-04-23T20:00+0000\",\"height\":0.58},{\"dt\":1524515400,\"date\":\"2018-04-23T20:30+0000\",\"height\":0.478},{\"dt\":1524517200,\"date\":\"2018-04-23T21:00+0000\",\"height\":0.346},{\"dt\":1524519000,\"date\":\"2018-04-23T21:30+0000\",\"height\":0.199},{\"dt\":1524520800,\"date\":\"2018-04-23T22:00+0000\",\"height\":0.053},{\"dt\":1524522600,\"date\":\"2018-04-23T22:30+0000\",\"height\":-0.084},{\"dt\":1524524400,\"date\":\"2018-04-23T23:00+0000\",\"height\":-0.21},{\"dt\":1524526200,\"date\":\"2018-04-23T23:30+0000\",\"height\":-0.325},{\"dt\":1524528000,\"date\":\"2018-04-24T00:00+0000\",\"height\":-0.43},{\"dt\":1524529800,\"date\":\"2018-04-24T00:30+0000\",\"height\":-0.52},{\"dt\":1524531600,\"date\":\"2018-04-24T01:00+0000\",\"height\":-0.585},{\"dt\":1524533400,\"date\":\"2018-04-24T01:30+0000\",\"height\":-0.612},{\"dt\":1524535200,\"date\":\"2018-04-24T02:00+0000\",\"height\":-0.591},{\"dt\":1524537000,\"date\":\"2018-04-24T02:30+0000\",\"height\":-0.518},{\"dt\":1524538800,\"date\":\"2018-04-24T03:00+0000\",\"height\":-0.398},{\"dt\":1524540600,\"date\":\"2018-04-24T03:30+0000\",\"height\":-0.242},{\"dt\":1524542400,\"date\":\"2018-04-24T04:00+0000\",\"height\":-0.066},{\"dt\":1524544200,\"date\":\"2018-04-24T04:30+0000\",\"height\":0.112},{\"dt\":1524546000,\"date\":\"2018-04-24T05:00+0000\",\"height\":0.283},{\"dt\":1524547800,\"date\":\"2018-04-24T05:30+0000\",\"height\":0.438},{\"dt\":1524549600,\"date\":\"2018-04-24T06:00+0000\",\"height\":0.57},{\"dt\":1524551400,\"date\":\"2018-04-24T06:30+0000\",\"height\":0.673},{\"dt\":1524553200,\"date\":\"2018-04-24T07:00+0000\",\"height\":0.74},{\"dt\":1524555000,\"date\":\"2018-04-24T07:30+0000\",\"height\":0.762},{\"dt\":1524556800,\"date\":\"2018-04-24T08:00+0000\",\"height\":0.736},{\"dt\":1524558600,\"date\":\"2018-04-24T08:30+0000\",\"height\":0.662},{\"dt\":1524560400,\"date\":\"2018-04-24T09:00+0000\",\"height\":0.549},{\"dt\":1524562200,\"date\":\"2018-04-24T09:30+0000\",\"height\":0.41},{\"dt\":1524564000,\"date\":\"2018-04-24T10:00+0000\",\"height\":0.261},{\"dt\":1524565800,\"date\":\"2018-04-24T10:30+0000\",\"height\":0.112},{\"dt\":1524567600,\"date\":\"2018-04-24T11:00+0000\",\"height\":-0.031},{\"dt\":1524569400,\"date\":\"2018-04-24T11:30+0000\",\"height\":-0.17},{\"dt\":1524571200,\"date\":\"2018-04-24T12:00+0000\",\"height\":-0.306},{\"dt\":1524573000,\"date\":\"2018-04-24T12:30+0000\",\"height\":-0.439},{\"dt\":1524574800,\"date\":\"2018-04-24T13:00+0000\",\"height\":-0.563},{\"dt\":1524576600,\"date\":\"2018-04-24T13:30+0000\",\"height\":-0.665},{\"dt\":1524578400,\"date\":\"2018-04-24T14:00+0000\",\"height\":-0.73},{\"dt\":1524580200,\"date\":\"2018-04-24T14:30+0000\",\"height\":-0.743},{\"dt\":1524582000,\"date\":\"2018-04-24T15:00+0000\",\"height\":-0.699},{\"dt\":1524583800,\"date\":\"2018-04-24T15:30+0000\",\"height\":-0.601},{\"dt\":1524585600,\"date\":\"2018-04-24T16:00+0000\",\"height\":-0.461},{\"dt\":1524587400,\"date\":\"2018-04-24T16:30+0000\",\"height\":-0.292},{\"dt\":1524589200,\"date\":\"2018-04-24T17:00+0000\",\"height\":-0.111},{\"dt\":1524591000,\"date\":\"2018-04-24T17:30+0000\",\"height\":0.071},{\"dt\":1524592800,\"date\":\"2018-04-24T18:00+0000\",\"height\":0.246},{\"dt\":1524594600,\"date\":\"2018-04-24T18:30+0000\",\"height\":0.405}],\"extremes\":[{\"dt\":1524442684,\"date\":\"2018-04-23T00:18+0000\",\"height\":-0.6,\"type\":\"Low\"},{\"dt\":1524464695,\"date\":\"2018-04-23T06:24+0000\",\"height\":0.789,\"type\":\"High\"},{\"dt\":1524489548,\"date\":\"2018-04-23T13:19+0000\",\"height\":-0.703,\"type\":\"Low\"},{\"dt\":1524510730,\"date\":\"2018-04-23T19:12+0000\",\"height\":0.646,\"type\":\"High\"},{\"dt\":1524533566,\"date\":\"2018-04-24T01:32+0000\",\"height\":-0.612,\"type\":\"Low\"},{\"dt\":1524554939,\"date\":\"2018-04-24T07:28+0000\",\"height\":0.762,\"type\":\"High\"},{\"dt\":1524579724,\"date\":\"2018-04-24T14:22+0000\",\"height\":-0.745,\"type\":\"Low\"}]}';
    // console.log(latestTides);
    calculateTide(latestTides);
  }
}

function geoError(error) {
  print(error);
}

function success(data) {
  latestTides = data[0].extremes;
  console.log(data);
}

function getTides(lat, lon) {
  var url = 'https://www.worldtides.info/api?heights&extremes&lat=' + lat +
  '&lon=' + lon + '&key=' + apiKey;
  //  loadStrings(url, success);
}
