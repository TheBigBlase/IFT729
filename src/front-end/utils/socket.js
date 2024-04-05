// cors ? 
const address = 'ws://localhost:8888';
let socket = new WebSocket(address);

// leaving this as example of how to get response
// TODO get events
//     win / lose
//     new page
//     new guesses
//     other's guesses

// TODO
function handle_message(msg) {
	let res = msg.split(":");
	switch (res[0]) {
		case "PX":
			break
		case "MSSG":
			break
		case "WIN":
			break
		case "LOOSE":
			break
		case "ROOMS":
			// TODO do that in batch
			let ul = document.getElementById("roomList");
			let li = document.createElement("ul")
			li.appendChild(document.createTextNode(res[1]));
			ul.appendChild(li);
			break
		default:
			break;
	}
}

socket.onmessage = (msg) => {
	console.log(msg);
}

socket.onopen = () =>  {
	console.log("Socket connected")
}
