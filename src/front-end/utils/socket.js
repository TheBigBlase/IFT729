// cors ? 


const address = 'ws://localhost:8888';
let socket = new WebSocket(address);
// leaving this as example of how to get response
// TODO get events
//     win / lose
//     new guesses
//     other's guesses

// TODO

function go_to_draw(id) {
	sessionStorage.setItem("game_id", id);
}

function handle_message(msg, id = 0) {
	let res = msg.split(":");
	switch (res[0]) {
		case "PX":
			console.log("PIXEL x: " + res[1] + " y: "+ res[2]);
			break;
		case "MSSG":
			break;
		case "WIN":
			break;
		case "LOOSE":
			break;
		case "ERR":
			break;
		case "ROOM":
			// TODO do that in batch
			sessionStorage.setItem("id", res[1]);
			res = res.slice(1, undefined);

			let ul = document.getElementById("roomList");
			while (ul.firstChild) {
				myNode.removeChild(ul.lastChild);
			}
			for (let elt of res) {
				ul = document.getElementById("roomList");
				let li = document.createElement("li");
				let a = document.createElement("a");
				a.setAttribute("href", "drawer");
				a.setAttribute("onClick", "go_to_draw(" + elt + ")");
				a.appendChild(document.createTextNode("Player " + elt + "'s room"));
				li.appendChild(a);
				ul.appendChild(li);
			};
			break;
		case "CONN":
			let id = sessionStorage.getItem("player_id");
			if (id != undefined) {
				socket.send("RECONN:" + id + ":\0");
			}
			break;
		default:
			break;
	}
}


socket.onmessage = (msg) => {
	console.log("got res" + msg.data);
	handle_message(msg.data);
}


socket.onclose = () => {
}
