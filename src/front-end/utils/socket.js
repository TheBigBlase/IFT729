
const address = 'ws://localhost:8888';
let socket = new WebSocket(address);
document.addEventListener("DOMContentLoaded", function () {
	// leaving this as example of how to get response
	// TODO get events
	//     win / lose
	//     new guesses
	//     other's guesses

	let canvas, ctx, canvasData, width, height;

	if (window.location.href.endsWith("guesser")) {
		canvas = document.getElementById('canvas');
		ctx = canvas.getContext('2d');
		width = canvas.getBoundingClientRect().width;
		height = canvas.getBoundingClientRect().height;
		canvasData = ctx.getImageData(0, 0, width, height);
	}

	function store_game_id(id) {
		sessionStorage.setItem("game_id", id);
	}

	function handle_message(msg, id = 0) {
		let res = msg.split(":");
		switch (res[0]) {
			case "PX": {
				// TODO print on guesser side
				let x = res[1], y = res[2];
				// TODO separate files maybe?
				if (window.location.href.endsWith("guesser")) {
					ctx.fillRect(x, y, 10, 10);
					console.log("PIXEL x: " + x + " y: " + y);
				}
				break;
			}
			case "MSSG":
				// TODO
				break;
			case "WIN":
				// TODO
				break;
			case "LOOSE":
				// TODO
				break;
			case "ERR":
				break;
			case "ROOM": {
				// TODO do that in batch
				sessionStorage.setItem("id", res[1]);
				res = res.slice(1, undefined);
				let ul = document.getElementById("roomList");
				while (ul.firstChild) {
					ul.removeChild(ul.lastChild);
				}
				for (let elt of res) {
					ul = document.getElementById("roomList");
					let li = document.createElement("li");
					let a = document.createElement("a");
					a.setAttribute("href", "guesser");
					a.setAttribute("onClick", "store_game_id(" + elt + ")");
					a.appendChild(document.createTextNode("Room n°" + elt));
					li.appendChild(a);
					ul.appendChild(li);
				};
				break;
			}
			case "CONN":
				console.log("Connected as player " + res[1]);
				break;
			case "DRAWER": {
				// first is room to go
				let room = res[1];
				let li = document.createElement("li");
				let a = document.createElement("a");
				let ul = document.getElementById("roomList");
				a.setAttribute("href", "drawer");
				a.setAttribute("onClick", "store_game_id(" + room + ")");
				a.appendChild(document.createTextNode("Go to your lobby!"));
				li.appendChild(a);
				ul.appendChild(li);
				break;
			}
			default:
				break;
		}
	}

	socket.onmessage = (msg) => {
		console.log("got msg: " + msg.data);
		handle_message(msg.data);
	}

	socket.onclose = () => {
	}
});
