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
		case "ROOM":
			// TODO do that in batch
			sessionStorage.setItem("id", res[1]);
			let ul = document.getElementById("roomList");
			let li = document.createElement("ul");
			let a  = document.createElement("a");
			a.setAttribute("href", "drawer");
			a.appendChild(document.createTextNode("Player " + res[1] + "'s room"));
			li.appendChild(a);
			ul.appendChild(li);
			break
		default:
			break;
	}
}

socket.onmessage = (msg) => {
	console.log("got res" + msg.data);
	handle_message(msg.data);
}

socket.onopen = () =>  {
	console.log("Socket connected")
}
