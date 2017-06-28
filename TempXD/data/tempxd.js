// graph Data points 
var dataPoints = [];	// Liquor
var dataPoints1 = [];	// Mash		
var dataPoints2 = [];	// Boil


// get Data times
var lastTempUpdate = 0;
	
	
	
	
/*    ---------------   */





function startStopRecording() {
	$( '#recordingTrue' ).hide();
	$( '#recordingFalse' ).hide();
	$.get("startStopRecord.json?" + Math.random(), function(data) {
			console.log(data);
	});
}

var lastRecordedTempUpdate = 1;
var utime = 1;
function updateTime() {
	
	if ( lastTempUpdate == lastRecordedTempUpdate ) {
		utime = utime + 1;
	} else {
		utime = 1;
		console.log("updated");
	}
		
	lastRecordedTempUpdate = lastTempUpdate;
	
	$( '#liquorTime' ).text( utime );
	$( '#mashTime' ).text( utime );
	$( '#boilTime' ).text( utime );
}

function getData() {
	$.get("getData.json?" + Math.random(), function(data) {
			$( '#liquorValue' ).text( data.tempLiquor );
			$( '#mashValue' ).text( data.tempMash );
			$( '#boilValue' ).text( data.tempBoil );	
			if ( data.recording == true) {
				$( '#recordingFalse' ).hide();
				$( '#recordingTrue' ).show();			
			} else {
				$( '#recordingTrue' ).hide();
				$( '#recordingFalse' ).show();
			}
			lastTempUpdate = data.lastTempUpdate;
	});
}	
	
	
/*    ---------------   */

function getDataPointsFromCSV(csv) {
	var dataPoints = csvLines = points = [];
	var yearmontday = [];
	var hourminsec = [];
	csvLines = csv.split(/[\r?\n|\r|\n]+/);         
								
	for (var i = 0; i < csvLines.length; i++)
		if (csvLines[i].length > 0) {
			points = csvLines[i].split(",");
			
			yearmontday = points[0].split("-");
			hourminsec = points[1].split(":");
	
			date = new Date(yearmontday[0], yearmontday[1], yearmontday[2], hourminsec[0], hourminsec[1], hourminsec[2]);
	
			dataPoints.push({ 
				x: date, 
				y: parseFloat(points[2]) 		
			});
			
			dataPoints1.push({ 
				x: date, 
				y: parseFloat(points[3]) 		
			});
			
			dataPoints2.push({ 
				x: date, 
				y: parseFloat(points[4]) 		
			});
		}
	return dataPoints;
}

function graphCsv(filePath) {
	$.get(filePath, function(data) {
		var chart = new CanvasJS.Chart("chartContainer", {
			axisX:{
				title: "Time"
			},
			axisY: {
				title: "Temperature in Celsius",
				interlacedColor: "#FEFDDF"
			},
			data: [{
				 type: "line",
				 color: "#5cb85c",
				 showInLegend: true,
				 legendText: "Liquor",
				 dataPoints: getDataPointsFromCSV(data)
			  },{
				 type: "line",
				 color: "#f0ad4e",
				 showInLegend: true,
				 legendText: "Mash",
				 dataPoints: dataPoints1
			  },{
				 type: "line",
				 color: "#d9534f",
				 showInLegend: true,
				 legendText: "Boil",
				 dataPoints: dataPoints2
			  }]
		});
	  chart.render();
	});
}	
	
	
	