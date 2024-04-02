// cors ? 
const address = 'ws://localhost:8888';
let socket = new WebSocket(address);

// leaving this as example of how to get response
// TODO get events
//     win / lose
//     new page
//     new guesses
//     other's guesses
socket.onmessage = (msg) => {
	console.log(msg);
}


