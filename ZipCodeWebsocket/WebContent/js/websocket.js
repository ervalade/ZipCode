/**
 * functions for websocket
 */
// setup websocket with callbacks
var ws = new WebSocket('ws://127.0.0.1:8080/');
ws.onopen = function() {
	document.getElementById('title').innerHTML = 'Ready to convert Zip code';
	document.getElementById('title').style.color = 'green';
	document.getElementById('getBarCode').disabled = false;
};
ws.onclose = function() { };
ws.onmessage = function(event) {
	update(event.data);
};
function send() {
	ws.send(document.getElementById('zipCode').value);
};